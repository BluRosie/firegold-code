#include "../include/global.h"
#include "../include/alloc.h"
#include "../include/constants/species.h"
#include "../include/event_data.h"
#include "../include/main.h"
#include "../include/overworld.h"
#include "../include/pokemon.h"
#include "../include/save.h"
#include "../include/sound.h"
#include "../include/sprite.h"
#include "../include/string_util.h"
#include "../include/task.h"
#include "../include/window.h"

#define SPAWN_BCC_SCREEN_ON_NULL
#define SPAWN_BCC_MON_ON_NULL

#define FLAG_BUG_CATCHING_CONTEST (0x2342)
#define IS_IN_BUG_CATCHING_CONTEST (FlagGet(FLAG_BUG_CATCHING_CONTEST))
#define gRemainingParkBalls (*(u8 *)0x0203FEC8)
#define SECONDS_IN_CONTEST (20 * 60) // 20 minute total time
#define gMonIconPalettes ((u16 *)(0x083d3740))

#define X_POS_MON_TO_SWAP 56
#define Y_POS_MON_TO_SWAP 92

struct BugCatchingContestSwapScreen
{
    //struct Sprite *monIconSprites[2];
    u8 spriteIds[2]; // index of gSprites
    u8 windowId;
    u8 cursorPos;
    u8 timer; // temporary
};

extern struct Pokemon *gBugContestMon;
extern struct BugCatchingContestSwapScreen *gBCCSwapScreen;

static const struct WindowTemplate sMonWindowTemplate = {0, X_POS_MON_TO_SWAP/8-2, Y_POS_MON_TO_SWAP/8-1, 4, 4, 0xF, 8};

u32 StoreCaughtBCCMon(void);
u32 FreeCaughtBCCMonAndDeposit(void);
void bcc_DeleteSpriteAfterASecond(u8 taskId);

// change start menu behavior:
// get rid of save, add script to quit out


// timer for bug catching contest


// functions to spawn the icons in their own textboxes
void SpawnIconsForBCC(void)
{
    // need to print a textbox to the screen and also print the mon icons to the screen such that they go through the box
    // animate the one that is selected

    // sanity check - if data is not initialized, do nothing.  maybe
    if (gBCCSwapScreen == NULL || gBugContestMon == NULL)
    {
#ifdef SPAWN_BCC_SCREEN_ON_NULL
        if (gBCCSwapScreen == NULL)
        {
            gBCCSwapScreen = AllocZeroed(sizeof(struct BugCatchingContestSwapScreen));
        }
#endif
#ifdef SPAWN_BCC_MON_ON_NULL
        if (gBugContestMon == NULL)
        {
            gBugContestMon = AllocZeroed(sizeof(struct Pokemon));
            CreateMon(gBugContestMon, SPECIES_SCYTHER, 20, 32, 0, 0, 0, 0);
        }
#else
        return;
#endif
    }

    // load icon pals
    LoadMonIconPalettes();

    // set regs that will let me print a textbox and print an icon over it?
    SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_OBJWIN_ON);
    SetGpuRegBits(REG_OFFSET_WINOUT, WINOUT_WINOBJ_OBJ);
    SetGpuRegBits(REG_OFFSET_WININ, WININ_WIN0_OBJ);

    // print icon of gBugContestMon -- first the actual icon
    u32 species = GetMonData(gBugContestMon, MON_DATA_SPECIES, NULL);
    u32 pid = GetMonData(gBugContestMon, MON_DATA_PERSONALITY, NULL);
    u32 spriteId;

    spriteId = CreateMonIcon(species, 0x0809718d, X_POS_MON_TO_SWAP, Y_POS_MON_TO_SWAP, 0, pid, 0);
    gSprites[spriteId].oam.priority = 0;
    gSprites[spriteId].invisible = 0;
    gSprites[spriteId].pos1.x = 0;
    gSprites[spriteId].pos1.y = 0;
    gSprites[spriteId].pos2.x = X_POS_MON_TO_SWAP;
    gSprites[spriteId].pos2.y = Y_POS_MON_TO_SWAP;

    gBCCSwapScreen->spriteIds[0] = spriteId;

    // then cut it out of the textbox
    spriteId = CreateMonIcon(species, 0x0809718d, X_POS_MON_TO_SWAP, Y_POS_MON_TO_SWAP, 0, pid, 0);
    gSprites[spriteId].oam.priority = 0;
    gSprites[spriteId].invisible = 0;
    gSprites[spriteId].pos1.x = 0;
    gSprites[spriteId].pos1.y = 0;
    gSprites[spriteId].pos2.x = X_POS_MON_TO_SWAP;
    gSprites[spriteId].pos2.y = Y_POS_MON_TO_SWAP;
    gSprites[spriteId].oam.objMode = ST_OAM_OBJ_WINDOW;

    gBCCSwapScreen->spriteIds[1] = spriteId;

    // now print window
    LoadStdWindowFrameGfx();
    gBCCSwapScreen->windowId = AddWindow(&sMonWindowTemplate);
    FillWindowPixelBuffer(gBCCSwapScreen->windowId, 0x11);
    PutWindowTilemap(gBCCSwapScreen->windowId);
    DrawStdWindowFrame(gBCCSwapScreen->windowId, 0);
    CopyWindowToVram(gBCCSwapScreen->windowId, COPYWIN_FULL);

    CreateTask(bcc_DeleteSpriteAfterASecond, 0);
}

void bcc_DeleteSprites(u8 taskId)
{
    DestroyMonIcon(&gSprites[gBCCSwapScreen->spriteIds[0]]);
    DestroyMonIcon(&gSprites[gBCCSwapScreen->spriteIds[1]]);

    // now also destroy window
    ClearStdWindowAndFrameToTransparent(gBCCSwapScreen->windowId, FALSE);
    CopyWindowToVram(gBCCSwapScreen->windowId, COPYWIN_FULL);
    RemoveWindow(gBCCSwapScreen->windowId);
}

void bcc_DeleteSpriteAfterASecond(u8 taskId)
{
    if (gBCCSwapScreen->timer++ == 240)
    {
        gBCCSwapScreen->timer = 0;
        bcc_DeleteSprites(taskId);
        Free(gBCCSwapScreen);
        Free(gBugContestMon);
        gBCCSwapScreen = NULL;
        gBugContestMon = NULL;
        DestroyTask(taskId);
    }
}

// score caught mon in gBugContestMon
// max score is 400:
// level as percentage of max that can be found
// iv's relative to max as percentage (186)
// hp relative to max as percentage
// rarity factor -- caterpie metapod weedle kakuna wurmple silcoon cascoon kricketot are all at 60, scyther pinsir are at 100, 80 everything else
// scyther/pinsir with perfect iv's and no damage dealt is all that can get 400

u16 CommonBCCMons[] =
{
    SPECIES_CATERPIE,
    SPECIES_METAPOD,
    SPECIES_WEEDLE,
    SPECIES_KAKUNA,
    //SPECIES_WURMPLE,
    //SPECIES_SILCOON,
    //SPECIES_CASCOON,
    //SPECIES_KRICKETOT
};

u16 RareBCCMons[] =
{
    SPECIES_SCYTHER,
    SPECIES_PINSIR
};

u32 ScoreCaughtBCCMon(void)
{
    u32 species = GetMonData(gBugContestMon, MON_DATA_SPECIES, NULL);
    u32 totalScore = 0;
    u32 level = GetMonData(gBugContestMon, MON_DATA_LEVEL, NULL);
    u32 hp = GetMonData(gBugContestMon, MON_DATA_HP, NULL);
    u32 maxHp = GetMonData(gBugContestMon, MON_DATA_MAX_HP, NULL);
    int i = 0;
    u32 totalIvs = 0;
    u32 maxLevel = 0;

    // rarity factor
    for (i = 0; i < ARRAY_COUNT(CommonBCCMons); i++)
    {
        if (species == CommonBCCMons[i])
        {
            totalScore = 60;
            break;
        }
    }
    if (totalScore == 0)
    {
        for (i = 0; i < ARRAY_COUNT(RareBCCMons); i++)
        {
            if (species == RareBCCMons[i])
            {
                totalScore = 100;
                break;
            }
        }
    }
    if (totalScore == 0)
        totalScore = 80;

    // iv's relative to max
    for (i = MON_DATA_HP_IV; i < MON_DATA_SPDEF_IV; i++)
    {
        totalIvs += GetMonData(gBugContestMon, i, NULL);
    }
    totalScore += totalIvs * 100 / (31*6);

    // hp relative to max
    totalScore += hp * 100 / maxHp;

    // level compared to max
    // this one is a little tougher.  i might just hardcode it.
    switch (species)
    {
    case SPECIES_CATERPIE:
    case SPECIES_METAPOD:
    case SPECIES_WEEDLE:
    case SPECIES_KAKUNA:
        maxLevel = 18;
        break;
    case SPECIES_PARAS:
        maxLevel = 17;
        break;
    case SPECIES_VENONAT:
        maxLevel = 16;
        break;
    case SPECIES_BUTTERFREE:
    case SPECIES_BEEDRILL:
        maxLevel = 15;
        break;
    case SPECIES_SCYTHER:
    case SPECIES_PINSIR:
        maxLevel = 14;
        break;
    }
    totalScore += level * 100 / maxLevel;

    return totalScore;
}


// functions to handle storing bug catching contest mon direct from party as well as giving the player the bug catching contest mon
u32 StoreCaughtBCCMon(void)
{
    u32 ret = FALSE;
    if (gPlayerPartyCount > 1)
    {
        if (gBugContestMon == NULL)
            gBugContestMon = AllocZeroed(sizeof(struct Pokemon));
        memcpy(gBugContestMon, &gPlayerParty[1], sizeof(struct Pokemon));
        memset(&gPlayerParty[1], 0, sizeof(struct Pokemon));
        ret = TRUE;
    }
    return ret;
}

u32 FreeCaughtBCCMonAndDeposit(void)
{
    u32 ret = GiveMonToPlayer(gBugContestMon);
    if (ret != 2) // can't give to player
    {
        Free(gBugContestMon);
        gBugContestMon = NULL;
    }
    return ret;
}

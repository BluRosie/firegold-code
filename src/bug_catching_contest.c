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
#define SECONDS_IN_CONTEST 5 // (20 * 60) // 20 minute total time
#define FRAMES_IN_CONTEST (SECONDS_IN_CONTEST * 60) // 60 frames per second
#define gMonIconPalettes ((u16 *)(0x083d3740))

#define X_POS_MON_TO_SWAP 56
#define Y_POS_MON_TO_SWAP 36

#define X_POS_MON_SWAPPING (56)
#define Y_POS_MON_SWAPPING (84)

struct BugCatchingContestGlobalStruct
{
    //struct Sprite *monIconSprites[2];
    //struct Pokemon caughtMon;
    u8 caughtMon[0x64]; // my shit don't line up exact!  oh well
    u32 timer:27;
    u32 cursorPos:1;
    u32 activated:1;
    u32 initStep:3;
    u8 spriteIds[4]; // index of gSprites
    u8 windowIds[2];
    u8 palReloadTimer;
};

extern struct BugCatchingContestGlobalStruct gBccGlobalStruct;

extern const u8 *bcc_ContestIsOver[]; // script
extern const u8 gText_LevelOfMon[]; // string

static const struct WindowTemplate sMonWindowTemplate = {0, X_POS_MON_TO_SWAP/8-2, Y_POS_MON_TO_SWAP/8-1, 12, 4, 0xF, 8};
static const struct WindowTemplate sCurrentMonWindowTemplate = {0, X_POS_MON_SWAPPING/8-2, Y_POS_MON_SWAPPING/8-1, 12, 4, 0xF, 8+48};

u32 bcc_StoreCaughtMon(void);
void bcc_DeleteBCCMon(void);
void bcc_DeleteSprites(void);

// change start menu behavior:
// get rid of save, add script to quit out
// i might handle this instead in start_clock.c

// timer for bug catching contest
// every frame, increment a timer.  once it hits the limit, the bcc has ended

void bcc_Init(void)
{
    //if (gBccGlobalStruct == NULL)
    //    gBccGlobalStruct = AllocZeroed(sizeof(struct BugCatchingContestGlobalStruct));
    if (gBccGlobalStruct.activated == 0)
        memset(&gBccGlobalStruct.caughtMon, 0, sizeof(struct BugCatchingContestGlobalStruct));
    gBccGlobalStruct.activated = 1;

    //if (gBccGlobalStruct.caughtMon == NULL)
    //    gBccGlobalStruct.caughtMon = AllocZeroed(sizeof(gBccGlobalStruct.caughtMon));
    if (((u32 *)(&gBccGlobalStruct.caughtMon))[0] == 0)
        memset(&gBccGlobalStruct.caughtMon, 0, sizeof(gBccGlobalStruct.caughtMon));
}

void bcc_TimerCallback(u8 taskId)
{
    if (gBccGlobalStruct.activated)
    {
        if (gBccGlobalStruct.timer >= FRAMES_IN_CONTEST)
        {
            // trigger a script to run as soon as possible, destroy the task
            if (!ScriptContext2_IsEnabled()) // ScriptContext2_IsEnabled is now actually ArePlayerFieldControlsLocked
            {
                DestroyTask(taskId);
                ScriptContext1_SetupScript(bcc_ContestIsOver);
            }
        }
        else
        {
            gBccGlobalStruct.timer++;
        }
    }
}

// timer setting also allocates the gBccGlobalStruct
void bcc_SetTimer(void)
{
    // create a task that just counts down
    CreateTask(bcc_TimerCallback, 0);
}

enum SPAWN_ICONS_STEP
{
    BCC_SWAP_MENU_SPAWN_WINDOW_1,
    BCC_SWAP_MENU_SPAWN_WINDOW_2,
    BCC_SWAP_MENU_SPAWN_ICONS,
    BCC_SWAP_MENU_KEEP_ICON_PALS_LOADED,
    BCC_SWAP_MENU_DESTROY_TASK,
};

// functions to spawn the icons in their own textboxes
void bcc_SpawnIconsAndWindowsCallback(u8 taskId)
{
    // need to print a textbox to the screen and also print the mon icons to the screen such that they go through the box
    // animate the one that is selected

    // sanity check - if data is not initialized, do nothing.  maybe
    if (gBccGlobalStruct.activated == 0)
    {
        return;
    }
    u32 species = GetMonData(&gBccGlobalStruct.caughtMon, MON_DATA_SPECIES, NULL);
    u32 pid = GetMonData(&gBccGlobalStruct.caughtMon, MON_DATA_PERSONALITY, NULL);
    u32 spriteId, windowId, level, hp, maxHp;
    u8 *ptr;

    switch (gBccGlobalStruct.initStep)
    {
    case BCC_SWAP_MENU_SPAWN_WINDOW_1:
        // now print window
        LoadStdWindowFrameGfx();
        windowId = AddWindow(&sCurrentMonWindowTemplate);
        //FillWindowPixelBuffer(windowId, 0x11);
        DrawStdWindowFrame(windowId, 0);

        level = GetMonData(&gBccGlobalStruct.caughtMon, MON_DATA_LEVEL, NULL);
        hp = GetMonData(&gBccGlobalStruct.caughtMon, MON_DATA_HP, NULL);
        maxHp = GetMonData(&gBccGlobalStruct.caughtMon, MON_DATA_MAX_HP, NULL);
        ptr = StringExpandPlaceholders(gStringVar1, gText_LevelOfMon);
        ConvertIntToDecimalStringN(ptr, level, STR_CONV_MODE_LEFT_ALIGN, 3);
        AddTextPrinterParameterized(windowId, 0, gStringVar1, 32, 1, 0xFF, 0);
        ptr = ConvertIntToDecimalStringN(gStringVar3, hp, STR_CONV_MODE_LEFT_ALIGN, 3);
        *ptr++ = 0xBA; // /
        ptr = ConvertIntToDecimalStringN(ptr, maxHp, STR_CONV_MODE_LEFT_ALIGN, 3);
        *ptr++ = 0x00; // [space]
        *ptr++ = 0xC2; // H
        *ptr++ = 0xCA; // P
        *ptr++ = 0xFF; // end
        AddTextPrinterParameterized(windowId, 0, gStringVar3, 32, 15, 0xFF, 0);
        PutWindowTilemap(windowId);
        CopyWindowToVram(windowId, COPYWIN_FULL);

        gBccGlobalStruct.windowIds[0] = windowId;
        gBccGlobalStruct.initStep++;
        break;
    case BCC_SWAP_MENU_SPAWN_WINDOW_2:
        windowId = AddWindow(&sMonWindowTemplate);
        //FillWindowPixelBuffer(windowId, 0x11);
        DrawStdWindowFrame(windowId, 1);

        level = GetMonData(&gPlayerParty[1], MON_DATA_LEVEL, NULL);
        hp = GetMonData(&gPlayerParty[1], MON_DATA_HP, NULL);
        maxHp = GetMonData(&gPlayerParty[1], MON_DATA_MAX_HP, NULL);
        ptr = StringExpandPlaceholders(gStringVar1, gText_LevelOfMon);
        ConvertIntToDecimalStringN(ptr, level, STR_CONV_MODE_LEFT_ALIGN, 3);
        AddTextPrinterParameterized(windowId, 0, gStringVar1, 32, 1, 0xFF, 0);
        ptr = ConvertIntToDecimalStringN(gStringVar3, hp, STR_CONV_MODE_LEFT_ALIGN, 3);
        *ptr++ = 0xBA; // /
        ptr = ConvertIntToDecimalStringN(ptr, maxHp, STR_CONV_MODE_LEFT_ALIGN, 3);
        *ptr++ = 0x00; // [space]
        *ptr++ = 0xC2; // H
        *ptr++ = 0xCA; // P
        *ptr++ = 0xFF; // end
        AddTextPrinterParameterized(windowId, 0, gStringVar3, 32, 15, 0xFF, 0);
        PutWindowTilemap(windowId);
        CopyWindowToVram(windowId, COPYWIN_FULL);

        gBccGlobalStruct.windowIds[1] = windowId;
        gBccGlobalStruct.initStep++;
        break;
    case BCC_SWAP_MENU_SPAWN_ICONS:
        bcc_SpawnSprites();
        gBccGlobalStruct.initStep++;
        //break;
    case BCC_SWAP_MENU_KEEP_ICON_PALS_LOADED:
        // something of a hack to keep the palettes loaded because of that super funny
        if (gCurrentTimeSeconds == 0)
        {
            if (gBccGlobalStruct.palReloadTimer == 50)
            {
                bcc_DeleteSprites();
                bcc_SpawnSprites();
                gBccGlobalStruct.palReloadTimer = 0;
            }
            else
            {
                gBccGlobalStruct.palReloadTimer++;
            }
        }
        else
        {
            gBccGlobalStruct.palReloadTimer = 0;
        }
        break;
    case BCC_SWAP_MENU_DESTROY_TASK:
        DestroyTask(taskId);
        gBccGlobalStruct.initStep = 0;
        //break;
    }
}

void bcc_SpawnIconsAndWindows(void)
{
    // create a task that just counts down
    CreateTask(bcc_SpawnIconsAndWindowsCallback, 0);
    gBccGlobalStruct.initStep = 0;
    // see gText_bcc_SwapThisMon
    StringCopy(gStringVar2, gSpeciesNames[GetMonData(&gBccGlobalStruct.caughtMon, MON_DATA_SPECIES, NULL)]);
    StringCopy(gStringVar1, gSpeciesNames[GetMonData(&gPlayerParty[1], MON_DATA_SPECIES, NULL)]);
}

void bcc_DeleteBCCMon(void)
{
    //Free(gBccGlobalStruct.caughtMon);
    //gBccGlobalStruct.caughtMon = NULL;
    memset(&gBccGlobalStruct.caughtMon, 0, sizeof(BugCatchingContestGlobalStruct));
}

void bcc_SpawnSprites(void)
{
    u32 spriteId, species, pid;

    // load icon pals
    LoadMonIconPalettes();

    // set regs that will let me print a textbox and print an icon over it?
    SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_OBJWIN_ON);
    SetGpuRegBits(REG_OFFSET_WINOUT, WINOUT_WINOBJ_OBJ);
    SetGpuRegBits(REG_OFFSET_WININ, WININ_WIN0_OBJ);


    // print icon of gBccGlobalStruct.caughtMon -- first the actual icon
    species = GetMonData(&gPlayerParty[1], MON_DATA_SPECIES, NULL);
    pid = GetMonData(&gPlayerParty[1], MON_DATA_PERSONALITY, NULL);

    spriteId = CreateMonIcon(species, 0x0809718d, X_POS_MON_TO_SWAP, Y_POS_MON_TO_SWAP, 0, pid, 0);
    gSprites[spriteId].oam.priority = 0;
    gSprites[spriteId].invisible = 0;
    gSprites[spriteId].pos1.x = 0;
    gSprites[spriteId].pos1.y = 0;
    gSprites[spriteId].pos2.x = X_POS_MON_TO_SWAP;
    gSprites[spriteId].pos2.y = Y_POS_MON_TO_SWAP;

    gBccGlobalStruct.spriteIds[0] = spriteId;

    // then cut it out of the textbox
    spriteId = CreateMonIcon(species, 0x0809718d, X_POS_MON_TO_SWAP, Y_POS_MON_TO_SWAP, 0, pid, 0);
    gSprites[spriteId].oam.priority = 0;
    gSprites[spriteId].invisible = 0;
    gSprites[spriteId].pos1.x = 0;
    gSprites[spriteId].pos1.y = 0;
    gSprites[spriteId].pos2.x = X_POS_MON_TO_SWAP;
    gSprites[spriteId].pos2.y = Y_POS_MON_TO_SWAP;
    gSprites[spriteId].oam.objMode = ST_OAM_OBJ_WINDOW;

    gBccGlobalStruct.spriteIds[1] = spriteId;

    species = GetMonData(&gBccGlobalStruct.caughtMon, MON_DATA_SPECIES, NULL);
    pid = GetMonData(&gBccGlobalStruct.caughtMon, MON_DATA_PERSONALITY, NULL);

    spriteId = CreateMonIcon(species, 0x0809718d, X_POS_MON_SWAPPING, Y_POS_MON_SWAPPING, 0, pid, 0);
    gSprites[spriteId].oam.priority = 0;
    gSprites[spriteId].invisible = 0;
    gSprites[spriteId].pos1.x = 0;
    gSprites[spriteId].pos1.y = 0;
    gSprites[spriteId].pos2.x = X_POS_MON_SWAPPING;
    gSprites[spriteId].pos2.y = Y_POS_MON_SWAPPING;

    gBccGlobalStruct.spriteIds[2] = spriteId;

    // then cut it out of the textbox
    spriteId = CreateMonIcon(species, 0x0809718d, X_POS_MON_SWAPPING, Y_POS_MON_SWAPPING, 0, pid, 0);
    gSprites[spriteId].oam.priority = 0;
    gSprites[spriteId].invisible = 0;
    gSprites[spriteId].pos1.x = 0;
    gSprites[spriteId].pos1.y = 0;
    gSprites[spriteId].pos2.x = X_POS_MON_SWAPPING;
    gSprites[spriteId].pos2.y = Y_POS_MON_SWAPPING;
    gSprites[spriteId].oam.objMode = ST_OAM_OBJ_WINDOW;

    gBccGlobalStruct.spriteIds[3] = spriteId;
}

void bcc_DeleteSprites(void)
{
    DestroyMonIcon(&gSprites[gBccGlobalStruct.spriteIds[0]]);
    DestroyMonIcon(&gSprites[gBccGlobalStruct.spriteIds[1]]);
    DestroyMonIcon(&gSprites[gBccGlobalStruct.spriteIds[2]]);
    DestroyMonIcon(&gSprites[gBccGlobalStruct.spriteIds[3]]);
    gBccGlobalStruct.spriteIds[0] = 0;
    gBccGlobalStruct.spriteIds[1] = 0;
    gBccGlobalStruct.spriteIds[2] = 0;
    gBccGlobalStruct.spriteIds[3] = 0;
}

void bcc_DeleteSpritesAndWindow(void)
{
    bcc_DeleteSprites();

    // now also destroy window
    ClearStdWindowAndFrameToTransparent(gBccGlobalStruct.windowIds[0], FALSE);
    CopyWindowToVram(gBccGlobalStruct.windowIds[0], COPYWIN_FULL);
    RemoveWindow(gBccGlobalStruct.windowIds[0]);

    ClearStdWindowAndFrameToTransparent(gBccGlobalStruct.windowIds[1], FALSE);
    CopyWindowToVram(gBccGlobalStruct.windowIds[1], COPYWIN_FULL);
    RemoveWindow(gBccGlobalStruct.windowIds[1]);

    gBccGlobalStruct.windowIds[0] = 0;
    gBccGlobalStruct.windowIds[1] = 0;

    gBccGlobalStruct.initStep = BCC_SWAP_MENU_DESTROY_TASK;
}

// score caught mon in gBccGlobalStruct.caughtMon
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

u32 bcc_ScoreCaughtMon(void)
{
    struct Pokemon *bccMon = &gBccGlobalStruct.caughtMon;
    u32 species = GetMonData(bccMon, MON_DATA_SPECIES, NULL);
    u32 totalScore = 0;
    u32 level = GetMonData(bccMon, MON_DATA_LEVEL, NULL);
    u32 hp = GetMonData(bccMon, MON_DATA_HP, NULL);
    u32 maxHp = GetMonData(bccMon, MON_DATA_MAX_HP, NULL);
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
        totalIvs += GetMonData(bccMon, i, NULL);
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

    VarSet(0x800D, totalScore);

    return totalScore;
}


// functions to handle storing bug catching contest mon direct from party as well as giving the player the bug catching contest mon
u32 bcc_StoreCaughtMon(void)
{
    u32 ret = FALSE;
    if (gPlayerPartyCount > 1 && ((u32 *)&gBccGlobalStruct.caughtMon)[0] == 0) // is an uninitialized PartyPokemon
    {
        memcpy(&gBccGlobalStruct.caughtMon, &gPlayerParty[1], sizeof(gBccGlobalStruct.caughtMon));
        memset(&gPlayerParty[1], 0, sizeof(gBccGlobalStruct.caughtMon));
        memcpy(&gPlayerParty[1], &gPlayerParty[2], 4 * sizeof(gBccGlobalStruct.caughtMon));
        memset(&gPlayerParty[5], 0, sizeof(gBccGlobalStruct.caughtMon));
        ret = TRUE;
    }
    return ret;
}

u32 bcc_DepositBCCMon(void)
{
    u32 ret = GiveMonToPlayer(&gBccGlobalStruct.caughtMon);
    if (ret != 2) // can't give to player
    {
        //Free(gBccGlobalStruct.caughtMon);
        //gBccGlobalStruct.caughtMon = NULL;
    }
    return ret;
}

#include "../include/global.h"
#include "../include/alloc.h"
#include "../include/battle.h"
#include "../include/bug_catching_contest.h"
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

extern const u8 *bcc_ContestIsOver[]; // script
extern const u8 *bcc_SwapMonPrompt[]; // script
extern const u8 gText_LevelOfMon[]; // string

static const struct WindowTemplate sMonWindowTemplate = {0, X_POS_MON_TO_SWAP/8-2, Y_POS_MON_TO_SWAP/8-1, 12, 4, 0xF, 8};
static const struct WindowTemplate sCurrentMonWindowTemplate = {0, X_POS_MON_SWAPPING/8-2, Y_POS_MON_SWAPPING/8-1, 12, 4, 0xF, 8+48};

u32 bcc_StoreCaughtMon(void);
void bcc_DeleteBCCMon(void);
void bcc_DeleteSprites(void);
void bcc_DeleteBCCStruct(void);

// change start menu behavior:
// get rid of save, add script to quit out
// i might handle this instead in start_clock.c

// timer for bug catching contest
// every frame, increment a timer.  once it hits the limit, the bcc has ended

void bcc_Init(void)
{
    if (gBccGlobalStruct.activated == 0)
        memset(&gBccGlobalStruct, 0, sizeof(struct BugCatchingContestGlobalStruct));
    gBccGlobalStruct.balls = INITIAL_BALL_QUANTITY;

    if (IS_BCC_MON_INVALID)
        memset(&gBccGlobalStruct.caughtMon, 0, sizeof(gBccGlobalStruct.caughtMon));
    gBccGlobalStruct.activated = 1;
}

void bcc_TimerCallback(void)
{
    if (gBccGlobalStruct.activated)
    {
        u32 currDay = gCurrentTimeDayOfWeek;
        /*if (gMapHeader.regionMapSectionId != 0xBC) // not in the national park town map
        {
            bcc_DeleteBCCStruct(); // silently delete BCC struct and exit timer task
            DestroyTask(taskId);
        }
        else */if (gPlayerPartyCount > 1
              && IS_BCC_MON_INVALID)
        {
            if (!ScriptContext2_IsEnabled()) // ScriptContext2_IsEnabled is now actually ArePlayerFieldControlsLocked
                bcc_StoreCaughtMon();
        }
        else if (gPlayerPartyCount > 1
              && GetMonData(&gBccGlobalStruct.caughtMon, MON_DATA_HP, NULL) != 0) // if the player has caught a mon and already has a BCC mon
        {
            if (!ScriptContext2_IsEnabled()) // ScriptContext2_IsEnabled is now actually ArePlayerFieldControlsLocked
                ScriptContext1_SetupScript(bcc_SwapMonPrompt);
        }
        else if (gBccGlobalStruct.secondTimer >= SECONDS_IN_CONTEST // time is up
              || gBccGlobalStruct.balls == 0                        // no more balls
              || AllMonsFainted()                                   // needs to white out
              || (currDay != 2 && currDay != 4 && currDay != 6))    // current day is not valid for BCC
        {
            // trigger a script to run as soon as possible, destroy the task
            if (!ScriptContext2_IsEnabled()) // ScriptContext2_IsEnabled is now actually ArePlayerFieldControlsLocked
            {
                gBccGlobalStruct.activated = 0;
                ScriptContext1_SetupScript(bcc_ContestIsOver);
                HealPlayerParty(); // heal the party just in case the player whited out
            }
        }
        else
        {
            gBccGlobalStruct.frameTimer++;
            if (gBccGlobalStruct.frameTimer == FRAMES_PER_SECOND)
            {
                gBccGlobalStruct.secondTimer++;
                gBccGlobalStruct.frameTimer = 0;
            }
        }
    }
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
    memset(&gBccGlobalStruct.caughtMon, 0, sizeof(gBccGlobalStruct.caughtMon));
}

void bcc_DeleteBCCStruct(void)
{
    //Free(gBccGlobalStruct.caughtMon);
    //gBccGlobalStruct.caughtMon = NULL;
    memset(&gBccGlobalStruct, 0, sizeof(gBccGlobalStruct));
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

void bcc_StoreSpeciesInLastResult(void)
{
    struct Pokemon *bccMon = &gBccGlobalStruct.caughtMon;
    VarSet(0x800D, GetMonData(bccMon, MON_DATA_SPECIES, NULL));
    return;
}


u32 bcc_DeleteCaughtMon(void)
{
    if (gPlayerPartyCount > 1) // has an extra mon
    {
        memset(&gPlayerParty[1], 0, 5 * sizeof(gBccGlobalStruct.caughtMon));
    }
    CalculatePlayerPartyCount();
}


// functions to handle storing bug catching contest mon direct from party as well as giving the player the bug catching contest mon
u32 bcc_StoreCaughtMon(void)
{
    u32 ret = FALSE;
    if (gPlayerPartyCount > 1)
    {
        memcpy(&gBccGlobalStruct.caughtMon, &gPlayerParty[1], sizeof(gBccGlobalStruct.caughtMon));
        memset(&gPlayerParty[1], 0, 5 * sizeof(gBccGlobalStruct.caughtMon));
        ret = TRUE;
    }
    CalculatePlayerPartyCount();
    return ret;
}

u32 bcc_DepositBCCMon(void)
{
    u32 ret = GiveMonToPlayer(gBccGlobalStruct.caughtMon);
    if (ret != 2) // can't give to player
    {
        //Free(gBccGlobalStruct.caughtMon);
        //gBccGlobalStruct.caughtMon = NULL;
    }
    return ret;
}

// disable fly when in bcc

bool8 SetUpFieldMove_Fly(void)
{
    bool8 ret = TRUE;
    if (!(Overworld_MapTypeAllowsTeleportAndFly(gMapHeader.mapType) == TRUE))
        ret = FALSE;
    else if (IS_IN_BUG_CATCHING_CONTEST)
        ret = FALSE;
    return ret;
}

// disable start menu save when in bcc

extern u8 sNumStartMenuItems;
extern u8 sStartMenuOrder[];

enum StartMenuOption
{
    STARTMENU_POKEDEX = 0,
    STARTMENU_POKEMON,
    STARTMENU_BAG,
    STARTMENU_PLAYER,
    STARTMENU_SAVE,
    STARTMENU_OPTION,
    STARTMENU_EXIT,
    STARTMENU_RETIRE,
    STARTMENU_PLAYER2,
    MAX_STARTMENU_ITEMS
};

void SetUpStartMenu_BCC(void)
{
    if (FlagGet(0x829) == TRUE) // FLAG_SYS_POKEDEX_GET
        AppendToStartMenuItems(STARTMENU_POKEDEX);
    if (FlagGet(0x828) == TRUE) // FLAG_SYS_POKEMON_GET
        AppendToStartMenuItems(STARTMENU_POKEMON);
    AppendToStartMenuItems(STARTMENU_BAG);
    AppendToStartMenuItems(STARTMENU_PLAYER);
    AppendToStartMenuItems(STARTMENU_OPTION);
    AppendToStartMenuItems(STARTMENU_EXIT);
}

void SetUpStartMenu(void)
{
    sNumStartMenuItems = 0;
    if (IsUpdateLinkStateCBActive() == TRUE)
        SetUpStartMenu_Link();
    else if (InUnionRoom() == TRUE)
        SetUpStartMenu_UnionRoom();
    else if (GetSafariZoneFlag() == TRUE)
        SetUpStartMenu_SafariZone();
    else if (IS_IN_BUG_CATCHING_CONTEST)
        SetUpStartMenu_BCC();
    else
        SetUpStartMenu_NormalField();
}

#define BCC_BATTLE_MENU_BALLS_TENS_POS 27
#define BCC_BATTLE_MENU_BALLS_ONES_POS 28

u8 gText_BattleMenuBCC[] =
{ // Fight Ball xXX Pokémon Run
    0xFC, 0x05, 0x05,
    0xFC, 0x04, 0x0D, 0x0E, 0x0F,
    // Fight
    0xC0, 0xDD, 0xDB, 0xDC, 0xE8,
    0xFC, 0x13, 0x38,
    // Ball xXX
    0xBC, 0xD5, 0xE0, 0xE0,
    0xFC, 0x06, 0x00, // small font?
    0xFC, 0x13, 0x38+23,
    0xEC, 0xEC, 0xEC,
    0xFE,
    0xFC, 0x06, 0x02, // normal font
    // Pokémon
    0xCA, 0xE3, 0xDF, 0x1B, 0xE1, 0xE3, 0xE2,
    0xFC, 0x13, 0x38,
    // Run
    0xCC, 0xE9, 0xE2,
    0xFF
};

void PlayerHandleChooseAction(void)
{
    s32 i;

    gBattlerControllerFuncs[gActiveBattler] = 0x8032B94 | 1; // HandleChooseActionAfterDma3;
    BattlePutTextOnWindow(0x083fda4c, 0); // B_WIN_MNSG
    // replace BAG with BALL when in the relevant scenario
    if (IS_IN_BUG_CATCHING_CONTEST)
    {
        u32 balls = gBccGlobalStruct.balls;
        StringExpandPlaceholders(gStringVar3, gText_BattleMenuBCC);
        if (balls >= 10)
        {
            gStringVar3[BCC_BATTLE_MENU_BALLS_TENS_POS] = balls / 10 + 0xA1;
            gStringVar3[BCC_BATTLE_MENU_BALLS_ONES_POS] = balls % 10 + 0xA1;
        } else {
            gStringVar3[BCC_BATTLE_MENU_BALLS_TENS_POS] = balls + 0xA1;
            gStringVar3[BCC_BATTLE_MENU_BALLS_ONES_POS] = 0x00; // space
        }
        BattlePutTextOnWindow(gStringVar3, 2); // B_WIN_ACTION_MENU
    }
    else
        BattlePutTextOnWindow(0x083fe725, 2); // B_WIN_ACTION_MENU

    for (i = 0; i < 4; ++i)
        ActionSelectionDestroyCursorAt(i);
    ActionSelectionCreateCursorAt(gActionSelectionCursor[gActiveBattler], 0);
    BattleStringExpandPlaceholdersToDisplayedString(0x083fe6d5);
    BattlePutTextOnWindow(gDisplayedStringBattle, 1); // B_WIN_ACTION_PROMPT
}

// ugh throw ball when select ball
u32 HandleInputChooseAction_editedcase(void)
{
    u32 ret = 0;
    if (IS_IN_BUG_CATCHING_CONTEST && gBccGlobalStruct.balls == 0)
    {
        // immediately end the battle upon another selection after ball quantity hits 0
        gBattleOutcome = 1;
        return ret;
    }
    switch (gActionSelectionCursor[gActiveBattler])
    {
    case 0:
        BtlController_EmitTwoReturnValues(1, 0, 0); // use move
        break;
    case 1:
        if (IS_IN_BUG_CATCHING_CONTEST)
        {
            BtlController_EmitTwoReturnValues(1, 5, 0); // use safari ball
        }
        else
        {
            BtlController_EmitTwoReturnValues(1, 1, 0); // use item
        }
        break;
    case 2:
        BtlController_EmitTwoReturnValues(1, 2, 0); // switch
        break;
    case 3:
        BtlController_EmitTwoReturnValues(1, 3, 0); // run
        break;
    }
    return ret;
}

void HandleAction_SafariZoneBallThrow(void)
{
    gBattlerAttacker = gBattlerByTurnOrder[gCurrentTurnActionNumber];
    gBattle_BG0_X = 0;
    gBattle_BG0_Y = 0;
    if (IS_IN_BUG_CATCHING_CONTEST)
    {
        gUsedBall = 0x17;
        gLastUsedItem = 0x5C;
        gBattlescriptCurrInstr = BattleScript_ThrowBall;
        --gBccGlobalStruct.balls;
    }
    else
    {
        --gNumSafariBalls;
        gUsedBall = 5;
        gLastUsedItem = 5;
        gBattlescriptCurrInstr = gBattlescriptsForBallThrow[5];
    }
    gCurrentActionFuncId = 10; // B_ACTION_EXEC_SCRIPT
}

u16 BCC_StartMenuCoords[] =
{
    X_POS_MON_PAUSE_MENU, Y_POS_MON_PAUSE_MENU
};

static const struct WindowTemplate sBugPauseTemplate = {0, X_POS_MON_PAUSE_MENU/8-2, Y_POS_MON_PAUSE_MENU/8-1, 12, 4, 0xF, 8};

void ShowBCCStartWindow(void)
{
    struct Pokemon *bccMon = &gBccGlobalStruct.caughtMon;

    if (!IS_BCC_MON_INVALID) // has valid mon, caller already covers the "is in bcc" state
    {
        //SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_OBJWIN_ON);
        //SetGpuRegBits(REG_OFFSET_WINOUT, WINOUT_WINOBJ_OBJ);
        //SetGpuRegBits(REG_OFFSET_WININ, WININ_WIN0_OBJ);

        u8 *ptr;
        u32 windowId = AddWindow(&sBugPauseTemplate);
        DrawStdWindowFrame(windowId, 1);
        gBccGlobalStruct.windowIds[0] = windowId;

        LoadMonIconPalettes();

        u32 level = GetMonData(&gBccGlobalStruct.caughtMon, MON_DATA_LEVEL, NULL);
        u32 hp = GetMonData(&gBccGlobalStruct.caughtMon, MON_DATA_HP, NULL);
        u32 maxHp = GetMonData(&gBccGlobalStruct.caughtMon, MON_DATA_MAX_HP, NULL);
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
        *ptr++ = 0xFF; // end
        *ptr++ = 0xFF; // end
        AddTextPrinterParameterized(windowId, 0, gStringVar3, 32, 15, 0xFF, 0);
        PutWindowTilemap(windowId);
        CopyWindowToVram(windowId, COPYWIN_FULL);

        u32 species = GetMonData(bccMon, MON_DATA_SPECIES, NULL);
        u32 pid = GetMonData(bccMon, MON_DATA_PERSONALITY, NULL);
        u8 spriteId = CreateMonIcon(species, 0x0809718d, BCC_StartMenuCoords[0], BCC_StartMenuCoords[1], 0, pid, 0);
        gSprites[spriteId].oam.priority = 0;
        gSprites[spriteId].invisible = 0;
        gSprites[spriteId].pos1.x = 0;
        gSprites[spriteId].pos1.y = 0;
        gSprites[spriteId].pos2.x = BCC_StartMenuCoords[0];
        gSprites[spriteId].pos2.y = BCC_StartMenuCoords[1];

        gBccGlobalStruct.spriteIds[0] = spriteId;

        // then cut it out of the textbox
        spriteId = CreateMonIcon(species, 0x0809718d, BCC_StartMenuCoords[0], BCC_StartMenuCoords[1], 0, pid, 0);
        gSprites[spriteId].oam.priority = 0;
        gSprites[spriteId].invisible = 0;
        gSprites[spriteId].pos1.x = 0;
        gSprites[spriteId].pos1.y = 0;
        gSprites[spriteId].pos2.x = BCC_StartMenuCoords[0];
        gSprites[spriteId].pos2.y = BCC_StartMenuCoords[1];
        gSprites[spriteId].oam.objMode = ST_OAM_OBJ_WINDOW;

        gBccGlobalStruct.spriteIds[1] = spriteId;
    }
}

#include "../include/global.h"
#include "../include/alloc.h"
#include "../include/battle.h"
#include "../include/event_data.h"
#include "../include/main.h"
#include "../include/overworld.h"
#include "../include/pokemon.h"
#include "../include/save.h"
#include "../include/sound.h"
#include "../include/sprite.h"
#include "../include/string_util.h"
#include "../include/task.h"
#include "../include/constants/moves.h"



/////////////////////////////////////
//         CUT UPDATE CODE         //
/////////////////////////////////////



u8 GetFieldMoveMonAbility(void)
{
    u32 species = GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_SPECIES, 0);
    u32 abilityNum = GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_ABILITY_NUM, 0);
    
    if (abilityNum && gBaseStats[species].abilities[1] != 0)
        return gBaseStats[species].abilities[1];
    return gBaseStats[species].abilities[0];
}


u16 sCutGrassMetatileMapping[][2] =
{
    {0xD, 1},
    {0xA, 0x13},
    {0xB, 0xE},
    {0xC, 0xF},
    {0x352, 0x33E},
    {0x300, 0x310},
    {0x301, 0x311},
    {0x302, 0x312},
    {0x284, 0x281},
    {0x370, 0x1},      // long long grass natl park (but there is still special handling)
    {0x393, 0x1},      // long long grass safari zone (but there is still special handling)
    {0x282, 0x281},    // snow grass
    {0x283, 0x281},    // snow grass after it's been stepped in
    {0x39B, 1},        // long long grass bottom
    {0x371, 1},        // long long grass bottom
    {0xFFFF, 0xFFFF},
};


void MapGridSetMetatileIdAt(s16 x, s16 y, u16 metatileId);
u32 MapGridGetMetatileIdAt(s16 x, s16 y);


void SetCutGrassMetatileAt(s16 x, s16 y)
{
    u16 i = 0;
    u16 metatileId = MapGridGetMetatileIdAt(x, y);

    // natl park long long grass
    if (metatileId == 0x371 && MapGridGetMetatileIdAt(x, y-1) == 0x370) // handle setting the bottom part of long long grass if below it is cut
    {
        return;
    }

    if (metatileId == 0x370 && MapGridGetMetatileIdAt(x, y-1) == 0x370) // handle setting the bottom part of long long grass if below it is cut
    {
        MapGridSetMetatileIdAt(x, y, 0x371);
        return;
    }

    if (metatileId == 0x370 && MapGridGetMetatileIdAt(x, y+1) == 0x371) // handle clearing the bottom part of long long grass if above it is cut
    {
        MapGridSetMetatileIdAt(x, y+1, 0x1);
    }

    // safari zone long long grass
    if (metatileId == 0x39B && MapGridGetMetatileIdAt(x, y-1) == 0x393) // handle setting the bottom part of long long grass if below it is cut
    {
        return;
    }

    if (metatileId == 0x393 && MapGridGetMetatileIdAt(x, y-1) == 0x393) // handle setting the bottom part of long long grass if below it is cut
    {
        MapGridSetMetatileIdAt(x, y, 0x39B);
        return;
    }

    if (metatileId == 0x393 && MapGridGetMetatileIdAt(x, y+1) == 0x39B) // handle clearing the bottom part of long long grass if above it is cut
    {
        MapGridSetMetatileIdAt(x, y+1, 0x1);
    }

    while (1)
    {
        if (sCutGrassMetatileMapping[i][0] == 0xFFFF)
            return;
        if (sCutGrassMetatileMapping[i][0] == metatileId)
        {
            MapGridSetMetatileIdAt(x, y, sCutGrassMetatileMapping[i][1]);
            break;
        }
        i++;
    }
}


#define CUT_GRASS_SPRITE_COUNT 8

// when god judges his children, will he look kindly upon me?
// gPlayerFacingPosition in global fuck it
extern u8 *sCutGrassSpriteArrayPtr;

void PlayerGetDestCoords(s16 *x, s16 *y);
s8 MapGridGetElevationAt(s16 x, s16 y);
bool32 MetatileAtCoordsIsGrassTile(s16 x, s16 y);
void EnableObjectGroundEffectsByXY(s16 x, s16 y);
void DrawWholeMapView(void);

const struct SpriteTemplate sSpriteTemplate_FldEff_CutGrass;

bool8 FldEff_CutGrass(void)
{
    u8 i, j;
    s16 x, y;
    u8 pos;
    u32 cut_side = 3;
    if (GetFieldMoveMonAbility() == 52) // hyper cutter
        cut_side = 5;

    i = 0;
    PlaySE(121);
    pos = gFieldEffectArguments[1] - 1;
    PlayerGetDestCoords(&gPlayerFacingPosition.x, &gPlayerFacingPosition.y);

    for (i = 0; i < cut_side; i++)
    {
        y = gPlayerFacingPosition.y - cut_side/2 + i;
        for (j = 0; j < cut_side; j++)
        {
            x = gPlayerFacingPosition.x - cut_side/2 + j;
            if (MapGridGetElevationAt(x, y) == gPlayerFacingPosition.elevation)
            {
                if (MetatileAtCoordsIsGrassTile(x, y) == TRUE
                     || MapGridGetMetatileIdAt(x, y) == 0x371 || MapGridGetMetatileIdAt(x, y) == 0x39B)
                {
                    SetCutGrassMetatileAt(x, y);
                    EnableObjectGroundEffectsByXY(x, y);
                }
            }
        }
    }
    DrawWholeMapView();
    sCutGrassSpriteArrayPtr = Alloc(CUT_GRASS_SPRITE_COUNT);
    for (i = 0; i < 8; i++)
    {
        sCutGrassSpriteArrayPtr[i] = CreateSprite(&sSpriteTemplate_FldEff_CutGrass, gSprites[gPlayerAvatar.spriteId].oam.x + 8, gSprites[gPlayerAvatar.spriteId].oam.y + 20, 0);
        gSprites[sCutGrassSpriteArrayPtr[i]].data[2] = i * (0x100 / CUT_GRASS_SPRITE_COUNT);
    }
    return FALSE;
}


#define sScheduleOpenDottedHole *(u8 *)(0x02039874)
#define gFieldCallback2 *(u32 *)(0x03005024)
#define gPostMenuFieldCallback *(u32 *)(0x0203b0c4)

bool32 CutMoveRuinValleyCheck(void);
bool32 CheckObjectGraphicsInFrontOfPlayer(u16 gfxId);

bool8 SetUpFieldMove_Cut(void)
{
    s16 x, y;
    u8 i, j;
    u32 cut_side = 3;
    if (GetFieldMoveMonAbility() == 52) // hyper cutter
        cut_side = 5;

    sScheduleOpenDottedHole = FALSE;

    if (CutMoveRuinValleyCheck() == TRUE)
    {
        sScheduleOpenDottedHole = TRUE;
        gFieldCallback2 = 0x081248b1;
        gPostMenuFieldCallback = 0x08097985;
        return TRUE;
    }

    if (CheckObjectGraphicsInFrontOfPlayer(95) == TRUE) // check cut tree
    {
        gFieldCallback2 = 0x081248b1;
        gPostMenuFieldCallback = 0x080979d1;
        return TRUE;
    }
    
    else
    {
        PlayerGetDestCoords(&gPlayerFacingPosition.x, &gPlayerFacingPosition.y);
    
        for (i = 0; i < cut_side; i++)
        {
            y = gPlayerFacingPosition.y - cut_side/2 + i;
            for (j = 0; j < cut_side; j++)
            {
                x = gPlayerFacingPosition.x - cut_side/2 + j;
                if (MapGridGetElevationAt(x, y) == gPlayerFacingPosition.elevation)
                {
                    if (MetatileAtCoordsIsGrassTile(x, y) == TRUE)
                    {
                        gFieldCallback2 = 0x081248b1;
                        gPostMenuFieldCallback = 0x08097985;
                        return TRUE;
                    }
                }
            }
        }
        return FALSE;
    }
}


/////////////////////////////////////
//         FIELD MOVE CODE         //
/////////////////////////////////////





#define FIELD_MOVE_FLASH        0
#define FIELD_MOVE_CUT          1
#define FIELD_MOVE_FLY          2
#define FIELD_MOVE_STRENGTH     3
#define FIELD_MOVE_SURF         4
#define FIELD_MOVE_ROCK_SMASH   5
#define FIELD_MOVE_WATERFALL    6
#define FIELD_MOVE_TELEPORT     7
#define FIELD_MOVE_DIG          8
#define FIELD_MOVE_MILK_DRINK   9
#define FIELD_MOVE_SOFT_BOILED  10
#define FIELD_MOVE_SWEET_SCENT  11
#define FIELD_MOVE_HEADBUTT     12
#define FIELD_MOVE_ROCK_CLIMB   13
#define FIELD_MOVE_WHIRLPOOL    14
#define FIELD_MOVE_END          15


// IDs for DisplayPartyMenuStdMessage, to display the message at the bottom of the party menu
#define PARTY_MSG_CHOOSE_MON                0
#define PARTY_MSG_CHOOSE_MON_OR_CANCEL      1
#define PARTY_MSG_CHOOSE_MON_AND_CONFIRM    2
#define PARTY_MSG_MOVE_TO_WHERE             3 
#define PARTY_MSG_TEACH_WHICH_MON           4
#define PARTY_MSG_USE_ON_WHICH_MON          5
#define PARTY_MSG_GIVE_TO_WHICH_MON         6
#define PARTY_MSG_NOTHING_TO_CUT            7
#define PARTY_MSG_CANT_SURF_HERE            8
#define PARTY_MSG_ALREADY_SURFING           9
#define PARTY_MSG_CURRENT_TOO_FAST          10
#define PARTY_MSG_ENJOY_CYCLING             11
#define PARTY_MSG_ALREADY_IN_USE            12
#define PARTY_MSG_CANT_USE_HERE             13
#define PARTY_MSG_NO_MON_FOR_BATTLE         14
#define PARTY_MSG_CHOOSE_MON_2              15
#define PARTY_MSG_NOT_ENOUGH_HP             16
#define PARTY_MSG_THREE_MONS_ARE_NEEDED     17
#define PARTY_MSG_TWO_MONS_ARE_NEEDED       18
#define PARTY_MSG_MONS_CANT_BE_SAME         19
#define PARTY_MSG_NO_SAME_HOLD_ITEMS        20
#define PARTY_MSG_UNUSED                    21
#define PARTY_MSG_DO_WHAT_WITH_MON          22
#define PARTY_MSG_RESTORE_WHICH_MOVE        23
#define PARTY_MSG_BOOST_PP_WHICH_MOVE       24
#define PARTY_MSG_DO_WHAT_WITH_ITEM         25
#define PARTY_MSG_DO_WHAT_WITH_MAIL         26
#define PARTY_MSG_NONE                      127


enum
{
    CURSOR_OPTION_SUMMARY,
    CURSOR_OPTION_SWITCH,
    CURSOR_OPTION_CANCEL1,
    CURSOR_OPTION_ITEM,
    CURSOR_OPTION_GIVE,
    CURSOR_OPTION_TAKE_ITEM,
    CURSOR_OPTION_MAIL,
    CURSOR_OPTION_TAKE_MAIL,
    CURSOR_OPTION_READ,
    CURSOR_OPTION_CANCEL2,
    CURSOR_OPTION_SHIFT,
    CURSOR_OPTION_SEND_OUT,
    CURSOR_OPTION_ENTER,
    CURSOR_OPTION_NO_ENTRY,
    CURSOR_OPTION_STORE,
    CURSOR_OPTION_REGISTER,
    CURSOR_OPTION_TRADE1,
    CURSOR_OPTION_TRADE2,
    CURSOR_OPTION_FIELD_MOVES,
};

u16 ALIGN4 sFieldMoves[] =
{
    [FIELD_MOVE_FLASH      ] = MOVE_FLASH,
    [FIELD_MOVE_CUT        ] = MOVE_CUT,
    [FIELD_MOVE_FLY        ] = MOVE_FLY,
    [FIELD_MOVE_STRENGTH   ] = MOVE_STRENGTH,
    [FIELD_MOVE_SURF       ] = MOVE_SURF,
    [FIELD_MOVE_ROCK_SMASH ] = MOVE_ROCKSMASH,
    [FIELD_MOVE_WATERFALL  ] = MOVE_WATERFALL,
    [FIELD_MOVE_TELEPORT   ] = MOVE_TELEPORT,
    [FIELD_MOVE_DIG        ] = MOVE_DIG,
    [FIELD_MOVE_MILK_DRINK ] = MOVE_MILKDRINK,
    [FIELD_MOVE_SOFT_BOILED] = MOVE_SOFTBOILED,
    [FIELD_MOVE_SWEET_SCENT] = MOVE_SWEETSCENT,
    [FIELD_MOVE_HEADBUTT   ] = MOVE_HEADBUTT,
    [FIELD_MOVE_ROCK_CLIMB ] = MOVE_ROCKCLIMB,
    [FIELD_MOVE_WHIRLPOOL  ] = MOVE_WHIRLPOOL,
    [FIELD_MOVE_END        ] = FIELD_MOVE_END // this may be misuse of enum. same in emerald
};






u8 gText_HeadbuttDesc[];
u8 gText_RockClimbDesc[];
u8 gText_WhirlpoolDesc[];

u8 *sFieldMoveDescriptionTable[] =
{
    [FIELD_MOVE_FLASH]       = 0x08417583,
    [FIELD_MOVE_CUT]         = 0x08417533,
    [FIELD_MOVE_FLY]         = 0x08417548,
    [FIELD_MOVE_STRENGTH]    = 0x0841756e,
    [FIELD_MOVE_SURF]        = 0x0841755d,
    [FIELD_MOVE_ROCK_SMASH]  = 0x08417596,
    [FIELD_MOVE_WATERFALL]   = 0x084175ae,
    [FIELD_MOVE_TELEPORT]    = 0x084175fb,
    [FIELD_MOVE_DIG]         = 0x084175cc,
    [FIELD_MOVE_MILK_DRINK]  = 0x084175f1,
    [FIELD_MOVE_SOFT_BOILED] = 0x084175f1,
    [FIELD_MOVE_SWEET_SCENT] = 0x084175de,
    [FIELD_MOVE_HEADBUTT]    = gText_HeadbuttDesc,
    [FIELD_MOVE_ROCK_CLIMB]  = gText_RockClimbDesc,
    [FIELD_MOVE_WHIRLPOOL]   = gText_WhirlpoolDesc,
};






void CursorCB_FieldMove(u8 taskId);


struct
{
    const u8 *text;
    TaskFunc func;
} const ALIGN4 sCursorOptions[] =
{
    [CURSOR_OPTION_SUMMARY]                              = {0x08416994,                           0x08122d4d},
    [CURSOR_OPTION_SWITCH]                               = {0x0841698d,                           0x08122e01},
    [CURSOR_OPTION_CANCEL1]                              = {0x084161c1,                           0x08123641},
    [CURSOR_OPTION_ITEM]                                 = {0x084161d4,                           0x081236a1},
    [CURSOR_OPTION_GIVE]                                 = {0x084161b2,                           0x08123705},
    [CURSOR_OPTION_TAKE_ITEM]                            = {0x084161de,                           0x08123c39},
    [CURSOR_OPTION_MAIL]                                 = {0x084161d9,                           0x08123cf5},
    [CURSOR_OPTION_TAKE_MAIL]                            = {0x084169b2,                           0x08123e0d},
    [CURSOR_OPTION_READ]                                 = {0x084169b7,                           0x08123d59},
    [CURSOR_OPTION_CANCEL2]                              = {0x084161c1,                           0x08124065},
    [CURSOR_OPTION_SHIFT]                                = {0x0841697e,                           0x081240f5},
    [CURSOR_OPTION_SEND_OUT]                             = {0x08416984,                           0x081240f5},
    [CURSOR_OPTION_ENTER]                                = {0x084169a3,                           0x08124155},
    [CURSOR_OPTION_NO_ENTRY]                             = {0x084169a9,                           0x08124279},
    [CURSOR_OPTION_STORE]                                = {0x084161e3,                           0x08124355},
    [CURSOR_OPTION_REGISTER]                             = {0x0841b6f4,                           0x08124385},
    [CURSOR_OPTION_TRADE1]                               = {0x084169bc,                           0x08124491},
    [CURSOR_OPTION_TRADE2]                               = {0x084169bc,                           0x081245a1},
    [CURSOR_OPTION_FIELD_MOVES + FIELD_MOVE_FLASH]       = {gMoveNames[MOVE_FLASH],      CursorCB_FieldMove},
    [CURSOR_OPTION_FIELD_MOVES + FIELD_MOVE_CUT]         = {gMoveNames[MOVE_CUT],        CursorCB_FieldMove},
    [CURSOR_OPTION_FIELD_MOVES + FIELD_MOVE_FLY]         = {gMoveNames[MOVE_FLY],        CursorCB_FieldMove},
    [CURSOR_OPTION_FIELD_MOVES + FIELD_MOVE_STRENGTH]    = {gMoveNames[MOVE_STRENGTH],   CursorCB_FieldMove},
    [CURSOR_OPTION_FIELD_MOVES + FIELD_MOVE_SURF]        = {gMoveNames[MOVE_SURF],       CursorCB_FieldMove},
    [CURSOR_OPTION_FIELD_MOVES + FIELD_MOVE_ROCK_SMASH]  = {gMoveNames[MOVE_ROCKSMASH],  CursorCB_FieldMove},
    [CURSOR_OPTION_FIELD_MOVES + FIELD_MOVE_WATERFALL]   = {gMoveNames[MOVE_WATERFALL],  CursorCB_FieldMove},
    [CURSOR_OPTION_FIELD_MOVES + FIELD_MOVE_TELEPORT]    = {gMoveNames[MOVE_TELEPORT],   CursorCB_FieldMove},
    [CURSOR_OPTION_FIELD_MOVES + FIELD_MOVE_DIG]         = {gMoveNames[MOVE_DIG],        CursorCB_FieldMove},
    [CURSOR_OPTION_FIELD_MOVES + FIELD_MOVE_MILK_DRINK]  = {gMoveNames[MOVE_MILKDRINK],  CursorCB_FieldMove},
    [CURSOR_OPTION_FIELD_MOVES + FIELD_MOVE_SOFT_BOILED] = {gMoveNames[MOVE_SOFTBOILED], CursorCB_FieldMove},
    [CURSOR_OPTION_FIELD_MOVES + FIELD_MOVE_SWEET_SCENT] = {gMoveNames[MOVE_SWEETSCENT], CursorCB_FieldMove},
    [CURSOR_OPTION_FIELD_MOVES + FIELD_MOVE_HEADBUTT]    = {gMoveNames[MOVE_HEADBUTT],   CursorCB_FieldMove},
    [CURSOR_OPTION_FIELD_MOVES + FIELD_MOVE_ROCK_CLIMB]  = {gMoveNames[MOVE_ROCKCLIMB],  CursorCB_FieldMove},
    [CURSOR_OPTION_FIELD_MOVES + FIELD_MOVE_WHIRLPOOL]   = {gMoveNames[MOVE_WHIRLPOOL],  CursorCB_FieldMove},
};






bool8 SetUpFieldMove_Headbutt();
bool8 SetUpFieldMove_RockClimb();
bool8 SetUpFieldMove_Whirlpool();
bool8 SetUpFieldMove_SweetScent();


struct
{
    bool8 (*fieldMoveFunc)(void);
    u8 msgId;
} const sFieldMoveCursorCallbacks[] =
{
    [FIELD_MOVE_FLASH]        = {0x080c9b2d,                PARTY_MSG_CANT_USE_HERE},
    [FIELD_MOVE_CUT]          = {SetUpFieldMove_Cut,        PARTY_MSG_NOTHING_TO_CUT},
    [FIELD_MOVE_FLY]          = {0x08124a8d,                PARTY_MSG_CANT_USE_HERE},
    [FIELD_MOVE_STRENGTH]     = {0x080d07ed,                PARTY_MSG_CANT_USE_HERE},
    [FIELD_MOVE_SURF]         = {0x08124999,                PARTY_MSG_CANT_SURF_HERE},
    [FIELD_MOVE_ROCK_SMASH]   = {0x080c99d9,                PARTY_MSG_CANT_USE_HERE},
    [FIELD_MOVE_WATERFALL]    = {0x08124af9,                PARTY_MSG_CANT_USE_HERE},
    [FIELD_MOVE_TELEPORT]     = {0x080f66f1,                PARTY_MSG_CANT_USE_HERE},
    [FIELD_MOVE_DIG]          = {0x080c9a79,                PARTY_MSG_CANT_USE_HERE},
    [FIELD_MOVE_MILK_DRINK]   = {0x080e5685,                PARTY_MSG_NOT_ENOUGH_HP},
    [FIELD_MOVE_SOFT_BOILED]  = {0x080e5685,                PARTY_MSG_NOT_ENOUGH_HP},
    [FIELD_MOVE_SWEET_SCENT]  = {SetUpFieldMove_SweetScent, PARTY_MSG_CANT_USE_HERE},
    [FIELD_MOVE_HEADBUTT]     = {SetUpFieldMove_Headbutt,  PARTY_MSG_CANT_USE_HERE},
    [FIELD_MOVE_ROCK_CLIMB]   = {SetUpFieldMove_RockClimb, PARTY_MSG_CANT_USE_HERE},
    [FIELD_MOVE_WHIRLPOOL]    = {SetUpFieldMove_Whirlpool, PARTY_MSG_CANT_USE_HERE},
};


u16 sHMFieldMoveToCheckFlag[] =
{
    [FIELD_MOVE_FLASH     ] = 0x820,
    [FIELD_MOVE_CUT       ] = 0x821,
    [FIELD_MOVE_FLY       ] = 0x824,
    [FIELD_MOVE_STRENGTH  ] = 0x822,
    [FIELD_MOVE_SURF      ] = 0x823,
    [FIELD_MOVE_ROCK_SMASH] = 0x825,
    [FIELD_MOVE_WATERFALL ] = 0x827,
    [FIELD_MOVE_WHIRLPOOL ] = 0x826,
};


void DisplayPartyMenuStdMessage(u32 id);
void ChooseMonForSoftboiled(u32 taskId);
u32 Overworld_GetMapHeaderByGroupAndId(u32 mapGroup, u32 mapNum);
void GetMapNameGeneric(u8 *strBuf, u32 regionalMap);
void Task_ClosePartyMenu(u32 taskId);
void SetUsedFieldMoveQuestLogEvent(struct Pokemon *mon, u32 fieldMove);
void DisplayCantUseSurfMessage(void);
void DisplayCantUseFlashMessage(void);
u32 GetCursorSelectionMonId(void);
u32 Menu_GetCursorPos(void);


void CursorCB_FieldMove(u8 taskId)
{
    u8 fieldMove = sPartyMenuInternal->actions[Menu_GetCursorPos()] - CURSOR_OPTION_FIELD_MOVES;
    const struct MapHeader *mapHeader;

    PlaySE(SE_SELECT);
    if (sFieldMoveCursorCallbacks[fieldMove].fieldMoveFunc == NULL)
        return;
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
    if (MenuHelpers_IsLinkActive() == TRUE || InUnionRoom() == TRUE)
    {
        if (fieldMove == FIELD_MOVE_MILK_DRINK || fieldMove == FIELD_MOVE_SOFT_BOILED)
            DisplayPartyMenuStdMessage(PARTY_MSG_CANT_USE_HERE);
        else
            DisplayPartyMenuStdMessage(sFieldMoveCursorCallbacks[fieldMove].msgId);
        gTasks[taskId].func = 0x0812492d; //Task_CancelAfterAorBPress;
    }
    else
    {
        // All field moves before WATERFALL are HMs.
        //if (fieldMove <= FIELD_MOVE_WATERFALL && FlagGet(FLAG_BADGE01_GET + fieldMove) != TRUE)
        if (fieldMove <= FIELD_MOVE_WATERFALL && FlagGet(sHMFieldMoveToCheckFlag[fieldMove]) != TRUE)
        {
            DisplayPartyMenuMessage(0x08416ae2, TRUE); // Can't use until new badge is obtained
            gTasks[taskId].func = 0x081203b9; // Task_ReturnToChooseMonAfterText
        }
        else if (sFieldMoveCursorCallbacks[fieldMove].fieldMoveFunc() == TRUE)
        {
            switch (fieldMove)
            {
            case FIELD_MOVE_MILK_DRINK:
            case FIELD_MOVE_SOFT_BOILED:
                ChooseMonForSoftboiled(taskId);
                break;
            case FIELD_MOVE_TELEPORT:
                mapHeader = Overworld_GetMapHeaderByGroupAndId(gSaveBlock1->lastHealLocation.mapGroup, gSaveBlock1->lastHealLocation.mapNum);
                GetMapNameGeneric(gStringVar1, mapHeader->regionMapSectionId);
                StringExpandPlaceholders(gStringVar4, 0x08417640); // return to healing spot
                DisplayFieldMoveExitAreaMessage(taskId);
                sPartyMenuInternal->data[0] = fieldMove;
                break;
            case FIELD_MOVE_DIG:
                mapHeader = Overworld_GetMapHeaderByGroupAndId(gSaveBlock1->escapeWarp.mapGroup, gSaveBlock1->escapeWarp.mapNum);
                GetMapNameGeneric(gStringVar1, mapHeader->regionMapSectionId);
                StringExpandPlaceholders(gStringVar4, 0x08417615); // escape from here and return to
                DisplayFieldMoveExitAreaMessage(taskId);
                sPartyMenuInternal->data[0] = fieldMove;
                break;
            case FIELD_MOVE_FLY:
                gPartyMenu.exitCallback = 0x080c4ef9; // CB2_OpenFlyMap
                Task_ClosePartyMenu(taskId);
                break;
            default:
                gPartyMenu.exitCallback = CB2_ReturnToField;
                SetUsedFieldMoveQuestLogEvent(&gPlayerParty[GetCursorSelectionMonId()], fieldMove);
                Task_ClosePartyMenu(taskId);
                break;
            }
        }
        // Cant use Field Move
        else
        {
            switch (fieldMove)
            {
            case FIELD_MOVE_SURF:
                DisplayCantUseSurfMessage();
                break;
            case FIELD_MOVE_FLASH:
                DisplayCantUseFlashMessage();
                break;
            default:
                DisplayPartyMenuStdMessage(sFieldMoveCursorCallbacks[fieldMove].msgId);
                break;
            }
            gTasks[taskId].func = 0x0812492d;
        }
    }
}


void AppendToList(u8 *actions, u8 *numActions, u32 cursorFieldMove);
u32 ItemIsMail(u16 item);



void SetPartyMonFieldSelectionActions(struct Pokemon *mons, u8 slotId)
{
    u32 i, j;

    sPartyMenuInternal->numActions = 0;
    AppendToList(sPartyMenuInternal->actions, &sPartyMenuInternal->numActions, CURSOR_OPTION_SUMMARY);
    // Add field moves to action list
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        for (j = 0; j < FIELD_MOVE_END; j++)
        {
            if (GetMonData(&mons[slotId], i + MON_DATA_MOVE1, NULL) == sFieldMoves[j])
            {
                AppendToList(sPartyMenuInternal->actions, &sPartyMenuInternal->numActions, j + CURSOR_OPTION_FIELD_MOVES);
                break;
            }
        }
    }
    if (GetMonData(&mons[1], MON_DATA_SPECIES) != 0)
        AppendToList(sPartyMenuInternal->actions, &sPartyMenuInternal->numActions, CURSOR_OPTION_SWITCH);
    if (ItemIsMail(GetMonData(&mons[slotId], MON_DATA_HELD_ITEM)))
        AppendToList(sPartyMenuInternal->actions, &sPartyMenuInternal->numActions, CURSOR_OPTION_MAIL);
    else
        AppendToList(sPartyMenuInternal->actions, &sPartyMenuInternal->numActions, CURSOR_OPTION_ITEM);
    AppendToList(sPartyMenuInternal->actions, &sPartyMenuInternal->numActions, CURSOR_OPTION_CANCEL1);
}


/////////////////////////////////////
//           SWEET SCENT           //
/////////////////////////////////////


bool8 SetUpFieldMove_SweetScent(void)
{
    if (gSaveBlock1->location.mapGroup == 44 && gSaveBlock1->location.mapNum >= 83 && gSaveBlock1->location.mapNum <= 95) // sweet scent can not be used in ruins of alph
        return FALSE;
    gFieldCallback2 = 0x081248b1;
    gPostMenuFieldCallback = 0x080de0e9;
    return TRUE;
}


/////////////////////////////////////
//               DIG               //
/////////////////////////////////////


void PostFadeInDigSetup(void)
{
    // leftover debug code but who cares
    //if (FlagGet(0x215B))
    //{
    //    PlaySE(8);
    //    FlagClear(0x215B);
    //}
    //else
    {
        MapGridSetMetatileIdAt(4+7, 2+7, 0x2E3);
        MapGridSetMetatileIdAt(5+7, 2+7, 0x2E3);
        MapGridSetMetatileIdAt(4+7, 1+7, 0x308);
        MapGridSetMetatileIdAt(4+7, 0+7, 0x300);
        PlaySE(8);
        DrawWholeMapView();
        FlagSet(0x215B);
    }
    ScriptContext2_Disable();
}


bool8 SetUpFieldMove_Dig(void)
{
    if (gSaveBlock1->location.mapGroup == 44 && gSaveBlock1->location.mapNum == 84 && gSaveBlock1->pos.x == 4 && gSaveBlock1->pos.y == 2 && GetPlayerFacingDirection() == DIR_NORTH && !FlagGet(0x215B))
    {
        gFieldCallback2 = 0x081248b1;
        gPostMenuFieldCallback = 0x080c9aad;
        return TRUE;
    }
    else if (CanUseEscapeRopeOnCurrMap() == TRUE)
    {
        gFieldCallback2 = 0x081248b1;
        gPostMenuFieldCallback = 0x080c9aad;
        return TRUE;
    }
    return FALSE;
}

void FieldCallback_Dig(void)
{
    if (gSaveBlock1->location.mapGroup == 44 && gSaveBlock1->location.mapNum == 84 && gSaveBlock1->pos.x == 4 && gSaveBlock1->pos.y == 2 && GetPlayerFacingDirection() == DIR_NORTH && !FlagGet(0x215B))
    {
        PostFadeInDigSetup();
    }
    else
    {
        Overworld_ResetStateAfterDigEscRope();
        FieldEffectStart(38);
    }
    gFieldEffectArguments[0] = GetCursorSelectionMonId();
}


/////////////////////////////////////
//            HEADBUTT             //
/////////////////////////////////////


u8 HeadbuttScript[] =
{
    0x6A,                                       // lock
    0x9D, 0x00, 0x0D, 0x80,                     // setanimation 0x0 LASTRESULT
    0x7F, 0x00, 0x0D, 0x80,                     // bufferpartypokemon 0x0 LASTRESULT
    0x82, 0x01, 0x1D, 0x00,                     // bufferattack 0x1 MOVE_HEADBUTT
    0x05, 0xFE, 0xBA, 0xCF, 0x08,               // goto 0x08CFBAFE
};


void FieldCallback_Headbutt(void)
{
    VarSet(0x800D, GetCursorSelectionMonId()); // set mon animation slot
    ScriptContext_SetupScript(HeadbuttScript); // global headbutt script wrapper that we use
}

bool8 SetUpFieldMove_Headbutt(void)
{
    struct MapPosition position;
    GetInFrontOfPlayerPosition(&position);
    
    if (MapGridGetMetatileAttributeAt(position.x, position.y) == 0xA4) // headbutt tree
    {
        gFieldCallback2 = 0x081248b1;
        gPostMenuFieldCallback = FieldCallback_Headbutt;
        return TRUE;
    }
    
    return FALSE;
}


/////////////////////////////////////
//           WHIRLPOOL             //
/////////////////////////////////////


bool8 SetUpFieldMove_Whirlpool(void)
{
    return FALSE;
}


/////////////////////////////////////
//           ROCK CLIMB            //
/////////////////////////////////////

extern bool8 MetatileBehavior_IsRockClimbable(u8 metatileBehavior);


static bool8 RockClimb_Init(struct Task *task, struct ObjectEvent *objectEvent);
static bool8 RockClimb_FieldMovePose(struct Task *task, struct ObjectEvent *objectEvent);
static bool8 RockClimb_ShowMon(struct Task *task, struct ObjectEvent *objectEvent);
static bool8 RockClimb_JumpOnRockClimbBlob(struct Task *task, struct ObjectEvent *objectEvent);
static bool8 RockClimb_WaitJumpOnRockClimbBlob(struct Task *task, struct ObjectEvent *objectEvent);
static void RockClimbDust(struct ObjectEvent *objectEvent, u8 direction);
static bool8 RockClimb_Ride(struct Task *task, struct ObjectEvent *objectEvent);
static bool8 RockClimb_ContinueRideOrEnd(struct Task *task, struct ObjectEvent *objectEvent);
static bool8 RockClimb_StopRockClimbInit(struct Task *task, struct ObjectEvent *objectEvent);
static bool8 RockClimb_WaitStopRockClimb(struct Task *task, struct ObjectEvent *objectEvent);


// ROCK CLIMB
enum RockClimbState
{
    STATE_ROCK_CLIMB_INIT,
    STATE_ROCK_CLIMB_POSE,
    STATE_ROCK_CLIMB_SHOW_MON,
    STATE_ROCK_CLIMB_JUMP_ON,
    STATE_ROCK_CLIMB_WAIT_JUMP,
    STATE_ROCK_CLIMB_RIDE,
    STATE_ROCK_CLIMB_CONTINUE_RIDE,
    STATE_ROCK_CLIMB_STOP_INIT,
    STATE_ROCK_CLIMB_WAIT_STOP
};


extern const struct SpriteTemplate gFieldEffectObjectTemplate_RockClimbBlob;
extern const struct SpriteTemplate gFieldEffectObjectTemplate_RockClimbDust;


const struct SpriteTemplate *const gNewFieldEffectObjectTemplatePointers[] = {
    [FLDEFFOBJ_ROCK_CLIMB_BLOB - FLDEFFOBJ_NEW_TEMPLATES] = &gFieldEffectObjectTemplate_RockClimbBlob,
    [FLDEFFOBJ_ROCK_CLIMB_DUST - FLDEFFOBJ_NEW_TEMPLATES] = &gFieldEffectObjectTemplate_RockClimbDust,
};



#define tState       data[0]
#define tDestX       data[1]
#define tDestY       data[2]
#define tMonId       data[15]

u8 CreateRockClimbBlob(void)
{
    u8 spriteId = MAX_SPRITES;
    struct Sprite *sprite;

    SetSpritePosToOffsetMapCoords((s16 *)&gFieldEffectArguments[0], (s16 *)&gFieldEffectArguments[1], 8, 8);
    spriteId = CreateSpriteAtEnd(gNewFieldEffectObjectTemplatePointers[FLDEFFOBJ_ROCK_CLIMB_BLOB - FLDEFFOBJ_NEW_TEMPLATES], gFieldEffectArguments[0], gFieldEffectArguments[1], 0x96);
    if (spriteId != MAX_SPRITES)
    {
        sprite = &gSprites[spriteId];
        sprite->coordOffsetEnabled = TRUE;
        //sprite->oam.paletteNum = 0;
        sprite->data[2] = gFieldEffectArguments[2];
        sprite->data[3] = -1;
        sprite->data[6] = -1;
        sprite->data[7] = -1;
    }

    return spriteId;
}

u32 FldEff_RockClimbDust(void)
{
    u8 spriteId;
    struct Sprite *sprite;

    SetSpritePosToOffsetMapCoords((s16 *)&gFieldEffectArguments[0], (s16 *)&gFieldEffectArguments[1], 8, 12);
    spriteId = CreateSpriteAtEnd(gNewFieldEffectObjectTemplatePointers[FLDEFFOBJ_ROCK_CLIMB_DUST - FLDEFFOBJ_NEW_TEMPLATES], gFieldEffectArguments[0], gFieldEffectArguments[1], 0);
    if (spriteId != MAX_SPRITES)
    {
        sprite = &gSprites[spriteId];
        sprite->coordOffsetEnabled = TRUE;
        sprite->oam.priority = gFieldEffectArguments[3];
        sprite->data[0] = gFieldEffectArguments[2];
        sprite->data[1] = FLDEFF_ROCK_CLIMB_DUST;
    }
    return 0;
}

bool8 (*const sRockClimbFieldEffectFuncs[])(struct Task *, struct ObjectEvent *) =
{
    [STATE_ROCK_CLIMB_INIT]          = RockClimb_Init,
    [STATE_ROCK_CLIMB_POSE]          = RockClimb_FieldMovePose,
    [STATE_ROCK_CLIMB_SHOW_MON]      = RockClimb_ShowMon,
    [STATE_ROCK_CLIMB_JUMP_ON]       = RockClimb_JumpOnRockClimbBlob,
    [STATE_ROCK_CLIMB_WAIT_JUMP]     = RockClimb_WaitJumpOnRockClimbBlob,
    [STATE_ROCK_CLIMB_RIDE]          = RockClimb_Ride,
    [STATE_ROCK_CLIMB_CONTINUE_RIDE] = RockClimb_ContinueRideOrEnd,
    [STATE_ROCK_CLIMB_STOP_INIT]     = RockClimb_StopRockClimbInit,
    [STATE_ROCK_CLIMB_WAIT_STOP]     = RockClimb_WaitStopRockClimb
};

void Task_UseRockClimb(u8 taskId)
{
    //*(u32 *)(0x0203FFFC) = gTasks[taskId].tState;
    while (sRockClimbFieldEffectFuncs[gTasks[taskId].tState](&gTasks[taskId], &gObjectEvents[gPlayerAvatar.objectEventId]))
        ;
}

bool8 RockClimb_Init(struct Task *task, struct ObjectEvent *objectEvent)
{
    ScriptContext2_Enable();
    FreezeObjectEvents();
    gPlayerAvatar.preventStep = TRUE;
    SetPlayerAvatarStateMask(PLAYER_AVATAR_FLAG_SURFING);
    PlayerGetDestCoords(&task->tDestX, &task->tDestY);
    MoveCoords(gObjectEvents[gPlayerAvatar.objectEventId].movementDirection, &task->tDestX, &task->tDestY);
    task->tState++;
    return FALSE;
}

bool8 RockClimb_FieldMovePose(struct Task *task, struct ObjectEvent *objectEvent)
{
    if (!ObjectEventIsMovementOverridden(objectEvent) || ObjectEventClearHeldMovementIfFinished(objectEvent))
    {
        StartPlayerAvatarSummonMonForFieldMoveAnim();
        ObjectEventSetHeldMovement(objectEvent, 0x45); // MOVEMENT_ACTION_START_ANIM_IN_DIRECTION
        task->tState++;
    }
    return FALSE;
}

bool8 RockClimb_ShowMon(struct Task *task, struct ObjectEvent *objectEvent)
{
    if (ObjectEventCheckHeldMovementStatus(objectEvent))
    {
        gFieldEffectArguments[0] = task->tMonId | 0x80000000;
        FieldEffectStart(FLDEFF_FIELD_MOVE_SHOW_MON_INIT);
        task->tState++;
        return TRUE;
    }
    return FALSE;
}

bool8 RockClimb_JumpOnRockClimbBlob(struct Task *task, struct ObjectEvent *objectEvent)
{
    if (!FieldEffectActiveListContains(FLDEFF_FIELD_MOVE_SHOW_MON))
    {
        ObjectEventSetGraphicsId(objectEvent, GetPlayerAvatarGraphicsIdByStateId(PLAYER_AVATAR_GFX_RIDE));
        ObjectEventClearHeldMovementIfFinished(objectEvent);
        ObjectEventSetHeldMovement(objectEvent, GetJumpSpecialMovementAction(objectEvent->movementDirection));
        gFieldEffectArguments[0] = task->tDestX;
        gFieldEffectArguments[1] = task->tDestY;
        gFieldEffectArguments[2] = gPlayerAvatar.objectEventId;
        objectEvent->fieldEffectSpriteId = CreateRockClimbBlob();
        task->tState++;
    }

    return FALSE;
}

bool8 RockClimb_WaitJumpOnRockClimbBlob(struct Task *task, struct ObjectEvent *objectEvent)
{
    if (ObjectEventClearHeldMovementIfFinished(objectEvent))
    {
        SetSurfBlob_BobState(objectEvent->fieldEffectSpriteId, BOB_PLAYER_AND_MON);
        //switch (objectEvent->facingDirection)
        //{
        //case DIR_EAST:
        //    //check southeast then northeast
        //    if (MetatileBehavior_IsRockClimbable(MapGridGetMetatileBehaviorAt(task->tDestX + 1, task->tDestY + 1)))
        //        objectEvent->movementDirection = DIR_SOUTHEAST;
        //    else if (MetatileBehavior_IsRockClimbable(MapGridGetMetatileBehaviorAt(task->tDestX + 1, task->tDestY - 1)))
        //        objectEvent->movementDirection = DIR_NORTHEAST;
        //    break;
        //case DIR_WEST:
        //    //check northwest then southwest
        //    if (MetatileBehavior_IsRockClimbable(MapGridGetMetatileBehaviorAt(task->tDestX - 1, task->tDestY - 1)))
        //        objectEvent->movementDirection = DIR_NORTHWEST;
        //    else if (MetatileBehavior_IsRockClimbable(MapGridGetMetatileBehaviorAt(task->tDestX - 1, task->tDestY + 1)))
        //        objectEvent->movementDirection = DIR_SOUTHWEST;
        //    break;
        //}

        task->tState = STATE_ROCK_CLIMB_CONTINUE_RIDE;
    }

    return FALSE;
}

struct RockClimbRide
{
    u8 action;
    s8 dx;
    s8 dy;
    u8 jumpDir;
};
const struct RockClimbRide sRockClimbMovement[] = 
{
    [DIR_NONE] = {MOVEMENT_ACTION_WALK_FAST_DOWN, 0, 0, DIR_NONE},
    [DIR_SOUTH] = {MOVEMENT_ACTION_WALK_FAST_DOWN, 0, -1, DIR_SOUTH},
    [DIR_NORTH] = {MOVEMENT_ACTION_WALK_FAST_UP, 0, 1, DIR_NORTH},
    [DIR_WEST] = {MOVEMENT_ACTION_WALK_FAST_LEFT, 1, 1, DIR_WEST},
    [DIR_EAST] = {MOVEMENT_ACTION_WALK_FAST_RIGHT, -1, -1, DIR_EAST},
    //[DIR_SOUTHWEST] = {MOVEMENT_ACTION_WALK_FAST_DIAGONAL_DOWN_LEFT, 1, -1, DIR_WEST},
    //[DIR_SOUTHEAST] = {MOVEMENT_ACTION_WALK_FAST_DIAGONAL_DOWN_RIGHT, -1, -1, DIR_EAST},
    //[DIR_NORTHWEST] = {MOVEMENT_ACTION_WALK_FAST_DIAGONAL_UP_LEFT, 1, 1, DIR_WEST},
    //[DIR_NORTHEAST] = {MOVEMENT_ACTION_WALK_FAST_DIAGONAL_UP_RIGHT, -1, 1, DIR_EAST},
};

void RockClimbDust(struct ObjectEvent *objectEvent, u8 direction)
{
    s8 dx = sRockClimbMovement[direction].dx;
    s8 dy = sRockClimbMovement[direction].dy;

    gFieldEffectArguments[0] = objectEvent->currentCoords.x + dx;
    gFieldEffectArguments[1] = objectEvent->currentCoords.y + dy;
    gFieldEffectArguments[2] = objectEvent->previousElevation;
    gFieldEffectArguments[3] = gSprites[objectEvent->spriteId].oam.priority;
    FieldEffectStart(FLDEFF_ROCK_CLIMB_DUST);
}

bool8 RockClimb_Ride(struct Task *task, struct ObjectEvent *objectEvent)
{    
    ObjectEventSetHeldMovement(objectEvent, sRockClimbMovement[objectEvent->movementDirection].action);
    PlaySE(124); // m_rock_throw
    RockClimbDust(objectEvent, objectEvent->movementDirection);
    task->tState++;
    return FALSE;
}

bool8 RockClimb_ContinueRideOrEnd(struct Task *task, struct ObjectEvent *objectEvent)
{
    if (!ObjectEventClearHeldMovementIfFinished(objectEvent))
        return FALSE;

    PlayerGetDestCoords(&task->tDestX, &task->tDestY);
    MoveCoords(objectEvent->movementDirection, &task->tDestX, &task->tDestY);
    if (MetatileBehavior_IsRockClimbable(MapGridGetMetatileBehaviorAt(task->tDestX, task->tDestY)))
    {        
        task->tState = STATE_ROCK_CLIMB_RIDE;
        return TRUE;
    }

    ScriptContext2_Enable();
    gPlayerAvatar.flags &= ~PLAYER_AVATAR_FLAG_SURFING;
    gPlayerAvatar.flags |= PLAYER_AVATAR_FLAG_ON_FOOT;
    task->tState++;
    return FALSE;
}

bool8 RockClimb_StopRockClimbInit(struct Task *task, struct ObjectEvent *objectEvent)
{
    if (ObjectEventIsMovementOverridden(objectEvent))
    {
        if (!ObjectEventClearHeldMovementIfFinished(objectEvent))
            return FALSE;
    }

    RockClimbDust(objectEvent, DIR_NONE);   //dust on final spot
    ObjectEventSetHeldMovement(objectEvent, GetJumpSpecialMovementAction(sRockClimbMovement[objectEvent->movementDirection].jumpDir));
    SetSurfBlob_BobState(objectEvent->fieldEffectSpriteId, BOB_NONE);
    task->tState++;
    return TRUE;
}

bool8 RockClimb_WaitStopRockClimb(struct Task *task, struct ObjectEvent *objectEvent)
{
    if (ObjectEventClearHeldMovementIfFinished(objectEvent))
    {
        ObjectEventSetGraphicsId(objectEvent, GetPlayerAvatarGraphicsIdByStateId(PLAYER_AVATAR_STATE_NORMAL));
        ObjectEventSetHeldMovement(objectEvent, GetFaceDirectionMovementAction(objectEvent->facingDirection));
        gPlayerAvatar.preventStep = FALSE;
        UnfreezeObjectEvents();
        ScriptContext2_Disable();
        DestroySprite(&gSprites[objectEvent->fieldEffectSpriteId]); // this seems to destroy the palette too
        FieldEffectActiveListRemove(FLDEFF_USE_ROCK_CLIMB);
        objectEvent->triggerGroundEffectsOnMove = TRUE; // e.g. if dismount on grass
        DestroyTask(FindTaskIdByFunc(Task_UseRockClimb));
    }

    return FALSE;
}

bool8 IsRockClimbActive(void)
{
    if (FieldEffectActiveListContains(FLDEFF_USE_ROCK_CLIMB))
        return TRUE;
    else
        return FALSE;
}



void FieldCallback_RockClimb(void)
{
    gFieldEffectArguments[0] = GetCursorSelectionMonId();
    FieldEffectStart(FLDEFF_USE_ROCK_CLIMB);
}

bool8 SetUpFieldMove_RockClimb(void)
{
    s16 x, y;

    GetXYCoordsOneStepInFrontOfPlayer(&x, &y);
    if (MetatileBehavior_IsRockClimbable(MapGridGetMetatileBehaviorAt(x, y)))
    {
        gFieldCallback2 = 0x081248b1;
        gPostMenuFieldCallback = FieldCallback_RockClimb;
        return TRUE;
    }

    return FALSE;
}

#undef tState
#undef tDestX
#undef tDestY
#undef tMonId

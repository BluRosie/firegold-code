#include "../include/global.h"

#include "../include/alloc.h"
#include "../include/constants/songs.h"
#include "../include/event_data.h"
#include "../include/pokemon.h"
#include "../include/sound.h"





void SetPartyToLevel50(void)
{
    for (int i = 0; i < gPlayerPartyCount; i++)
    {
        u32 species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES, NULL);
        u32 level = GetMonData(&gPlayerParty[i], MON_DATA_LEVEL, NULL);
        if (species != 0 /* && level > 50 // test without this first */ && GetMonData(&gPlayerParty[i], MON_DATA_IS_EGG, NULL) == 0)
        {
            SetMonData(&gPlayerParty[i], MON_DATA_EXP, &gExperienceTables[gBaseStats[species].growthRate][level]);
            CalculateMonStats(&gPlayerParty[i]);
        }
    }
}


#define NUM_OF_EASY_MODE_SPREADS 75
#define NUM_OF_HARD_MODE_SPREADS NUM_OF_EASY_MODE_SPREADS

#define VAR_BATTLE_TOWER_TYPE 0x43CB

#define BATTLE_TOWER_TYPE_NONE 0
#define BATTLE_TOWER_TYPE_SINGLE_EASY 1
#define BATTLE_TOWER_TYPE_SINGLE_HARD 2
#define BATTLE_TOWER_TYPE_DOUBLE_EASY 3
#define BATTLE_TOWER_TYPE_DOUBLE_HARD 4

#define BATTLE_TOWER_TYPE_EASY_BIT 0x01

#define gSelectedOrderFromParty (u8 *)(0x0203b0d4)


enum
{
    CHOOSE_MONS_FOR_CABLE_CLUB_BATTLE,
    CHOOSE_MONS_FOR_BATTLE_TOWER,
    CHOOSE_MONS_FOR_UNION_ROOM_BATTLE,
};

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
// new
#define PARTY_MSG_FOUR_MONS_ARE_NEEDED      27
#define PARTY_MSG_NONE                      127




struct PartyMenuBox
{
    void *infoRects;
    const u8 *spriteCoords;
    u8 windowId;
    u8 monSpriteId;
    u8 itemSpriteId;
    u8 pokeballSpriteId;
    u8 statusSpriteId;
};

struct PartyMenuBox *sPartyMenuBoxes;




u8 CheckBattleEntriesAndGetMessage(void)
{
    u8 i, j;
    struct Pokemon *party = gPlayerParty;
    u8 *order = gSelectedOrderFromParty;
    
    switch (gPartyMenu.chooseMonsBattleType)
    {
    case CHOOSE_MONS_FOR_BATTLE_TOWER:
        if (VarGet(VAR_BATTLE_TOWER_TYPE) >= BATTLE_TOWER_TYPE_DOUBLE_EASY)
        {
            if (order[2] == 0 || order[3] == 0)
                return PARTY_MSG_FOUR_MONS_ARE_NEEDED;
            for (i = 0; i < 4; ++i)
            {
                sPartyMenuInternal->data[15] = GetMonData(&party[order[i] - 1], MON_DATA_SPECIES);
                sPartyMenuInternal->data[14] = GetMonData(&party[order[i] - 1], MON_DATA_HELD_ITEM);
                for (j = i + 1; j < 4; ++j)
                {
                    if (sPartyMenuInternal->data[15] == GetMonData(&party[order[j] - 1], MON_DATA_SPECIES))
                        return PARTY_MSG_MONS_CANT_BE_SAME;
                    if (sPartyMenuInternal->data[14] != 0 && sPartyMenuInternal->data[14] == GetMonData(&party[order[j] - 1], MON_DATA_HELD_ITEM))
                        return PARTY_MSG_NO_SAME_HOLD_ITEMS;
                }
            }
        }
        else
        {
            if (order[2] == 0)
                return PARTY_MSG_THREE_MONS_ARE_NEEDED;
            for (i = 0; i < 3; ++i)
            {
                sPartyMenuInternal->data[15] = GetMonData(&party[order[i] - 1], MON_DATA_SPECIES);
                sPartyMenuInternal->data[14] = GetMonData(&party[order[i] - 1], MON_DATA_HELD_ITEM);
                for (j = i + 1; j < 3; ++j)
                {
                    if (sPartyMenuInternal->data[15] == GetMonData(&party[order[j] - 1], MON_DATA_SPECIES))
                        return PARTY_MSG_MONS_CANT_BE_SAME;
                    if (sPartyMenuInternal->data[14] != 0 && sPartyMenuInternal->data[14] == GetMonData(&party[order[j] - 1], MON_DATA_HELD_ITEM))
                        return PARTY_MSG_NO_SAME_HOLD_ITEMS;
                }
            }
        }
        break;
    case CHOOSE_MONS_FOR_UNION_ROOM_BATTLE:
        if (order[1] == 0)
            return PARTY_MSG_TWO_MONS_ARE_NEEDED;
        break;
    }
    return 0xFF;
}


void ReducePlayerPartyToThree(void)
{
    struct Pokemon * party = Alloc(4 * sizeof(struct Pokemon));
    int i;

    // copy the selected pokemon according to the order.
    for (i = 0; i < 4; i++)
        if (gSelectedOrderFromParty[i]) // as long as the order keeps going (did the player select 1 mon? 2? 3?), do not stop
            party[i] = gPlayerParty[gSelectedOrderFromParty[i] - 1]; // index is 0 based, not literal

    Memset(gPlayerParty, 0, 6 * sizeof(struct Pokemon));

    // overwrite the first 3 with the order copied to.
    for (i = 0; i < 4; i++)
        gPlayerParty[i] = party[i];

    CalculatePlayerPartyCount();
    Free(party);
}


bool8 HasPartySlotAlreadyBeenSelected(u8 slot)
{
    u8 i;

    for (i = 0; i < 4; ++i)
        if (gSelectedOrderFromParty[i] == slot)
            return TRUE;
    return FALSE;
}


#define PARTYBOX_DESC_NO_USE       0
#define PARTYBOX_DESC_ABLE_3       1
#define PARTYBOX_DESC_FIRST        2
#define PARTYBOX_DESC_SECOND       3
#define PARTYBOX_DESC_THIRD        4
#define PARTYBOX_DESC_ABLE         5
#define PARTYBOX_DESC_NOT_ABLE     6
#define PARTYBOX_DESC_ABLE_2       7
#define PARTYBOX_DESC_NOT_ABLE_2   8
#define PARTYBOX_DESC_LEARNED      9
#define PARTYBOX_DESC_FOURTH      10


enum
{
    DRAW_TEXT_ONLY,
    DRAW_MENU_BOX_AND_TEXT,
    DRAW_MENU_BOX_ONLY,
};




// committing absolute crimes
const u32 sDescriptionStringTable[] =
{
    [PARTYBOX_DESC_NO_USE]     = 0x08417411,
    [PARTYBOX_DESC_ABLE_3]     = 0x08417419,
    [PARTYBOX_DESC_FIRST]      = 0x0841741e,
    [PARTYBOX_DESC_SECOND]     = 0x08417424,
    [PARTYBOX_DESC_THIRD]      = 0x0841742b,
    [PARTYBOX_DESC_ABLE]       = 0x08417431,
    [PARTYBOX_DESC_NOT_ABLE]   = 0x08417436,
    [PARTYBOX_DESC_ABLE_2]     = 0x0841743f,
    [PARTYBOX_DESC_NOT_ABLE_2] = 0x08417445,
    [PARTYBOX_DESC_LEARNED]    = 0x0841744f,
    [PARTYBOX_DESC_FOURTH]     = gText_Fourth_PM,
}





void CursorCB_NoEntry(u8 taskId)
{
    u8 i;

    PlaySE(SE_SELECT);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
    for (i = 0; i < 4; ++i)
    {
        if (gSelectedOrderFromParty[i] ==  gPartyMenu.slotId + 1)
        {
            gSelectedOrderFromParty[i] = 0;
            switch (i)
            {
            case 0:
                gSelectedOrderFromParty[0] = gSelectedOrderFromParty[1];
                gSelectedOrderFromParty[1] = gSelectedOrderFromParty[2];
                gSelectedOrderFromParty[2] = gSelectedOrderFromParty[3];
                gSelectedOrderFromParty[3] = 0;
                break;
            case 1:
                gSelectedOrderFromParty[1] = gSelectedOrderFromParty[2];
                gSelectedOrderFromParty[2] = gSelectedOrderFromParty[3];
                gSelectedOrderFromParty[3] = 0;
                break;
            case 2:
                gSelectedOrderFromParty[2] = gSelectedOrderFromParty[3];
                gSelectedOrderFromParty[3] = 0;
                break;
            }
            break;
        }
    }
    DisplayPartyPokemonDescriptionText(PARTYBOX_DESC_ABLE_3, &sPartyMenuBoxes[gPartyMenu.slotId], DRAW_MENU_BOX_AND_TEXT);
    if (gSelectedOrderFromParty[0] != 0)
        DisplayPartyPokemonDescriptionText(PARTYBOX_DESC_FIRST, &sPartyMenuBoxes[gSelectedOrderFromParty[0] - 1], DRAW_MENU_BOX_AND_TEXT);
    if (gSelectedOrderFromParty[1] != 0)
        DisplayPartyPokemonDescriptionText(PARTYBOX_DESC_SECOND, &sPartyMenuBoxes[gSelectedOrderFromParty[1] - 1], DRAW_MENU_BOX_AND_TEXT);
    if (gSelectedOrderFromParty[2] != 0)
        DisplayPartyPokemonDescriptionText(PARTYBOX_DESC_THIRD, &sPartyMenuBoxes[gSelectedOrderFromParty[2] - 1], DRAW_MENU_BOX_AND_TEXT);
    DisplayPartyMenuStdMessage(PARTY_MSG_CHOOSE_MON);
    gTasks[taskId].func = Task_HandleChooseMonInput;
}


void ClearSelectedPartyOrder(void)
{
    Memset(gSelectedOrderFromParty, 0, 4);
}


static void CursorCB_Enter(u8 taskId)
{
    u32 maxBattlers;
    u32 i;
    const u8 *str;
    
    if (gPartyMenu.chooseMonsBattleType == CHOOSE_MONS_FOR_UNION_ROOM_BATTLE)
    {
        maxBattlers = 2;
        str = (const u8 *)(0x08416b3e); // gText_NoMoreThanTwoMayEnter
    }
    else if (VarGet(VAR_BATTLE_TOWER_TYPE) >= BATTLE_TOWER_TYPE_DOUBLE_EASY)
    {
        maxBattlers = 4;
        str = gText_NoMoreThanFourMayEnter;
    }
    else
    {
        maxBattlers = 3;
        str = (const u8 *)(0x08416b16); // gText_NoMoreThanThreeMayEnter
    }
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
    for (i = 0; i < maxBattlers; ++i)
    {
        if (gSelectedOrderFromParty[i] == 0)
        {
            PlaySE(SE_SELECT);
            gSelectedOrderFromParty[i] = gPartyMenu.slotId + 1;
            if (i < 3)
                DisplayPartyPokemonDescriptionText(i + PARTYBOX_DESC_FIRST, &sPartyMenuBoxes[gPartyMenu.slotId], 1);
            else
                DisplayPartyPokemonDescriptionText(PARTYBOX_DESC_FOURTH, &sPartyMenuBoxes[gPartyMenu.slotId], 1);

            if (i == (maxBattlers - 1))
                MoveCursorToConfirm();

            DisplayPartyMenuStdMessage(PARTY_MSG_CHOOSE_MON);
            gTasks[taskId].func = Task_HandleChooseMonInput;
            return;
        }
    }
    PlaySE(SE_FAILURE);
    DisplayPartyMenuMessage(str, 1);
    gTasks[taskId].func = (void (u8))(0x081203b8 | 1); // Task_ReturnToChooseMonAfterText
}


void DisplayPartyPokemonDataForChooseMultiple(u8 slot)
{
    u8 i;
    struct Pokemon *mon = &gPlayerParty[slot];
    u8 *order = gSelectedOrderFromParty;
    u8 maxBattlers;

    if (!GetBattleEntryEligibility(mon))
        DisplayPartyPokemonDescriptionData(slot, PARTYBOX_DESC_NOT_ABLE);
    else
    {
        if (gPartyMenu.chooseMonsBattleType == CHOOSE_MONS_FOR_UNION_ROOM_BATTLE)
            maxBattlers = 2;
        else if (VarGet(VAR_BATTLE_TOWER_TYPE) >= BATTLE_TOWER_TYPE_DOUBLE_EASY)
            maxBattlers = 4;
        else
            maxBattlers = 3;

        for (i = 0; i < maxBattlers; ++i)
        {
            if (order[i] != 0 && (order[i] - 1) == slot)
            {
                if (i < 3)
                    DisplayPartyPokemonDescriptionData(slot, i + PARTYBOX_DESC_FIRST);
                else
                    DisplayPartyPokemonDescriptionData(slot, PARTYBOX_DESC_FOURTH);
                return;
            }
        }
        DisplayPartyPokemonDescriptionData(slot, PARTYBOX_DESC_ABLE_3);
    }
}

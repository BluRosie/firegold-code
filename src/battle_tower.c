#include "../include/global.h"

#include "../include/alloc.h"
#include "../include/constants/easy_chat.h"
#include "../include/constants/songs.h"
#include "../include/constants/species.h"
#include "../include/event_data.h"
#include "../include/pokemon.h"
#include "../include/save.h"
#include "../include/sound.h"
#include "../include/string_util.h"
#include "../include/window.h"


u32 IsMonInSlotInvalid(u8 slot);
u32 MonNotAlreadySelected(u8 slot);


// comment this out:  was made a permanent addition on 17 nov 22
//void SetPartyToLevel50(void)
//{
//    CalculatePlayerPartyCount();
//    for (u32 i = 0; i < gPlayerPartyCount; i++)
//    {
//        u32 species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES, NULL);
//        u32 level = GetMonData(&gPlayerParty[i], MON_DATA_LEVEL, NULL);
//        if (species != 0 && level > 50 && GetMonData(&gPlayerParty[i], MON_DATA_IS_EGG, NULL) == 0)
//        {
//            u32 experience[] = {125000, 100000, /*125000, */117360, 156250, 142500};
//            int j = 0;
//            while (GetMonData(&gPlayerParty[i], MON_DATA_LEVEL, NULL) != 50)
//            {
//                SetMonData(&gPlayerParty[i], MON_DATA_EXP, (u8 *)&experience[j]);
//                CalculateMonStats(&gPlayerParty[i]);
//                j++;
//            }
//        }
//    }
//}


#define NUM_OF_EASY_MODE_SPREADS 75
#define NUM_OF_HARD_MODE_SPREADS 567

#define VAR_BATTLE_TOWER_TYPE 0x43CB
#define VAR_BATTLE_TOWER_OBJ_ID 0x4010

#define BATTLE_TOWER_TYPE_NONE 0
#define BATTLE_TOWER_TYPE_SINGLE_EASY 1
#define BATTLE_TOWER_TYPE_SINGLE_HARD 2
#define BATTLE_TOWER_TYPE_DOUBLE_EASY 3
#define BATTLE_TOWER_TYPE_DOUBLE_HARD 4
#define BATTLE_TOWER_TYPE_MULTI_EASY 5
#define BATTLE_TOWER_TYPE_MULTI_HARD 6

#define BATTLE_TOWER_TYPE_EASY_BIT 0x01

#define gSelectedOrderFromParty ((u8 *)(0x0203b0d4))
#define gSelectedOrderFromPartySave ((u8 *)(0x0203c124)) // in the save block right after the roamers, 4 bytes.


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
    //u8 *order = gSelectedOrderFromParty;
    u32 limit = 0;
    
    switch (gPartyMenu.chooseMonsBattleType)
    {
    default:
    case CHOOSE_MONS_FOR_BATTLE_TOWER:
        if (VarGet(VAR_BATTLE_TOWER_TYPE) >= BATTLE_TOWER_TYPE_MULTI_EASY)
        {
            if (gSelectedOrderFromParty[1] == 0)
                return PARTY_MSG_TWO_MONS_ARE_NEEDED;
            limit = 2;
        }
        else if (VarGet(VAR_BATTLE_TOWER_TYPE) >= BATTLE_TOWER_TYPE_DOUBLE_EASY)
        {
            if (gSelectedOrderFromParty[3] == 0)
                return PARTY_MSG_FOUR_MONS_ARE_NEEDED;
            limit = 4;
        }
        else
        {
            if (gSelectedOrderFromParty[2] == 0)
                return PARTY_MSG_THREE_MONS_ARE_NEEDED;
            limit = 3;
        }

        for (i = 0; i < limit; ++i)
        {
            sPartyMenuInternal->data[15] = GetMonData(&party[gSelectedOrderFromParty[i] - 1], MON_DATA_SPECIES);
            sPartyMenuInternal->data[14] = GetMonData(&party[gSelectedOrderFromParty[i] - 1], MON_DATA_HELD_ITEM);
            for (j = i + 1; j < limit; ++j)
            {
                if (sPartyMenuInternal->data[15] == GetMonData(&party[gSelectedOrderFromParty[j] - 1], MON_DATA_SPECIES))
                    return PARTY_MSG_MONS_CANT_BE_SAME;
                if (sPartyMenuInternal->data[14] != 0 && sPartyMenuInternal->data[14] == GetMonData(&party[gSelectedOrderFromParty[j] - 1], MON_DATA_HELD_ITEM))
                    return PARTY_MSG_NO_SAME_HOLD_ITEMS;
            }
        }
        break;
    case CHOOSE_MONS_FOR_UNION_ROOM_BATTLE:
        if (gSelectedOrderFromParty[1] == 0)
            return PARTY_MSG_TWO_MONS_ARE_NEEDED;
        break;
    }
    return 0xFF;
}


void ReducePlayerPartyToThree(void)
{
    struct Pokemon * party = Alloc(6 * sizeof(struct Pokemon));
    int i;
    
    if (!gSelectedOrderFromParty[0]) // needs to be initialized from save
    {
        for (i = 0; i < 4; i++)
        {
            gSelectedOrderFromParty[i] = gSelectedOrderFromPartySave[i];
        }
    }

    // copy the selected pokemon according to the order.
    for (i = 0; i < 4; i++)
    {
        if (gSelectedOrderFromParty[i]) // as long as the order keeps going (did the player select 1 mon? 2? 3?), do not stop
        {
            party[i] = gPlayerParty[gSelectedOrderFromParty[i] - 1]; // index is 0 based, not literal
        }
    }

    Memset(gPlayerParty, 0, 6 * sizeof(struct Pokemon));

    // overwrite the first 3 with the order copied to.
    for (i = 0; i < 4; i++)
    {
        if (gSelectedOrderFromParty[i]) // as long as the order keeps going (did the player select 1 mon? 2? 3?), do not stop
        {
            gPlayerParty[i] = party[i];
        }
    }

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



extern const u8 gText_Fourth_PM[];
extern const u8 gText_NoMoreThanFourMayEnter[];
extern const u8 gText_NoTwoPokemonHoldSameItem[];
extern const u8 gText_TwoMembersOfTheSameSpecies[];


// committing absolute crimes
const u8 *const sDescriptionStringTable[] =
{
    [PARTYBOX_DESC_NO_USE]     = (const u8 *)0x08417411,
    [PARTYBOX_DESC_ABLE_3]     = (const u8 *)0x08417419,
    [PARTYBOX_DESC_FIRST]      = (const u8 *)0x0841741e,
    [PARTYBOX_DESC_SECOND]     = (const u8 *)0x08417424,
    [PARTYBOX_DESC_THIRD]      = (const u8 *)0x0841742b,
    [PARTYBOX_DESC_ABLE]       = (const u8 *)0x08417431,
    [PARTYBOX_DESC_NOT_ABLE]   = (const u8 *)0x08417436,
    [PARTYBOX_DESC_ABLE_2]     = (const u8 *)0x0841743f,
    [PARTYBOX_DESC_NOT_ABLE_2] = (const u8 *)0x08417445,
    [PARTYBOX_DESC_LEARNED]    = (const u8 *)0x0841744f,
    [PARTYBOX_DESC_FOURTH]     = gText_Fourth_PM,
};





void CursorCB_NoEntry(u8 taskId)
{
    u8 i;

    PlaySE(SE_SELECT);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[0]);
    PartyMenuRemoveWindow(&sPartyMenuInternal->windowId[1]);
    for (i = 0; i < 4; ++i)
    {
        if (gSelectedOrderFromParty[i] == gPartyMenu.slotId + 1)
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

    for (i = 0; i < 4; i++) // after no entry is sorted out, reupdate gSelectedOrderFromParty
    {
        gSelectedOrderFromPartySave[i] = gSelectedOrderFromParty[i];
    }
    //DisplayPartyPokemonDescriptionText(PARTYBOX_DESC_ABLE_3, &sPartyMenuBoxes[gPartyMenu.slotId], DRAW_MENU_BOX_AND_TEXT);
    
    for (i = 0; i < gPlayerPartyCount; i++)
    {
        if (MonNotAlreadySelected(i))
        {
            if (IsMonInSlotInvalid(i))
            {
                DisplayPartyPokemonDescriptionText(PARTYBOX_DESC_NOT_ABLE_2, &sPartyMenuBoxes[i], DRAW_MENU_BOX_AND_TEXT);
            }
            else
            {
                DisplayPartyPokemonDescriptionText(PARTYBOX_DESC_ABLE_3, &sPartyMenuBoxes[i], DRAW_MENU_BOX_AND_TEXT);
            }
        }
    }
    
    if (gSelectedOrderFromParty[0] != 0)
        DisplayPartyPokemonDescriptionText(PARTYBOX_DESC_FIRST, &sPartyMenuBoxes[gSelectedOrderFromParty[0] - 1], DRAW_MENU_BOX_AND_TEXT);
    if (gSelectedOrderFromParty[1] != 0)
        DisplayPartyPokemonDescriptionText(PARTYBOX_DESC_SECOND, &sPartyMenuBoxes[gSelectedOrderFromParty[1] - 1], DRAW_MENU_BOX_AND_TEXT);
    if (gSelectedOrderFromParty[2] != 0)
        DisplayPartyPokemonDescriptionText(PARTYBOX_DESC_THIRD, &sPartyMenuBoxes[gSelectedOrderFromParty[2] - 1], DRAW_MENU_BOX_AND_TEXT);
    if (gSelectedOrderFromParty[3] != 0)
        DisplayPartyPokemonDescriptionText(PARTYBOX_DESC_FOURTH, &sPartyMenuBoxes[gSelectedOrderFromParty[2] - 1], DRAW_MENU_BOX_AND_TEXT);
    DisplayPartyMenuStdMessage(PARTY_MSG_CHOOSE_MON);
    gTasks[taskId].func = (void (*)(u8))(0x0811fb28 | 1); //Task_HandleChooseMonInput
}


void ClearSelectedPartyOrder(void)
{
    Memset(gSelectedOrderFromParty, 0, 4);
    Memset(gSelectedOrderFromPartySave, 0, 4);
}


void CursorCB_Enter(u8 taskId)
{
    u32 maxBattlers;
    u32 i;
    const u8 *str;
    
    if (gPartyMenu.chooseMonsBattleType == CHOOSE_MONS_FOR_UNION_ROOM_BATTLE)
    {
        maxBattlers = 2;
        str = (const u8 *)(0x08416b3e); // gText_NoMoreThanTwoMayEnter
    }
    else if (VarGet(VAR_BATTLE_TOWER_TYPE) >= BATTLE_TOWER_TYPE_MULTI_EASY)
    {
        maxBattlers = 3;
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
    
    u8 result = IsMonInSlotInvalid(gPartyMenu.slotId);
    
    if (result)
    {
        PlaySE(SE_FAILURE);
        if (result == 1)
            DisplayPartyMenuMessage(&gText_TwoMembersOfTheSameSpecies, 1);
        else
            DisplayPartyMenuMessage(&gText_NoTwoPokemonHoldSameItem, 1);
        gTasks[taskId].func = (void (*)(u8))(0x081203b8 | 1); // Task_ReturnToChooseMonAfterText
        return;
    }
    else
    {
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
                
                for (int j = 0; j < gPlayerPartyCount; j++)
                {
                    if (MonNotAlreadySelected(j))
                    {
                        if (IsMonInSlotInvalid(j))
                        {
                            DisplayPartyPokemonDescriptionText(PARTYBOX_DESC_NOT_ABLE_2, &sPartyMenuBoxes[j], DRAW_MENU_BOX_AND_TEXT);
                        }
                        else
                        {
                            DisplayPartyPokemonDescriptionText(PARTYBOX_DESC_ABLE_3, &sPartyMenuBoxes[j], DRAW_MENU_BOX_AND_TEXT);
                        }
                    }
                }

                if (gSelectedOrderFromParty[0] != 0)
                    DisplayPartyPokemonDescriptionText(PARTYBOX_DESC_FIRST, &sPartyMenuBoxes[gSelectedOrderFromParty[0] - 1], DRAW_MENU_BOX_AND_TEXT);
                if (gSelectedOrderFromParty[1] != 0)
                    DisplayPartyPokemonDescriptionText(PARTYBOX_DESC_SECOND, &sPartyMenuBoxes[gSelectedOrderFromParty[1] - 1], DRAW_MENU_BOX_AND_TEXT);
                if (gSelectedOrderFromParty[2] != 0)
                    DisplayPartyPokemonDescriptionText(PARTYBOX_DESC_THIRD, &sPartyMenuBoxes[gSelectedOrderFromParty[2] - 1], DRAW_MENU_BOX_AND_TEXT);

                DisplayPartyMenuStdMessage(PARTY_MSG_CHOOSE_MON);
                gSelectedOrderFromPartySave[i] = gSelectedOrderFromParty[i];
                gTasks[taskId].func = (void (*)(u8))(0x0811fb28 | 1); //Task_HandleChooseMonInput
                return;
            }
            else
            {
                gSelectedOrderFromPartySave[i] = gSelectedOrderFromParty[i];
            }
        }
    }
    PlaySE(SE_FAILURE);
    DisplayPartyMenuMessage(str, 1);
    gTasks[taskId].func = (void (*)(u8))(0x081203b8 | 1); // Task_ReturnToChooseMonAfterText
}


u32 IsMonInSlotInvalid(u8 slot)
{
    struct Pokemon *mon = &gPlayerParty[slot];
    u8 maxBattlers;
    int i;
    u32 ret = 0;
    u32 slotSpecies = GetMonData(&gPlayerParty[slot], MON_DATA_SPECIES);
    u32 slotItem = GetMonData(&gPlayerParty[slot], MON_DATA_HELD_ITEM);

    for (int index = 0; index < 4; index++)
    {
        if (gSelectedOrderFromParty[index] == 0) { return 0; } // no further selected mons
        i = gSelectedOrderFromParty[index] - 1; // slot in party of previously selected pokemon
        if (i == slot) { continue; }
        
        u32 targetSpecies = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES);
        u32 targetItem = GetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM);

        switch (slotSpecies)
        {
            // mythical mons
            case SPECIES_MEWTWO:
            case SPECIES_MEW:
            case SPECIES_LUGIA:
            case SPECIES_HOOH:
            case SPECIES_CELEBI:
            case SPECIES_MELTAN:
            case SPECIES_MELMETAL:
                return 1;

            // form handling
            case SPECIES_RATTATA:
            case SPECIES_RATTATAALOLAN:
                if (targetSpecies == SPECIES_RATICATE || targetSpecies == SPECIES_RATICATEALOLAN)
                    return 1; // invalid selection
                break;
            case SPECIES_RATICATE:
            case SPECIES_RATICATEALOLAN:
                if (targetSpecies == SPECIES_RATICATE || targetSpecies == SPECIES_RATICATEALOLAN)
                    return 1; // invalid selection
                break;
            case SPECIES_RAICHU:
            case SPECIES_RAICHUALOLAN:
                if (targetSpecies == SPECIES_RAICHU || targetSpecies == SPECIES_RAICHUALOLAN)
                    return 1; // invalid selection
                break;
            case SPECIES_SANDSHREW:
            case SPECIES_SANDSHREWALOLAN:
                if (targetSpecies == SPECIES_SANDSHREW || targetSpecies == SPECIES_SANDSHREWALOLAN)
                    return 1; // invalid selection
                break;
            case SPECIES_SANDSLASH:
            case SPECIES_SANDSLASHALOLAN:
                if (targetSpecies == SPECIES_SANDSLASH || targetSpecies == SPECIES_SANDSLASHALOLAN)
                    return 1; // invalid selection
                break;
            case SPECIES_VULPIX:
            case SPECIES_VULPIXALOLAN:
                if (targetSpecies == SPECIES_VULPIX || targetSpecies == SPECIES_VULPIXALOLAN)
                    return 1; // invalid selection
                break;
            case SPECIES_NINETALES:
            case SPECIES_NINETALESALOLAN:
                if (targetSpecies == SPECIES_NINETALES || targetSpecies == SPECIES_NINETALESALOLAN)
                    return 1; // invalid selection
                break;
            case SPECIES_DIGLETT:
            case SPECIES_DIGLETTALOLAN:
                if (targetSpecies == SPECIES_DIGLETT || targetSpecies == SPECIES_DIGLETTALOLAN)
                    return 1; // invalid selection
                break;
            case SPECIES_DUGTRIO:
            case SPECIES_DUGTRIOALOLAN:
                if (targetSpecies == SPECIES_DUGTRIO || targetSpecies == SPECIES_DUGTRIOALOLAN)
                    return 1; // invalid selection
                break;
            case SPECIES_MEOWTH:
            case SPECIES_MEOWTHALOLAN:
            case SPECIES_MEOWTHGALARIAN:
                if (targetSpecies == SPECIES_MEOWTH || targetSpecies == SPECIES_MEOWTHALOLAN || targetSpecies == SPECIES_MEOWTHGALARIAN)
                    return 1; // invalid selection
                break;
            case SPECIES_PERSIAN:
            case SPECIES_PERSIANALOLAN:
                if (targetSpecies == SPECIES_PERSIAN || targetSpecies == SPECIES_PERSIANALOLAN)
                    return 1; // invalid selection
                break;
            case SPECIES_GEODUDE:
            case SPECIES_GEODUDEALOLAN:
                if (targetSpecies == SPECIES_GEODUDE || targetSpecies == SPECIES_GEODUDEALOLAN)
                    return 1; // invalid selection
                break;
            case SPECIES_GRAVELER:
            case SPECIES_GRAVELERALOLAN:
                if (targetSpecies == SPECIES_GRAVELER || targetSpecies == SPECIES_GRAVELERALOLAN)
                    return 1; // invalid selection
                break;
            case SPECIES_GOLEM:
            case SPECIES_GOLEMALOLAN:
                if (targetSpecies == SPECIES_GOLEM || targetSpecies == SPECIES_GOLEMALOLAN)
                    return 1; // invalid selection
                break;
            case SPECIES_GRIMER:
            case SPECIES_GRIMERALOLAN:
                if (targetSpecies == SPECIES_GRIMER || targetSpecies == SPECIES_GRIMERALOLAN)
                    return 1; // invalid selection
                break;
            case SPECIES_MUK:
            case SPECIES_MUKALOLAN:
                if (targetSpecies == SPECIES_MUK || targetSpecies == SPECIES_MUKALOLAN)
                    return 1; // invalid selection
                break;
            case SPECIES_EXEGGUTOR:
            case SPECIES_EXEGGUTORALOLAN:
                if (targetSpecies == SPECIES_EXEGGUTOR || targetSpecies == SPECIES_EXEGGUTORALOLAN)
                    return 1; // invalid selection
                break;
            case SPECIES_PONYTA:
            case SPECIES_PONYTAGALARIAN:
                if (targetSpecies == SPECIES_PONYTA || targetSpecies == SPECIES_PONYTAGALARIAN)
                    return 1; // invalid selection
                break;
            case SPECIES_RAPIDASH:
            case SPECIES_RAPIDASHGALARIAN:
                if (targetSpecies == SPECIES_RAPIDASH || targetSpecies == SPECIES_RAPIDASHGALARIAN)
                    return 1; // invalid selection
                break;
            case SPECIES_FARFETCHD:
            case SPECIES_FARFETCHDGALARIAN:
                if (targetSpecies == SPECIES_FARFETCHD || targetSpecies == SPECIES_FARFETCHDGALARIAN)
                    return 1; // invalid selection
                break;
            case SPECIES_WEEZING:
            case SPECIES_WEEZINGGALARIAN:
                if (targetSpecies == SPECIES_WEEZING || targetSpecies == SPECIES_WEEZINGGALARIAN)
                    return 1; // invalid selection
                break;
            case SPECIES_MRMIME:
            case SPECIES_MRMIMEGALARIAN:
                if (targetSpecies == SPECIES_MRMIME || targetSpecies == SPECIES_MRMIMEGALARIAN)
                    return 1; // invalid selection
                break;
            case SPECIES_CORSOLA:
            case SPECIES_CORSOLAGALARIAN:
                if (targetSpecies == SPECIES_CORSOLA || targetSpecies == SPECIES_CORSOLAGALARIAN)
                    return 1; // invalid selection
                break;
            case SPECIES_SLOWPOKE:
            case SPECIES_SLOWPOKEGALARIAN:
                if (targetSpecies == SPECIES_SLOWPOKE || targetSpecies == SPECIES_SLOWPOKEGALARIAN)
                    return 1; // invalid selection
                break;
            case SPECIES_SLOWBRO:
            case SPECIES_SLOWBROGALARIAN:
                if (targetSpecies == SPECIES_SLOWBRO || targetSpecies == SPECIES_SLOWBROGALARIAN)
                    return 1; // invalid selection
                break;
            case SPECIES_SLOWKING:
            case SPECIES_SLOWKINGGALARIAN:
                if (targetSpecies == SPECIES_SLOWKING || targetSpecies == SPECIES_SLOWKINGGALARIAN)
                    return 1; // invalid selection
                break;
            case SPECIES_ARTICUNO:
            case SPECIES_ARTICUNOGALARIAN:
                if (targetSpecies == SPECIES_ARTICUNO || targetSpecies == SPECIES_ARTICUNOGALARIAN)
                    return 1; // invalid selection
                break;
            case SPECIES_ZAPDOS:
            case SPECIES_ZAPDOSGALARIAN:
                if (targetSpecies == SPECIES_ZAPDOS || targetSpecies == SPECIES_ZAPDOSGALARIAN)
                    return 1; // invalid selection
                break;
            case SPECIES_GROWLITHE:
            case SPECIES_GROWLITHEHISUIAN:
                if (targetSpecies == SPECIES_GROWLITHE || targetSpecies == SPECIES_GROWLITHEHISUIAN)
                    return 1; // invalid selection
                break;
            case SPECIES_ARCANINE:
            case SPECIES_ARCANINEHISUIAN:
                if (targetSpecies == SPECIES_ARCANINE || targetSpecies == SPECIES_ARCANINEHISUIAN)
                    return 1; // invalid selection
                break;
            case SPECIES_VOLTORB:
            case SPECIES_VOLTORBHISUIAN:
                if (targetSpecies == SPECIES_VOLTORB || targetSpecies == SPECIES_VOLTORBHISUIAN)
                    return 1; // invalid selection
                break;
            case SPECIES_ELECTRODE:
            case SPECIES_ELECTRODEHISUIAN:
                if (targetSpecies == SPECIES_ELECTRODE || targetSpecies == SPECIES_ELECTRODEHISUIAN)
                    return 1; // invalid selection
                break;
            case SPECIES_TYPHLOSION:
            case SPECIES_TYPHLOSIONHISUIAN:
                if (targetSpecies == SPECIES_TYPHLOSION || targetSpecies == SPECIES_TYPHLOSIONHISUIAN)
                    return 1; // invalid selection
                break;
            case SPECIES_QWILFISH:
            case SPECIES_QWILFISHHISUIAN:
                if (targetSpecies == SPECIES_QWILFISH || targetSpecies == SPECIES_QWILFISHHISUIAN)
                    return 1; // invalid selection
                break;
            case SPECIES_SNEASEL:
            case SPECIES_SNEASELHISUIAN:
                if (targetSpecies == SPECIES_SNEASEL || targetSpecies == SPECIES_SNEASELHISUIAN)
                    return 1; // invalid selection
                break;
            case SPECIES_WOOPER:
            case SPECIES_WOOPERPALDEAN:
                if (targetSpecies == SPECIES_WOOPER || targetSpecies == SPECIES_WOOPERPALDEAN)
                    return 1; // invalid selection
                break;
            case SPECIES_TAUROS:
            case SPECIES_TAUROSPALDEAN1:
            case SPECIES_TAUROSPALDEAN2:
            case SPECIES_TAUROSPALDEAN3:
                if (targetSpecies == SPECIES_TAUROS || targetSpecies == SPECIES_TAUROSPALDEAN1 || targetSpecies == SPECIES_TAUROSPALDEAN2 || targetSpecies == SPECIES_TAUROSPALDEAN3)
                    return 1; // invalid selection
                break;
            default:
                if (targetSpecies == slotSpecies)
                    return 1; // invalid selection
                break;
        }        

        if (targetItem && targetItem == slotItem) { return 2; } // 2 mons can't hold the same item
    }
    
    return 0;
}



u32 AreTwoTargetSpeciesIncompatible(u32 slotSpecies, u32 targetSpecies)
{
    switch (slotSpecies)
    {
        // mythical mons
        case SPECIES_MEWTWO:
        case SPECIES_MEW:
        case SPECIES_LUGIA:
        case SPECIES_HOOH:
        case SPECIES_CELEBI:
        case SPECIES_MELTAN:
        case SPECIES_MELMETAL:
            return 1;

        // form handling
        case SPECIES_RATTATA:
        case SPECIES_RATTATAALOLAN:
            if (targetSpecies == SPECIES_RATICATE || targetSpecies == SPECIES_RATICATEALOLAN)
                return 1; // invalid selection
            break;
        case SPECIES_RATICATE:
        case SPECIES_RATICATEALOLAN:
            if (targetSpecies == SPECIES_RATICATE || targetSpecies == SPECIES_RATICATEALOLAN)
                return 1; // invalid selection
            break;
        case SPECIES_RAICHU:
        case SPECIES_RAICHUALOLAN:
            if (targetSpecies == SPECIES_RAICHU || targetSpecies == SPECIES_RAICHUALOLAN)
                return 1; // invalid selection
            break;
        case SPECIES_SANDSHREW:
        case SPECIES_SANDSHREWALOLAN:
            if (targetSpecies == SPECIES_SANDSHREW || targetSpecies == SPECIES_SANDSHREWALOLAN)
                return 1; // invalid selection
            break;
        case SPECIES_SANDSLASH:
        case SPECIES_SANDSLASHALOLAN:
            if (targetSpecies == SPECIES_SANDSLASH || targetSpecies == SPECIES_SANDSLASHALOLAN)
                return 1; // invalid selection
            break;
        case SPECIES_VULPIX:
        case SPECIES_VULPIXALOLAN:
            if (targetSpecies == SPECIES_VULPIX || targetSpecies == SPECIES_VULPIXALOLAN)
                return 1; // invalid selection
            break;
        case SPECIES_NINETALES:
        case SPECIES_NINETALESALOLAN:
            if (targetSpecies == SPECIES_NINETALES || targetSpecies == SPECIES_NINETALESALOLAN)
                return 1; // invalid selection
            break;
        case SPECIES_DIGLETT:
        case SPECIES_DIGLETTALOLAN:
            if (targetSpecies == SPECIES_DIGLETT || targetSpecies == SPECIES_DIGLETTALOLAN)
                return 1; // invalid selection
            break;
        case SPECIES_DUGTRIO:
        case SPECIES_DUGTRIOALOLAN:
            if (targetSpecies == SPECIES_DUGTRIO || targetSpecies == SPECIES_DUGTRIOALOLAN)
                return 1; // invalid selection
            break;
        case SPECIES_MEOWTH:
        case SPECIES_MEOWTHALOLAN:
        case SPECIES_MEOWTHGALARIAN:
            if (targetSpecies == SPECIES_MEOWTH || targetSpecies == SPECIES_MEOWTHALOLAN || targetSpecies == SPECIES_MEOWTHGALARIAN)
                return 1; // invalid selection
            break;
        case SPECIES_PERSIAN:
        case SPECIES_PERSIANALOLAN:
            if (targetSpecies == SPECIES_PERSIAN || targetSpecies == SPECIES_PERSIANALOLAN)
                return 1; // invalid selection
            break;
        case SPECIES_GEODUDE:
        case SPECIES_GEODUDEALOLAN:
            if (targetSpecies == SPECIES_GEODUDE || targetSpecies == SPECIES_GEODUDEALOLAN)
                return 1; // invalid selection
            break;
        case SPECIES_GRAVELER:
        case SPECIES_GRAVELERALOLAN:
            if (targetSpecies == SPECIES_GRAVELER || targetSpecies == SPECIES_GRAVELERALOLAN)
                return 1; // invalid selection
            break;
        case SPECIES_GOLEM:
        case SPECIES_GOLEMALOLAN:
            if (targetSpecies == SPECIES_GOLEM || targetSpecies == SPECIES_GOLEMALOLAN)
                return 1; // invalid selection
            break;
        case SPECIES_GRIMER:
        case SPECIES_GRIMERALOLAN:
            if (targetSpecies == SPECIES_GRIMER || targetSpecies == SPECIES_GRIMERALOLAN)
                return 1; // invalid selection
            break;
        case SPECIES_MUK:
        case SPECIES_MUKALOLAN:
            if (targetSpecies == SPECIES_MUK || targetSpecies == SPECIES_MUKALOLAN)
                return 1; // invalid selection
            break;
        case SPECIES_EXEGGUTOR:
        case SPECIES_EXEGGUTORALOLAN:
            if (targetSpecies == SPECIES_EXEGGUTOR || targetSpecies == SPECIES_EXEGGUTORALOLAN)
                return 1; // invalid selection
            break;
        case SPECIES_PONYTA:
        case SPECIES_PONYTAGALARIAN:
            if (targetSpecies == SPECIES_PONYTA || targetSpecies == SPECIES_PONYTAGALARIAN)
                return 1; // invalid selection
            break;
        case SPECIES_RAPIDASH:
        case SPECIES_RAPIDASHGALARIAN:
            if (targetSpecies == SPECIES_RAPIDASH || targetSpecies == SPECIES_RAPIDASHGALARIAN)
                return 1; // invalid selection
            break;
        case SPECIES_FARFETCHD:
        case SPECIES_FARFETCHDGALARIAN:
            if (targetSpecies == SPECIES_FARFETCHD || targetSpecies == SPECIES_FARFETCHDGALARIAN)
                return 1; // invalid selection
            break;
        case SPECIES_WEEZING:
        case SPECIES_WEEZINGGALARIAN:
            if (targetSpecies == SPECIES_WEEZING || targetSpecies == SPECIES_WEEZINGGALARIAN)
                return 1; // invalid selection
            break;
        case SPECIES_MRMIME:
        case SPECIES_MRMIMEGALARIAN:
            if (targetSpecies == SPECIES_MRMIME || targetSpecies == SPECIES_MRMIMEGALARIAN)
                return 1; // invalid selection
            break;
        case SPECIES_CORSOLA:
        case SPECIES_CORSOLAGALARIAN:
            if (targetSpecies == SPECIES_CORSOLA || targetSpecies == SPECIES_CORSOLAGALARIAN)
                return 1; // invalid selection
            break;
        case SPECIES_SLOWPOKE:
        case SPECIES_SLOWPOKEGALARIAN:
            if (targetSpecies == SPECIES_SLOWPOKE || targetSpecies == SPECIES_SLOWPOKEGALARIAN)
                return 1; // invalid selection
            break;
        case SPECIES_SLOWBRO:
        case SPECIES_SLOWBROGALARIAN:
            if (targetSpecies == SPECIES_SLOWBRO || targetSpecies == SPECIES_SLOWBROGALARIAN)
                return 1; // invalid selection
            break;
        case SPECIES_SLOWKING:
        case SPECIES_SLOWKINGGALARIAN:
            if (targetSpecies == SPECIES_SLOWKING || targetSpecies == SPECIES_SLOWKINGGALARIAN)
                return 1; // invalid selection
            break;
        case SPECIES_ARTICUNO:
        case SPECIES_ARTICUNOGALARIAN:
            if (targetSpecies == SPECIES_ARTICUNO || targetSpecies == SPECIES_ARTICUNOGALARIAN)
                return 1; // invalid selection
            break;
        case SPECIES_ZAPDOS:
        case SPECIES_ZAPDOSGALARIAN:
            if (targetSpecies == SPECIES_ZAPDOS || targetSpecies == SPECIES_ZAPDOSGALARIAN)
                return 1; // invalid selection
            break;
        case SPECIES_GROWLITHE:
        case SPECIES_GROWLITHEHISUIAN:
            if (targetSpecies == SPECIES_GROWLITHE || targetSpecies == SPECIES_GROWLITHEHISUIAN)
                return 1; // invalid selection
            break;
        case SPECIES_ARCANINE:
        case SPECIES_ARCANINEHISUIAN:
            if (targetSpecies == SPECIES_ARCANINE || targetSpecies == SPECIES_ARCANINEHISUIAN)
                return 1; // invalid selection
            break;
        case SPECIES_VOLTORB:
        case SPECIES_VOLTORBHISUIAN:
            if (targetSpecies == SPECIES_VOLTORB || targetSpecies == SPECIES_VOLTORBHISUIAN)
                return 1; // invalid selection
            break;
        case SPECIES_ELECTRODE:
        case SPECIES_ELECTRODEHISUIAN:
            if (targetSpecies == SPECIES_ELECTRODE || targetSpecies == SPECIES_ELECTRODEHISUIAN)
                return 1; // invalid selection
            break;
        case SPECIES_TYPHLOSION:
        case SPECIES_TYPHLOSIONHISUIAN:
            if (targetSpecies == SPECIES_TYPHLOSION || targetSpecies == SPECIES_TYPHLOSIONHISUIAN)
                return 1; // invalid selection
            break;
        case SPECIES_QWILFISH:
        case SPECIES_QWILFISHHISUIAN:
            if (targetSpecies == SPECIES_QWILFISH || targetSpecies == SPECIES_QWILFISHHISUIAN)
                return 1; // invalid selection
            break;
        case SPECIES_SNEASEL:
        case SPECIES_SNEASELHISUIAN:
            if (targetSpecies == SPECIES_SNEASEL || targetSpecies == SPECIES_SNEASELHISUIAN)
                return 1; // invalid selection
            break;
        case SPECIES_WOOPER:
        case SPECIES_WOOPERPALDEAN:
            if (targetSpecies == SPECIES_WOOPER || targetSpecies == SPECIES_WOOPERPALDEAN)
                return 1; // invalid selection
            break;
        case SPECIES_TAUROS:
        case SPECIES_TAUROSPALDEAN1:
        case SPECIES_TAUROSPALDEAN2:
        case SPECIES_TAUROSPALDEAN3:
            if (targetSpecies == SPECIES_TAUROS || targetSpecies == SPECIES_TAUROSPALDEAN1 || targetSpecies == SPECIES_TAUROSPALDEAN2 || targetSpecies == SPECIES_TAUROSPALDEAN3)
                return 1; // invalid selection
            break;
        default:
            if (targetSpecies == slotSpecies)
                return 1; // invalid selection
            break;
    }
    
    return 0;
}



u32 MonNotAlreadySelected(u8 slot)
{
    int i;
    
    slot++;
    
    for (i = 0; i < 4; i++)
    {
        if (gSelectedOrderFromParty[i] == slot)
            return FALSE;
    }
    
    return TRUE;
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
        else if (VarGet(VAR_BATTLE_TOWER_TYPE) >= BATTLE_TOWER_TYPE_MULTI_EASY)
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


#define gSpecialVar_0x8004 (*(u16 *)0x020370c0)
#define gStringVarDefeatText ((u8 *)0x0203FF40)


void ShowEasyChatMessage(void)
{
    u16 *easyChatWords;
    u16 easyChatWordsAlt[6];
    int columns, rows;
    int dontShowMessage = 0, printToOtherArea = 0;
    switch (gSpecialVar_0x8004)
    {
    case 0:
        easyChatWords = gSaveBlock1->easyChatProfile;
        columns = 2;
        rows = 2;
        break;
    case 1:
        easyChatWords = gSaveBlock1->easyChatBattleStart;
        if (EC_DoesEasyChatStringFitOnLine(gSaveBlock1->easyChatBattleStart, 3, 2, 18))
        {
            columns = 2;
            rows = 3;
        }
        else
        {
            columns = 3;
            rows = 2;
        }
        break;
    case 2:
        easyChatWords = gSaveBlock1->easyChatBattleWon;
        columns = 3;
        rows = 2;
        break;
    case 3:
        easyChatWords = gSaveBlock1->easyChatBattleLost;
        columns = 3;
        rows = 2;
        break;
    case 4: // pre battle
        easyChatWordsAlt[0] = ((EC_GROUP_GREETINGS << 9) | Random() % EC_NUM_OF_GREETINGS);
        easyChatWordsAlt[1] = ((EC_GROUP_POKEMON << 9) | Random() % 252) + 1; // random mon 1-252
        easyChatWordsAlt[2] = ((EC_GROUP_ACTIONS << 9) | Random() % EC_NUM_OF_ACTIONS);
        easyChatWordsAlt[3] = ((EC_GROUP_BATTLE << 9) | Random() % EC_NUM_OF_BATTLE);
        easyChatWordsAlt[4] = ((EC_GROUP_ENDINGS << 9) | Random() % EC_NUM_OF_ENDINGS);
        easyChatWordsAlt[5] = ((EC_GROUP_STATUS << 9) | Random() % EC_NUM_OF_STATUS);
        columns = 3;
        rows = 2;
        dontShowMessage = 1;
        break;
    case 5: // defeat text
        easyChatWordsAlt[0] = ((EC_GROUP_VOICES << 9) | Random() % EC_NUM_VOICES);
        easyChatWordsAlt[1] = ((EC_GROUP_BATTLE << 9) | Random() % EC_NUM_OF_BATTLE);
        easyChatWordsAlt[2] = ((EC_GROUP_SPEECH << 9) | Random() % EC_NUM_OF_SPEECH);
        easyChatWordsAlt[3] = ((EC_GROUP_GREETINGS << 9) | Random() % EC_NUM_OF_GREETINGS);
        easyChatWordsAlt[4] = ((EC_GROUP_POKEMON << 9) | Random() % 252) + 1;
        easyChatWordsAlt[5] = ((EC_GROUP_ACTIONS << 9) | Random() % EC_NUM_OF_ACTIONS);
        columns = 3;
        rows = 2;
        dontShowMessage = 1;
        printToOtherArea = 1;
        break;
    default:
        return;
    }

    ConvertEasyChatWordsToString(printToOtherArea == 0 ? gStringVar4 : gStringVarDefeatText, dontShowMessage == 1 ? &easyChatWordsAlt[0] : easyChatWords, columns, rows);
    if (!dontShowMessage)
        ShowFieldAutoScrollMessage(gStringVar4);
}




struct BattleTowerTrainerClass
{
    u8 class;
    u8 gender;
    u8 picture;
    u8 owId;
}; // size = 0x4


struct TrainerBattleStructure
{
    u8 partyFlags;
    u8 trainerClass;
    u8 encounterMusic_Gender;
    u8 trainerPic;
    u8 trainername[12];
    u16 items[4];
    u32 doubleBattle;
    u32 aiFlags;
    u32 partySize;
    void *party;
}; // size = 0x28


struct BattleTowerTrainerSets
{
    u16 index; // technically iv but we overwrite it
    u16 level;
    u16 species;
    u16 item;
    u16 moves[4];
}; // size = 0x10



extern struct TrainerBattleStructure TowerData;
extern struct BattleTowerTrainerSets TowerPokemonParty[];

extern struct BattleTowerTrainerSets PokemonTableStartEasyMode[];
extern struct BattleTowerTrainerSets PokemonTableStartHardMode[];
extern struct BattleTowerTrainerSets PalmerMons[];


extern struct BattleTowerTrainerClass ClassTableStart[32]; // 32 total trainer classes
extern u8 NamesStart[][5][12]; // indexed by classIndex




void CreateBattleTowerTrainerParty()
{
    int i;
    u8 palmerOrder[4] = {0,0,0,0};
    
    // step 1 - create trainer entry in RAM
    
    u32 classIndex = VarGet(VAR_BATTLE_TOWER_OBJ_ID);
    u32 trainerGender = ClassTableStart[classIndex].gender;
    u32 nameIndex = Random() % 5;

    for (i = 0; i < 32; i++)
    {
        if (ClassTableStart[i].owId == classIndex)
        {
            classIndex = i;
            break;
        }
    }

    TowerData.partyFlags = 3; // custom moves + items
    TowerData.trainerClass = ClassTableStart[classIndex].class;
    TowerData.encounterMusic_Gender = trainerGender;
    TowerData.trainerPic = ClassTableStart[classIndex].picture;
    
    for (i = 0; i < 12; i++)
    {
        TowerData.trainername[i] = NamesStart[classIndex][nameIndex][i]; // interesting
    }
    
    for (i = 0; i < 4; i++)
    {
        TowerData.items[i] = 0;
    }
    
    if (VarGet(VAR_BATTLE_TOWER_TYPE) >= BATTLE_TOWER_TYPE_DOUBLE_EASY)
    {
        TowerData.doubleBattle = 1;
        TowerData.aiFlags = 0xBF; // don't attack your doubles partner
        TowerData.partySize = 4;
    }
    else
    {
        TowerData.doubleBattle = 0;
        TowerData.aiFlags = 0x3F;
        TowerData.partySize = 3;
    }
    
    TowerData.party = TowerPokemonParty;
    
    u32 baseIndex;

    if (classIndex == 31) // palmer
    {
        u32 roundTwo = 0;
        u32 maxRange = (TowerData.doubleBattle != 0 ? 4 : 3);
        
        if (VarGet(VAR_BATTLE_TOWER_TYPE) == BATTLE_TOWER_TYPE_SINGLE_HARD && VarGet(0x43ce) > 40) // streak over 35 means round two, doesn't appear until 70 though
            roundTwo = 1;
        else if (VarGet(VAR_BATTLE_TOWER_TYPE) == BATTLE_TOWER_TYPE_DOUBLE_HARD && VarGet(0x43d2) > 40)
            roundTwo = 1;
        
        if (!roundTwo)
        {
            if (!TowerData.doubleBattle)
            {
                baseIndex = 0+800;
            }
            else
            {
                baseIndex = 3+800;
            }
        }
        else
        {
            if (!TowerData.doubleBattle)
            {
                baseIndex = 7+800;
            }
            else
            {
                baseIndex = 10+800;
            }
        }
        
        
        for (i = 0; i < maxRange; i++)
        {
            int j;
            u32 foundSlot = 0;
            u8 newNum;
            while (foundSlot == 0)
            {
                foundSlot = 0;
                newNum = Random() % maxRange;
                for (j = 0; j < i; j++)
                {
                    if (palmerOrder[j] == newNum)
                    {
                        break;
                    }
                }
                if (j == i)
                {
                    palmerOrder[i] = newNum;
                    foundSlot = 1;
                }
            }
        }
    }
    
    // step 2 - create party in RAM
    for (i = 0; i < TowerData.partySize; i++)
    {
        u32 easyMode = (VarGet(VAR_BATTLE_TOWER_TYPE) != 0 && VarGet(VAR_BATTLE_TOWER_TYPE) & 1);
        
        if (classIndex == 31) // palmer
        {
            TowerPokemonParty[i] = PokemonTableStartHardMode[baseIndex + palmerOrder[i]]; // palmer specific mons are >800
        }
        else if (easyMode)
        {
            u32 randIndex;
            _reChooseEasyIndex:
            randIndex = Random() % NUM_OF_EASY_MODE_SPREADS;
            TowerPokemonParty[i] = PokemonTableStartEasyMode[randIndex];
            
            for (int j = 0; j < i; j++) // make sure that no two species are the same
            {
                if (AreTwoTargetSpeciesIncompatible(TowerPokemonParty[j].species, TowerPokemonParty[i].species)
                 || TowerPokemonParty[j].item == TowerPokemonParty[i].item)
                {
                    goto _reChooseEasyIndex;
                }
            }
        }
        else
        {
            u32 randIndex;
            _reChooseHardIndex:
            randIndex = Random() % NUM_OF_HARD_MODE_SPREADS;
            TowerPokemonParty[i] = PokemonTableStartHardMode[randIndex];
            
            for (int j = 0; j < i; j++) // make sure that no two species are the same
            {
                if (AreTwoTargetSpeciesIncompatible(TowerPokemonParty[j].species, TowerPokemonParty[i].species)
                 || TowerPokemonParty[j].item == TowerPokemonParty[i].item)
                {
                    goto _reChooseHardIndex;
                }
            }
        }
    }
}


extern u8 gText_BattleTowerStreaks[];
extern u8 gText_BattlePointsColon[];
extern u8 gText_CurrentRecord[];
extern u8 gText_SingleSimple[];
extern u8 gText_SingleChallenge[];
extern u8 gText_DoubleSimple[];
extern u8 gText_DoubleChallenge[];
extern u8 gText_BattlePoints[];
extern u8 gText_BP[];


void PrintBattleRecords(void)
{
    u32 left;
    s32 i;

    FillWindowPixelRect(0, /*PIXEL_FILL(0)*/0, 0, 0, 0xD8, 0x90);
    
    if (FlagGet(0x2322) != 0)
    {
        u8 buf[4];
        u32 gString4Pos;

        // print "Battle Tower Streaks"
        StringExpandPlaceholders(gStringVar4, gText_BattleTowerStreaks);
        left = 0xD0 - GetStringWidth(FONT_NORMAL, gStringVar4, -1);
        AddTextPrinterParameterized4(0, FONT_NORMAL, left / 2, 4, 0, 2, (void*)0x081a7C4d, 0, gStringVar4);
        
        // print "Battle Points: NNNNN"
        StringExpandPlaceholders(gStringVar4, gText_BattlePointsColon);
        gString4Pos = 15;
        ConvertIntToDecimalStringN(&gStringVar4[gString4Pos], VarGet(0x43df), 0, 5); // battle points
        left = 0xD0 - GetStringWidth(FONT_NORMAL, gStringVar4, -1);
        AddTextPrinterParameterized4(0, FONT_NORMAL, left / 2, 20, 0, 2, (void*)0x081a7C4d, 0, gStringVar4);
        
#define BASE_RECORDS_Y 50
        // print "Current     Record"
        StringExpandPlaceholders(gStringVar4, gText_CurrentRecord);
        AddTextPrinterParameterized4(0, FONT_NORMAL, 0x68, BASE_RECORDS_Y, 0, 2, (void*)0x081a7C4d, 0, gStringVar4);

        // print "Single (Simple) and friends"
        StringExpandPlaceholders(gStringVar4, gText_SingleSimple);
        AddTextPrinterParameterized4(0, FONT_NORMAL, 0, BASE_RECORDS_Y+16, 0, 2, (void*)0x081a7C4d, 0, gStringVar4);
        StringExpandPlaceholders(gStringVar4, gText_SingleChallenge);
        AddTextPrinterParameterized4(0, FONT_NORMAL, 0, BASE_RECORDS_Y+2*16, 0, 2, (void*)0x081a7C4d, 0, gStringVar4);
        StringExpandPlaceholders(gStringVar4, gText_DoubleSimple);
        AddTextPrinterParameterized4(0, FONT_NORMAL, 0, BASE_RECORDS_Y+3*16, 0, 2, (void*)0x081a7C4d, 0, gStringVar4);
        StringExpandPlaceholders(gStringVar4, gText_DoubleChallenge);
        AddTextPrinterParameterized4(0, FONT_NORMAL, 0, BASE_RECORDS_Y+4*16, 0, 2, (void*)0x081a7C4d, 0, gStringVar4);
        
        // print Numbers for streaks
        StringExpandPlaceholders(gStringVar4, gText_BattlePointsColon);
        gString4Pos = 0;
        ConvertIntToDecimalStringN(&gStringVar4[gString4Pos], VarGet(0x43cc), 1, 5); // single simple current
        left = 0x8E - GetStringWidth(FONT_NORMAL, gStringVar4, -1);
        AddTextPrinterParameterized4(0, FONT_NORMAL, left, BASE_RECORDS_Y+16, 0, 2, (void*)0x081a7C4d, 0, gStringVar4);

        gString4Pos = 0;
        ConvertIntToDecimalStringN(&gStringVar4[gString4Pos], VarGet(0x43cd), 1, 5); // single simple record
        left = 0x8E + 0x35 - GetStringWidth(FONT_NORMAL, gStringVar4, -1);
        AddTextPrinterParameterized4(0, FONT_NORMAL, left, BASE_RECORDS_Y+16, 0, 2, (void*)0x081a7C4d, 0, gStringVar4);

        gString4Pos = 0;
        ConvertIntToDecimalStringN(&gStringVar4[gString4Pos], VarGet(0x43ce), 1, 5); // single challenge current
        left = 0x8E - GetStringWidth(FONT_NORMAL, gStringVar4, -1);
        AddTextPrinterParameterized4(0, FONT_NORMAL, left, BASE_RECORDS_Y+2*16, 0, 2, (void*)0x081a7C4d, 0, gStringVar4);

        gString4Pos = 0;
        ConvertIntToDecimalStringN(&gStringVar4[gString4Pos], VarGet(0x43cf), 1, 5); // single challenge record
        left = 0x8E + 0x35 - GetStringWidth(FONT_NORMAL, gStringVar4, -1);
        AddTextPrinterParameterized4(0, FONT_NORMAL, left, BASE_RECORDS_Y+2*16, 0, 2, (void*)0x081a7C4d, 0, gStringVar4);

        gString4Pos = 0;
        ConvertIntToDecimalStringN(&gStringVar4[gString4Pos], VarGet(0x43d0), 1, 5); // double simple current
        left = 0x8E - GetStringWidth(FONT_NORMAL, gStringVar4, -1);
        AddTextPrinterParameterized4(0, FONT_NORMAL, left, BASE_RECORDS_Y+3*16, 0, 2, (void*)0x081a7C4d, 0, gStringVar4);

        gString4Pos = 0;
        ConvertIntToDecimalStringN(&gStringVar4[gString4Pos], VarGet(0x43d1), 1, 5); // double simple record
        left = 0x8E + 0x35 - GetStringWidth(FONT_NORMAL, gStringVar4, -1);
        AddTextPrinterParameterized4(0, FONT_NORMAL, left, BASE_RECORDS_Y+3*16, 0, 2, (void*)0x081a7C4d, 0, gStringVar4);

        gString4Pos = 0;
        ConvertIntToDecimalStringN(&gStringVar4[gString4Pos], VarGet(0x43d2), 1, 5); // double challenge current
        left = 0x8E - GetStringWidth(FONT_NORMAL, gStringVar4, -1);
        AddTextPrinterParameterized4(0, FONT_NORMAL, left, BASE_RECORDS_Y+4*16, 0, 2, (void*)0x081a7C4d, 0, gStringVar4);

        gString4Pos = 0;
        ConvertIntToDecimalStringN(&gStringVar4[gString4Pos], VarGet(0x43d3), 1, 5); // double challenge record
        left = 0x8E + 0x35 - GetStringWidth(FONT_NORMAL, gStringVar4, -1);
        AddTextPrinterParameterized4(0, FONT_NORMAL, left, BASE_RECORDS_Y+4*16, 0, 2, (void*)0x081a7C4d, 0, gStringVar4);
    }
    else
    {
        StringExpandPlaceholders(gStringVar4, (void*)0x08418174);
        left = 0xD0 - GetStringWidth(FONT_NORMAL, gStringVar4, -1);
        AddTextPrinterParameterized4(0, FONT_NORMAL, left / 2, 4, 0, 2, (void*)0x081a7C4d, 0, gStringVar4);
        PrintTotalRecord(&gSaveBlock2->linkBattleRecords);
        AddTextPrinterParameterized4(0, FONT_NORMAL, 0x54, 0x30, 0, 2, (void*)0x081a7C4d, 0, (void*)0x084181a4);
        for (i = 0; i < 5; i++)
            PrintOpponentBattleRecord(&gSaveBlock2->linkBattleRecords.entries[i], 0x3D + 14 * i);
    }
    CommitWindow(0);
}


// BP windows should just be handleable by this
void PrintMoneyAmountInMoneyBox(u8 windowId, int amount, u8 speed)
{
    u8 *txtPtr;
    s32 strLength;

    if (FlagGet(0x2322))
        amount = VarGet(0x43df);
    
    ConvertIntToDecimalStringN(gStringVar1, amount, 1, 6);
    strLength = 6 - StringLength(gStringVar1);

    if (FlagGet(0x2322))
    {
        //StringExpandPlaceholders(&gStringVar4[strLength+1], gText_BP);
        //gStringVar4[strLength] = 0xBC;
        //gStringVar4[strLength+1] = 0xCA;
        AddTextPrinterParameterized(windowId, FONT_SMALL, gStringVar1, 64 - GetStringWidth(FONT_SMALL, gStringVar1, 0), 0xC, speed, NULL);
    }
    else
    {
        txtPtr = gStringVar4;

        while (strLength-- != 0)
            *(txtPtr++) = 0;

        StringExpandPlaceholders(txtPtr, 0x0841697a);
        AddTextPrinterParameterized(windowId, FONT_SMALL, gStringVar4, 64 - GetStringWidth(FONT_SMALL, gStringVar4, 0), 0xC, speed, NULL);
    }
}

void PrintMoneyAmountInMoneyBoxWithBorder(u8 windowId, u16 tileStart, u8 pallete)
{
    u32 amount;
    
    DrawStdFrameWithCustomTileAndPalette(windowId, FALSE, tileStart, pallete);
    if (FlagGet(0x2322))
    {
        amount = VarGet(0x43df);
        AddTextPrinterParameterized(windowId, FONT_NORMAL, gText_BattlePoints, 0, 0, 0xFF, 0);
    }
    else
    {
        amount = GetMoney(&gSaveBlock1->money);
        AddTextPrinterParameterized(windowId, FONT_NORMAL, 0x08419ce7, 0, 0, 0xFF, 0);
    }
    PrintMoneyAmountInMoneyBox(windowId, amount, 0);
}

#include "../include/gba/defines.h"
#include "../include/gba/types.h"
#include "../include/constants/songs.h"
#include "../include/constants/species.h"
#include "../include/pokemon.h"
#include "../include/main.h"

// see if implicit declarations just work anyway

struct Roamer
{
    u32 pid;
    u32 status;
    u16 hp;
    u16 inited:1;
    u16 maxHP:15;
};

void CB2_EndWildBattle();
void CB2_EndScriptedWildBattle();
#define BATTLE_TYPE_ROAMER (1 << 10)
#define BATTLE_TYPE_LEGENDARY (1 << 13)
#define BATTLE_TYPE_WILD_SCRIPTED (1 << 17)
#define BATTLE_TYPE_LEGENDARY_FRLG (1 << 18)
#define GAME_STAT_TOTAL_BATTLES              7
#define GAME_STAT_WILD_BATTLES               8
u32 gBattleTypeFlags;

void StartLegendaryBattle(void)
{
    u16 species;
    u32 roamer = 0xFF;
    struct Roamer *roamerDataInVars = GetVarPointer(0x43C6); // roamer var start

    ScriptContext2_Enable();
    gMain.savedCallback = CB2_EndScriptedWildBattle;
    gBattleTypeFlags = BATTLE_TYPE_LEGENDARY | BATTLE_TYPE_LEGENDARY_FRLG;
    species = GetMonData(&gEnemyParty[0], MON_DATA_SPECIES);
    switch (species)
    {
    case SPECIES_MEWTWO:
        CreateBattleStartTask(0, MUS_VS_MEWTWO);
        break;
    case SPECIES_DEOXYS:
        CreateBattleStartTask(0, MUS_VS_DEOXYS);
        break;
    case SPECIES_MOLTRES:
    case SPECIES_ARTICUNO:
    case SPECIES_ZAPDOS:
    case SPECIES_HO_OH:
    case SPECIES_LUGIA:
        CreateBattleStartTask(0, MUS_VS_LEGEND);
        break;
    default:
        CreateBattleStartTask(0, MUS_RS_VS_TRAINER);
        break;
    }



    switch (species)
    {
    case SPECIES_ENTEI:
        roamer = 0;
        break;
    case SPECIES_RAIKOU:
        roamer = 1;
        break;
    case SPECIES_LATIOS:
        if (FlagGet(0x2312))
            roamer = 2;
        else
            roamer = 0xFF;
        break;
    case SPECIES_LATIAS:
        if (!FlagGet(0x2312))
            roamer = 2;
        else
            roamer = 0xFF;
        break;
    }
    if (roamer != 0xFF)
    {
        u32 temp;
        gBattleTypeFlags |= BATTLE_TYPE_ROAMER;
        
        if (roamerDataInVars[roamer].inited)
        {
            temp = roamerDataInVars[roamer].hp;
            SetMonData(&gEnemyParty[0], MON_DATA_HP, &temp);
            temp = roamerDataInVars[roamer].maxHP;
            SetMonData(&gEnemyParty[0], MON_DATA_MAX_HP, &temp);
            temp = roamerDataInVars[roamer].pid;
            SetMonData(&gEnemyParty[0], MON_DATA_PERSONALITY, &temp);
            temp = roamerDataInVars[roamer].status;
            SetMonData(&gEnemyParty[0], MON_DATA_STATUS, &temp);
        }
        else
        {
            roamerDataInVars[roamer].inited = TRUE;

            roamerDataInVars[roamer].hp = GetMonData(&gEnemyParty[0], MON_DATA_HP, NULL);
            roamerDataInVars[roamer].maxHP = GetMonData(&gEnemyParty[0], MON_DATA_MAX_HP, NULL);
            roamerDataInVars[roamer].pid = GetMonData(&gEnemyParty[0], MON_DATA_PERSONALITY, NULL);
            roamerDataInVars[roamer].status = GetMonData(&gEnemyParty[0], MON_DATA_STATUS, NULL);
        }
    }
    else
    {
        gBattleTypeFlags = 0;
        gBattleTypeFlags |= BATTLE_TYPE_WILD_SCRIPTED;
    }



    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
}

void UpdateRoamerHPStatus(struct Pokemon *mon)
{
    // completely strip this because we no longer need it
    //ROAMER->hp = GetMonData(mon, MON_DATA_HP);
    //ROAMER->status = GetMonData(mon, MON_DATA_STATUS);
    //
    //RoamerMoveToOtherLocationSet();
    
    u16 species = GetMonData(mon, MON_DATA_SPECIES);;
    u32 roamer = 0xFF;
    struct Roamer *roamerDataInVars = GetVarPointer(0x43C6); // roamer var start
    switch (species)
    {
    case SPECIES_ENTEI:
        roamer = 0;
        break;
    case SPECIES_RAIKOU:
        roamer = 1;
        break;
    case SPECIES_LATIOS:
        if (FlagGet(0x2312))
            roamer = 2;
        else
            roamer = 0xFF;
        break;
    case SPECIES_LATIAS:
        if (!FlagGet(0x2312))
            roamer = 2;
        else
            roamer = 0xFF;
        break;
    }


    if (roamerDataInVars[roamer].inited)
    {
        u32 temp;
        temp = roamerDataInVars[roamer].hp;
        SetMonData(&gEnemyParty[0], MON_DATA_HP, &temp);
        temp = roamerDataInVars[roamer].maxHP;
        SetMonData(&gEnemyParty[0], MON_DATA_MAX_HP, &temp);
        temp = roamerDataInVars[roamer].pid;
        SetMonData(&gEnemyParty[0], MON_DATA_PERSONALITY, &temp);
        temp = roamerDataInVars[roamer].status;
        SetMonData(&gEnemyParty[0], MON_DATA_STATUS, &temp);
    }
    else
    {
        roamerDataInVars[roamer].inited = TRUE;

        roamerDataInVars[roamer].hp = GetMonData(mon, MON_DATA_HP, NULL);
        roamerDataInVars[roamer].maxHP = GetMonData(mon, MON_DATA_MAX_HP, NULL);
        roamerDataInVars[roamer].pid = GetMonData(mon, MON_DATA_PERSONALITY, NULL);
        roamerDataInVars[roamer].status = GetMonData(mon, MON_DATA_STATUS, NULL);
    }
}

//void DoStandardWildBattle(void)
//{
//    u16 species;
//    u32 roamer = 0xFF;
//    struct Roamer *roamerDataInVars = GetVarPointer(0x43C6); // roamer var start
//
//    ScriptContext2_Enable();
//    FreezeObjectEvents();
//    StopPlayerAvatar();
//    gMain.savedCallback = CB2_EndWildBattle;
//
//    species = GetMonData(&gEnemyParty[0], MON_DATA_SPECIES);
//    switch (species)
//    {
//    case SPECIES_ENTEI:
//        roamer = 0;
//        break;
//    case SPECIES_RAIKOU:
//        roamer = 1;
//        break;
//    case SPECIES_LATIOS:
//        if (FlagGet(0x2312))
//            roamer = 2;
//        else
//            roamer = 0xFF;
//        break;
//    case SPECIES_LATIAS:
//        if (!FlagGet(0x2312))
//            roamer = 2;
//        else
//            roamer = 0xFF;
//        break;
//    }
//    if (roamer != 0xFF)
//    {
//        u32 temp;
//        gBattleTypeFlags = BATTLE_TYPE_ROAMER;
//        
//        if (roamerDataInVars[roamer].inited)
//        {
//            roamerDataInVars[roamer].inited = TRUE;
//
//            temp = roamerDataInVars[roamer].hp;
//            SetMonData(&gEnemyParty[roamer], MON_DATA_HP, &temp);
//            temp = roamerDataInVars[roamer].maxHP;
//            SetMonData(&gEnemyParty[roamer], MON_DATA_MAX_HP, &temp);
//            temp = roamerDataInVars[roamer].pid;
//            SetMonData(&gEnemyParty[roamer], MON_DATA_PERSONALITY, &temp);
//            temp = roamerDataInVars[roamer].status;
//            SetMonData(&gEnemyParty[roamer], MON_DATA_STATUS, &temp);
//        }
//        else
//        {
//            roamerDataInVars[roamer].hp = GetMonData(&gEnemyParty[0], MON_DATA_HP, NULL);
//            roamerDataInVars[roamer].maxHP = GetMonData(&gEnemyParty[0], MON_DATA_MAX_HP, NULL);
//            roamerDataInVars[roamer].pid = GetMonData(&gEnemyParty[0], MON_DATA_PERSONALITY, NULL);
//            roamerDataInVars[roamer].status = GetMonData(&gEnemyParty[0], MON_DATA_STATUS, NULL);
//        }
//    }
//    else
//    {
//        gBattleTypeFlags = 0;
//        gBattleTypeFlags |= BATTLE_TYPE_WILD_SCRIPTED;
//    }
//
//    CreateBattleStartTask(GetWildBattleTransition(), 0);
//    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
//    IncrementGameStat(GAME_STAT_WILD_BATTLES);
//}
//
//
//void StartScriptedWildBattle(void)
//{
//    u16 species;
//    u32 roamer = 0xFF;
//    struct Roamer *roamerDataInVars = GetVarPointer(0x43C6); // roamer var start
//
//
//    ScriptContext2_Enable();
//    gMain.savedCallback = CB2_EndScriptedWildBattle;
//
//    species = GetMonData(&gEnemyParty[0], MON_DATA_SPECIES);
//    switch (species)
//    {
//    case SPECIES_ENTEI:
//        roamer = 0;
//        break;
//    case SPECIES_RAIKOU:
//        roamer = 1;
//        break;
//    case SPECIES_LATIOS:
//        if (FlagGet(0x2312))
//            roamer = 2;
//        else
//            roamer = 0xFF;
//        break;
//    case SPECIES_LATIAS:
//        if (!FlagGet(0x2312))
//            roamer = 2;
//        else
//            roamer = 0xFF;
//        break;
//    }
//    if (roamer != 0xFF)
//    {
//        u32 temp;
//        gBattleTypeFlags = BATTLE_TYPE_ROAMER;
//        
//        if (roamerDataInVars[roamer].inited)
//        {
//            roamerDataInVars[roamer].inited = TRUE;
//
//            temp = roamerDataInVars[roamer].hp;
//            SetMonData(&gEnemyParty[roamer], MON_DATA_HP, &temp);
//            temp = roamerDataInVars[roamer].maxHP;
//            SetMonData(&gEnemyParty[roamer], MON_DATA_MAX_HP, &temp);
//            temp = roamerDataInVars[roamer].pid;
//            SetMonData(&gEnemyParty[roamer], MON_DATA_PERSONALITY, &temp);
//            temp = roamerDataInVars[roamer].status;
//            SetMonData(&gEnemyParty[roamer], MON_DATA_STATUS, &temp);
//        }
//        else
//        {
//            roamerDataInVars[roamer].hp = GetMonData(&gEnemyParty[0], MON_DATA_HP, NULL);
//            roamerDataInVars[roamer].maxHP = GetMonData(&gEnemyParty[0], MON_DATA_MAX_HP, NULL);
//            roamerDataInVars[roamer].pid = GetMonData(&gEnemyParty[0], MON_DATA_PERSONALITY, NULL);
//            roamerDataInVars[roamer].status = GetMonData(&gEnemyParty[0], MON_DATA_STATUS, NULL);
//        }
//    }
//    else
//    {
//        gBattleTypeFlags = 0;
//        gBattleTypeFlags |= BATTLE_TYPE_WILD_SCRIPTED;
//    }
//
//
//    CreateBattleStartTask(GetWildBattleTransition(), 0);
//    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
//    IncrementGameStat(GAME_STAT_WILD_BATTLES);
//}

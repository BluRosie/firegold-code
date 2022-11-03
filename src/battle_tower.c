#include "../include/global.h"

#include "../include/pokemon.h"

#define NUM_OF_EASY_MODE_SPREADS 75
#define NUM_OF_HARD_MODE_SPREADS NUM_OF_EASY_MODE_SPREADS

#define VAR_BATTLE_TOWER_TYPE 0x43CB

#define BATTLE_TOWER_TYPE_NONE 0
#define BATTLE_TOWER_TYPE_SINGLE_EASY 1
#define BATTLE_TOWER_TYPE_SINGLE_HARD 2
#define BATTLE_TOWER_TYPE_DOUBLE_EASY 3
#define BATTLE_TOWER_TYPE_DOUBLE_HARD 4

#define BATTLE_TOWER_TYPE_EASY_BIT 0x01



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

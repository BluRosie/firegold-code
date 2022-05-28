#include "../include/global.h"

#include "../include/battle.h"
#include "../include/pokedex.h"
#include "../include/pokemon.h"
#include "../include/pokemon_icon.h"
#include "../include/unown_report.h"

#include "../include/battle_script_commands.h"

#include "../include/constants/species.h"

void atkF1_TrySetCaughtMonDexFlags(void) {
    u16 species = GetMonData(&gEnemyParty[0], MON_DATA_SPECIES, NULL);
    u32 personality = GetMonData(&gEnemyParty[0], MON_DATA_PERSONALITY, NULL);

    if (species == SPECIES_UNOWN) {
        SetCaughtUnown(GetUnownLetterByPersonality(personality));
    }

    species = SpeciesToNationalPokedexNum(species);
    if (GetSetPokedexFlag(species, FLAG_GET_CAUGHT)) {
        gBattlescriptCurrInstr = T1_READ_PTR(gBattlescriptCurrInstr + 1);
    } else {
        HandleSetPokedexFlag(species, FLAG_SET_CAUGHT, personality);
        gBattlescriptCurrInstr += 5;
    }
}

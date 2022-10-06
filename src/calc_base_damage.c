#include "../include/global.h"
#include "../include/battle.h"
#include "../include/constants/flags.h"
#include "../include/constants/species.h"

#define ITEM_CHOICE_BAND 0xBA
#define ITEM_CHOICE_SPECS 0xE2
#define ITEM_CHOICE_SCARF 0xE3
#define ITEM_MUSCLE_BAND 0xEC
#define ITEM_WISE_GLASSES 0xED

u32 GetBattlerSpeed(u8 battler1)
{
    u8 speedMultiplierBattler1 = 0;
    u32 speedBattler1 = 0;
    u8 holdEffect = 0;
    u8 holdEffectParam = 0;

    if (WEATHER_HAS_EFFECT)
    {
        if ((gBattleMons[battler1].ability == ABILITY_SWIFT_SWIM && gBattleWeather & B_WEATHER_RAIN)
            || (gBattleMons[battler1].ability == ABILITY_CHLOROPHYLL && gBattleWeather & B_WEATHER_SUN))
            speedMultiplierBattler1 = 2;
        else
            speedMultiplierBattler1 = 1;
    }
    else
    {
        speedMultiplierBattler1 = 1;
    }

    speedBattler1 = (gBattleMons[battler1].speed * speedMultiplierBattler1)
                * (gStatStageRatios[gBattleMons[battler1].statStages[STAT_SPEED]][0])
                / (gStatStageRatios[gBattleMons[battler1].statStages[STAT_SPEED]][1]);

    //if (gBattleMons[battler1].item == ITEM_ENIGMA_BERRY)
    //{
    //    holdEffect = gEnigmaBerries[battler1].holdEffect;
    //    holdEffectParam = gEnigmaBerries[battler1].holdEffectParam;
    //}
    //else
    {
        holdEffect = ItemId_GetHoldEffect(gBattleMons[battler1].item);
        holdEffectParam = ItemId_GetHoldEffectParam(gBattleMons[battler1].item);
    }
    //// badge boost
    //if (!(gBattleTypeFlags & BATTLE_TYPE_LINK)
    // && FlagGet(FLAG_BADGE03_GET)
    // && GetBattlerSide(battler1) == B_SIDE_PLAYER)
    //    speedBattler1 = (speedBattler1 * 110) / 100;

    if (holdEffect == HOLD_EFFECT_MACHO_BRACE)
        speedBattler1 /= 2;
    if (gBattleMons[battler1].status1 & STATUS1_PARALYSIS)
        speedBattler1 /= 4;
    if (gBattleMons[battler1].item == ITEM_CHOICE_SCARF)
        speedBattler1 = speedBattler1 * 150 / 100;
    //if (holdEffect == HOLD_EFFECT_QUICK_CLAW && gRandomTurnNumber < (0xFFFF * holdEffectParam) / 100)
    //    speedBattler1 = UINT_MAX;

    return speedBattler1;
}

s32 CalculateBaseDamage(struct BattlePokemon *attacker, struct BattlePokemon *defender, u32 move, u16 sideStatus, u32 stack_for_lr, u16 powerOverride, u8 typeOverride, u8 battlerIdAtk, u8 battlerIdDef)
{
    u32 i;
    s32 damage = 0;
    s32 damageHelper;
    u8 type;
    u16 attack, defense;
    u16 spAttack, spDefense;
    u8 defenderHoldEffect;
    u8 defenderHoldEffectParam;
    u8 attackerHoldEffect;
    u8 attackerHoldEffectParam;
    s32 splitOverride = -1; // -1 for no override, 0, 1, or 2 to override to that split

    switch (move)
    {
    case MOVE_GYRO_BALL:
        if (GetBattlerSpeed(battlerIdAtk) == 0)
            gBattleMovePower = 1;
        else
            gBattleMovePower = 25 * GetBattlerSpeed(battlerIdDef) / GetBattlerSpeed(battlerIdAtk);
        break;
    case MOVE_SHELL_SIDE_ARM:
        u32 damageAtk = 0, damageSpAtk = 0;

        // ((((2 * the user's level / 5 + 2) * 90 * X) / Y) / 50)
        // where X is the user's Attack stat and Y is the target's Defense stat, 
        // is greater than the same value where X is the user's Special Attack stat 
        // and Y is the target's Special Defense stat
        damageAtk = ((((2 * attacker->level / 5 + 2) * 90 * attacker->attack) / defender->defense) / 50);
        damageSpAtk = ((((2 * attacker->level / 5 + 2) * 90 * attacker->spAttack) / defender->spDefense) / 50);

        if (damageAtk == damageSpAtk)
            splitOverride = Random() & 1;
        else if (damageAtk > damageSpAtk)
            splitOverride = SPLIT_PHYSICAL;
        else
            splitOverride = SPLIT_SPECIAL;

        gBattleMovePower = gBattleMoves[move].power;
        break;
    case MOVE_BRINE:
        gBattleMovePower = gBattleMoves[move].power;
        if ((defender->maxHP / defender->hp) >= 2)
            gBattleMovePower *= 2;
        break;
    default:
        if (!powerOverride)
            gBattleMovePower = gBattleMoves[move].power;
        else
            gBattleMovePower = powerOverride;
        break;
    }

    if (!typeOverride)
        type = gBattleMoves[move].type;
    else
        type = typeOverride & 0x3F;

    attack = attacker->attack;
    defense = defender->defense;
    spAttack = attacker->spAttack;
    spDefense = defender->spDefense;

    //if (attacker->item == ITEM_ENIGMA_BERRY)
    //{
    //    attackerHoldEffect = gEnigmaBerries[battlerIdAtk].holdEffect;
    //    attackerHoldEffectParam = gEnigmaBerries[battlerIdAtk].holdEffectParam;
    //}
    //else
    {
        attackerHoldEffect = ItemId_GetHoldEffect(attacker->item);
        attackerHoldEffectParam = ItemId_GetHoldEffectParam(attacker->item);
    }

    //if (defender->item == ITEM_ENIGMA_BERRY)
    //{
    //    defenderHoldEffect = gEnigmaBerries[battlerIdDef].holdEffect;
    //    defenderHoldEffectParam = gEnigmaBerries[battlerIdDef].holdEffectParam;
    //}
    //else
    {
        defenderHoldEffect = ItemId_GetHoldEffect(defender->item);
        defenderHoldEffectParam = ItemId_GetHoldEffectParam(defender->item);
    }

    if (attacker->ability == ABILITY_HUGE_POWER || attacker->ability == ABILITY_PURE_POWER)
        attack *= 2;

    //// In FRLG, the Battle Tower and opponent checks are stubbed here.
    //if (!(gBattleTypeFlags & (BATTLE_TYPE_LINK | /*BATTLE_TYPE_BATTLE_TOWER |*/ BATTLE_TYPE_EREADER_TRAINER)))
    //{
    //    if (FlagGet(FLAG_BADGE01_GET)
    //        && GetBattlerSide(battlerIdAtk) == B_SIDE_PLAYER)
    //        attack = (110 * attack) / 100;
    //}
    //if (!(gBattleTypeFlags & (BATTLE_TYPE_LINK | /*BATTLE_TYPE_BATTLE_TOWER |*/ BATTLE_TYPE_EREADER_TRAINER)))
    //{
    //    if (FlagGet(FLAG_BADGE05_GET)
    //        && GetBattlerSide(battlerIdDef) == B_SIDE_PLAYER)
    //        defense = (110 * defense) / 100;
    //}
    //if (!(gBattleTypeFlags & (BATTLE_TYPE_LINK | /*BATTLE_TYPE_BATTLE_TOWER |*/ BATTLE_TYPE_EREADER_TRAINER)))
    //{
    //    if (FlagGet(FLAG_BADGE07_GET)
    //        && GetBattlerSide(battlerIdAtk) == B_SIDE_PLAYER)
    //        spAttack = (110 * spAttack) / 100;
    //}
    //if (!(gBattleTypeFlags & (BATTLE_TYPE_LINK | /*BATTLE_TYPE_BATTLE_TOWER |*/ BATTLE_TYPE_EREADER_TRAINER)))
    //{
    //    if (FlagGet(FLAG_BADGE07_GET)
    //        && GetBattlerSide(battlerIdDef) == B_SIDE_PLAYER)
    //        spDefense = (110 * spDefense) / 100;
    //}

    for (i = 0; i < 17 /*NELEMS(sHoldEffectToType)*/; i++)
    {
        if (attackerHoldEffect == sHoldEffectToType[i][0]
            && type == sHoldEffectToType[i][1])
        {
            if (IS_MOVE_PHYSICAL(move))
                attack = (attack * (attackerHoldEffectParam + 100)) / 100;
            else
                spAttack = (spAttack * (attackerHoldEffectParam + 100)) / 100;
            break;
        }
    }

    // new choice item handling
    if (attacker->item == ITEM_CHOICE_BAND && ((IS_MOVE_PHYSICAL(move) && splitOverride < 0) || splitOverride == SPLIT_PHYSICAL))
        attack = (150 * attack) / 100;
    if (attacker->item == ITEM_MUSCLE_BAND && ((IS_MOVE_PHYSICAL(move) && splitOverride < 0) || splitOverride == SPLIT_PHYSICAL))
        attack = (110 * attack) / 100;
    if (attacker->item == ITEM_CHOICE_SPECS && ((IS_MOVE_SPECIAL(move) && splitOverride < 0) || splitOverride == SPLIT_SPECIAL))
        spAttack = (150 * spAttack) / 100;
    if (attacker->item == ITEM_WISE_GLASSES && ((IS_MOVE_SPECIAL(move) && splitOverride < 0) || splitOverride == SPLIT_SPECIAL))
        spAttack = (110 * spAttack) / 100;
    if (attackerHoldEffect == HOLD_EFFECT_SOUL_DEW && !(gBattleTypeFlags & (BATTLE_TYPE_BATTLE_TOWER)) && (attacker->species == SPECIES_LATIAS || attacker->species == SPECIES_LATIOS))
        spAttack = (150 * spAttack) / 100;
    if (defenderHoldEffect == HOLD_EFFECT_SOUL_DEW && !(gBattleTypeFlags & (BATTLE_TYPE_BATTLE_TOWER)) && (defender->species == SPECIES_LATIAS || defender->species == SPECIES_LATIOS))
        spDefense = (150 * spDefense) / 100;
    if (attackerHoldEffect == HOLD_EFFECT_DEEP_SEA_TOOTH && attacker->species == SPECIES_CLAMPERL)
        spAttack *= 2;
    if (defenderHoldEffect == HOLD_EFFECT_DEEP_SEA_SCALE && defender->species == SPECIES_CLAMPERL)
        spDefense *= 2;
    if (attackerHoldEffect == HOLD_EFFECT_LIGHT_BALL && attacker->species == SPECIES_PIKACHU)
        spAttack *= 2;
    if (defenderHoldEffect == HOLD_EFFECT_METAL_POWDER && defender->species == SPECIES_DITTO)
        defense *= 2;
    if (attackerHoldEffect == HOLD_EFFECT_THICK_CLUB && (attacker->species == SPECIES_CUBONE || attacker->species == SPECIES_MAROWAK))
        attack *= 2;
    if (defender->ability == ABILITY_THICK_FAT && (type == TYPE_FIRE || type == TYPE_ICE))
        spAttack /= 2;
    if (attacker->ability == ABILITY_HUSTLE)
        attack = (150 * attack) / 100;
    if (attacker->ability == ABILITY_PLUS && ABILITY_ON_FIELD2(ABILITY_MINUS))
        spAttack = (150 * spAttack) / 100;
    if (attacker->ability == ABILITY_MINUS && ABILITY_ON_FIELD2(ABILITY_PLUS))
        spAttack = (150 * spAttack) / 100;
    if (attacker->ability == ABILITY_GUTS && attacker->status1)
        attack = (150 * attack) / 100;
    if (defender->ability == ABILITY_MARVEL_SCALE && defender->status1)
        defense = (150 * defense) / 100;
    if (defender->ability == ABILITY_FUR_COAT)
        defense *= 2;
    if (type == TYPE_ELECTRIC && AbilityBattleEffects(ABILITYEFFECT_FIELD_SPORT, 0, 0, ABILITYEFFECT_MUD_SPORT, 0))
        gBattleMovePower /= 2;
    if (type == TYPE_FIRE && AbilityBattleEffects(ABILITYEFFECT_FIELD_SPORT, 0, 0, ABILITYEFFECT_WATER_SPORT, 0))
        gBattleMovePower /= 2;
    if (type == TYPE_GRASS && attacker->ability == ABILITY_OVERGROW && attacker->hp <= (attacker->maxHP / 3))
        gBattleMovePower = (150 * gBattleMovePower) / 100;
    if (type == TYPE_FIRE && attacker->ability == ABILITY_BLAZE && attacker->hp <= (attacker->maxHP / 3))
        gBattleMovePower = (150 * gBattleMovePower) / 100;
    if (type == TYPE_WATER && attacker->ability == ABILITY_TORRENT && attacker->hp <= (attacker->maxHP / 3))
        gBattleMovePower = (150 * gBattleMovePower) / 100;
    if (type == TYPE_BUG && attacker->ability == ABILITY_SWARM && attacker->hp <= (attacker->maxHP / 3))
        gBattleMovePower = (150 * gBattleMovePower) / 100;
    if (defender->ability == ABILITY_MULTISCALE && (defender->hp == defender->maxHP))
        gBattleMovePower /= 2;
    if (gBattleMoves[gCurrentMove].effect == EFFECT_EXPLOSION)
        defense /= 2;

    if ((IS_MOVE_PHYSICAL(move) && splitOverride < 0) || splitOverride == SPLIT_PHYSICAL)
    {
        if (gCritMultiplier == 2)
        {
            if (attacker->statStages[STAT_ATK] > 6)
                APPLY_STAT_MOD(damage, attacker, attack, STAT_ATK)
            else
                damage = attack;
        }
        else
            APPLY_STAT_MOD(damage, attacker, attack, STAT_ATK)

        damage = damage * gBattleMovePower;
        damage *= (2 * attacker->level / 5 + 2);

        if (gCritMultiplier == 2)
        {
            if (defender->statStages[STAT_DEF] < 6)
                APPLY_STAT_MOD(damageHelper, defender, defense, STAT_DEF)
            else
                damageHelper = defense;
        }
        else
            APPLY_STAT_MOD(damageHelper, defender, defense, STAT_DEF)

        damage = damage / damageHelper;
        damage /= 50;

        if ((attacker->status1 & STATUS1_BURN) && attacker->ability != ABILITY_GUTS)
            damage /= 2;

        if ((sideStatus & SIDE_STATUS_REFLECT) && gCritMultiplier == 1)
        {
            if ((gBattleTypeFlags & BATTLE_TYPE_DOUBLE) && CountAliveMonsInBattle(BATTLE_ALIVE_DEF_SIDE) == 2)
                damage = 2 * (damage / 3);
            else
                damage /= 2;
        }

        if ((gBattleTypeFlags & BATTLE_TYPE_DOUBLE) && gBattleMoves[move].target == 8 && CountAliveMonsInBattle(BATTLE_ALIVE_DEF_SIDE) == 2)
            damage /= 2;

        // moves always do at least 1 damage.
        if (damage == 0)
            damage = 1;
    }

    //if (type == TYPE_MYSTERY)
    //    damage = 0; // is ??? type. does 0 damage.

    if ((IS_MOVE_SPECIAL(move) && splitOverride < 0) || splitOverride == SPLIT_SPECIAL)
    {
        if (gCritMultiplier == 2)
        {
            if (attacker->statStages[STAT_SPATK] > 6)
                APPLY_STAT_MOD(damage, attacker, spAttack, STAT_SPATK)
            else
                damage = spAttack;
        }
        else
            APPLY_STAT_MOD(damage, attacker, spAttack, STAT_SPATK)

        damage = damage * gBattleMovePower;
        damage *= (2 * attacker->level / 5 + 2);

        if (move != MOVE_PSYSHOCK)
        {
            if (gCritMultiplier == 2)
            {
                if (defender->statStages[STAT_SPDEF] < 6)
                    APPLY_STAT_MOD(damageHelper, defender, spDefense, STAT_SPDEF)
                else
                    damageHelper = spDefense;
            }
            else
                APPLY_STAT_MOD(damageHelper, defender, spDefense, STAT_SPDEF)
        }
        else
        {
            if (gCritMultiplier == 2)
            {
                if (defender->statStages[STAT_DEF] < 6)
                    APPLY_STAT_MOD(damageHelper, defender, defense, STAT_DEF)
                else
                    damageHelper = defense;
            }
            else
                APPLY_STAT_MOD(damageHelper, defender, defense, STAT_DEF)
        }
        damage = (damage / damageHelper);
        damage /= 50;

        if ((sideStatus & SIDE_STATUS_LIGHTSCREEN) && gCritMultiplier == 1)
        {
            if ((gBattleTypeFlags & BATTLE_TYPE_DOUBLE) && CountAliveMonsInBattle(BATTLE_ALIVE_DEF_SIDE) == 2)
                damage = 2 * (damage / 3);
            else
                damage /= 2;
        }

        if ((gBattleTypeFlags & BATTLE_TYPE_DOUBLE) && gBattleMoves[move].target == 8 && CountAliveMonsInBattle(BATTLE_ALIVE_DEF_SIDE) == 2)
            damage /= 2;
    }

    // are effects of weather negated with cloud nine or air lock
    if (WEATHER_HAS_EFFECT2)
    {
        if (gBattleWeather & B_WEATHER_RAIN_TEMPORARY)
        {
            switch (type)
            {
            case TYPE_FIRE:
                damage /= 2;
                break;
            case TYPE_WATER:
                damage = (15 * damage) / 10;
                break;
            }
        }

        // any weather except sun weakens solar beam
        if ((gBattleWeather & (B_WEATHER_RAIN | B_WEATHER_SANDSTORM | B_WEATHER_HAIL_TEMPORARY)) && gCurrentMove == MOVE_SOLAR_BEAM)
            damage /= 2;

        // sunny
        if (gBattleWeather & B_WEATHER_SUN)
        {
            switch (type)
            {
            case TYPE_FIRE:
                damage = (15 * damage) / 10;
                break;
            case TYPE_WATER:
                damage /= 2;
                break;
            }
        }
    }
    
    // flash fire triggered
    if ((gBattleResources->flags->flags[battlerIdAtk] & RESOURCE_FLAG_FLASH_FIRE) && type == TYPE_FIRE)
        damage = (15 * damage) / 10;

    return damage + 2;
}

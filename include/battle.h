#ifndef GUARD_BATTLE_H
#define GUARD_BATTLE_H


// Battle move flags
#define FLAG_MAKES_CONTACT          (1 << 0)
#define FLAG_PROTECT_AFFECTED       (1 << 1)
#define FLAG_MAGIC_COAT_AFFECTED    (1 << 2)
#define FLAG_SNATCH_AFFECTED        (1 << 3)
#define FLAG_MIRROR_MOVE_AFFECTED   (1 << 4)
#define FLAG_KINGS_ROCK_AFFECTED    (1 << 5)


#define SPLIT_PHYSICAL 0
#define SPLIT_SPECIAL 1
#define SPLIT_STATUS 2


#define IS_MOVE_PHYSICAL(move) (gBattleMoves[move].split == SPLIT_PHYSICAL)
#define IS_MOVE_SPECIAL(move) (gBattleMoves[move].split == SPLIT_SPECIAL)


// abilities
#define ABILITY_NONE 0
#define ABILITY_STENCH 1
#define ABILITY_DRIZZLE 2
#define ABILITY_SPEED_BOOST 3
#define ABILITY_BATTLE_ARMOR 4
#define ABILITY_STURDY 5
#define ABILITY_DAMP 6
#define ABILITY_LIMBER 7
#define ABILITY_SAND_VEIL 8
#define ABILITY_STATIC 9
#define ABILITY_VOLT_ABSORB 10
#define ABILITY_WATER_ABSORB 11
#define ABILITY_OBLIVIOUS 12
#define ABILITY_CLOUD_NINE 13
#define ABILITY_COMPOUND_EYES 14
#define ABILITY_INSOMNIA 15
#define ABILITY_COLOR_CHANGE 16
#define ABILITY_IMMUNITY 17
#define ABILITY_FLASH_FIRE 18
#define ABILITY_SHIELD_DUST 19
#define ABILITY_OWN_TEMPO 20
#define ABILITY_SUCTION_CUPS 21
#define ABILITY_INTIMIDATE 22
#define ABILITY_SHADOW_TAG 23
#define ABILITY_ROUGH_SKIN 24
#define ABILITY_WONDER_GUARD 25
#define ABILITY_LEVITATE 26
#define ABILITY_EFFECT_SPORE 27
#define ABILITY_SYNCHRONIZE 28
#define ABILITY_CLEAR_BODY 29
#define ABILITY_NATURAL_CURE 30
#define ABILITY_LIGHTNING_ROD 31
#define ABILITY_SERENE_GRACE 32
#define ABILITY_SWIFT_SWIM 33
#define ABILITY_CHLOROPHYLL 34
#define ABILITY_ILLUMINATE 35
#define ABILITY_TRACE 36
#define ABILITY_HUGE_POWER 37
#define ABILITY_POISON_POINT 38
#define ABILITY_INNER_FOCUS 39
#define ABILITY_MAGMA_ARMOR 40
#define ABILITY_WATER_VEIL 41
#define ABILITY_MAGNET_PULL 42
#define ABILITY_SOUNDPROOF 43
#define ABILITY_RAIN_DISH 44
#define ABILITY_SAND_STREAM 45
#define ABILITY_PRESSURE 46
#define ABILITY_THICK_FAT 47
#define ABILITY_EARLY_BIRD 48
#define ABILITY_FLAME_BODY 49
#define ABILITY_RUN_AWAY 50
#define ABILITY_KEEN_EYE 51
#define ABILITY_HYPER_CUTTER 52
#define ABILITY_PICKUP 53
#define ABILITY_TRUANT 54
#define ABILITY_HUSTLE 55
#define ABILITY_CUTE_CHARM 56
#define ABILITY_PLUS 57
#define ABILITY_MINUS 58
#define ABILITY_FORECAST 59
#define ABILITY_STICKY_HOLD 60
#define ABILITY_SHED_SKIN 61
#define ABILITY_GUTS 62
#define ABILITY_MARVEL_SCALE 63
#define ABILITY_LIQUID_OOZE 64
#define ABILITY_OVERGROW 65
#define ABILITY_BLAZE 66
#define ABILITY_TORRENT 67
#define ABILITY_SWARM 68
#define ABILITY_ROCK_HEAD 69
#define ABILITY_DROUGHT 70
#define ABILITY_ARENA_TRAP 71
#define ABILITY_VITAL_SPIRIT 72
#define ABILITY_WHITE_SMOKE 73
#define ABILITY_PURE_POWER 74
#define ABILITY_SHELL_ARMOR 75
#define ABILITY_CACOPHONY 76
#define ABILITY_AIR_LOCK 77

#define ABILITY_MULTISCALE 81
#define ABILITY_FUR_COAT 142

// hold effects
#define HOLD_EFFECT_NONE            0
#define HOLD_EFFECT_RESTORE_HP      1
#define HOLD_EFFECT_CURE_PAR        2
#define HOLD_EFFECT_CURE_SLP        3
#define HOLD_EFFECT_CURE_PSN        4
#define HOLD_EFFECT_CURE_BRN        5
#define HOLD_EFFECT_CURE_FRZ        6
#define HOLD_EFFECT_RESTORE_PP      7
#define HOLD_EFFECT_CURE_CONFUSION  8
#define HOLD_EFFECT_CURE_STATUS     9
#define HOLD_EFFECT_CONFUSE_SPICY  10
#define HOLD_EFFECT_CONFUSE_DRY    11
#define HOLD_EFFECT_CONFUSE_SWEET  12
#define HOLD_EFFECT_CONFUSE_BITTER 13
#define HOLD_EFFECT_CONFUSE_SOUR   14
#define HOLD_EFFECT_ATTACK_UP      15
#define HOLD_EFFECT_DEFENSE_UP     16
#define HOLD_EFFECT_SPEED_UP       17
#define HOLD_EFFECT_SP_ATTACK_UP   18
#define HOLD_EFFECT_SP_DEFENSE_UP  19
#define HOLD_EFFECT_CRITICAL_UP    20
#define HOLD_EFFECT_RANDOM_STAT_UP 21
#define HOLD_EFFECT_EVASION_UP     22
#define HOLD_EFFECT_RESTORE_STATS  23
#define HOLD_EFFECT_MACHO_BRACE    24
#define HOLD_EFFECT_EXP_SHARE      25
#define HOLD_EFFECT_QUICK_CLAW     26
#define HOLD_EFFECT_HAPPINESS_UP   27
#define HOLD_EFFECT_CURE_ATTRACT   28
#define HOLD_EFFECT_CHOICE_BAND    29
#define HOLD_EFFECT_FLINCH         30
#define HOLD_EFFECT_BUG_POWER      31
#define HOLD_EFFECT_DOUBLE_PRIZE   32
#define HOLD_EFFECT_REPEL          33
#define HOLD_EFFECT_SOUL_DEW       34
#define HOLD_EFFECT_DEEP_SEA_TOOTH 35
#define HOLD_EFFECT_DEEP_SEA_SCALE 36
#define HOLD_EFFECT_CAN_ALWAYS_RUN 37
#define HOLD_EFFECT_PREVENT_EVOLVE 38
#define HOLD_EFFECT_FOCUS_BAND     39
#define HOLD_EFFECT_LUCKY_EGG      40
#define HOLD_EFFECT_SCOPE_LENS     41
#define HOLD_EFFECT_STEEL_POWER    42
#define HOLD_EFFECT_LEFTOVERS      43
#define HOLD_EFFECT_DRAGON_SCALE   44
#define HOLD_EFFECT_LIGHT_BALL     45
#define HOLD_EFFECT_GROUND_POWER   46
#define HOLD_EFFECT_ROCK_POWER     47
#define HOLD_EFFECT_GRASS_POWER    48
#define HOLD_EFFECT_DARK_POWER     49
#define HOLD_EFFECT_FIGHTING_POWER 50
#define HOLD_EFFECT_ELECTRIC_POWER 51
#define HOLD_EFFECT_WATER_POWER    52
#define HOLD_EFFECT_FLYING_POWER   53
#define HOLD_EFFECT_POISON_POWER   54
#define HOLD_EFFECT_ICE_POWER      55
#define HOLD_EFFECT_GHOST_POWER    56
#define HOLD_EFFECT_PSYCHIC_POWER  57
#define HOLD_EFFECT_FIRE_POWER     58
#define HOLD_EFFECT_DRAGON_POWER   59
#define HOLD_EFFECT_NORMAL_POWER   60
#define HOLD_EFFECT_UP_GRADE       61
#define HOLD_EFFECT_SHELL_BELL     62
#define HOLD_EFFECT_LUCKY_PUNCH    63
#define HOLD_EFFECT_METAL_POWDER   64
#define HOLD_EFFECT_THICK_CLUB     65
#define HOLD_EFFECT_STICK          66


// battle type flags
#define BATTLE_TYPE_DOUBLE             (1 << 0)
#define BATTLE_TYPE_LINK               (1 << 1)
#define BATTLE_TYPE_IS_MASTER          (1 << 2) // In not-link battles, it's always set.
#define BATTLE_TYPE_TRAINER            (1 << 3)
#define BATTLE_TYPE_FIRST_BATTLE       (1 << 4)
#define BATTLE_TYPE_LINK_IN_BATTLE     (1 << 5) // Set on battle entry, cleared on exit. Checked rarely
#define BATTLE_TYPE_MULTI              (1 << 6)
#define BATTLE_TYPE_SAFARI             (1 << 7)
#define BATTLE_TYPE_BATTLE_TOWER       (1 << 8)
#define BATTLE_TYPE_OLD_MAN_TUTORIAL   (1 << 9) // Used in pokeemerald as BATTLE_TYPE_WALLY_TUTORIAL.
#define BATTLE_TYPE_ROAMER             (1 << 10)
#define BATTLE_TYPE_EREADER_TRAINER    (1 << 11)
#define BATTLE_TYPE_KYOGRE_GROUDON     (1 << 12)
#define BATTLE_TYPE_LEGENDARY          (1 << 13)
#define BATTLE_TYPE_GHOST_UNVEILED     (1 << 13) // Re-use of BATTLE_TYPE_LEGENDARY, when combined with BATTLE_TYPE_GHOST
#define BATTLE_TYPE_REGI               (1 << 14)
#define BATTLE_TYPE_GHOST              (1 << 15) // Used in pokeemerald as BATTLE_TYPE_TWO_OPPONENTS.
#define BATTLE_TYPE_POKEDUDE           (1 << 16) // Used in pokeemerald as BATTLE_TYPE_DOME.
#define BATTLE_TYPE_WILD_SCRIPTED      (1 << 17) // Used in pokeemerald as BATTLE_TYPE_PALACE.
#define BATTLE_TYPE_LEGENDARY_FRLG     (1 << 18) // Used in pokeemerald as BATTLE_TYPE_ARENA.
#define BATTLE_TYPE_TRAINER_TOWER      (1 << 19) // Used in pokeemerald as BATTLE_TYPE_FACTORY.


// Pokemon types
#define TYPE_NONE           255
#define TYPE_NORMAL         0
#define TYPE_FIGHTING       1
#define TYPE_FLYING         2
#define TYPE_POISON         3
#define TYPE_GROUND         4
#define TYPE_ROCK           5
#define TYPE_BUG            6
#define TYPE_GHOST          7
#define TYPE_STEEL          8
#define TYPE_MYSTERY        9
#define TYPE_FIRE           10
#define TYPE_WATER          11
#define TYPE_GRASS          12
#define TYPE_ELECTRIC       13
#define TYPE_PSYCHIC        14
#define TYPE_ICE            15
#define TYPE_DRAGON         16
#define TYPE_DARK           17
#define NUMBER_OF_MON_TYPES 18


#define ABILITY_ON_FIELD(abilityId)(AbilityBattleEffects(ABILITYEFFECT_CHECK_ON_FIELD, 0, abilityId, 0, 0))
#define ABILITY_ON_FIELD2(abilityId)(AbilityBattleEffects(ABILITYEFFECT_FIELD_SPORT, 0, abilityId, 0, 0))

#define ABILITYEFFECT_ON_SWITCHIN                0
#define ABILITYEFFECT_ENDTURN                    1
#define ABILITYEFFECT_MOVES_BLOCK                2
#define ABILITYEFFECT_ABSORBING                  3
#define ABILITYEFFECT_ON_DAMAGE                  4
#define ABILITYEFFECT_IMMUNITY                   5
#define ABILITYEFFECT_FORECAST                   6
#define ABILITYEFFECT_SYNCHRONIZE                7
#define ABILITYEFFECT_ATK_SYNCHRONIZE            8
#define ABILITYEFFECT_INTIMIDATE1                9
#define ABILITYEFFECT_INTIMIDATE2                10
#define ABILITYEFFECT_TRACE                      11
#define ABILITYEFFECT_CHECK_OTHER_SIDE           12
#define ABILITYEFFECT_CHECK_BATTLER_SIDE         13
#define ABILITYEFFECT_FIELD_SPORT                14
#define ABILITYEFFECT_CHECK_FIELD_EXCEPT_BATTLER 15
#define ABILITYEFFECT_COUNT_OTHER_SIDE           16
#define ABILITYEFFECT_COUNT_BATTLER_SIDE         17
#define ABILITYEFFECT_COUNT_ON_FIELD             18
#define ABILITYEFFECT_CHECK_ON_FIELD             19
#define ABILITYEFFECT_MUD_SPORT                  253
#define ABILITYEFFECT_WATER_SPORT                254
#define ABILITYEFFECT_SWITCH_IN_WEATHER          255


#define EFFECT_HIT 0
#define EFFECT_SLEEP 1
#define EFFECT_POISON_HIT 2
#define EFFECT_ABSORB 3
#define EFFECT_BURN_HIT 4
#define EFFECT_FREEZE_HIT 5
#define EFFECT_PARALYZE_HIT 6
#define EFFECT_EXPLOSION 7
#define EFFECT_DREAM_EATER 8
#define EFFECT_MIRROR_MOVE 9
#define EFFECT_ATTACK_UP 10
#define EFFECT_DEFENSE_UP 11
#define EFFECT_SPEED_UP 12
#define EFFECT_SPECIAL_ATTACK_UP 13
#define EFFECT_SPECIAL_DEFENSE_UP 14
#define EFFECT_ACCURACY_UP 15
#define EFFECT_EVASION_UP 16
#define EFFECT_ALWAYS_HIT 17
#define EFFECT_ATTACK_DOWN 18
#define EFFECT_DEFENSE_DOWN 19
#define EFFECT_SPEED_DOWN 20
#define EFFECT_SPECIAL_ATTACK_DOWN 21  // unused
#define EFFECT_SPECIAL_DEFENSE_DOWN 22  // unused
#define EFFECT_ACCURACY_DOWN 23
#define EFFECT_EVASION_DOWN 24
#define EFFECT_HAZE 25
#define EFFECT_BIDE 26
#define EFFECT_RAMPAGE 27
#define EFFECT_ROAR 28
#define EFFECT_MULTI_HIT 29
#define EFFECT_CONVERSION 30
#define EFFECT_FLINCH_HIT 31
#define EFFECT_RESTORE_HP 32
#define EFFECT_TOXIC 33
#define EFFECT_PAY_DAY 34
#define EFFECT_LIGHT_SCREEN 35
#define EFFECT_TRI_ATTACK 36
#define EFFECT_REST 37
#define EFFECT_OHKO 38
#define EFFECT_RAZOR_WIND 39
#define EFFECT_SUPER_FANG 40
#define EFFECT_DRAGON_RAGE 41
#define EFFECT_TRAP 42
#define EFFECT_HIGH_CRITICAL 43
#define EFFECT_DOUBLE_HIT 44
#define EFFECT_RECOIL_IF_MISS 45
#define EFFECT_MIST 46
#define EFFECT_FOCUS_ENERGY 47
#define EFFECT_RECOIL 48
#define EFFECT_CONFUSE 49
#define EFFECT_ATTACK_UP_2 50
#define EFFECT_DEFENSE_UP_2 51
#define EFFECT_SPEED_UP_2 52
#define EFFECT_SPECIAL_ATTACK_UP_2 53
#define EFFECT_SPECIAL_DEFENSE_UP_2 54
#define EFFECT_ACCURACY_UP_2 55
#define EFFECT_EVASION_UP_2 56
#define EFFECT_TRANSFORM 57
#define EFFECT_ATTACK_DOWN_2 58
#define EFFECT_DEFENSE_DOWN_2 59
#define EFFECT_SPEED_DOWN_2 60
#define EFFECT_SPECIAL_ATTACK_DOWN_2 61
#define EFFECT_SPECIAL_DEFENSE_DOWN_2 62
#define EFFECT_ACCURACY_DOWN_2 63
#define EFFECT_EVASION_DOWN_2 64
#define EFFECT_REFLECT 65
#define EFFECT_POISON 66
#define EFFECT_PARALYZE 67
#define EFFECT_ATTACK_DOWN_HIT 68
#define EFFECT_DEFENSE_DOWN_HIT 69
#define EFFECT_SPEED_DOWN_HIT 70
#define EFFECT_SPECIAL_ATTACK_DOWN_HIT 71
#define EFFECT_SPECIAL_DEFENSE_DOWN_HIT 72
#define EFFECT_ACCURACY_DOWN_HIT 73
#define EFFECT_EVASION_DOWN_HIT 74
#define EFFECT_SKY_ATTACK 75
#define EFFECT_CONFUSE_HIT 76
#define EFFECT_TWINEEDLE 77
#define EFFECT_VITAL_THROW 78
#define EFFECT_SUBSTITUTE 79
#define EFFECT_RECHARGE 80
#define EFFECT_RAGE 81
#define EFFECT_MIMIC 82
#define EFFECT_METRONOME 83
#define EFFECT_LEECH_SEED 84
#define EFFECT_SPLASH 85
#define EFFECT_DISABLE 86
#define EFFECT_LEVEL_DAMAGE 87
#define EFFECT_PSYWAVE 88
#define EFFECT_COUNTER 89
#define EFFECT_ENCORE 90
#define EFFECT_PAIN_SPLIT 91
#define EFFECT_SNORE 92
#define EFFECT_CONVERSION_2 93
#define EFFECT_LOCK_ON 94
#define EFFECT_SKETCH 95
#define EFFECT_UNUSED_60 96  // thaw
#define EFFECT_SLEEP_TALK 97
#define EFFECT_DESTINY_BOND 98
#define EFFECT_FLAIL 99
#define EFFECT_SPITE 100
#define EFFECT_FALSE_SWIPE 101
#define EFFECT_HEAL_BELL 102
#define EFFECT_QUICK_ATTACK 103
#define EFFECT_TRIPLE_KICK 104
#define EFFECT_THIEF 105
#define EFFECT_MEAN_LOOK 106
#define EFFECT_NIGHTMARE 107
#define EFFECT_MINIMIZE 108
#define EFFECT_CURSE 109
#define EFFECT_UNUSED_6E 110
#define EFFECT_PROTECT 111
#define EFFECT_SPIKES 112
#define EFFECT_FORESIGHT 113
#define EFFECT_PERISH_SONG 114
#define EFFECT_SANDSTORM 115
#define EFFECT_ENDURE 116
#define EFFECT_ROLLOUT 117
#define EFFECT_SWAGGER 118
#define EFFECT_FURY_CUTTER 119
#define EFFECT_ATTRACT 120
#define EFFECT_RETURN 121
#define EFFECT_PRESENT 122
#define EFFECT_FRUSTRATION 123
#define EFFECT_SAFEGUARD 124
#define EFFECT_THAW_HIT 125
#define EFFECT_MAGNITUDE 126
#define EFFECT_BATON_PASS 127
#define EFFECT_PURSUIT 128
#define EFFECT_RAPID_SPIN 129
#define EFFECT_SONICBOOM 130
#define EFFECT_UNUSED_83 131
#define EFFECT_MORNING_SUN 132
#define EFFECT_SYNTHESIS 133
#define EFFECT_MOONLIGHT 134
#define EFFECT_HIDDEN_POWER 135
#define EFFECT_RAIN_DANCE 136
#define EFFECT_SUNNY_DAY 137
#define EFFECT_DEFENSE_UP_HIT 138
#define EFFECT_ATTACK_UP_HIT 139
#define EFFECT_ALL_STATS_UP_HIT 140
#define EFFECT_UNUSED_8D 141  // incomplete fake out in gen 2
#define EFFECT_BELLY_DRUM 142
#define EFFECT_PSYCH_UP 143
#define EFFECT_MIRROR_COAT 144
#define EFFECT_SKULL_BASH 145
#define EFFECT_TWISTER 146
#define EFFECT_EARTHQUAKE 147
#define EFFECT_FUTURE_SIGHT 148
#define EFFECT_GUST 149
#define EFFECT_FLINCH_MINIMIZE_HIT 150  // STOMP ASTONISH EXTRASENSORY NEEDLE_ARM
#define EFFECT_SOLAR_BEAM 151
#define EFFECT_THUNDER 152
#define EFFECT_TELEPORT 153
#define EFFECT_BEAT_UP 154
#define EFFECT_SEMI_INVULNERABLE 155
#define EFFECT_DEFENSE_CURL 156
#define EFFECT_SOFTBOILED 157
#define EFFECT_FAKE_OUT 158
#define EFFECT_UPROAR 159
#define EFFECT_STOCKPILE 160
#define EFFECT_SPIT_UP 161
#define EFFECT_SWALLOW 162
#define EFFECT_UNUSED_A3 163
#define EFFECT_HAIL 164
#define EFFECT_TORMENT 165
#define EFFECT_FLATTER 166
#define EFFECT_WILL_O_WISP 167
#define EFFECT_MEMENTO 168
#define EFFECT_FACADE 169
#define EFFECT_FOCUS_PUNCH 170
#define EFFECT_SMELLINGSALT 171
#define EFFECT_FOLLOW_ME 172
#define EFFECT_NATURE_POWER 173
#define EFFECT_CHARGE 174
#define EFFECT_TAUNT 175
#define EFFECT_HELPING_HAND 176
#define EFFECT_TRICK 177
#define EFFECT_ROLE_PLAY 178
#define EFFECT_WISH 179
#define EFFECT_ASSIST 180
#define EFFECT_INGRAIN 181
#define EFFECT_SUPERPOWER 182
#define EFFECT_MAGIC_COAT 183
#define EFFECT_RECYCLE 184
#define EFFECT_REVENGE 185
#define EFFECT_BRICK_BREAK 186
#define EFFECT_YAWN 187
#define EFFECT_KNOCK_OFF 188
#define EFFECT_ENDEAVOR 189
#define EFFECT_ERUPTION 190
#define EFFECT_SKILL_SWAP 191
#define EFFECT_IMPRISON 192
#define EFFECT_REFRESH 193
#define EFFECT_GRUDGE 194
#define EFFECT_SNATCH 195
#define EFFECT_LOW_KICK 196
#define EFFECT_SECRET_POWER 197
#define EFFECT_DOUBLE_EDGE 198
#define EFFECT_TEETER_DANCE 199
#define EFFECT_BLAZE_KICK 200
#define EFFECT_MUD_SPORT 201
#define EFFECT_POISON_FANG 202
#define EFFECT_WEATHER_BALL 203
#define EFFECT_OVERHEAT 204
#define EFFECT_TICKLE 205
#define EFFECT_COSMIC_POWER 206
#define EFFECT_SKY_UPPERCUT 207
#define EFFECT_BULK_UP 208
#define EFFECT_POISON_TAIL 209
#define EFFECT_WATER_SPORT 210
#define EFFECT_CALM_MIND 211
#define EFFECT_DRAGON_DANCE 212
#define EFFECT_CAMOUFLAGE 213


// Pokemon Stats
#define STAT_HP      0
#define STAT_ATK     1
#define STAT_DEF     2
#define STAT_SPEED   3
#define STAT_SPATK   4
#define STAT_SPDEF   5
#define NUM_STATS    6

#define STAT_ACC     6 // Only in battles.
#define STAT_EVASION 7 // Only in battles.


#define APPLY_STAT_MOD(var, mon, stat, statIndex)                                   \
{                                                                                   \
    (var) = (stat) * (gStatStageRatios)[(mon)->statStages[(statIndex)]][0];         \
    (var) /= (gStatStageRatios)[(mon)->statStages[(statIndex)]][1];                 \
}


// Non-volatile status conditions
// These persist remain outside of battle and after switching out
#define STATUS1_NONE             0
#define STATUS1_SLEEP            (1 << 0 | 1 << 1 | 1 << 2) // First 3 bits (Number of turns to sleep)
#define STATUS1_SLEEP_TURN(num)  ((num) << 0) // Just for readability (or if rearranging statuses)
#define STATUS1_POISON           (1 << 3)
#define STATUS1_BURN             (1 << 4)
#define STATUS1_FREEZE           (1 << 5)
#define STATUS1_PARALYSIS        (1 << 6)
#define STATUS1_TOXIC_POISON     (1 << 7)
#define STATUS1_TOXIC_COUNTER    (1 << 8 | 1 << 9 | 1 << 10 | 1 << 11)
#define STATUS1_TOXIC_TURN(num)  ((num) << 8)
#define STATUS1_PSN_ANY          (STATUS1_POISON | STATUS1_TOXIC_POISON)
#define STATUS1_ANY              (STATUS1_SLEEP | STATUS1_POISON | STATUS1_BURN | STATUS1_FREEZE | STATUS1_PARALYSIS | STATUS1_TOXIC_POISON)


// Per-side statuses that affect an entire party
#define SIDE_STATUS_REFLECT          (1 << 0)
#define SIDE_STATUS_LIGHTSCREEN      (1 << 1)
#define SIDE_STATUS_X4               (1 << 2)
#define SIDE_STATUS_SPIKES           (1 << 4)
#define SIDE_STATUS_SAFEGUARD        (1 << 5)
#define SIDE_STATUS_FUTUREATTACK     (1 << 6)
#define SIDE_STATUS_MIST             (1 << 8)
#define SIDE_STATUS_SPIKES_DAMAGED   (1 << 9)


#define BATTLE_ALIVE_EXCEPT_ACTIVE  0
#define BATTLE_ALIVE_ATK_SIDE       1
#define BATTLE_ALIVE_DEF_SIDE       2


#define WEATHER_HAS_EFFECT ((!AbilityBattleEffects(ABILITYEFFECT_CHECK_ON_FIELD, 0, ABILITY_CLOUD_NINE, 0, 0) && !AbilityBattleEffects(ABILITYEFFECT_CHECK_ON_FIELD, 0, ABILITY_AIR_LOCK, 0, 0)))
#define WEATHER_HAS_EFFECT2 ((!AbilityBattleEffects(ABILITYEFFECT_FIELD_SPORT, 0, ABILITY_CLOUD_NINE, 0, 0) && !AbilityBattleEffects(ABILITYEFFECT_FIELD_SPORT, 0, ABILITY_AIR_LOCK, 0, 0)))


// Battle Weather flags
#define B_WEATHER_RAIN_TEMPORARY      (1 << 0)
#define B_WEATHER_RAIN_DOWNPOUR       (1 << 1)  // unused
#define B_WEATHER_RAIN_PERMANENT      (1 << 2)
#define B_WEATHER_RAIN                (B_WEATHER_RAIN_TEMPORARY | B_WEATHER_RAIN_DOWNPOUR | B_WEATHER_RAIN_PERMANENT)
#define B_WEATHER_SANDSTORM_TEMPORARY (1 << 3)
#define B_WEATHER_SANDSTORM_PERMANENT (1 << 4)
#define B_WEATHER_SANDSTORM           (B_WEATHER_SANDSTORM_TEMPORARY | B_WEATHER_SANDSTORM_PERMANENT)
#define B_WEATHER_SUN_TEMPORARY       (1 << 5)
#define B_WEATHER_SUN_PERMANENT       (1 << 6)
#define B_WEATHER_SUN                 (B_WEATHER_SUN_TEMPORARY | B_WEATHER_SUN_PERMANENT)
#define B_WEATHER_HAIL_TEMPORARY      (1 << 7)
#define B_WEATHER_HAIL                (B_WEATHER_HAIL_TEMPORARY)
#define B_WEATHER_ANY                 (B_WEATHER_RAIN | B_WEATHER_SANDSTORM | B_WEATHER_SUN | B_WEATHER_HAIL)


// moves
#define MOVE_SOLAR_BEAM 76


struct ResourceFlags
{
    u32 flags[4];
};

struct BattleResources
{
    void /*struct SecretBaseRecord*/ *secretBase;
    struct ResourceFlags *flags;
    void /*struct BattleScriptsStack*/ *battleScriptsStack;
    void /*struct BattleCallbacksStack*/ *battleCallbackStack;
    void /*struct StatsArray*/ *beforeLvlUp;
    void /*struct AI_ThinkingStruct*/ *ai;
    void /*struct BattleHistory*/ *battleHistory;
    void /*struct BattleScriptsStack*/ *AI_ScriptsStack;
};

#define RESOURCE_FLAG_FLASH_FIRE 1
extern struct BattleResources *gBattleResources;


/*
new shit

psyshock        1fd
gyroball        1aa(fiery dance)
shell side arm        1f2
stomptantrum        1eb
brine            1cc
*/
#define MOVE_PSYSHOCK 0x1FD
#define MOVE_PSYSTRIKE 0x1FE
#define MOVE_GYRO_BALL 0x1AA
#define MOVE_SHELL_SIDE_ARM 0x1F2
#define MOVE_STOMP_TANTRUM 0x1EB
#define MOVE_BRINE 0x1CC

struct BattleMove
{
    u8 effect;
    u8 power;
    u8 type;
    u8 accuracy;
    u8 pp;
    u8 secondaryEffectChance;
    u8 target;
    s8 priority;
    u8 flags;
    u8 paddingA;
    u8 split;
    u8 paddingC;
};


struct BattlePokemon
{
    /*0x00*/ u16 species;
    /*0x02*/ u16 attack;
    /*0x04*/ u16 defense;
    /*0x06*/ u16 speed;
    /*0x08*/ u16 spAttack;
    /*0x0A*/ u16 spDefense;
    /*0x0C*/ u16 moves[4];
    /*0x14*/ u32 hpIV:5;
    /*0x14*/ u32 attackIV:5;
    /*0x15*/ u32 defenseIV:5;
    /*0x15*/ u32 speedIV:5;
    /*0x16*/ u32 spAttackIV:5;
    /*0x17*/ u32 spDefenseIV:5;
    /*0x17*/ u32 isEgg:1;
    /*0x17*/ u32 abilityNum:1;
    /*0x18*/ s8 statStages[8];
    /*0x20*/ u8 ability;
    /*0x21*/ u8 type1;
    /*0x22*/ u8 type2;
    /*0x23*/ u8 unknown;
    /*0x24*/ u8 pp[4];
    /*0x28*/ u16 hp;
    /*0x2A*/ u8 level;
    /*0x2B*/ u8 friendship;
    /*0x2C*/ u16 maxHP;
    /*0x2E*/ u16 item;
    /*0x30*/ u8 nickname[10 + 1];
    /*0x3B*/ u8 ppBonuses;
    /*0x3C*/ u8 otName[8];
    /*0x44*/ u32 experience;
    /*0x48*/ u32 personality;
    /*0x4C*/ u32 status1;
    /*0x50*/ u32 status2;
    /*0x54*/ u32 otId;
};


extern const u8 *gBattlescriptCurrInstr;
extern u16 gBattleMovePower;
extern const struct BattleMove gBattleMoves[];
extern const u8 sHoldEffectToType[][2];
extern u32 gBattleTypeFlags;
extern u16 gCurrentMove;
extern u8 gCritMultiplier;
extern const u8 gStatStageRatios[][2];
extern u32 gBattleWeather;
extern struct BattlePokemon gBattleMons[];

u32 AbilityBattleEffects(u32 arg0, u32 arg1, u32 ability, u32 arg3, u32 arg4);
u32 CountAliveMonsInBattle(u32 arg0);

u8 ItemId_GetHoldEffect(u16 itemId);
u8 ItemId_GetHoldEffectParam(u16 itemId);

#endif // GUARD_BATTLE_H
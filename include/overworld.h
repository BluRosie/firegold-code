#ifndef GUARD_OVERWORLD_H
#define GUARD_OVERWORLD_H



#include "save.h"


// rock climb stuff

// https://github.com/pret/pokefirered/blob/master/include/constants/field_effects.h
#define FLDEFFOBJ_SHADOW_S                  0
#define FLDEFFOBJ_SHADOW_M                  1
#define FLDEFFOBJ_SHADOW_L                  2
#define FLDEFFOBJ_SHADOW_XL                 3
#define FLDEFFOBJ_TALL_GRASS                4
#define FLDEFFOBJ_RIPPLE                    5
#define FLDEFFOBJ_ASH                       6
#define FLDEFFOBJ_SURF_BLOB                 7
#define FLDEFFOBJ_ARROW                     8
#define FLDEFFOBJ_GROUND_IMPACT_DUST        9
#define FLDEFFOBJ_JUMP_TALL_GRASS          10
#define FLDEFFOBJ_SAND_FOOTPRINTS          11
#define FLDEFFOBJ_JUMP_BIG_SPLASH          12
#define FLDEFFOBJ_SPLASH                   13
#define FLDEFFOBJ_JUMP_SMALL_SPLASH        14
#define FLDEFFOBJ_LONG_GRASS               15
#define FLDEFFOBJ_JUMP_LONG_GRASS          16
#define FLDEFFOBJ_UNUSED_GRASS             17
#define FLDEFFOBJ_UNUSED_GRASS_2           18
#define FLDEFFOBJ_UNUSED_SAND              19
#define FLDEFFOBJ_WATER_SURFACING          20
#define FLDEFFOBJ_REFLECTION_DISTORTION    21
#define FLDEFFOBJ_SPARKLE                  22
#define FLDEFFOBJ_DEEP_SAND_FOOTPRINTS     23
#define FLDEFFOBJ_TREE_DISGUISE            24
#define FLDEFFOBJ_MOUNTAIN_DISGUISE        25
#define FLDEFFOBJ_BIRD                     26
#define FLDEFFOBJ_BIKE_TIRE_TRACKS         27
#define FLDEFFOBJ_SAND_DISGUISE            28
#define FLDEFFOBJ_SAND_PILE                29
#define FLDEFFOBJ_SHORT_GRASS              30
#define FLDEFFOBJ_HOT_SPRINGS_WATER        31
#define FLDEFFOBJ_ASH_PUFF                 32
#define FLDEFFOBJ_ASH_LAUNCH               33
#define FLDEFFOBJ_BUBBLES                  34
#define FLDEFFOBJ_SMALL_SPARKLE            35
#define FLDEFFOBJ_ROCK_CLIMB_BLOB          36
#define FLDEFFOBJ_ROCK_CLIMB_DUST          37

#define FLDEFFOBJ_NEW_TEMPLATES FLDEFFOBJ_ROCK_CLIMB_BLOB


#define FLDEFF_EXCLAMATION_MARK_ICON      0
#define FLDEFF_USE_CUT_ON_GRASS           1
#define FLDEFF_USE_CUT_ON_TREE            2
#define FLDEFF_SHADOW                     3
#define FLDEFF_TALL_GRASS                 4
#define FLDEFF_RIPPLE                     5
#define FLDEFF_FIELD_MOVE_SHOW_MON        6
#define FLDEFF_ASH                        7
#define FLDEFF_SURF_BLOB                  8
#define FLDEFF_USE_SURF                   9
#define FLDEFF_DUST                      10
#define FLDEFF_USE_SECRET_POWER_CAVE     11
#define FLDEFF_JUMP_TALL_GRASS           12
#define FLDEFF_SAND_FOOTPRINTS           13
#define FLDEFF_JUMP_BIG_SPLASH           14
#define FLDEFF_SPLASH                    15
#define FLDEFF_JUMP_SMALL_SPLASH         16
#define FLDEFF_LONG_GRASS                17
#define FLDEFF_JUMP_LONG_GRASS           18
#define FLDEFF_UNUSED_GRASS              19
#define FLDEFF_UNUSED_GRASS_2            20
#define FLDEFF_UNUSED_SAND               21
#define FLDEFF_UNUSED_WATER_SURFACING    22
#define FLDEFF_BERRY_TREE_GROWTH_SPARKLE 23
#define FLDEFF_DEEP_SAND_FOOTPRINTS      24
#define FLDEFF_POKECENTER_HEAL           25
#define FLDEFF_USE_SECRET_POWER_TREE     26
#define FLDEFF_USE_SECRET_POWER_SHRUB    27
#define FLDEFF_TREE_DISGUISE             28
#define FLDEFF_MOUNTAIN_DISGUISE         29
#define FLDEFF_NPCFLY_OUT                30
#define FLDEFF_FLY_OUT                   31
#define FLDEFF_FLY_IN                    32
#define FLDEFF_QUESTION_MARK_ICON        33
#define FLDEFF_FEET_IN_FLOWING_WATER     34
#define FLDEFF_BIKE_TIRE_TRACKS          35
#define FLDEFF_SAND_DISGUISE             36
#define FLDEFF_USE_ROCK_SMASH            37
#define FLDEFF_USE_DIG                   38
#define FLDEFF_SAND_PILE                 39
#define FLDEFF_USE_STRENGTH              40
#define FLDEFF_SHORT_GRASS               41
#define FLDEFF_HOT_SPRINGS_WATER         42
#define FLDEFF_USE_WATERFALL             43
#define FLDEFF_USE_DIVE                  44
#define FLDEFF_POKEBALL                  45
#define FLDEFF_X_ICON                    46
#define FLDEFF_NOP_47                    47
#define FLDEFF_NOP_48                    48
#define FLDEFF_POP_OUT_OF_ASH            49
#define FLDEFF_LAVARIDGE_GYM_WARP        50
#define FLDEFF_SWEET_SCENT               51
#define FLDEFF_SAND_PILLAR               52
#define FLDEFF_BUBBLES                   53
#define FLDEFF_SPARKLE                   54
#define FLDEFF_SECRET_POWER_CAVE         55
#define FLDEFF_SECRET_POWER_TREE         56
#define FLDEFF_SECRET_POWER_SHRUB        57
#define FLDEFF_CUT_GRASS                 58
#define FLDEFF_FIELD_MOVE_SHOW_MON_INIT  59
#define FLDEFF_USE_FLY_ANCIENT_TOMB      60
#define FLDEFF_PCTURN_ON                 61
#define FLDEFF_HALL_OF_FAME_RECORD       62
#define FLDEFF_USE_TELEPORT              63
#define FLDEFF_SMILEY_FACE_ICON          64
#define FLDEFF_USE_VS_SEEKER             65
#define FLDEFF_DOUBLE_EXCL_MARK_ICON     66
#define FLDEFF_MOVE_DEOXYS_ROCK          67
#define FLDEFF_DESTROY_DEOXYS_ROCK       68
#define FLDEFF_PHOTO_FLASH               69
#define FLDEFF_USE_ROCK_CLIMB 70
#define FLDEFF_ROCK_CLIMB_DUST 71

#define START_OF_NEW_FLD_EFF FLDEFF_USE_ROCK_CLIMB

#define FLDEFF_PAL_TAG_DUST_CLOUD         0x1010
#define FLDEFF_PAL_TAG_ROCK_CLIMB_BLOB    0x1011



// movement actions, may need some of these if i decide to do diagonal
#define MOVEMENT_ACTION_FACE_DOWN                       0x0
#define MOVEMENT_ACTION_FACE_UP                         0x1
#define MOVEMENT_ACTION_FACE_LEFT                       0x2
#define MOVEMENT_ACTION_FACE_RIGHT                      0x3
#define MOVEMENT_ACTION_FACE_DOWN_FAST                  0x4
#define MOVEMENT_ACTION_FACE_UP_FAST                    0x5
#define MOVEMENT_ACTION_FACE_LEFT_FAST                  0x6
#define MOVEMENT_ACTION_FACE_RIGHT_FAST                 0x7
#define MOVEMENT_ACTION_WALK_SLOWER_DOWN                0x8
#define MOVEMENT_ACTION_WALK_SLOWER_UP                  0x9
#define MOVEMENT_ACTION_WALK_SLOWER_LEFT                0xA
#define MOVEMENT_ACTION_WALK_SLOWER_RIGHT               0xB
#define MOVEMENT_ACTION_WALK_SLOW_DOWN                  0xC
#define MOVEMENT_ACTION_WALK_SLOW_UP                    0xD
#define MOVEMENT_ACTION_WALK_SLOW_LEFT                  0xE
#define MOVEMENT_ACTION_WALK_SLOW_RIGHT                 0xF
#define MOVEMENT_ACTION_WALK_NORMAL_DOWN                0x10
#define MOVEMENT_ACTION_WALK_NORMAL_UP                  0x11
#define MOVEMENT_ACTION_WALK_NORMAL_LEFT                0x12
#define MOVEMENT_ACTION_WALK_NORMAL_RIGHT               0x13
#define MOVEMENT_ACTION_JUMP_2_DOWN                     0x14
#define MOVEMENT_ACTION_JUMP_2_UP                       0x15
#define MOVEMENT_ACTION_JUMP_2_LEFT                     0x16
#define MOVEMENT_ACTION_JUMP_2_RIGHT                    0x17
#define MOVEMENT_ACTION_DELAY_1                         0x18
#define MOVEMENT_ACTION_DELAY_2                         0x19
#define MOVEMENT_ACTION_DELAY_4                         0x1A
#define MOVEMENT_ACTION_DELAY_8                         0x1B
#define MOVEMENT_ACTION_DELAY_16                        0x1C
#define MOVEMENT_ACTION_WALK_FAST_DOWN                  0x1D
#define MOVEMENT_ACTION_WALK_FAST_UP                    0x1E
#define MOVEMENT_ACTION_WALK_FAST_LEFT                  0x1F
#define MOVEMENT_ACTION_WALK_FAST_RIGHT                 0x20
#define MOVEMENT_ACTION_WALK_IN_PLACE_SLOW_DOWN         0x21
#define MOVEMENT_ACTION_WALK_IN_PLACE_SLOW_UP           0x22
#define MOVEMENT_ACTION_WALK_IN_PLACE_SLOW_LEFT         0x23
#define MOVEMENT_ACTION_WALK_IN_PLACE_SLOW_RIGHT        0x24
#define MOVEMENT_ACTION_WALK_IN_PLACE_NORMAL_DOWN       0x25
#define MOVEMENT_ACTION_WALK_IN_PLACE_NORMAL_UP         0x26
#define MOVEMENT_ACTION_WALK_IN_PLACE_NORMAL_LEFT       0x27
#define MOVEMENT_ACTION_WALK_IN_PLACE_NORMAL_RIGHT      0x28
#define MOVEMENT_ACTION_WALK_IN_PLACE_FAST_DOWN         0x29
#define MOVEMENT_ACTION_WALK_IN_PLACE_FAST_UP           0x2A
#define MOVEMENT_ACTION_WALK_IN_PLACE_FAST_LEFT         0x2B
#define MOVEMENT_ACTION_WALK_IN_PLACE_FAST_RIGHT        0x2C
#define MOVEMENT_ACTION_WALK_IN_PLACE_FASTER_DOWN       0x2D
#define MOVEMENT_ACTION_WALK_IN_PLACE_FASTER_UP         0x2E
#define MOVEMENT_ACTION_WALK_IN_PLACE_FASTER_LEFT       0x2F
#define MOVEMENT_ACTION_WALK_IN_PLACE_FASTER_RIGHT      0x30
#define MOVEMENT_ACTION_RIDE_WATER_CURRENT_DOWN         0x31
#define MOVEMENT_ACTION_RIDE_WATER_CURRENT_UP           0x32
#define MOVEMENT_ACTION_RIDE_WATER_CURRENT_LEFT         0x33
#define MOVEMENT_ACTION_RIDE_WATER_CURRENT_RIGHT        0x34
#define MOVEMENT_ACTION_WALK_FASTER_DOWN                0x35
#define MOVEMENT_ACTION_WALK_FASTER_UP                  0x36
#define MOVEMENT_ACTION_WALK_FASTER_LEFT                0x37
#define MOVEMENT_ACTION_WALK_FASTER_RIGHT               0x38
#define MOVEMENT_ACTION_SLIDE_DOWN                      0x39
#define MOVEMENT_ACTION_SLIDE_UP                        0x3A
#define MOVEMENT_ACTION_SLIDE_LEFT                      0x3B
#define MOVEMENT_ACTION_SLIDE_RIGHT                     0x3C
#define MOVEMENT_ACTION_PLAYER_RUN_DOWN                 0x3D
#define MOVEMENT_ACTION_PLAYER_RUN_UP                   0x3E
#define MOVEMENT_ACTION_PLAYER_RUN_LEFT                 0x3F
#define MOVEMENT_ACTION_PLAYER_RUN_RIGHT                0x40
#define MOVEMENT_ACTION_PLAYER_RUN_DOWN_SLOW            0x41
#define MOVEMENT_ACTION_PLAYER_RUN_UP_SLOW              0x42
#define MOVEMENT_ACTION_PLAYER_RUN_LEFT_SLOW            0x43
#define MOVEMENT_ACTION_PLAYER_RUN_RIGHT_SLOW           0x44
#define MOVEMENT_ACTION_START_ANIM_IN_DIRECTION         0x45
#define MOVEMENT_ACTION_JUMP_SPECIAL_DOWN               0x46
#define MOVEMENT_ACTION_JUMP_SPECIAL_UP                 0x47
#define MOVEMENT_ACTION_JUMP_SPECIAL_LEFT               0x48
#define MOVEMENT_ACTION_JUMP_SPECIAL_RIGHT              0x49
#define MOVEMENT_ACTION_FACE_PLAYER                     0x4A
#define MOVEMENT_ACTION_FACE_AWAY_PLAYER                0x4B
#define MOVEMENT_ACTION_LOCK_FACING_DIRECTION           0x4C
#define MOVEMENT_ACTION_UNLOCK_FACING_DIRECTION         0x4D
#define MOVEMENT_ACTION_JUMP_DOWN                       0x4E
#define MOVEMENT_ACTION_JUMP_UP                         0x4F
#define MOVEMENT_ACTION_JUMP_LEFT                       0x50
#define MOVEMENT_ACTION_JUMP_RIGHT                      0x51
#define MOVEMENT_ACTION_JUMP_IN_PLACE_DOWN              0x52
#define MOVEMENT_ACTION_JUMP_IN_PLACE_UP                0x53
#define MOVEMENT_ACTION_JUMP_IN_PLACE_LEFT              0x54
#define MOVEMENT_ACTION_JUMP_IN_PLACE_RIGHT             0x55
#define MOVEMENT_ACTION_JUMP_IN_PLACE_DOWN_UP           0x56
#define MOVEMENT_ACTION_JUMP_IN_PLACE_UP_DOWN           0x57
#define MOVEMENT_ACTION_JUMP_IN_PLACE_LEFT_RIGHT        0x58
#define MOVEMENT_ACTION_JUMP_IN_PLACE_RIGHT_LEFT        0x59
#define MOVEMENT_ACTION_FACE_ORIGINAL_DIRECTION         0x5A
#define MOVEMENT_ACTION_NURSE_JOY_BOW_DOWN              0x5B
#define MOVEMENT_ACTION_ENABLE_JUMP_LANDING_GROUND_EFFECT 0x5C
#define MOVEMENT_ACTION_DISABLE_JUMP_LANDING_GROUND_EFFECT 0x5D
#define MOVEMENT_ACTION_DISABLE_ANIMATION               0x5E
#define MOVEMENT_ACTION_RESTORE_ANIMATION               0x5F
#define MOVEMENT_ACTION_SET_INVISIBLE                   0x60
#define MOVEMENT_ACTION_SET_VISIBLE                     0x61
#define MOVEMENT_ACTION_EMOTE_EXCLAMATION_MARK          0x62
#define MOVEMENT_ACTION_EMOTE_QUESTION_MARK             0x63
#define MOVEMENT_ACTION_EMOTE_X                         0x64
#define MOVEMENT_ACTION_EMOTE_DOUBLE_EXCL_MARK          0x65
#define MOVEMENT_ACTION_EMOTE_SMILE                     0x66
#define MOVEMENT_ACTION_REVEAL_TRAINER                  0x67
#define MOVEMENT_ACTION_ROCK_SMASH_BREAK                0x68
#define MOVEMENT_ACTION_CUT_TREE                        0x69
#define MOVEMENT_ACTION_SET_FIXED_PRIORITY              0x6A
#define MOVEMENT_ACTION_CLEAR_FIXED_PRIORITY            0x6B
#define MOVEMENT_ACTION_INIT_AFFINE_ANIM                0x6C
#define MOVEMENT_ACTION_CLEAR_AFFINE_ANIM               0x6D

// These still exist in FRLG for some reason. They're not used by anything obvious.
#define MOVEMENT_ACTION_WALK_DOWN_START_AFFINE          0x6E
#define MOVEMENT_ACTION_WALK_DOWN_AFFINE                0x6F
#define MOVEMENT_ACTION_ACRO_WHEELIE_FACE_DOWN          0x70
#define MOVEMENT_ACTION_ACRO_WHEELIE_FACE_UP            0x71
#define MOVEMENT_ACTION_ACRO_WHEELIE_FACE_LEFT          0x72
#define MOVEMENT_ACTION_ACRO_WHEELIE_FACE_RIGHT         0x73
#define MOVEMENT_ACTION_ACRO_POP_WHEELIE_DOWN           0x74
#define MOVEMENT_ACTION_ACRO_POP_WHEELIE_UP             0x75
#define MOVEMENT_ACTION_ACRO_POP_WHEELIE_LEFT           0x76
#define MOVEMENT_ACTION_ACRO_POP_WHEELIE_RIGHT          0x77
#define MOVEMENT_ACTION_ACRO_END_WHEELIE_FACE_DOWN      0x78
#define MOVEMENT_ACTION_ACRO_END_WHEELIE_FACE_UP        0x79
#define MOVEMENT_ACTION_ACRO_END_WHEELIE_FACE_LEFT      0x7A
#define MOVEMENT_ACTION_ACRO_END_WHEELIE_FACE_RIGHT     0x7B
#define MOVEMENT_ACTION_ACRO_WHEELIE_HOP_FACE_DOWN      0x7C
#define MOVEMENT_ACTION_ACRO_WHEELIE_HOP_FACE_UP        0x7D
#define MOVEMENT_ACTION_ACRO_WHEELIE_HOP_FACE_LEFT      0x7E
#define MOVEMENT_ACTION_ACRO_WHEELIE_HOP_FACE_RIGHT     0x7F
#define MOVEMENT_ACTION_ACRO_WHEELIE_HOP_DOWN           0x80
#define MOVEMENT_ACTION_ACRO_WHEELIE_HOP_UP             0x81
#define MOVEMENT_ACTION_ACRO_WHEELIE_HOP_LEFT           0x82
#define MOVEMENT_ACTION_ACRO_WHEELIE_HOP_RIGHT          0x83
#define MOVEMENT_ACTION_ACRO_WHEELIE_JUMP_DOWN          0x84
#define MOVEMENT_ACTION_ACRO_WHEELIE_JUMP_UP            0x85
#define MOVEMENT_ACTION_ACRO_WHEELIE_JUMP_LEFT          0x86
#define MOVEMENT_ACTION_ACRO_WHEELIE_JUMP_RIGHT         0x87
#define MOVEMENT_ACTION_ACRO_WHEELIE_IN_PLACE_DOWN      0x88
#define MOVEMENT_ACTION_ACRO_WHEELIE_IN_PLACE_UP        0x89
#define MOVEMENT_ACTION_ACRO_WHEELIE_IN_PLACE_LEFT      0x8A
#define MOVEMENT_ACTION_ACRO_WHEELIE_IN_PLACE_RIGHT     0x8B
#define MOVEMENT_ACTION_ACRO_POP_WHEELIE_MOVE_DOWN      0x8C
#define MOVEMENT_ACTION_ACRO_POP_WHEELIE_MOVE_UP        0x8D
#define MOVEMENT_ACTION_ACRO_POP_WHEELIE_MOVE_LEFT      0x8E
#define MOVEMENT_ACTION_ACRO_POP_WHEELIE_MOVE_RIGHT     0x8F
#define MOVEMENT_ACTION_ACRO_WHEELIE_MOVE_DOWN          0x90
#define MOVEMENT_ACTION_ACRO_WHEELIE_MOVE_UP            0x91
#define MOVEMENT_ACTION_ACRO_WHEELIE_MOVE_LEFT          0x92
#define MOVEMENT_ACTION_ACRO_WHEELIE_MOVE_RIGHT         0x93

#define MOVEMENT_ACTION_SPIN_DOWN                       0x94
#define MOVEMENT_ACTION_SPIN_UP                         0x95
#define MOVEMENT_ACTION_SPIN_LEFT                       0x96
#define MOVEMENT_ACTION_SPIN_RIGHT                      0x97
#define MOVEMENT_ACTION_RAISE_HAND_AND_STOP             0x98
#define MOVEMENT_ACTION_RAISE_HAND_AND_JUMP             0x99
#define MOVEMENT_ACTION_RAISE_HAND_AND_SWIM             0x9A
#define MOVEMENT_ACTION_WALK_SLOWEST_DOWN               0x9B
#define MOVEMENT_ACTION_WALK_SLOWEST_UP                 0x9C
#define MOVEMENT_ACTION_WALK_SLOWEST_LEFT               0x9D
#define MOVEMENT_ACTION_WALK_SLOWEST_RIGHT              0x9E
#define MOVEMENT_ACTION_SHAKE_HEAD_OR_WALK_IN_PLACE     0x9F
#define MOVEMENT_ACTION_GLIDE_DOWN                      0xA0
#define MOVEMENT_ACTION_GLIDE_UP                        0xA1
#define MOVEMENT_ACTION_GLIDE_LEFT                      0xA2
#define MOVEMENT_ACTION_GLIDE_RIGHT                     0xA3
#define MOVEMENT_ACTION_FLY_UP                          0xA4
#define MOVEMENT_ACTION_FLY_DOWN                        0xA5
#define MOVEMENT_ACTION_JUMP_SPECIAL_WITH_EFFECT_DOWN   0xA6
#define MOVEMENT_ACTION_JUMP_SPECIAL_WITH_EFFECT_UP     0xA7
#define MOVEMENT_ACTION_JUMP_SPECIAL_WITH_EFFECT_LEFT   0xA8
#define MOVEMENT_ACTION_JUMP_SPECIAL_WITH_EFFECT_RIGHT  0xA9



#define MB_ROCK_CLIMB 0xA5


extern const struct SpriteTemplate *const gFieldEffectObjectTemplatePointers[];
//extern const struct SpriteTemplate *const gNewFieldEffectObjectTemplatePointers[];


enum {
    PLAYER_AVATAR_GFX_NORMAL,
    PLAYER_AVATAR_GFX_BIKE,
    PLAYER_AVATAR_GFX_RIDE,
    PLAYER_AVATAR_GFX_FIELD_MOVE,
    PLAYER_AVATAR_GFX_FISH,
    PLAYER_AVATAR_GFX_VSSEEKER,
};


enum {
    PLAYER_AVATAR_STATE_NORMAL,
    PLAYER_AVATAR_STATE_MACH_BIKE,
    PLAYER_AVATAR_STATE_ACRO_BIKE,
    PLAYER_AVATAR_STATE_SURFING,
    PLAYER_AVATAR_STATE_UNDERWATER,
    PLAYER_AVATAR_STATE_CONTROLLABLE,
    PLAYER_AVATAR_STATE_FORCED,
    PLAYER_AVATAR_STATE_DASH,
};

#define PLAYER_AVATAR_FLAG_ON_FOOT      (1 << PLAYER_AVATAR_STATE_NORMAL)
#define PLAYER_AVATAR_FLAG_MACH_BIKE    (1 << PLAYER_AVATAR_STATE_MACH_BIKE)
#define PLAYER_AVATAR_FLAG_ACRO_BIKE    (1 << PLAYER_AVATAR_STATE_ACRO_BIKE)
#define PLAYER_AVATAR_FLAG_SURFING      (1 << PLAYER_AVATAR_STATE_SURFING)
#define PLAYER_AVATAR_FLAG_UNDERWATER   (1 << PLAYER_AVATAR_STATE_UNDERWATER)
#define PLAYER_AVATAR_FLAG_CONTROLLABLE (1 << PLAYER_AVATAR_STATE_CONTROLLABLE)
#define PLAYER_AVATAR_FLAG_FORCED       (1 << PLAYER_AVATAR_STATE_FORCED)
#define PLAYER_AVATAR_FLAG_DASH         (1 << PLAYER_AVATAR_STATE_DASH)

// bob state lol
enum {
    BOB_NONE,
    BOB_PLAYER_AND_MON,
    BOB_MON_ONLY, // when player has jumped / flown off
};

extern u32 gFieldEffectArguments[];


#define invokedFromOW data[3]

void CB2_ReturnToField(void);
void CB2_ReturnToBag(void);
void PrepareOverworldReturn();
void FreeOverworldBGs();
void GetInFrontOfPlayerPosition(struct MapPosition * position);
u32 MapGridGetMetatileBehaviorAt(s16 x, s16 y);
u32 MapGridGetMetatileAttributeAt(s16 x, s16 y);

void SetSpritePosToOffsetMapCoords(s16 *, s16 *, s16, s16);
void FreezeObjectEvents(void);
void SetPlayerAvatarStateMask(u32);
void MoveCoords(u32 dir, s16 *destX, s16 *destY);
bool32 ObjectEventIsMovementOverridden(struct ObjectEvent *obj);
bool32 ObjectEventClearHeldMovementIfFinished(struct ObjectEvent *obj);
void StartPlayerAvatarSummonMonForFieldMoveAnim(void);
void ObjectEventSetHeldMovement(struct ObjectEvent *objectEvent, u32 movAction);
bool32 ObjectEventCheckHeldMovementStatus(struct ObjectEvent *objectEvent);
bool32 FieldEffectActiveListContains(u32 fldeff);
u32 GetPlayerAvatarGraphicsIdByStateId(u32 state);
void ObjectEventSetGraphicsId(struct ObjectEvent *objectEvent, u32 id);
u32 GetJumpSpecialMovementAction(u32 dir);
u32 SetSurfBlob_BobState(u32 spriteId, u32 state);
void UnfreezeObjectEvents(void);
void FieldEffectActiveListRemove(u32 id);
void GetXYCoordsOneStepInFrontOfPlayer(s16 *x, s16 *y);

#endif // GUARD_OVERWORLD_H

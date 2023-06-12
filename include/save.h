#ifndef SAVE_H
#define SAVE_H

#include "sprite.h"

// constant defines
#define OBJECT_EVENTS_COUNT 16
#define obj_frame_tiles(ptr) {.data = (u8 *)ptr, .size = sizeof ptr}

#define MAP_OFFSET 7
#define MAP_OFFSET_W (MAP_OFFSET * 2 + 1)
#define MAP_OFFSET_H (MAP_OFFSET * 2)

#define gTimeOfDay *((u8*)0x0203C000)
#define gCurrentTimeHours *((u8*)0x03005542)
#define gCurrentTimeMins *((u8*)0x03005543)
#define gCurrentTimeSeconds *((u8*)0x03005544)

// structure defines
struct ObjectEvent
{
    /*0x00*/ u32 active:1;
             u32 singleMovementActive:1;
             u32 triggerGroundEffectsOnMove:1;
             u32 triggerGroundEffectsOnStop:1;
             u32 disableCoveringGroundEffects:1;
             u32 landingJump:1;
             u32 heldMovementActive:1;
             u32 heldMovementFinished:1;
    /*0x01*/ u32 frozen:1;
             u32 facingDirectionLocked:1;
             u32 disableAnim:1;
             u32 enableAnim:1;
             u32 inanimate:1;
             u32 invisible:1;
             u32 offScreen:1;
             u32 trackedByCamera:1;
    /*0x02*/ u32 isPlayer:1;
             u32 hasReflection:1;
             u32 inShortGrass:1;
             u32 inShallowFlowingWater:1;
             u32 inSandPile:1;
             u32 inHotSprings:1;
             u32 noShadow:1;
             u32 spriteAnimPausedBackup:1;
    /*0x03*/ u32 spriteAffineAnimPausedBackup:1;
             u32 disableJumpLandingGroundEffect:1;
             u32 fixedPriority:1;
             u32 hideReflection:1;
    /*0x04*/ u8 spriteId;
    /*0x05*/ u8 graphicsId;
    /*0x06*/ u8 movementType;
    /*0x07*/ u8 trainerType;
    /*0x08*/ u8 localId;
    /*0x09*/ u8 mapNum;
    /*0x0A*/ u8 mapGroup;
    /*0x0B*/ u8 currentElevation:4;
             u8 previousElevation:4;
    /*0x0C*/ struct Coords16 initialCoords;
    /*0x10*/ struct Coords16 currentCoords;
    /*0x14*/ struct Coords16 previousCoords;
    /*0x18*/ u16 facingDirection:4; // current direction?
             u16 movementDirection:4;
             u16 rangeX:4;
             u16 rangeY:4;
    /*0x1A*/ u8 fieldEffectSpriteId;
    /*0x1B*/ u8 warpArrowSpriteId;
    /*0x1C*/ u8 movementActionId;
    /*0x1D*/ u8 trainerRange_berryTreeId;
    /*0x1E*/ u8 currentMetatileBehavior;
    /*0x1F*/ u8 previousMetatileBehavior;
    /*0x20*/ u8 previousMovementDirection;
    /*0x21*/ u8 directionSequenceIndex;
    /*0x22*/ u8 playerCopyableMovement;
    /*size = 0x24*/
};

struct ObjectEventTemplate
{
    /*0x00*/ u8 localId;
    /*0x01*/ u8 graphicsId;
    /*0x02*/ u8 inConnection;
    /*0x04*/ s16 x;
    /*0x06*/ s16 y;
    /*0x08*/ u8 elevation;
    /*0x09*/ u8 movementType;
    /*0x0A*/ u16 movementRangeX:4;
             u16 movementRangeY:4;
    /*0x0C*/ u16 trainerType;
    /*0x0E*/ u16 trainerRange_berryTreeId;
    /*0x10*/ const u8 *script;
    /*0x14*/ u16 flagId;
};  /*size = 0x18*/

struct WarpData
{
    s8 mapGroup;
    s8 mapNum;
    s8 warpId;
    s16 x, y;
};

struct SaveBlock1
{
    /*0x0000*/ struct Coords16 pos;
    /*0x0004*/ struct WarpData location;
    /*0x000C*/ //struct WarpData continueGameWarp;
    /*0x0014*/ //struct WarpData dynamicWarp;
    /*0x001C*/ //struct WarpData lastHealLocation;
    /*0x0024*/ //struct WarpData escapeWarp;
    /*0x002C*/ //u16 savedMusic;
    /*0x002E*/ //u8 weather;
    /*0x002F*/ //u8 weatherCycleStage;
    /*0x0030*/ //u8 flashLevel;
    /*0x0032*/ //u16 mapLayoutId;
    /*0x0034*/ //u8 playerPartyCount;
    /*0x0038*/ //struct Pokemon playerParty[PARTY_SIZE];
               u8 padding_4[0x290-0xC];
    /*0x0290*/ u32 money;
    /*0x0294*/ //u16 coins;
    /*0x0296*/ //u16 registeredItem; // registered for use with SELECT button
    /*0x0298*/ //struct ItemSlot pcItems[PC_ITEMS_COUNT];
    /*0x0310*/ //struct ItemSlot bagPocket_Items[BAG_ITEMS_COUNT];
    /*0x03b8*/ //struct ItemSlot bagPocket_KeyItems[BAG_KEYITEMS_COUNT];
    /*0x0430*/ //struct ItemSlot bagPocket_PokeBalls[BAG_POKEBALLS_COUNT];
    /*0x0464*/ //struct ItemSlot bagPocket_TMHM[BAG_TMHM_COUNT];
    /*0x054c*/ //struct ItemSlot bagPocket_Berries[BAG_BERRIES_COUNT];
    /*0x05F8*/ //u8 seen1[DEX_FLAGS_NO];
    /*0x062C*/ //u16 berryBlenderRecords[3]; // unused
    /*0x0632*/ //u8 unused_632[6];
    /*0x0638*/ //u16 trainerRematchStepCounter;
    /*0x063A*/ //u8 ALIGNED(2) trainerRematches[MAX_REMATCH_ENTRIES];
    /*0x06A0*/ //struct ObjectEvent objectEvents[OBJECT_EVENTS_COUNT];
               u8 padding[0x8E0-0x294]; // padding to get object event templates where they need to be
    /*0x08E0*/ struct ObjectEventTemplate objectEventTemplates[16];
    /*0x0EE0*/ //u8 flags[NUM_FLAG_BYTES];
    /*0x1000*/ //u16 vars[VARS_COUNT];
    /*0x1200*/ //u32 gameStats[NUM_GAME_STATS];
    /*0x1300*/ //struct QuestLog questLog[QUEST_LOG_SCENE_COUNT];
               u8 padding_EE0[0x2CA0-0xEE0];
    /*0x2CA0*/ u16 easyChatProfile[6];
    /*0x2CAC*/ u16 easyChatBattleStart[6];
    /*0x2CB8*/ u16 easyChatBattleWon[6];
    /*0x2CC4*/ u16 easyChatBattleLost[6];
    /*0x2CD0*/ //struct Mail mail[MAIL_COUNT];
    /*0x2F10*/ //u8 additionalPhrases[NUM_ADDITIONAL_PHRASE_BYTES];
    /*0x2F18*/ //OldMan oldMan; // unused
    /*0x2F54*/ //struct DewfordTrend dewfordTrends[5]; // unused
    /*0x2F80*/ //struct DayCare daycare;
    /*0x309C*/ //u8 giftRibbons[GIFT_RIBBONS_COUNT];
    /*0x30A7*/ //struct ExternalEventData externalEventData;
    /*0x30BB*/ //struct ExternalEventFlags externalEventFlags;
    /*0x30D0*/ //struct Roamer roamer;
    /*0x30EC*/ //struct EnigmaBerry enigmaBerry;
    /*0x3120*/ //struct MysteryGiftSave mysteryGift;
    /*0x348C*/ //u8 unused_348C[400];
    /*0x361C*/ //struct RamScript ramScript;
    /*0x3A08*/ //struct RecordMixingGift recordMixingGift; // unused
    /*0x3A18*/ //u8 seen2[DEX_FLAGS_NO];
    /*0x3A4C*/ //u8 rivalName[PLAYER_NAME_LENGTH + 1];
    /*0x3A54*/ //struct FameCheckerSaveData fameChecker[NUM_FAMECHECKER_PERSONS];
    /*0x3A94*/ //u8 unused_3A94[64];
    /*0x3AD4*/ //u8 registeredTexts[UNION_ROOM_KB_ROW_COUNT][21];
    /*0x3BA8*/ //struct TrainerNameRecord trainerNameRecords[20];
    /*0x3C98*/ //struct DaycareMon route5DayCareMon;
    /*0x3D24*/ //u8 unused_3D24[16];
    /*0x3D34*/ //u32 towerChallengeId;
    /*0x3D38*/ //struct TrainerTower trainerTower[NUM_TOWER_CHALLENGE_TYPES];
}; // size: 0x3D68

struct LinkBattleRecord
{
    u8 name[8];
    u16 trainerId;
    u16 wins;
    u16 losses;
    u16 draws;
};

struct LinkBattleRecords
{
    struct LinkBattleRecord entries[5];
    u8 languages[5];
};

struct SaveBlock2
{
    /*0x000*/ u8 playerName[7 + 1];
    /*0x008*/ u8 playerGender; // MALE, FEMALE
    /*0x009*/ u8 specialSaveWarpFlags;
    /*0x00A*/ u8 playerTrainerId[4];
    /*0x00E*/ u16 playTimeHours;
    /*0x010*/ u8 playTimeMinutes;
    /*0x011*/ u8 playTimeSeconds;
    /*0x012*/ u8 playTimeVBlanks;
    /*0x013*/ u8 optionsButtonMode;  // OPTIONS_BUTTON_MODE_[NORMAL/LR/L_EQUALS_A]
    /*0x014*/ u16 optionsTextSpeed:3; // OPTIONS_TEXT_SPEED_[SLOW/MID/FAST]
              u16 optionsWindowFrameType:5; // Specifies one of the 20 decorative borders for text boxes
    /*0x15*/  u16 optionsSound:1; // OPTIONS_SOUND_[MONO/STEREO]
              u16 optionsBattleStyle:1; // OPTIONS_BATTLE_STYLE_[SHIFT/SET]
              u16 optionsBattleSceneOff:1; // whether battle animations are disabled
              u16 regionMapZoom:1; // whether the map is zoomed in
              u8 padding_x16[2];
              u8 padding_x18[0xA98 - 0x18];

//    /*0x018*/ struct Pokedex pokedex;
//    /*0x090*/ u8 filler_90[0x8+8+8];
//    /*0x098*/ //struct Time localTimeOffset;
//    /*0x0A0*/ //struct Time lastBerryTreeUpdate;
//    /*0x0A8*/ u32 gcnLinkFlags; // Read by Pokemon Colosseum/XD
//    /*0x0AC*/ bool8 unkFlag1; // Set TRUE, never read
//    /*0x0AD*/ bool8 unkFlag2; // Set FALSE, never read
//    /*0x0B0*/ struct BattleTowerData battleTower;
//    /*0x898*/ u16 mapView[0x100];
    /*0xA98*/ struct LinkBattleRecords linkBattleRecords;
//    /*0xAF0*/ struct BerryCrush berryCrush;
//    /*0xB00*/ struct PokemonJumpRecords pokeJump;
//    /*0xB10*/ struct BerryPickingResults berryPick;
//    /*0xB20*/ u8 filler_B20[0x400];
//    /*0xF20*/ u32 encryptionKey;
}; // size: 0xF24

struct PlayerAvatar
{
    /*0x00*/ u8 flags;
    /*0x01*/ u8 transitionFlags; // used to be bike, but it's not that in Emerald and probably isn't here either. maybe transition flags?
    /*0x02*/ u8 runningState; // this is a static running state. 00 is not moving, 01 is turn direction, 02 is moving.
    /*0x03*/ u8 tileTransitionState; // this is a transition running state: 00 is not moving, 01 is transition between tiles, 02 means you are on the frame in which you have centered on a tile but are about to keep moving, even if changing directions. 2 is also used for a ledge hop, since you are transitioning.
    /*0x04*/ u8 spriteId;
    /*0x05*/ u8 objectEventId;
    /*0x06*/ bool8 preventStep;
    /*0x07*/ u8 gender;
    // These are not used in FRLG
    u8 acroBikeState;
    u8 newDirBackup;
    u8 bikeFrameCounter;
    u8 bikeSpeed;
    u32 directionHistory;
    u32 abStartSelectHistory;
    u8 dirTimerHistory[8];
    // For the Rocket mazes
    u16 lastSpinTile;
};

struct MapEvents
{
    u8 objectEventCount;
    u8 warpCount;
    u8 coordEventCount;
    u8 bgEventCount;
    struct ObjectEventTemplate *objectEvents;
    /*struct WarpEvent*/  void *warps;
    /*struct CoordEvent*/ void *coordEvents;
    /*struct BgEvent*/    void *bgEvents;
};

struct MapHeader
{
    /* 0x00 */ /*const struct MapLayout*/ void *mapLayout;
    /* 0x04 */ const struct MapEvents *events;
    /* 0x08 */ const u8 *mapScripts;
    /* 0x0C */ /*const struct MapConnections*/ void *connections;
    /* 0x10 */ u16 music;
    /* 0x12 */ u16 mapLayoutId;
    /* 0x14 */ u8 regionMapSectionId;
    /* 0x15 */ u8 cave;
    /* 0x16 */ u8 weather;
    /* 0x17 */ u8 mapType;
    /* 0x18 */ u8 filler_18[2];
               // fields correspond to the arguments in the map_header_flags macro
    /* 0x1A */ bool8 allowCycling:1;
               bool8 allowEscaping:1; // Escape Rope and Dig
               bool8 allowRunning:1;
               bool8 showMapName:5; // the last 4 bits are unused
                                    // but the 5 bit sized bitfield is required to match
    /* 0x1B */ u8 battleType;
};

struct BackupMapLayout
{
    s32 width;
    s32 height;
    u16 *map;
};

struct ObjectEvent gObjectEvents[OBJECT_EVENTS_COUNT];
struct SaveBlock1 *gSaveBlock1;
struct SaveBlock2 *gSaveBlock2;
struct PlayerAvatar gPlayerAvatar;
const union AnimCmd *const sAnimTable_Inanimate[];

struct MapHeader gMapHeader;

#endif

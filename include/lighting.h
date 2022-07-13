#ifndef LIGHTING_H
#define LIGHTING_H

// constant defines
#define OBJECT_EVENTS_COUNT 16
#define obj_frame_tiles(ptr) {.data = (u8 *)ptr, .size = sizeof ptr}

// struct defines
struct Coords16
{
    s16 x;
    s16 y;
};

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

struct SaveBlock1
{
    /*0x0000*/ struct Coords16 pos;
    /*0x0004*/ //struct WarpData location;
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
    /*0x0290*/ //u32 money;
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
               u8 padding[0x8E0-4]; // padding to get object event templates where they need to be
    /*0x08E0*/ struct ObjectEventTemplate objectEventTemplates[16];
    /*0x0EE0*/ //u8 flags[NUM_FLAG_BYTES];
    /*0x1000*/ //u16 vars[VARS_COUNT];
    /*0x1200*/ //u32 gameStats[NUM_GAME_STATS];
    /*0x1300*/ //struct QuestLog questLog[QUEST_LOG_SCENE_COUNT];
    /*0x2CA0*/ //u16 easyChatProfile[EASY_CHAT_BATTLE_WORDS_COUNT];
    /*0x2CAC*/ //u16 easyChatBattleStart[EASY_CHAT_BATTLE_WORDS_COUNT];
    /*0x2CB8*/ //u16 easyChatBattleWon[EASY_CHAT_BATTLE_WORDS_COUNT];
    /*0x2CC4*/ //u16 easyChatBattleLost[EASY_CHAT_BATTLE_WORDS_COUNT];
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

/*struct AnimFrameCmd
{
    // If the sprite has an array of images, this is the array index.
    // If the sprite has a sheet, this is the tile offset.
    u32 imageValue:16;

    u32 duration:6;
    u32 hFlip:1;
    u32 vFlip:1;
};

struct AnimLoopCmd
{
    u32 type:16;
    u32 count:6;
};

struct AnimJumpCmd
{
    u32 type:16;
    u32 target:6;
};

// The first halfword of this union specifies the type of command.
// If it -2, then it is a jump command. If it is -1, then it is the end of the script.
// Otherwise, it is the imageValue for a frame command.
union AnimCmd
{
    s16 type;
    struct AnimFrameCmd frame;
    struct AnimLoopCmd loop;
    struct AnimJumpCmd jump;
};*/

struct ObjectEvent gObjectEvents[OBJECT_EVENTS_COUNT];
struct SaveBlock1 *gSaveBlock1;
struct PlayerAvatar gPlayerAvatar;
static const union AnimCmd *const sAnimTable_Inanimate[];

void ClearPlayerAvatarInfo(void);
void ReloadMapObjectWithOffset(u32 i, s16 x, s16 y);
void CreateReflectionEffectSprites(void);
void FieldEffectFreeTilesIfUnused(u16 sheetTileStart);
void FieldEffectFreePaletteIfUnused(u32 paletteNum);
void Weather_SetBlendCoeffs(u32, u32); // tbh idk

#endif // LIGHTING_H
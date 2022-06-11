#ifndef GUARD_TRAINER_CARD_H
#define GUARD_TRAINER_CARD_H

#define NUM_BADGES 16

#define FLAG_BADGE_VIOLET 0x820
#define FLAG_BADGE_AZALEA 0x821
#define FLAG_BADGE_GOLDENROD 0x822
#define FLAG_BADGE_ECRUTEAK 0x823
#define FLAG_BADGE_CIANWOOD 0x824
#define FLAG_BADGE_OLIVINE 0x825
#define FLAG_BADGE_MAHOGANY 0x826
#define FLAG_BADGE_BLACKTHORN 0x827

#define FLAG_BADGE_PEWTER 0x2235
#define FLAG_BADGE_CERULEAN 0x2234
#define FLAG_BADGE_VERMILION 0x2230
#define FLAG_BADGE_CELADON 0x2232
#define FLAG_BADGE_FUCHSIA 0x2233
#define FLAG_BADGE_SAFFRON 0x2231
#define FLAG_BADGE_CINNABAR 0x2236
#define FLAG_BADGE_VIRIDIAN 0x2237


// struct defines taken from trainer_card.h in pokefirered


struct TrainerCardRSE
{
    /*0x00*/ u8 gender;
    /*0x01*/ u8 stars;
    /*0x02*/ bool8 hasPokedex;
    /*0x03*/ bool8 caughtAllHoenn;
    /*0x04*/ bool8 hasAllPaintings;
    /*0x06*/ u16 hofDebutHours;
    /*0x08*/ u16 hofDebutMinutes;
    /*0x0A*/ u16 hofDebutSeconds;
    /*0x0C*/ u16 caughtMonsCount;
    /*0x0E*/ u16 trainerId;
    /*0x10*/ u16 playTimeHours;
    /*0x12*/ u16 playTimeMinutes;
    /*0x14*/ u16 linkBattleWins;
    /*0x16*/ u16 linkBattleLosses;
    /*0x18*/ u16 battleTowerWins;
    /*0x1A*/ u16 battleTowerStraightWins;
    /*0x1C*/ u16 contestsWithFriends;
    /*0x1E*/ u16 pokeblocksWithFriends;
    /*0x20*/ u16 pokemonTrades;
    /*0x24*/ u32 money;
    /*0x28*/ u16 easyChatProfile[4];
    /*0x30*/ u8 playerName[7 + 1];
};

struct TrainerCard
{
    /*0x00*/ struct TrainerCardRSE rse;
    /*0x38*/ u8 version;
    /*0x3A*/ bool16 hasAllFrontierSymbols;
    /*0x3C*/ u32 berryCrushPoints;
    /*0x40*/ u32 unionRoomNum;
    /*0x44*/ u32 berriesPicked;
    /*0x48*/ u32 jumpsInRow;
    /*0x4C*/ bool8 shouldDrawStickers;
    /*0x4D*/ bool8 hasAllMons;
    /*0x4E*/ u8 monIconTint;
    /*0x4F*/ u8 facilityClass;
    /*0x50*/ u8 stickers[3];
    /*0x54*/ u16 monSpecies[6];
};


// we have to expand certain fields from this structure.
// instead of trying to expand fields where they already are, just move them to the end of the structure:
struct TrainerCardData
{
    u8 mainState;
    u8 printState;
    u8 gfxLoadState;
    u8 bgPalLoadState;
    u8 flipDrawState;
    bool8 isLink;
    u8 timeColonBlinkTimer;
    bool8 timeColonInvisible;
    bool8 onBack;
    bool8 allowDMACopy;
    bool8 hasPokedex;
    bool8 hasHofResult;
    bool8 hasLinkResults;
    bool8 hasBattleTowerWins;
    bool8 var_E;
    bool8 var_F;
    bool8 hasTrades;
    bool8 hasBadgeOld[8];
    u8 easyChatProfile[4][13];
    u8 strings[12][70];
    u8 var_395;
    u16 monIconPals[16 * 6];
    s8 flipBlendY;
    u8 cardType;
    void (*callback2)(void);
    struct TrainerCard trainerCard;
    u16 frontTilemap[600];
    u16 backTilemap[600];
    u16 bgTilemap[600];
    u8 oldBadgeTiles[0x80 * 8];
    u16 stickerTiles[0x100];
    u16 cardTiles[0x1180];
    u16 cardTilemapBuffer[0x1000];
    u16 bgTilemapBuffer[0x1000];
    u16 cardTop;
    bool8 timeColonNeedDraw;
    u8 language; // 0x7BD0
    u8 badgeTiles[0x80 * NUM_BADGES]; // repoint this to have space for 16 badges + at the end of the stucture
    u16 badgeBitfield; // 1 bit per badge
};

extern struct TrainerCardData *sTrainerCardDataPtr;
extern const u8 sStarYOffsets[4];

void FillBgTilemapBufferRect(u8 bg, u16 tileNum, u8 x, u8 y, u8 width, u8 height, u8 palette);
void LoadMonIconGfx(void);
bool8 LoadCardGfx(void);
u16 LoadBgTiles(u8 bg, const void *src, u16 size, u16 destOffset);
void DrawTrainerCardWindow(u8 windowId);
void DrawCardScreenBackground(const u16 *ptr);
void DrawCardFrontOrBack(const u16 *ptr);


#endif // GUARD_TRAINER_CARD_H

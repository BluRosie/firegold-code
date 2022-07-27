#include "../include/gba/defines.h"
#include "../include/gba/types.h"
#include "../include/bg.h"

// part 1:  conversion table, which just needs its entries expanded to 1C
struct BattleSceneMapping 
{
    u8 mapScene;
    u8 battleTerrain;
};

#define sMapBattleSceneMapping ((struct BattleSceneMapping *)0x09D36030)

u8 GetBattleTerrainByMapScene(u8 mapBattleScene)
{
    int i;
    
    for (i = 0; i < 0x1C; i++)
    {
        if (mapBattleScene == sMapBattleSceneMapping[i].mapScene)
            return sMapBattleSceneMapping[i].battleTerrain;
    }
    return 9;
}


// part 2:  battle bg tables

struct BattleBackground
{
    void *tileset;
    void *tilemap;
    void *entryTileset;
    void *entryTilemap;
    void *palette;
};

#define gTimeOfDay *((u8*)0x0203C000)

extern struct BattleBackground sBattleTerrainTable_Morning[];
extern struct BattleBackground sBattleTerrainTable_Day[];
extern struct BattleBackground sBattleTerrainTable_Evening[];
extern struct BattleBackground sBattleTerrainTable_Night[];

void LZDecompressVram(void *, void*);
void LoadCompressedPalette(void *, u32, u32);
void *GetBgTilemapBuffer(u32);
void CopyToBgTilemapBuffer(u32, u8 *, u32, u32);

struct BattleBackground *GetCurrentBattleBGTable()
{
    switch (gTimeOfDay)
    {
    default:
    case 0:
    case 5:
        return sBattleTerrainTable_Night;
    case 1:
        return sBattleTerrainTable_Morning;
    case 2:
        return sBattleTerrainTable_Day;
    case 3:
    case 4:
        return sBattleTerrainTable_Evening;
    }
}

void LoadBattleTerrainGfx(u16 terrain)
{
    struct BattleBackground *currentBattleBackgroundTable = GetCurrentBattleBGTable();
    if (terrain >= 32)
        terrain = 9;
    // Copy to bg3
    LZDecompressVram(currentBattleBackgroundTable[terrain].tileset, (void *)BG_CHAR_ADDR(2));
    LZDecompressVram(currentBattleBackgroundTable[terrain].tilemap, (void *)BG_SCREEN_ADDR(26));
    LoadCompressedPalette(currentBattleBackgroundTable[terrain].palette, 0x20, 0x60);
}

void LoadBattleTerrainEntryGfx(u16 terrain)
{
    struct BattleBackground *currentBattleBackgroundTable = GetCurrentBattleBGTable();
    if (terrain >= 32)
        terrain = 9;
    // Copy to bg1
    LZDecompressVram(currentBattleBackgroundTable[terrain].entryTileset, (void *)BG_CHAR_ADDR(1));
    LZDecompressVram(currentBattleBackgroundTable[terrain].entryTilemap, (void *)BG_SCREEN_ADDR(28));
}

extern const u32 gBattleTextboxTiles[];
extern const u32 gBattleTextboxTilemap[];
extern const u32 gBattleTextboxPalette[];
u8 GetBattleTerrainOverride();
void LoadBattleMenuWindowGfx();

bool8 LoadChosenBattleElement(u8 caseId)
{
    bool8 ret = FALSE;
    u8 battleScene;
    struct BattleBackground *currentBattleBackgroundTable = GetCurrentBattleBGTable();
    
    switch (caseId)
    {
    case 0:
        LZDecompressVram(gBattleTextboxTiles, (void *)BG_CHAR_ADDR(0));
        break;
    case 1:
        CopyToBgTilemapBuffer(0, gBattleTextboxTilemap, 0, 0x000);
        CopyBgTilemapBufferToVram(0);
        break;
    case 2:
        LoadCompressedPalette(gBattleTextboxPalette, 0x00, 0x40);
        break;
    case 3:
        battleScene = GetBattleTerrainOverride();
        LZDecompressVram(currentBattleBackgroundTable[battleScene].tileset, (void *)BG_CHAR_ADDR(2));
        // fallthrough
    case 4:
        battleScene = GetBattleTerrainOverride();
        LZDecompressVram(currentBattleBackgroundTable[battleScene].tilemap, (void *)BG_SCREEN_ADDR(26));
        break;
    case 5:
        battleScene = GetBattleTerrainOverride();
        LoadCompressedPalette(currentBattleBackgroundTable[battleScene].palette, 0x20, 0x60);
        break;
    case 6:
        LoadBattleMenuWindowGfx();
        break;
    default:
        ret = TRUE;
        break;
    }
    return ret;
}

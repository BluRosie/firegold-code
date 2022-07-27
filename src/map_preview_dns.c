#include "../include/gba/types.h"
#include "../include/gba/defines.h"
#include "../include/alloc.h"
#include "../include/bg.h"
#include "../include/event_data.h"
#include "../include/menu.h"
#include "../include/palette.h"

#define MPS_TYPE_CAVE   0
#define MPS_TYPE_FOREST 1
#define MPS_TYPE_ANY    2

enum MapPreviewScreenId
{
    MPS_VIRIDIAN_FOREST = 0u,
    MPS_MT_MOON,
    MPS_DIGLETTS_CAVE,
    MPS_ROCK_TUNNEL,
    MPS_POKEMON_TOWER,
    MPS_SAFARI_ZONE,
    MPS_SEAFOAM_ISLANDS,
    MPS_POKEMON_MANSION,
    MPS_ROCKET_HIDEOUT,
    MPS_SILPH_CO,
    MPS_VICTORY_ROAD,
    MPS_CERULEAN_CAVE,
    MPS_POWER_PLANT,
    MPS_MT_EMBER,
    MPS_ROCKET_WAREHOUSE,
    MPS_MONEAN_CHAMBER,
    MPS_DOTTED_HOLE,
    MPS_BERRY_FOREST,
    MPS_ICEFALL_CAVE,
    MPS_LOST_CAVE,
    MPS_ALTERING_CAVE,
    MPS_PATTERN_BUSH,
    MPS_LIPTOO_CHAMBER,
    MPS_WEEPTH_CHAMBER,
    MPS_TDILFORD_CHAMBER,
    MPS_SCUFIB_CHAMBER,
    MPS_RIXY_CHAMBER,
    MPS_VIAPOIS_CHAMBER,
    MPS_COUNT
};

struct MapPreviewScreen
{
    u8 mapsec;
    u8 type;
    u16 flagId;
    const void * tilesptr;
    const void * tilemapptr;
    const void * palptr;
};

extern const struct MapPreviewScreen sMapPreviewScreenData_Morning[]; // original one
extern const struct MapPreviewScreen sMapPreviewScreenData_Day[];
extern const struct MapPreviewScreen sMapPreviewScreenData_Evening[];
extern const struct MapPreviewScreen sMapPreviewScreenData_Night[];

#define gTimeOfDay *((u8*)0x0203C000)

struct MapPreviewScreen *GrabCurrentPreviewScreenData()
{
    switch (gTimeOfDay)
    {
    default:
    case 0:
    case 5:
        return sMapPreviewScreenData_Night;
    case 1:
        return sMapPreviewScreenData_Morning;
    case 2:
        return sMapPreviewScreenData_Day;
    case 3:
    case 4:
        return sMapPreviewScreenData_Evening;
    }
}

u8 GetMapPreviewScreenIdx(u8 mapsec)
{
    s32 i;
    
    struct MapPreviewScreen *currentMapPreviewTable = GrabCurrentPreviewScreenData();

    for (i = 0; i < MPS_COUNT; i++)
    {
        if (currentMapPreviewTable[i].mapsec == mapsec)
        {
            return i;
        }
    }
    return MPS_COUNT;
}

void * GetBgTilemapBuffer(u32);
void CopyToBgTilemapBuffer(u32, u8 *, u32, u32);
#define sAllocedBg0TilemapBuffer *((u8 *)0x0203abed)

void MapPreview_LoadGfx(u8 mapsec)
{
    u8 idx;
    
    struct MapPreviewScreen *currentMapPreviewTable = GrabCurrentPreviewScreenData();

    idx = GetMapPreviewScreenIdx(mapsec);
    if (idx != MPS_COUNT)
    {
       ResetTempTileDataBuffers();
       LoadPalette(currentMapPreviewTable[idx].palptr, 0xD0, 0x60);
       DecompressAndCopyTileDataToVram(0, currentMapPreviewTable[idx].tilesptr, 0, 0, 0);
       if (GetBgTilemapBuffer(0) == 0)
       {
           SetBgTilemapBuffer(0, Alloc(BG_SCREEN_SIZE));
           sAllocedBg0TilemapBuffer = 1;
       }
       else
       {
           sAllocedBg0TilemapBuffer = 0;
       }
       CopyToBgTilemapBuffer(0, currentMapPreviewTable[idx].tilemapptr, 0, 0x000);
       CopyBgTilemapBufferToVram(0);
    }
}

const struct MapPreviewScreen * GetDungeonMapPreviewScreenInfo(u8 mapsec)
{
    u8 idx;
    
    struct MapPreviewScreen *currentMapPreviewTable = GrabCurrentPreviewScreenData();

    idx = GetMapPreviewScreenIdx(mapsec);
    
    if (idx == MPS_COUNT)
    {
        return NULL;
    }
    else
    {
        return &currentMapPreviewTable[idx];
    }
}

#define sHasVisitedMapBefore *((u8 *)0x0203abec)

u16 MapPreview_GetDuration(u8 mapsec)
{
    u8 idx;
    u16 flagId;
    
    struct MapPreviewScreen *currentMapPreviewTable = GrabCurrentPreviewScreenData();

    idx = GetMapPreviewScreenIdx(mapsec);
    if (idx == MPS_COUNT)
    {
        return 0;
    }
    flagId = currentMapPreviewTable[idx].flagId;
    if (currentMapPreviewTable[idx].type == MPS_TYPE_CAVE)
    {
        if (!FlagGet(flagId))
        {
            return 120;
        }
        else
        {
            return 40;
        }
    }
    else {
        if (sHasVisitedMapBefore)
        {
            return 120;
        }
        else
        {
            return 40;
        }
    }
}

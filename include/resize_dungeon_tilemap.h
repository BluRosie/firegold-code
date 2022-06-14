#ifndef RESIZE_DUNGEON_TILEMAP_H
#define RESIZE_DUNGEON_TILEMAP_H

#include "task.h"

struct MapPreviewScreen
{
    u8 mapsec;
    u8 type;
    u16 flagId;
    const void * tilesptr;
    const void * tilemapptr;
    const void * palptr;
};

struct DungeonMapPreview
{
    u16 oldtiles[7200];  // repointing these to later in the structure.
    u16 tilemap[640];
    const struct MapPreviewScreen * mapPreviewInfo;
    TaskFunc savedTask;
    u8 mainState;
    u8 drawState;
    u8 loadState;
    u8 updateCounter;
    u8 timer;
    u16 palette[0x30];
    u8 filler[0x60];
    u16 red;
    u16 green;
    u16 blue;
    u16 blendY;
    u16 left;
    u16 top;
    u16 right;
    u16 bottom;
    u16 leftIncrement;
    u16 topIncrement;
    u16 rightIncrement;
    u16 bottomIncrement;
    u16 tiles[14400];
}; // size = 0x3E28

extern struct DungeonMapPreview *sDungeonMapPreview;
u16 LoadBgTiles(u8 bg, const void* src, u16 size, u16 destOffset);

#endif // RESIZE_DUNGEON_TILEMAP_H

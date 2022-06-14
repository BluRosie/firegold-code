#include "../include/global.h"

#include "../include/gba/syscall.h"

#include "../include/bg.h"
#include "../include/palette.h"
#include "../include/resize_dungeon_tilemap.h"

bool8 LoadMapPreviewGfx(void)
{
    switch (sDungeonMapPreview->loadState)
    {
    case 0:
        LZ77UnCompWram(sDungeonMapPreview->mapPreviewInfo->tilesptr, sDungeonMapPreview->tiles);
        break;
    case 1:
        LZ77UnCompWram(sDungeonMapPreview->mapPreviewInfo->tilemapptr, sDungeonMapPreview->tilemap);
        break;
    case 2:
        LoadBgTiles(2, sDungeonMapPreview->tiles, sizeof(sDungeonMapPreview->tiles), 0);
        break;
    case 3:
        LoadPalette(sDungeonMapPreview->mapPreviewInfo->palptr, 0xD0, 0x60);
        break;
    default:
        return TRUE;
    }
    sDungeonMapPreview->loadState++;
    return FALSE;
}

#include "../include/global.h"
#include "../include/alloc.h"
#include "../include/pokemon.h"
#include "../include/save.h"
#include "../include/sound.h"
#include "../include/sprite.h"


u8 GetFieldMoveMonAbility(void)
{
    u32 species = GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_SPECIES, 0);
    u32 abilityNum = GetMonData(&gPlayerParty[gPartyMenu.slotId], MON_DATA_ABILITY_NUM, 0);
    
    if (abilityNum && gBaseStats[species].abilities[1] != 0)
        return gBaseStats[species].abilities[1];
    return gBaseStats[species].abilities[0];
}


u16 sCutGrassMetatileMapping[][2] =
{
    {0xD, 1},
    {0xA, 0x13},
    {0xB, 0xE},
    {0xC, 0xF},
    {0x352, 0x33E},
    {0x300, 0x310},
    {0x301, 0x311},
    {0x302, 0x312},
    {0x284, 0x281},
    {0x370, 0x1},      // long long grass natl park (but there is still special handling)
    {0x393, 0x1},      // long long grass safari zone (but there is still special handling)
    {0x282, 0x281},    // snow grass
    {0x281, 0x281},    // snow grass after it's been stepped in
    {0x39B, 1},        // long long grass bottom
    {0x371, 1},        // long long grass bottom
    {0xFFFF, 0xFFFF},
};


void MapGridSetMetatileIdAt(s16 x, s16 y, u16 metatileId);
u32 MapGridGetMetatileIdAt(s16 x, s16 y);


void SetCutGrassMetatileAt(s16 x, s16 y)
{
    u16 i = 0;
    u16 metatileId = MapGridGetMetatileIdAt(x, y);

    // natl park long long grass
    if (metatileId == 0x371 && MapGridGetMetatileIdAt(x, y-1) == 0x370) // handle setting the bottom part of long long grass if below it is cut
    {
        return;
    }

    if (metatileId == 0x370 && MapGridGetMetatileIdAt(x, y-1) == 0x370) // handle setting the bottom part of long long grass if below it is cut
    {
        MapGridSetMetatileIdAt(x, y, 0x371);
        return;
    }

    if (metatileId == 0x370 && MapGridGetMetatileIdAt(x, y+1) == 0x371) // handle clearing the bottom part of long long grass if above it is cut
    {
        MapGridSetMetatileIdAt(x, y+1, 0x1);
    }

    // safari zone long long grass
    if (metatileId == 0x39B && MapGridGetMetatileIdAt(x, y-1) == 0x393) // handle setting the bottom part of long long grass if below it is cut
    {
        return;
    }

    if (metatileId == 0x393 && MapGridGetMetatileIdAt(x, y-1) == 0x393) // handle setting the bottom part of long long grass if below it is cut
    {
        MapGridSetMetatileIdAt(x, y, 0x39B);
        return;
    }

    if (metatileId == 0x393 && MapGridGetMetatileIdAt(x, y+1) == 0x39B) // handle clearing the bottom part of long long grass if above it is cut
    {
        MapGridSetMetatileIdAt(x, y+1, 0x1);
    }

    while (1)
    {
        if (sCutGrassMetatileMapping[i][0] == 0xFFFF)
            return;
        if (sCutGrassMetatileMapping[i][0] == metatileId)
        {
            MapGridSetMetatileIdAt(x, y, sCutGrassMetatileMapping[i][1]);
            break;
        }
        i++;
    }
}


#define CUT_GRASS_SPRITE_COUNT 8

// when god judges his children, will he look kindly upon me?
extern u32 *gFieldEffectArguments;
// gPlayerFacingPosition in global fuck it
extern u8 *sCutGrassSpriteArrayPtr;

void PlayerGetDestCoords(s16 *x, s16 *y);
s8 MapGridGetElevationAt(s16 x, s16 y);
bool32 MetatileAtCoordsIsGrassTile(s16 x, s16 y);
void EnableObjectGroundEffectsByXY(s16 x, s16 y);
void DrawWholeMapView(void);

const struct SpriteTemplate sSpriteTemplate_FldEff_CutGrass;

bool8 FldEff_CutGrass(void)
{
    u8 i, j;
    s16 x, y;
    u8 pos;
    u32 cut_side = 3;
    if (GetFieldMoveMonAbility() == 52) // hyper cutter
        cut_side = 5;

    i = 0;
    PlaySE(121);
    pos = gFieldEffectArguments[1] - 1;
    PlayerGetDestCoords(&gPlayerFacingPosition.x, &gPlayerFacingPosition.y);

    for (i = 0; i < cut_side; i++)
    {
        y = gPlayerFacingPosition.y - cut_side/2 + i;
        for (j = 0; j < cut_side; j++)
        {
            x = gPlayerFacingPosition.x - cut_side/2 + j;
            if (MapGridGetElevationAt(x, y) == gPlayerFacingPosition.elevation)
            {
                if (MetatileAtCoordsIsGrassTile(x, y) == TRUE
                     || MapGridGetMetatileIdAt(x, y) == 0x371 || MapGridGetMetatileIdAt(x, y) == 0x39B)
                {
                    SetCutGrassMetatileAt(x, y);
                    EnableObjectGroundEffectsByXY(x, y);
                }
            }
        }
    }
    DrawWholeMapView();
    sCutGrassSpriteArrayPtr = Alloc(CUT_GRASS_SPRITE_COUNT);
    for (i = 0; i < 8; i++)
    {
        sCutGrassSpriteArrayPtr[i] = CreateSprite(&sSpriteTemplate_FldEff_CutGrass, gSprites[gPlayerAvatar.spriteId].oam.x + 8, gSprites[gPlayerAvatar.spriteId].oam.y + 20, 0);
        gSprites[sCutGrassSpriteArrayPtr[i]].data[2] = i * (0x100 / CUT_GRASS_SPRITE_COUNT);
    }
    return FALSE;
}


#define sScheduleOpenDottedHole *(u8 *)(0x02039874)
#define gFieldCallback2 *(u32 *)(0x03005024)
#define gPostMenuFieldCallback *(u32 *)(0x0203b0c4)

bool32 CutMoveRuinValleyCheck(void);
bool32 CheckObjectGraphicsInFrontOfPlayer(u16 gfxId);

bool8 SetUpFieldMove_Cut(void)
{
    s16 x, y;
    u8 i, j;
    u32 cut_side = 3;
    if (GetFieldMoveMonAbility() == 52) // hyper cutter
        cut_side = 5;

    sScheduleOpenDottedHole = FALSE;

    if (CutMoveRuinValleyCheck() == TRUE)
    {
        sScheduleOpenDottedHole = TRUE;
        gFieldCallback2 = 0x081248b1;
        gPostMenuFieldCallback = 0x08097985;
        return TRUE;
    }

    if (CheckObjectGraphicsInFrontOfPlayer(95) == TRUE) // check cut tree
    {
        gFieldCallback2 = 0x081248b1;
        gPostMenuFieldCallback = 0x080979d1;
        return TRUE;
    }
    
    else
    {
        PlayerGetDestCoords(&gPlayerFacingPosition.x, &gPlayerFacingPosition.y);
    
        for (i = 0; i < cut_side; i++)
        {
            y = gPlayerFacingPosition.y - cut_side/2 + i;
            for (j = 0; j < cut_side; j++)
            {
                x = gPlayerFacingPosition.x - cut_side/2 + j;
                if (MapGridGetElevationAt(x, y) == gPlayerFacingPosition.elevation)
                {
                    if (MetatileAtCoordsIsGrassTile(x, y) == TRUE)
                    {
                        gFieldCallback2 = 0x081248b1;
                        gPostMenuFieldCallback = 0x08097985;
                        return TRUE;
                    }
                }
            }
        }
        return FALSE;
    }
}

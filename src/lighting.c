#include "../include/gba/types.h"
#include "../include/event_data.h"
#include "../include/lighting.h"
#include "../include/palette.h"
#include "../include/sprite.h"

#define gTimeOfDay *((u8*)0x0203C000)
#define OBJ_EVENT_PAL_TAG_LIGHT 0x8001
#define OBJ_EVENT_PAL_TAG_LIGHT_2 0x8002
#define OBJ_EVENT_PAL_TAG_NEON_LIGHT 0x8003
#define gLightMetatiles ((struct Coords16*)0x0203C018) // reserve like 20 or so lights

// this file's functions
void TrySpawnLightSprites(s16 camX, s16 camY);
void UpdateLightSprite(struct Sprite *sprite);
void SpawnLightSprite(s16 x, s16 y, s16 camX, s16 camY);
u8 LoadSpritePaletteInSlot(const struct SpritePalette *palette, u8 paletteNum);
//void TrySpawnLightSprites(s16 camX, s16 camY);

// functions we expand on from rom
//void ReloadMapObjectsWithOffset(s16 x, s16 y);

// *holy fuck*
// all the oam/object things that this file uses
extern const u16 gFieldEffectObjectPic_BallLight[0x200/2];// = INCBIN("../graphics/light.4bpp");
extern const u16 gFieldEffectObjectPic_BallLightPal[0x10];
//const u32 gFieldEffectObjectPic_PokeCenterLight[] = INCBIN("../graphics/poke_center_light.4bpp");
//const u32 gFieldEffectObjectPic_MartLight[] = INCBIN("../graphics/mart_light.4bpp");

const struct SpriteFrameImage gFieldEffectObjectPicTable_BallLight[] = {
    {.data = (u8 *)gFieldEffectObjectPic_BallLight, .size = sizeof(gFieldEffectObjectPic_BallLight)},
};

//const struct SpriteFrameImage gFieldEffectObjectPicTable_PokeCenterLight[] = {
//    obj_frame_tiles(gFieldEffectObjectPic_PokeCenterLight),
//};
//
//const struct SpriteFrameImage gFieldEffectObjectPicTable_MartLight[] = {
//    obj_frame_tiles(gFieldEffectObjectPic_MartLight),
//};

const struct SpriteTemplate gFieldEffectObjectTemplate_BallLight = {
    .tileTag = 0xFFFF, 
    .paletteTag = OBJ_EVENT_PAL_TAG_LIGHT, 
    .oam = &gObjectEventBaseOam_32x32, 
    .anims = sAnimTable_Inanimate, // fuck
    .images = gFieldEffectObjectPicTable_BallLight, // fuck
    .affineAnims = gDummySpriteAffineAnimTable, 
    .callback = UpdateLightSprite,
};

//const struct SpriteTemplate gFieldEffectObjectTemplate_PokeCenterLight = {
//    .tileTag = 0xFFFF,
//    .paletteTag = OBJ_EVENT_PAL_TAG_NEON_LIGHT,
//    .oam = &gObjectEventBaseOam_16x16,
//    .anims = sAnimTable_Inanimate,
//    .images = gFieldEffectObjectPicTable_PokeCenterLight,
//    .affineAnims = gDummySpriteAffineAnimTable,
//    .callback = UpdateLightSprite,
//};
//
//const struct SpriteTemplate gFieldEffectObjectTemplate_MartLight = {
//    .tileTag = 0xFFFF,
//    .paletteTag = OBJ_EVENT_PAL_TAG_NEON_LIGHT,
//    .oam = &gObjectEventBaseOam_16x16,
//    .anims = sAnimTable_Inanimate,
//    .images = gFieldEffectObjectPicTable_MartLight,
//    .affineAnims = gDummySpriteAffineAnimTable,
//    .callback = UpdateLightSprite,
//};

const struct SpriteTemplate *const gFieldEffectLightTemplates[] = {
    &gFieldEffectObjectTemplate_BallLight,
//    &gFieldEffectObjectTemplate_PokeCenterLight,
//    &gFieldEffectObjectTemplate_MartLight,
};

typedef struct
{
    u8 Type;
    u8 Count;
    u16 PalTag;
} PalRef;

#define PalTags ((u16 *) 0x03000DE8)
#define PalRefs ((PalRef *) 0x0203FF00)
#define PalTagsStart *((u8 *) 0x3003E58)
#define PalTypeUnused 0
#define PalTypeNPC 1
#define PalTypeAnimation 2
#define PalTypeWeather 3
#define PalTypeReflection 4




/*** Funcs from Navenatox's dynamic OW pals repo ***/
u8 FindPalRef(u8 Type, u16 PalTag)
{
	int i;
	for (i = 0; i < 16; i++)
	{
		if (PalRefs[i].Type == Type && PalRefs[i].PalTag == PalTag) return i;
	}
	return 0xFF; // not found
}

u8 AddPalRef(u8 Type, u16 PalTag)
{
	int i;
	for (i = 0; i < 16; i++)
	{
		if (PalRefs[i].Type == PalTypeUnused)
		{
			PalRefs[i].Type = Type;
			PalRefs[i].PalTag = PalTag;
			return i;
		}
	}
	return 0xFF; // no more space
}

u8 FindPalTag(u16 PalTag)
{
	int i;
	if (PalTagsStart >= 16) return 0xFF;
	for (i = PalTagsStart; i < 16; i++)
	{
		if (sSpritePaletteTags[i] == PalTag) return i;
	}
	return 0xFF; // not found
}

u8 AddPalTag(u16 PalTag)
{
	int i;
	if (PalTagsStart >= 16) return 0xFF;
	for (i = PalTagsStart; i < 16; i++)
	{
		if (sSpritePaletteTags[i] == 0xFFFF)
		{
			sSpritePaletteTags[i] = PalTag;
			return i;
		}
	}
	return 0xFF; // no more space
}

//u8 PalRefIncreaseCount(u8 PalSlot)
//{
//	PalRefs[PalSlot].Count++;
//	return PalSlot;
//}
//
//void PalRefDecreaseCount(u8 PalSlot)
//{
//	if (PalRefs[PalSlot].Count != 0) PalRefs[PalSlot].Count--;
//	if (PalRefs[PalSlot].Count == 0)
//	{
//		PalRefs[PalSlot].Type = 0;
//		PalRefs[PalSlot].PalTag = 0;
//	}
//}





















/** custom/modded code, credits aarant/pokemerrp **/

u32 GrabLightSpritePaletteNum(void)
{
    u32 paletteNum = FindPalRef(PalTypeAnimation, OBJ_EVENT_PAL_TAG_LIGHT);
    
    if (paletteNum == 0xFF)
    {
        AddPalRef(PalTypeAnimation, OBJ_EVENT_PAL_TAG_LIGHT);
    }
    LoadSpritePaletteInSlot(&sObjectEventSpritePalettes[FindObjectEventPaletteIndexByTag(OBJ_EVENT_PAL_TAG_LIGHT)], paletteNum);
    return paletteNum;
}


// Like LoadSpriteSheet, but checks if already, and uses template image frames
u16 LoadSpriteSheetByTemplate(const struct SpriteTemplate *template, u8 frame) {
    u16 tileStart;
    struct SpriteSheet tempSheet;
    // error if template is null or tile tag or images not set
    if (!template || template->tileTag == 0xFFFF || !template->images)
        return 0xFFFF;
    if ((tileStart = GetSpriteTileStartByTag(template->tileTag)) != 0xFFFF) // return if already loaded
        return tileStart;
    tempSheet.data = template->images[frame].data;
    tempSheet.size = template->images[frame].size;
    tempSheet.tag = template->tileTag;
    return LoadSpriteSheet(&tempSheet);
}

u8 LoadSpritePaletteInSlot(const struct SpritePalette *palette, u8 paletteNum) {
    paletteNum = paletteNum > 15 ? 15 : paletteNum;
    sSpritePaletteTags[paletteNum] = palette->tag;
    DoLoadSpritePalette(palette->data, paletteNum * 16);
    return paletteNum;
}

u32 MetatileBehavior_IsLanternLight(u8 metatileBehavior)
{
    if (metatileBehavior == MB_LANTERN_LIGHT)
        return 1;
    else
        return 0;
}

// SpawnObjectEventsOnReturnToField in emerald
// add TrySpawnLightSprites to the end
void ReloadMapObjectsWithOffset(s16 x, s16 y)
{
    u8 i;

    ClearPlayerAvatarInfo();
    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        if (gObjectEvents[i].active)
        {
            ReloadMapObjectWithOffset(i, x, y);
        }
    }
    CreateReflectionEffectSprites();
    // new:  try and spawn light sprites
    TrySpawnLightSprites(x, y);
}

void TrySpawnObjectEvents(s16 cameraX, s16 cameraY)
{
    u8 i;
    u8 objectCount;

    if (gMapHeader.events != 0)
    {
        s16 left = gSaveBlock1->pos.x - 2;
        s16 right = gSaveBlock1->pos.x + 17;
        s16 top = gSaveBlock1->pos.y;
        s16 bottom = gSaveBlock1->pos.y + 16;

        objectCount = gMapHeader.events->objectEventCount;

        for (i = 0; i < objectCount; i++)
        {
            struct ObjectEventTemplate *template = &gSaveBlock1->objectEventTemplates[i];
            if (template->graphicsId == 4)
                continue;
            s16 npcX = template->x + 7;
            s16 npcY = template->y + 7;

            if (top <= npcY && bottom >= npcY && left <= npcX && right >= npcX
                && !FlagGet(template->flagId))
                TrySpawnObjectEventTemplate(template, gSaveBlock1->location.mapNum, gSaveBlock1->location.mapGroup, cameraX, cameraY);
        }
    }
    // new:  try and spawn light sprites
    TrySpawnLightSprites(cameraX, cameraY);
}

// Sprite callback for light sprites
void UpdateLightSprite(struct Sprite *sprite) {
    s16 left =   gSaveBlock1->pos.x - 2;
    s16 right =  gSaveBlock1->pos.x + 17;
    s16 top =    gSaveBlock1->pos.y;
    s16 bottom = gSaveBlock1->pos.y + 15;
    s16 x = sprite->data[6];
    s16 y = sprite->data[7];
    u16 sheetTileStart;
    u32 paletteNum;
    // Ripped from RemoveObjectEventIfOutsideView
    if (!(x >= left && x <= right && y >= top && y <= bottom)) {
        sheetTileStart = sprite->sheetTileStart;
        paletteNum = sprite->oam.paletteNum;
        DestroySprite(sprite);
        FieldEffectFreeTilesIfUnused(sheetTileStart);
        FieldEffectFreePaletteIfUnused(paletteNum);
        Weather_SetBlendCoeffs(7, 12); // TODO: Restore original blend coeffs at dawn
        return;
    }

    if (gTimeOfDay != 0 && gTimeOfDay != 5) { // if it is not currently night time
        sprite->invisible = 1;
        sprite->data[5] = 1;
        return;
    }
    else if (sprite->data[5] != 0 && sprite->invisible == 1)
    {
        sprite->oam.paletteNum = GrabLightSpritePaletteNum();//LoadSpritePaletteInSlot(&sObjectEventSpritePalettes[FindObjectEventPaletteIndexByTag(OBJ_EVENT_PAL_TAG_LIGHT)], sprite->oam.paletteNum);
        sprite->data[5] = 0;
    }

    sprite->oam.paletteNum = GrabLightSpritePaletteNum();
    if (gPaletteFade.active) { // if palette fade is active, don't flicker since the timer won't be updated
        Weather_SetBlendCoeffs(7, 12);
        sprite->invisible = 0;
    } else if (sprite->invisible = gSaveBlock2->playTimeVBlanks & 1) {
        Weather_SetBlendCoeffs(12, 12);
    }
}


// Spawn a light at a map coordinate
void SpawnLightSprite(s16 x, s16 y, s16 cameraX, s16 cameraY)
{
    struct Sprite *sprite;
    const struct SpriteTemplate *template;
    u8 i;
    for (i = 0; i < 64; i++) {
        sprite = &gSprites[i];
        if (sprite->inUse && sprite->callback == UpdateLightSprite && sprite->data[6] == x && sprite->data[7] == y)
            return;
    }
    u32 lightType = 0;
    template = gFieldEffectLightTemplates[lightType];
    LoadSpriteSheetByTemplate(template, 0);
    sprite = &gSprites[CreateSprite(template, 0, 0, 0)];

    sprite->oam.paletteNum = GrabLightSpritePaletteNum();
    
    GetMapCoordsFromSpritePos(x + cameraX, y + cameraY, &sprite->pos1.x, &sprite->pos1.y);
    sprite->data[5] = lightType;
    sprite->data[6] = x;
    sprite->data[7] = y;
    sprite->affineAnims = gDummySpriteAffineAnimTable;
    sprite->affineAnimBeginning = 1;
    sprite->coordOffsetEnabled = 1;
    sprite->centerToCornerVecX = -(32 >> 1);
    sprite->centerToCornerVecY = -(32 >> 1);
    sprite->oam.priority = 1;
    sprite->oam.objMode = 1; // BLEND
    sprite->oam.affineMode = 1;//ST_OAM_AFFINE_NORMAL;
    sprite->pos1.x += 8;
    sprite->pos1.y += 22 + sprite->centerToCornerVecY;
}

void TrySpawnLightSprites(s16 cameraX, s16 cameraY)
{
    s16 left =   gSaveBlock1->pos.x - 2;
    s16 right =  gSaveBlock1->pos.x + 17;
    s16 top =    gSaveBlock1->pos.y;
    s16 bottom = gSaveBlock1->pos.y + 16;
    s16 x, y;
    u32 behavior;
    u32 i;

    if (gTimeOfDay != 0 && gTimeOfDay != 5) { // if it is not currently night time
        return;
    }
    
    for (i = 0; gLightMetatiles[i].x > 0; i++)
    {
        x = gLightMetatiles[i].x;
        y = gLightMetatiles[i].y;
        if (x >= left && x <= right && y >= top && y <= bottom /*&&
            MetatileBehavior_IsLanternLight(MapGridGetMetatileBehaviorAt(x, y))*/)
        {
            SpawnLightSprite(x, y, cameraX, cameraY);
        }
    }
}




// Caches light metatile coordinates
void CacheLightMetatiles(void)
{
    u8 i = 0, objectEventCount = 0, j = 0;
    s32 x, y;

    // rewriting to do from map header
    
    objectEventCount = gMapHeader.events->objectEventCount;
    
    for (i = 0; i < objectEventCount; i++)
    {
        if (gMapHeader.events->objectEvents[i].graphicsId == 4)
        {
            gLightMetatiles[j].x = gMapHeader.events->objectEvents[i].x+7;
            gLightMetatiles[j].y = gMapHeader.events->objectEvents[i].y+7;
            j++;
        }
    }

    /*for (x = 0; x < gBackupMapLayout.width; x++)
    {
        for (y = 0; y < gBackupMapLayout.height; y++)
        {
            if (MetatileBehavior_IsLanternLight(MapGridGetMetatileBehaviorAt(x, y)))
            {
                gLightMetatiles[i].x = x;
                gLightMetatiles[i].y = y;
                i++;
            }
        }
    }*/
    
    gLightMetatiles[i].x = -1;
    gLightMetatiles[i].y = -1;
}

void InitMap(void)
{
    InitMapLayoutData(&gMapHeader);
    RunOnLoadMapScript();
    CacheLightMetatiles();
}

void InitMapFromSavedGame(void)
{
    InitMapLayoutData(&gMapHeader);
    LoadSavedMapView();
    RunOnLoadMapScript();
    CacheLightMetatiles();
}

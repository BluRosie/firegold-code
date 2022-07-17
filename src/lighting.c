/*#include "../include/gba/types.h"
#include "../include/lighting.h"
#include "../include/palette.h"
#include "../include/sprite.h"

#define gTimeOfDay *((u8*)0x0203C000)
#define OBJ_EVENT_PAL_TAG_LIGHT 0x8001
#define OBJ_EVENT_PAL_TAG_LIGHT_2 0x8002
#define OBJ_EVENT_PAL_TAG_NEON_LIGHT 0x8003

// this file's functions
void TrySpawnLightSprites(s16 camX, s16 camY);
void UpdateLightSprite(struct Sprite *sprite);
void SpawnLightSprite(s16 x, s16 y, s16 camX, s16 camY, u32 lightType);
void TrySpawnLightSprites(s16 camX, s16 camY);

// functions we expand on from rom
//void ReloadMapObjectsWithOffset(s16 x, s16 y);

// *holy fuck*
// all the oam/object things that this file uses
const u32 gFieldEffectObjectPic_BallLight[] = INCBIN("../graphics/light.4bpp");
//const u32 gFieldEffectObjectPic_PokeCenterLight[] = INCBIN("../graphics/poke_center_light.4bpp");
//const u32 gFieldEffectObjectPic_MartLight[] = INCBIN("../graphics/mart_light.4bpp");

const struct SpriteFrameImage gFieldEffectObjectPicTable_BallLight[] = {
    obj_frame_tiles(gFieldEffectObjectPic_BallLight),
};

//const struct SpriteFrameImage gFieldEffectObjectPicTable_PokeCenterLight[] = {
//    obj_frame_tiles(gFieldEffectObjectPic_PokeCenterLight),
//};
//
//const struct SpriteFrameImage gFieldEffectObjectPicTable_MartLight[] = {
//    obj_frame_tiles(gFieldEffectObjectPic_MartLight),
//};

const struct SpriteTemplate gFieldEffectObjectTemplate_BallLight = {
    .tileTag = OBJ_EVENT_PAL_TAG_LIGHT, 
    .paletteTag = OBJ_EVENT_PAL_TAG_LIGHT, 
    .oam = &gObjectEventBaseOam_32x32, 
    .anims = sAnimTable_Inanimate, // fuck
    .images = gFieldEffectObjectPicTable_BallLight, // fuck
    .affineAnims = gDummySpriteAffineAnimTable, 
    .callback = UpdateLightSprite,
};

//const struct SpriteTemplate gFieldEffectObjectTemplate_PokeCenterLight = {
//    .tileTag = TAG_NONE,
//    .paletteTag = OBJ_EVENT_PAL_TAG_NEON_LIGHT,
//    .oam = &gObjectEventBaseOam_16x16,
//    .anims = sAnimTable_Inanimate,
//    .images = gFieldEffectObjectPicTable_PokeCenterLight,
//    .affineAnims = gDummySpriteAffineAnimTable,
//    .callback = UpdateLightSprite,
//};
//
//const struct SpriteTemplate gFieldEffectObjectTemplate_MartLight = {
//    .tileTag = TAG_NONE,
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
        sprite->invisible = TRUE;
        return;
    }

    switch (sprite->data[5]) { // lightType
    case 0:
        if (gPaletteFade.active) { // if palette fade is active, don't flicker since the timer won't be updated
            Weather_SetBlendCoeffs(7, 12);
            sprite->invisible = FALSE;
        } else if (gPlayerAvatar.tileTransitionState) {
            Weather_SetBlendCoeffs(7, 12); // As long as the second coefficient stays 12, shadows will not change
            sprite->invisible = FALSE;
            //if (GetSpritePaletteTagByPaletteNum(sprite->oam.paletteNum) == OBJ_EVENT_PAL_TAG_LIGHT_2)
            //    LoadSpritePaletteInSlot(&sObjectEventSpritePalettes[FindObjectEventPaletteIndexByTag(OBJ_EVENT_PAL_TAG_LIGHT)], sprite->oam.paletteNum);
        } else if ((sprite->invisible = gTimeUpdateCounter & 1)) {
            Weather_SetBlendCoeffs(12, 12);
            //if (GetSpritePaletteTagByPaletteNum(sprite->oam.paletteNum) == OBJ_EVENT_PAL_TAG_LIGHT)
            //    LoadSpritePaletteInSlot(&sObjectEventSpritePalettes[FindObjectEventPaletteIndexByTag(OBJ_EVENT_PAL_TAG_LIGHT_2)], sprite->oam.paletteNum);
        }
        break;
    case 1 ... 2:
        Weather_SetBlendCoeffs(12, 12);
        sprite->invisible = FALSE;
        break;
    }
}


// Spawn a light at a map coordinate
void SpawnLightSprite(s16 x, s16 y, s16 camX, s16 camY, u32 lightType) {
    struct Sprite *sprite;
    const struct SpriteTemplate *template;
    u8 i;
    for (i = 0; i < MAX_SPRITES; i++) { // light already spawned
        sprite = &gSprites[i];
        if (sprite->inUse && sprite->callback == UpdateLightSprite && sprite->data[6] == x && sprite->data[7] == y)
            return;
    }
    lightType = 0;//min(lightType, ARRAY_COUNT(gFieldEffectLightTemplates) - 1); // bounds checking
    template = gFieldEffectLightTemplates[lightType];
    LoadSpriteSheetByTemplate(template, 0);
    sprite = &gSprites[CreateSprite(template, 0, 0, 0)];
    if (lightType == 0 && (i = IndexOfSpritePaletteTag(template->paletteTag + 1)) < 16)
        sprite->oam.paletteNum = i;
    else // update below this
        UpdateSpritePaletteByTemplate(template, sprite);
    GetMapCoordsFromSpritePos(x + camX, y + camY, &sprite->x, &sprite->y);
    sprite->data[5] = lightType;
    sprite->data[6] = x;
    sprite->data[7] = y;
    sprite->affineAnims = gDummySpriteAffineAnimTable;
    sprite->affineAnimBeginning = TRUE;
    sprite->coordOffsetEnabled = TRUE;
    switch (lightType) {
    case 0: // Rustboro lanterns
        sprite->centerToCornerVecX = -(32 >> 1);
        sprite->centerToCornerVecY = -(32 >> 1);
        sprite->oam.priority = 1;
        sprite->oam.objMode = 1; // BLEND
        sprite->oam.affineMode = ST_OAM_AFFINE_NORMAL;
        sprite->x += 8;
        sprite->y += 22 + sprite->centerToCornerVecY;
        break;
    case 1 ... 2: // Pokemon Center & mart
        sprite->centerToCornerVecX = -(16 >> 1);
        sprite->centerToCornerVecY = -(16 >> 1);
        sprite->oam.priority = 2;
        sprite->subpriority = 0xFF;
        sprite->oam.objMode = 1; // BLEND
    }
}

void TrySpawnLightSprites(s16 camX, s16 camY) {
    u8 i;
    u8 objectCount;
    s16 left = gSaveBlock1->pos.x - 2;
    s16 right = gSaveBlock1->pos.x + MAP_OFFSET_W + 2;
    s16 top = gSaveBlock1->pos.y;
    s16 bottom = gSaveBlock1->pos.y + MAP_OFFSET_H + 2;
    if (gMapHeader.events == NULL)
        return;

    objectCount = gMapHeader.events->objectEventCount;

    for (i = 0; i < objectCount; i++) {
        struct ObjectEventTemplate *template = &gSaveBlock1->objectEventTemplates[i];
        s16 npcX = template->x + MAP_OFFSET;
        s16 npcY = template->y + MAP_OFFSET;
        if (top <= npcY && bottom >= npcY && left <= npcX && right >= npcX && !FlagGet(template->flagId))
            if (template->graphicsId == OBJ_EVENT_GFX_LIGHT_SPRITE)  // event is light sprite instead
                SpawnLightSprite(npcX, npcY, camX, camY, template->trainerRange_berryTreeId);
    }
}*/

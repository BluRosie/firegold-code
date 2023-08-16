#include "../include/global.h"
#include "../include/alloc.h"
#include "../include/battle.h"
#include "../include/event_data.h"
#include "../include/main.h"
#include "../include/overworld.h"
#include "../include/pokemon.h"
#include "../include/save.h"
#include "../include/sound.h"
#include "../include/sprite.h"
#include "../include/string_util.h"
#include "../include/task.h"

extern bool8 (*const sFldEffScrcmdTable[])(const u8 **script, u32 *result);
extern const u8 *const gFieldEffectScriptPointers[];

extern void Task_UseRockClimb(u8 taskId);

bool8 FldEff_UseRockClimb(void);
u32 FldEff_RockClimbDust(void);

static const union AnimCmd sSurfBlobAnim_FaceSouth[] =
{
    ANIMCMD_FRAME(0, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sSurfBlobAnim_FaceNorth[] =
{
    ANIMCMD_FRAME(1, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sSurfBlobAnim_FaceWest[] =
{
    ANIMCMD_FRAME(2, 1),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sSurfBlobAnim_FaceEast[] =
{
    ANIMCMD_FRAME(2, 1, .hFlip = TRUE),
    ANIMCMD_JUMP(0),
};

const union AnimCmd *const sAnimTable_SurfBlob[] =
{
    sSurfBlobAnim_FaceSouth,
    sSurfBlobAnim_FaceNorth,
    sSurfBlobAnim_FaceWest,
    sSurfBlobAnim_FaceEast,
};


const struct SpriteFrameImage sPicTable_RockClimbBlob[] = {
    overworld_frame(0x09DA50A0, 4, 4, 1), // gFieldEffectObjectPic_RockClimbBlob
    overworld_frame(0x09DA50A0, 4, 4, 0),
    overworld_frame(0x09DA50A0, 4, 4, 2),
};

const struct SpriteTemplate gFieldEffectObjectTemplate_RockClimbBlob = {
    .tileTag = 0xFFFF,
    .paletteTag = FLDEFF_PAL_TAG_ROCK_CLIMB_BLOB,
    .oam = 0x083a3718, // gObjectEventBaseOam_32x32
    .anims = sAnimTable_SurfBlob,
    .images = sPicTable_RockClimbBlob,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = 0x080dc4f9,
};


const union AnimCmd sAnim_RockClimbDust[] =
{
    ANIMCMD_FRAME(0, 12),
    ANIMCMD_FRAME(1, 12),
    ANIMCMD_FRAME(2, 12),
    ANIMCMD_END,
};
const union AnimCmd *const sAnimTable_RockClimbDust[] =
{
    sAnim_RockClimbDust,
};
const struct SpriteFrameImage sPicTable_RockClimbDust[] = {
    overworld_frame(0x09DA56A0, 4, 4, 0), // gFieldEffectObjectPic_RockClimbDust
    overworld_frame(0x09DA56A0, 4, 4, 1),
    overworld_frame(0x09DA56A0, 4, 4, 2),
};
const struct SpriteTemplate gFieldEffectObjectTemplate_RockClimbDust = {
    .tileTag = 0xFFFF,
    .paletteTag = FLDEFF_PAL_TAG_DUST_CLOUD,
    .oam = 0x083a3718,// &gObjectEventBaseOam_32x32,
    .anims = sAnimTable_RockClimbDust,
    .images = sPicTable_RockClimbDust,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = 0x080dcce1, // UpdateJumpImpactEffect,
};

const struct SpritePalette gSpritePalette_BigDust = {0x9DA5080, /*gFieldEffectPal_DustCloudgFieldEffectPal_DustCloud,*/ 
                                                     FLDEFF_PAL_TAG_DUST_CLOUD};

const struct SpritePalette gSpritePalette_RockClimbBlob = {0x9DA5060, FLDEFF_PAL_TAG_ROCK_CLIMB_BLOB};









const union AnimCmd sAnim_Whirlpool[] =
{
    ANIMCMD_FRAME(0, 12),
    ANIMCMD_FRAME(1, 12),
    ANIMCMD_FRAME(2, 12),
    ANIMCMD_FRAME(3, 12),
    ANIMCMD_FRAME(4, 12),
    ANIMCMD_FRAME(5, 12),
    ANIMCMD_FRAME(6, 12),
    ANIMCMD_FRAME(7, 12),
    ANIMCMD_FRAME(8, 12),
    ANIMCMD_FRAME(9, 12),
    ANIMCMD_END,
};
const union AnimCmd *const sAnimTable_Whirlpool[] =
{
    sAnim_Whirlpool,
};
const struct SpriteFrameImage sPicTable_Whirlpool[] = {
    overworld_frame(0x09DA84F0, 2, 2, 0),
    overworld_frame(0x09DA84F0, 2, 2, 1),
    overworld_frame(0x09DA84F0, 2, 2, 2),
    overworld_frame(0x09DA84F0, 2, 2, 3),
    overworld_frame(0x09DA84F0, 2, 2, 4),
    overworld_frame(0x09DA84F0, 2, 2, 5),
    overworld_frame(0x09DA84F0, 2, 2, 6),
    overworld_frame(0x09DA84F0, 2, 2, 7),
    overworld_frame(0x09DA84F0, 2, 2, 8),
    overworld_frame(0x09DA84F0, 2, 2, 9),
};
const struct SpriteTemplate gFieldEffectObjectTemplate_Whirlpool = {
    .tileTag = 0xFFFF,
    .paletteTag = FLDEFF_PAL_TAG_WHIRLPOOL_DISAPPEAR,
    .oam = 0x083a36f0,// &gObjectEventBaseOam_32x32,
    .anims = sAnimTable_Whirlpool,
    .images = sPicTable_Whirlpool,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = 0x080dcce1, // UpdateJumpImpactEffect,
};


const struct SpritePalette gSpritePalette_WhirlpoolDisappear = {0x9DA84D0, FLDEFF_PAL_TAG_WHIRLPOOL_DISAPPEAR};









extern const u8 *const gFieldEffectScript_UseRockClimb;
extern const u8 *const gFieldEffectScript_RockClimbDust;
extern const u8 *const gNewFieldEffectScriptPointers[];

//u8 gFieldEffectScript_UseRockClimb[] =
//{
//    3, WORD_U8_ARRAY(FldEff_UseRockClimb),  // callnative FldEff_UseRockClimb
//    4                                       // end
//};
//
//gFieldEffectScript_RockClimbDust[] =
//{
//    7, WORD_U8_ARRAY(gSpritePalette_BigDust), WORD_U8_ARRAY(FldEff_RockClimbDust),      // loadfadedpal_callnative gSpritePalette_BigDust, FldEff_RockClimbDust
//    4                                                                                   // end
//};
//
//const u8 *const gNewFieldEffectScriptPointers[] = 
//{
//    [FLDEFF_USE_ROCK_CLIMB - START_OF_NEW_FLD_EFF]  = gFieldEffectScript_UseRockClimb,
//    [FLDEFF_ROCK_CLIMB_DUST - START_OF_NEW_FLD_EFF] = gFieldEffectScript_RockClimbDust,
//};


bool8 MetatileBehavior_IsRockClimbable(u8 metatileBehavior)
{
    if (metatileBehavior == MB_ROCK_CLIMB)
        return TRUE;
    else
        return FALSE;
}


u32 FieldEffectStart(u8 fldeff)
{
    const u8 *script;
    u32 result;
    s16 x, y;
    FieldEffectActiveListAdd(fldeff);

    PlayerGetDestCoords(&x, &y);
    if (fldeff == FLDEFF_TALL_GRASS && MapGridGetMetatileIdAt(x, y) == 0x283) // snowy grass tile
    {
        fldeff = FLDEFF_SNOWY_TALL_GRASS;
    }

    if (fldeff < START_OF_NEW_FLD_EFF)
    {
        script = gFieldEffectScriptPointers[fldeff];
    }
    else
    {
        script = gNewFieldEffectScriptPointers[fldeff-START_OF_NEW_FLD_EFF];
    }
    while (sFldEffScrcmdTable[*script](&script, &result))
        ;
    return result;
}

#define tState       data[0]
#define tDestX       data[1]
#define tDestY       data[2]
#define tMonId       data[15]

bool8 FldEff_UseRockClimb(void)
{
    u8 taskId;
    taskId = CreateTask(Task_UseRockClimb, 0xff);
    gTasks[taskId].tMonId = gFieldEffectArguments[0];
    gTasks[taskId].tState = 0;
    Task_UseRockClimb(taskId);
    return FALSE;
}

#undef tState
#undef tDestX
#undef tDestY
#undef tMonId







// snowy tall grass

const struct SpriteFrameImage sPicTable_SnowyTallGrass[] =
{
    overworld_frame(0x9D5E260, 2, 2, 0),
    overworld_frame(0x9D5E260, 2, 2, 1),
    overworld_frame(0x9D5E260, 2, 2, 2),
    overworld_frame(0x9D5E260, 2, 2, 3),
    overworld_frame(0x9D5E260, 2, 2, 4),
};

const union AnimCmd sAnim_SnowyTallGrass[] =
{
    ANIMCMD_FRAME(1, 10),
    ANIMCMD_FRAME(2, 10),
    ANIMCMD_FRAME(3, 10),
    ANIMCMD_FRAME(4, 10),
    ANIMCMD_FRAME(0, 10),
    ANIMCMD_END,
};

const union AnimCmd *const sAnimTable_SnowyTallGrass[] =
{
    sAnim_SnowyTallGrass,
};

const struct SpriteTemplate gFieldEffectObjectTemplate_SnowyTallGrass =
{
    .tileTag = 0xFFFF,
    .paletteTag = FLDEFF_PAL_TAG_SNOWY_TALL_GRASS,
    .oam = 0x083a36f0,
    .anims = sAnimTable_SnowyTallGrass,
    .images = sPicTable_SnowyTallGrass,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = 0x080db3ed,
};

const struct SpritePalette gSpritePalette_SnowyTallGrass = {0x9D5E4F0, FLDEFF_PAL_TAG_SNOWY_TALL_GRASS};


extern const struct SpriteTemplate *const gNewFieldEffectObjectTemplatePointers[];


u32 FldEff_SnowyTallGrass(void)
{
    s16 x;
    s16 y;
    u8 spriteId;
    struct Sprite *sprite;

    x = gFieldEffectArguments[0];
    y = gFieldEffectArguments[1];
    SetSpritePosToOffsetMapCoords(&x, &y, 8, 8);
    //spriteId = CreateSpriteAtEnd(gFieldEffectObjectTemplatePointers[FLDEFFOBJ_TALL_GRASS], x, y, 0);
    spriteId = CreateSpriteAtEnd(gNewFieldEffectObjectTemplatePointers[FLDEFFOBJ_SNOWY_TALL_GRASS - FLDEFFOBJ_NEW_TEMPLATES], x, y, 0);
    if (spriteId != MAX_SPRITES)
    {
        sprite = &gSprites[spriteId];
        sprite->coordOffsetEnabled = TRUE;
        sprite->oam.priority = gFieldEffectArguments[3];
        sprite->data[0] = gFieldEffectArguments[2];
        sprite->data[1] = gFieldEffectArguments[0];
        sprite->data[2] = gFieldEffectArguments[1];
        sprite->data[3] = gFieldEffectArguments[4];
        sprite->data[4] = gFieldEffectArguments[5];
        sprite->data[5] = gFieldEffectArguments[6];
        if (gFieldEffectArguments[7])
        {
            SeekSpriteAnim(sprite, 4);
        }
    }
    return 0;
}




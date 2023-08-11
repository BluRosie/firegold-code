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


const struct SpriteFrameImage sPicTable_RockClimbBlob[] = {
    overworld_frame(0x09DA50A0, 4, 4, 1), // gFieldEffectObjectPic_RockClimbBlob
    overworld_frame(0x09DA50A0, 4, 4, 0),
    overworld_frame(0x09DA50A0, 4, 4, 2),
};

const struct SpriteTemplate gFieldEffectObjectTemplate_RockClimbBlob = {
    .tileTag = 0xFFFF,
    .paletteTag = 0xFFFF,
    .oam = 0x083a3718, // gObjectEventBaseOam_32x32
    .anims = 0x083a555c, // sAnimTable_SurfBlob
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
    FieldEffectActiveListAdd(fldeff);
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

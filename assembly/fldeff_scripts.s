.text
.align 2
.data


.include "event.inc"


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


.global gFieldEffectScript_UseRockClimb
gFieldEffectScript_UseRockClimb:
	//field_eff_callnative FldEff_UseRockClimb
	field_eff_loadfadedpal_callnative gSpritePalette_RockClimbBlob, FldEff_UseRockClimb
	field_eff_end

.global gFieldEffectScript_RockClimbDust
gFieldEffectScript_RockClimbDust:
	field_eff_loadfadedpal_callnative gSpritePalette_BigDust, FldEff_RockClimbDust
	field_eff_end


.global gNewFieldEffectScriptPointers
gNewFieldEffectScriptPointers:
.word gFieldEffectScript_UseRockClimb
.word gFieldEffectScript_RockClimbDust

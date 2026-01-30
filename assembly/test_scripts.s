.include "include/event.inc"

.data
.align 1

@.global test_script
@test_script:
@@callnative bcc_SetTimer
@compare 0x43E9, 0
@goto_if_eq _stepOne
@compare 0x43E9, 1
@goto_if_eq _stepTwo
@goto _stepOne
@
@@ DEBUG!  get this reset later
@_stepOne:
@callnative bcc_Init
@callnative bcc_StoreCaughtMon
@setvar 0x43E9, 1
@end
@
@_stepTwo:
@@ real script
@callnative bcc_SpawnIconsAndWindows
@msgbox gText_bcc_SwapThisMon, MSGBOX_YESNO
@closemessage
@@ yes
@compare 0x800D, 1
@goto_if_eq acceptsMon
@goto postAcceptMon
@
@acceptsMon:
@callnative bcc_DepositBCCMon
@callnative bcc_DeleteBCCMon
@setvar 0x43E9, 0
@
@postAcceptMon:
@callnative bcc_DeleteSpritesAndWindow
@end

.global bcc_ContestIsOver
bcc_ContestIsOver:
lockall
msgbox gText_bcc_ContestIsOver
setvar 0x43E9 0x1
setvar 0x43B5 0x1
warp 0x722E, 0x16, 0x13
waitstate
end

.global bcc_SwapMonPrompt
bcc_SwapMonPrompt:
callnative bcc_SpawnIconsAndWindows
msgbox gText_bcc_SwapThisMon, MSGBOX_YESNO
closemessage
@ yes
compare 0x800D, 1
goto_if_eq acceptsMon
callnative bcc_DeleteCaughtMon
goto postAcceptMon

acceptsMon:
callnative bcc_StoreCaughtMon

postAcceptMon:
callnative bcc_DeleteSpritesAndWindow
end


@.global bcc_EventScriptInit
@bcc_EventScriptInit:
@callnative bcc_Init
@setworldmapflag 0x230A
@compare 0x43E9, 0x1
@goto_if_eq 0x08AE41E8
@end

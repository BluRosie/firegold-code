.include "include/event.inc"

.data
.align 1

.global test_script
test_script:
callnative bcc_SetTimer
@callnative bcc_StoreCaughtMon
@callnative bcc_SpawnIconsAndWindows
@callnative bcc_DepositAndFreeMon
end

.global bcc_ContestIsOver
bcc_ContestIsOver:
lockall
msgbox gText_bcc_ContestIsOver
setvar 0x43E9 0x1
setvar 0x43B5 0x1
warp 0x722E, 0x16, 0x13
waitstate
end

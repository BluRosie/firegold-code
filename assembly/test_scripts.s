.data
.align 1

.include "include/event.inc"

.global test_script
test_script:
callnative bcc_StoreCaughtMon
callnative bcc_SpawnIconsAndWindows
callnative bcc_DepositAndFreeMon
end

.global bcc_ContestIsOver
bcc_ContestIsOver:
lockall
msgbox gText_bcc_ContestIsOver

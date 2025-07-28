.data
.align 1

.include "include/event.inc"

.global test_script
test_script:
callnative StoreCaughtBCCMon
callnative SpawnIconsForBCC
callnative FreeCaughtBCCMonAndDeposit
end

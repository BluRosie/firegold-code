
// hook from 0805E7C0 using r6 which is just literally free at this point
.global costume_overworldHook
costume_overworldHook:
strb r1, [r4, #3]
ldr r0, [r5, #0x1C]
bl grabCostumeImagesPtrBasedOnOriginal
str r0, [r4, #0xC]
mov r3, r0
ldr r0, [r5, #0x18]
ldr r1, =0x0805F100 | 1
bx r1

.global costume_paletteHook
costume_paletteHook:
push {r1-r3}
bl grabCostumePalTagBasedOnOriginal
pop {r1-r3}
ldr r1, =0x0805F544 | 1
bx r1

.pool

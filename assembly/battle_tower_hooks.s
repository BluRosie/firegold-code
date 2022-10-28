.thumb
.thumb_func
.align 2


.equ BattleType,        0x02022B4C
.equ TrainerBuffer,     0x020386AE
.equ TrainerData,       0x0203C028
.equ TrainerTable,      0x0823EAC8


/* Put 00 4A 10 47 XX XX XX 08 at 0xFBE0 (hook via r2) */

/*
----------------------------------------------------------
This routine changes the address to load Trainer Data from
to be the Battle Tower Trainer RAM (0x0203C028) if the
index number of the current trainer is 0x0.
----------------------------------------------------------
*/

StartFBE0:
    ldr r0, =TrainerBuffer
    ldrh r1, [r0]
    cmp r1, #0x0
    beq LoadBattleTowerFBE0
    ldr r2, =TrainerTable
    lsl r0, r1, #0x2
    add r0, r0, r1
    lsl r0, r0, #0x3
    add r0, r0, r2
    ldrb r0, [r0, #0x1]
    b ReturnFBF0

LoadBattleTowerFBE0:
    ldr r2, =TrainerData
    ldrb r0, [r2, #0x1]

ReturnFBF0:
    ldr r7, .ReturnFBF0
    bx r7

.align 2
.ReturnFBF0:            .word 0x0800FBF1
.pool




/* Put 00 4A 10 47 XX XX XX 08 at 0xFC68 (hook via r2) */

/*
----------------------------------------------------------
This routine changes the address to load Trainer Data from
to be the Battle Tower Trainer RAM (0x0203C028) if the
index number of the current trainer is 0x0.
----------------------------------------------------------
*/

StartFC68:
    ldr r0, =TrainerBuffer
    ldrh r1, [r0]
    cmp r1, #0x0
    beq LoadBattleTowerFC68
    ldr r2, =TrainerTable
    lsl r0, r1, #0x2
    add r0, r0, r1
    lsl r0, r0, #0x3
    add r0, r0, r2
    ldrb r0, [r0, #0x1]
    b ReturnFC68

LoadBattleTowerFC68:
    ldr r2, =TrainerData
    ldrb r0, [r2, #0x1]

ReturnFC68:
    ldr r7, .ReturnFC68
    bx r7

.align 2
.ReturnFC68:            .word 0x0800FC79
.pool




/* Put 00 4A 10 47 XX XX XX 08 at 0x11320 (hook via r2) */

/*
----------------------------------------------------------
This routine changes the address to load Trainer Data from
to be the Battle Tower Trainer RAM (0x0203C028) if the
index number of the current trainer is 0x0.
----------------------------------------------------------
*/

Start11320:
    ldr r1, [sp, #0x20]
    ldr r3, [sp, #0x14]
    add r0, r1, r3
    cmp r3, #0x0
    beq LoadBattleTower11320
    ldr r2, =TrainerTable
    lsl r0, r0, #0x3
    add r0, r0, r2
    add r0, r0, #0x20
    b Return11320

LoadBattleTower11320:
    ldr r2, =TrainerData
    mov r0, r2
    add r0, r0, #0x20

Return11320:
    ldr r4, .Return11320
    bx r4

.align 2
.Return11320:           .word 0x0801132F
.pool




/* Put 00 4A 10 47 XX XX XX 08 at 0x11368 (hook via r2) */

/*
----------------------------------------------------------
This routine changes the address to load Trainer Data from
to be the Battle Tower Trainer RAM (0x0203C028) if the
index number of the current trainer is 0x0.
----------------------------------------------------------
*/

Start11368:
    ldr r2, [sp, #0x20]
    ldr r3, [sp, #0x14]
    cmp r3, #0x0
    beq LoadBattleTower11368
    ldr r0, =TrainerTable
    add r1, r2, r3
    lsl r1, r1, #0x3
    add r3, r0, #0x4
    add r1, r1, r3
    b Return11368

LoadBattleTower11368:
    ldr r1, =TrainerData
    mov r0, r1
    mov r3, r1
    add r3, r3, #0x4
    
Return11368:
    ldr r4, .Return11368
    bx r4

.align 2
.Return11368:           .word 0x08011377
.pool




/* Put 00 4A 10 47 XX XX XX 08 at 0x1169C (hook via r2) */

/*
----------------------------------------------------------
This routine changes the address to load Trainer Data from
to be the Battle Tower Trainer RAM (0x0203C028) if the
index number of the current trainer is 0x0.
----------------------------------------------------------
*/

Start1169C:
    ldr r4, [sp, #0x20]
    ldr r2, [sp, #0x14]
    cmp r2, #0x0
    beq LoadBattleTower1169C

WildBattle1169C:
    ldr r0, =TrainerTable
    add r1, r4, r2
    lsl r1, r1, #0x3
    add r1, r1, r0
    add r1, r1, #0x20
    b Return1169C

LoadBattleTower1169C:
    ldr r0, =BattleType
    ldr r0, [r0]
    mov r1, #0x4        /* Wild Battle */
    and r1, r0
    cmp r1, #0x0
    bne WildBattle1169C
    ldr r0, =TrainerData
    mov r1, r0
    add r1, r1, #0x20
    
Return1169C:
    ldr r4, .Return1169C
    bx r4

.align 2
.Return1169C:           .word 0x080116AB
.pool




/* Put 00 4A 10 47 XX XX XX 08 at 0x156FC (hook via r2) */

/*
----------------------------------------------------------
This routine changes the address to load Trainer Data from
to be the Battle Tower Trainer RAM (0x0203C028) if the
index number of the current trainer is 0x0.
----------------------------------------------------------
*/

Start156FC:
    str r0, [r1]
    ldr r0, =TrainerBuffer
    ldrh r1, [r0]
    cmp r1, #0x0
    beq LoadBattleTower156FC
    ldr r2, =TrainerTable
    lsl r0, r1, #0x2
    add r0, r0, r1
    lsl r0, r0, #0x3
    add r0, r0, r2
    b Return156FC

LoadBattleTower156FC:
    ldr r2, =TrainerData
    mov r0, r2

Return156FC:
    ldr r7, .Return156FC
    bx r7

.align 2
.Return156FC:           .word 0x0801570D
.pool




/* Put 00 4A 10 47 XX XX XX 08 at 0x25904 (hook via r2) */

/*
----------------------------------------------------------
This routine changes the address to load Trainer Data from
to be the Battle Tower Trainer RAM (0x0203C028) if the
index number of the current trainer is 0x0.
----------------------------------------------------------
*/

Start25904:
    ldrh r1, [r0]
    cmp r1, #0x0
    beq LoadBattleTower25904
    ldr r2, =TrainerTable
    lsl r0, r1, #0x2
    add r0, r0, r1
    lsl r3, r0, #0x3
    add r4, r3, r2
    b Return25904

LoadBattleTower25904:
    ldr r2, =TrainerData
    mov r4, r2

Return25904:
    ldr r1, .Return25904
    bx r1

.align 2
.Return25904:           .word 0x08025911
.pool




/* Put 00 4A 10 47 XX XX XX 08 at 0x25988 (hook via r2) */

/*
----------------------------------------------------------
This routine changes the address to load Trainer Data from
to be the Battle Tower Trainer RAM (0x0203C028) if the
index number of the current trainer is 0x0.
----------------------------------------------------------
*/

Start25988:
    ldr r0, =TrainerBuffer
    ldrh r1, [r0]
    cmp r1, #0x0
    beq LoadBattleTower25988
    ldr r2, =TrainerTable
    lsl r0, r1, #0x2
    add r0, r0, r1
    lsl r0, r0, #0x3
    add r0, r0, r2
    b Return25988

LoadBattleTower25988:
    ldr r0, =TrainerData

Return25988:
    ldr r2, .Return25988
    bx r2

.align 2
.Return25988:           .word 0x08025997
.pool




/* Put 00 4A 10 47 XX XX XX 08 at 0x37D2C (hook via r2) */

/*
----------------------------------------------------------
This routine changes the address to load Trainer Data from
to be the Battle Tower Trainer RAM (0x0203C028) if the
index number of the current trainer is 0x0.
----------------------------------------------------------
*/

Start37D2C:
    ldrh r1, [r3]
    cmp r1, #0x0
    beq LoadBattleTower37D2C
    ldr r2, =TrainerTable
    lsl r0, r1, #0x2
    add r0, r0, r1
    lsl r0, r0, #0x3
    add r0, r0, r2
    b Return37D2C

LoadBattleTower37D2C:
    ldr r2, =TrainerData
    mov r0, r2

Return37D2C:
    ldr r6, .Return37D2C
    bx r6

.align 2
.Return37D2C:           .word 0x08037D39
.pool




/* Put 00 4A 10 47 XX XX XX 08 at 0x37F00 */

/*
----------------------------------------------------------
This routine changes the address to load Trainer Data from
to be the Battle Tower Trainer RAM (0x0203C028) if the
index number of the current trainer is 0x0.
----------------------------------------------------------
*/

Start37F00:
    ldrh r1, [r3]
    cmp r1, #0x0
    beq LoadBattleTower37F00
    ldr r2, =TrainerTable
    lsl r0, r1, #0x2
    add r0, r0, r1
    lsl r0, r0, #0x3
    add r0, r0, r2
    b Return37F00

LoadBattleTower37F00:
    ldr r2, =TrainerData
    mov r0, r2

Return37F00:
    ldr r7, .Return37F00
    bx r7

.align 2
.Return37F00:           .word 0x08037F0D
.pool




/* Put 00 4A 10 47 XX XX XX 08 at 0x437B8 (hook via r2) */

/*
----------------------------------------------------------
This routine changes the address to load Trainer Data from
to be the Battle Tower Trainer RAM (0x0203C028) if the
index number of the current trainer is 0x0.
----------------------------------------------------------
*/

Start437B8:
    ldr r0, =TrainerBuffer
    ldrh r1, [r0]
    cmp r1, #0x0
    beq LoadBattleTower437B8
    ldr r2, =TrainerTable
    lsl r0, r1, #0x2
    add r0, r0, r1
    lsl r0, r0, #0x3
    add r0, r0, r2
    b Return437B8

LoadBattleTower437B8:
    ldr r2, =TrainerData
    mov r0, r2

Return437B8:
    ldr r4, .Return437B8
    bx r4

.align 2
.Return437B8:           .word 0x080437C7
.pool




/* Put 00 4A 10 47 XX XX XX 08 at 0x44008 (hook via r2) */

/*
----------------------------------------------------------
This routine changes the address to load Trainer Data from
to be the Battle Tower Trainer RAM (0x0203C028) if the
index number of the current trainer is 0x0.
----------------------------------------------------------
*/

Start44008:
    ldr r0, =TrainerBuffer
    ldrh r1, [r0]
    cmp r1, #0x0
    beq LoadBattleTower44008
    ldr r2, =TrainerTable
    lsl r0, r1, #0x2
    add r0, r0, r1
    lsl r0, r0, #0x3
    add r0, r0, r2
    b Return44008

LoadBattleTower44008:
    ldr r2, =TrainerData
    mov r0, r2

Return44008:
    ldr r7, .Return44008
    bx r7

.align 2
.Return44008:           .word 0x08044017
.pool




/* Put 00 4A 10 47 XX XX XX 08 at 0x7FE60 (hook via r2) */

/*
----------------------------------------------------------
This routine changes the address to load Trainer Data from
to be the Battle Tower Trainer RAM (0x0203C028) if the
index number of the current trainer is 0x0.
----------------------------------------------------------
*/

Start7FE60:
    cmp r0, #0x0
    beq LoadBattleTower7FE60
    ldr r5, =TrainerTable
    lsl r1, r0, #0x2
    add r1, r1, r0
    lsl r1, r1, #0x3
    add r2, r1, r5
    mov r0, r2
    add r0, r0, #0x20
    b Return7FE60

LoadBattleTower7FE60:
    ldr r5, =TrainerData
    mov r2, r5
    mov r0, r5
    mov r1, #0x0
    add r0, r0, #0x20
    
Return7FE60:
    ldr r7, .Return7FE60
    bx r7

.align 2
.Return7FE60:           .word 0x0807FE6D
.pool




/* Put 00 4A 10 47 XX XX XX 08 at 0x7FF90 (hook via r2) */

/*
----------------------------------------------------------
This routine changes the address to load Trainer Data from
to be the Battle Tower Trainer RAM (0x0203C028) if the
index number of the current trainer is 0x0.
----------------------------------------------------------
*/

Start7FF90:
    ldrh r2, [r4]
    cmp r2, #0x0
    beq LoadBattleTower7FF90
    ldr r1, =TrainerTable
    lsl r0, r2, #0x2
    add r0, r0, r2
    lsl r0, r0, #0x3
    add r0, r0, r1
    b Return7FF90

LoadBattleTower7FF90:
    ldr r1, =TrainerData
    mov r0, r1

Return7FF90:
    ldr r7, .Return7FF90
    bx r7

.align 2
.Return7FF90:           .word 0x0807FF9B
.pool




/* Put 00 4A 10 47 XX XX XX 08 at 0xC6F20 (hook via r2) */

/*
----------------------------------------------------------
This routine changes the address to load Trainer Data from
to be the Battle Tower Trainer RAM (0x0203C028) if the
index number of the current trainer is 0x0.
----------------------------------------------------------
*/

StartC6F20:
    ldr r3, [r0, #0x14]
    ldrh r1, [r4]
    cmp r1, #0x0
    beq LoadBattleTowerC6F20

WildBattleC6F20:
    ldr r2, =TrainerTable
    lsl r0, r1, #0x2
    add r0, r0, r1
    lsl r0, r0, #0x3
    add r2, r2, #0x1C
    add r0, r0, r2
    b ReturnC6F20

LoadBattleTowerC6F20:
    ldr r0, =BattleType
    ldr r0, [r0]
    mov r1, #0x4        /* Wild Battle */
    and r1, r0
    cmp r1, #0x0
    bne WildBattleC6F20
    ldr r2, =TrainerData
    mov r0, r2
    add r0, r0, #0x1C

ReturnC6F20:
    ldr r7, .ReturnC6F20
    bx r7

.align 2
.ReturnC6F20:           .word 0x080C6F31
.pool




/* Put 00 4A 10 47 XX XX XX 08 at 0xD8084 (hook via r2) */

/*
----------------------------------------------------------
This routine changes the address to load Trainer Data from
to be the Battle Tower Trainer RAM (0x0203C028) if the
index number of the current trainer is 0x0.
----------------------------------------------------------
*/

StartD8084:
    ldrh r1, [r3]
    cmp r1, #0x0
    beq LoadBattleTowerD8084
    ldr r2, =TrainerTable
    lsl r0, r1, #0x2
    add r0, r0, r1
    lsl r0, r0, #0x3
    add r0, r0, r2
    b ReturnD8084

LoadBattleTowerD8084:
    ldr r2, =TrainerData
    mov r0, r2

ReturnD8084:
    ldr r7, .ReturnD8084
    bx r7

.align 2
.ReturnD8084:           .word 0x080D8091
.pool




/* Put 00 4A 10 47 XX XX XX 08 at 0xD8134 (hook via r2) */

/*
----------------------------------------------------------
This routine changes the address to load Trainer Data from
to be the Battle Tower Trainer RAM (0x0203C028) if the
index number of the current trainer is 0x0.
----------------------------------------------------------
*/

StartD8134:
    ldrh r0, [r5]
    cmp r0, #0x0
    beq LoadBattleTowerD8134
    ldr r2, =TrainerTable
    lsl r1, r0, #0x2
    add r1, r1, r0
    lsl r1, r1, #0x3
    add r0, r1, r2
    b ReturnD8134

LoadBattleTowerD8134:
    ldr r2, =TrainerData
    mov r0, r2

ReturnD8134:
    ldr r7, .ReturnD8134
    bx r7

.align 2
.ReturnD8134:           .word 0x080D8141
.pool




/* Put 00 4A 10 47 XX XX XX 08 at 0x1137F0 (hook via r2) */

/*
----------------------------------------------------------
This routine changes the address to load Trainer Data from
to be the Battle Tower Trainer RAM (0x0203C028) if the
index number of the current trainer is 0x0.
----------------------------------------------------------
*/

Start1137F0:
    ldrh r1, [r1]
    cmp r1, #0x0
    beq LoadBattleTower1137F0
    ldr r2, =TrainerTable
    lsl r0, r1, #0x2
    add r0, r0, r1
    lsl r0, r0, #0x3
    add r0, r0, r2
    b Return1137F0

LoadBattleTower1137F0:
    ldr r2, =TrainerData
    mov r0, r2

Return1137F0:
    ldr r1, .Return1137F0
    bx r1

.align 2
.Return1137F0:          .word 0x081137FB
.pool




/* Put 00 4A 10 47 XX XX XX 08 at 0x115200 (hook via r2) */

/*
----------------------------------------------------------
This routine changes the address to load Trainer Data from
to be the Battle Tower Trainer RAM (0x0203C028) if the
index number of the current trainer is 0x0.
----------------------------------------------------------
*/

Start115200:
    ldrh r1, [r5, #0x4]
    cmp r1, #0x0
    beq LoadBattleTower115200
    ldr r3, =TrainerTable
    lsl r0, r1, #0x2
    add r0, r0, r1
    lsl r2, r0, #0x3
    add r0, r2, r3
    b Return115200

LoadBattleTower115200:
    ldr r3, =TrainerData
    mov r0, r3

Return115200:
    ldr r2, .Return115200
    bx r2

.align 2
.Return115200:          .word 0x0811520D
.pool




/* Put 00 4A 10 47 XX XX XX 08 at 0x12C020 (hook via r2) */

/*
----------------------------------------------------------
This routine changes the address to load Trainer Data from
to be the Battle Tower Trainer RAM (0x0203C028) if the
index number of the current trainer is 0x0.
----------------------------------------------------------
*/

Start12C020:
    ldr r2, =TrainerBuffer
    ldrh r1, [r2]
    cmp r1, #0x0
    beq LoadBattleTower12C020
    ldr r3, =TrainerTable
    lsl r0, r1, #0x2
    add r0, r0, r1
    lsl r0, r0, #0x3
    add r0, r0, r3
    b Return12C020

LoadBattleTower12C020:
    ldr r3, =TrainerData
    mov r0, r3

Return12C020:
    ldr r1, .Return12C020
    bx r1

.align 2
.Return12C020:          .word 0x0812C02D
.pool




/* Put 00 4A 10 47 XX XX XX 08 at 0x11670 */

/*
----------------------------------------------------------
This routine changes the address to load Trainer Data from
to be the Battle Tower Trainer RAM (0x0203C028) if the
index number of the current trainer is 0x0.
----------------------------------------------------------
*/

Start11670:
    ldr r1, [sp, #0x20]
    ldr r3, [sp, #0x14]
    cmp r3, #0x0
    beq LoadBattleTower11670
    ldr r2, =TrainerTable
    add r0, r1, r3
    lsl r0, r0, #0x3
    add r0, r0, r2
    add r0, r0, #0x20
    b Return11670

LoadBattleTower11670:
    ldr r2, =TrainerData
    mov r0, r2
    add r0, r0, #0x20

Return11670:
    ldr r7, .Return11670
    bx r7   

.align 2
.Return11670:           .word 0x0801167F
.pool




/* Put 00 4A 10 47 XX XX XX 08 at 0x11688 */

/*
----------------------------------------------------------
This routine changes the address to load Trainer Data from
to be the Battle Tower Trainer RAM (0x0203C028) if the
index number of the current trainer is 0x0.
----------------------------------------------------------
*/

Start11688:
    ldr r2, =BattleType
    ldr r4, [sp, #0x20]
    ldr r3, [sp, #0x14]
    cmp r3, #0x0
    beq LoadBattleTower11688
    ldr r1, =TrainerTable
    add r0, r4, r3
    lsl r0, r0, #0x3
    add r0, r0, r1
    b Return11688

LoadBattleTower11688:
    ldr r0, =TrainerData

Return11688:
    ldr r1, .Return11688
    bx r1   

.align 2
.Return11688:           .word 0x08011695
.pool

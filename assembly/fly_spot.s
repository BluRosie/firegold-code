.text
.align 2

.global GetMapSecType
GetMapSecType:
    push {lr}
    push {r2-r4}
    lsl r0, #0x18 // u8 cast
    lsr r0, #0x18
    sub r0, #0x58
    cmp r0, #0x6d
    bls map_is_valid
    b invalid_map
map_is_valid:
// add handling for excluding kanto when in johto and vice versa
// grab sRegionMap->playersRegion
    ldr r1, =0x23E1 // offsetof(struct RegionMap, playersRegion)
    ldr r2, =0x020399D4 // struct RegionMap *sRegionMap
    ldr r2, [r2] // struct RegionMap sRegionMap
    add r2, r1 // r2 = &sRegionMap.playersRegion
    ldrb r2, [r2] // sRegionMap.playersRegion
    cmp r2, #1
    bge handleJohto // assuming kanto is 0
    nop

handleKanto:
    mov r1, #3 // invalid town map?
    cmp r0, #(0x8E-0x58)
    bhi skip_r1_2
    b checkB

handleJohto:
    mov r1, #3
    cmp r0, #(0x8E-0x58)
    ble skip_r1_2
    //b checkB

checkB:
    cmp r0, #0xB
    beq handleB
return_to_main:
    lsl r0, #1
    ldr r1, =0x080C3654
    add r0, r1
    ldrh r0, [r0] // load in current flag
    ldr r4, =0xFFFF
    cmp r4, r0
    beq invalid_map
    mov r4, #0
    cmp r0, r4
    beq return_0
    ldr r4, =(0x806E6D0 | 1) // FlagGet
    bl bx_r4
    lsl r0, #0x18
    mov r1, #0x3
    cmp r0, #0
    beq skip_r1_2
    mov r1, #2
skip_r1_2:
    mov r0, r1
    b GetMapSecType_return
invalid_map:
    mov r0, #1
    b GetMapSecType_return
return_0:
    mov r0, #0
GetMapSecType_return:
    pop {r2-r4}
    pop {r1}
    bx r1

handleB:
    mov r0, #3
    ldr r1, =0x020399D4
    ldr r1, [r1]
    ldr r2, =0x4797
    add r1, r1, r2
    add r1, r1, r0
    ldrb r0, [r1]
    lsl r4, r0, #0x18
    mov r0, #0xB
    cmp r4, #0
    bne return_to_main
    mov r0, #0
    b GetMapSecType_return

bx_r4:
    bx r4

.pool

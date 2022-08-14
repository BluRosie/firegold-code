.thumb
.align 2

.global DecideWhichRegionMap
DecideWhichRegionMap:
    cmp r0, #0x88
    beq _isJohto
    cmp r0, #0x8E
    bls return_1
_isJohto:
    ldr r4, =0x08C01580 //0x083F1AA4
    mov r12, r4
    ldr r3, =0x080C006C|1
    bx r3
    
    
return_1:
    ldr r4, =0x080C00D8|1
    bx r4

.pool

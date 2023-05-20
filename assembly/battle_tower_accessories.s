.thumb
.thumb_func
.align 2

.equ Flag, 0x2322 // flag for in battle tower disables everything here

.global DisableExp
DisableExp:
	push {r0-r3}
    ldr r0, =Flag
	ldr r2, =(0x806E6D0 +1) @checkflag 0xFF *0x2 + 4 = 0x202
	bl bx_r2
	cmp r0, #0x1
	beq skipDisableExp
	pop {r0-r3}
	cmp r0, #0x64
	beq noCrashDisableExp
	ldr r0, =(0x8021D24 +1)
	bx r0
	
skipDisableExp:
	pop {r0-r3}
	
noCrashDisableExp:
	ldr r1, [r5]
	add r1, #0x53
	ldrb r0, [r1]
	ldr r2, =(0x8021D04 +1)
	bx r2

.pool



.align 2

.global DisablePrizeMoney1
DisablePrizeMoney1:
    push {r0-r3}
    ldr r0, =Flag
    ldr r2, =(0x806E6D0 +1)
    bl bx_r2
    cmp r0, #0x1
    beq skipDisablePrize1
    pop {r0-r3}
    mov r0, #0x0
    mov r1, r8
    ldr r0, [r1]
    mov r1, #0xa4
    lsl r1, r1, #0x2
    add r0, r0, r1
    add r1, r4, #0x0
    ldr r2, =(0x809FDA0 +1)
    bl bx_r2
    ldr r1, =(0x8025A00 +1)
    bx r1
    
skipDisablePrize1:
    pop {r0-r3}
    mov r0, #0x0
    mov r1, r8
    ldr r0, [r1]
    mov r1, #0xa4
    lsl r1, r1, #0x2
    add r0, r0, r1
    add r1, r4, #0x0
    ldr r1, =(0x8025A00 +1)
    bx r1

.pool





.align 2

.global DisablePrizeMoney2
DisablePrizeMoney2:
    ldr r0, =Flag
    ldr r2, =(0x806E6D0 +1)
    bl bx_r2
    cmp r0, #0x1
    beq skipDisablePrize2
    add r0, r4, #0x0
    ldr r2, =(0x809fdd8 +1)
    bl bx_r2
    
skipDisablePrize2:
    ldr r2, =(0x80a0058 +1)
    bl bx_r2
    ldr r2, =(0x8054BEA +1)
    bl bx_r2

.pool
    


.align 2


.global DisablePrizeMoney3
DisablePrizeMoney3:
    ldr r0, =(0x83fb432)
    cmp r2, r0
    beq checkflag3
    ldr r0, =(0x83fb4f6)
    cmp r2, r0
    beq checkflag3
    b noskip3

checkflag3:
    ldr r0, =Flag
    ldr r3, =(0x806E6D0 +1)
    bl bx_r3
    cmp r0, #0x1
    beq skipDisablePrize3

noskip3:
    ldr r0, =(0x202298C)
    mov r1, #0x0
    ldr r3, =(0x80D87BC +1)
    bl bx_r3
    
skipDisablePrize3:
    ldr r0, =(0x8032B4C +1)
    bx r0

.pool


.align 2

bx_r2:
	bx r2

.align 2

bx_r3:
	bx r3

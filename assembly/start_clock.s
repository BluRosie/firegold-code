	.text
	.align 1
    .thumb

.global StartCB_HandleInput_hook
StartCB_HandleInput_hook:
push {r0-r7}

bl StartCB_HandleInput

pop {r0-r7}
mov r0, #1
and r0, r1
cmp r0, #0
beq ret_2
ldr r0, =0x0806F32C|1
bx r0

ret_2:
ldr r0, =0x0806F378|1
bx r0


.global DoDrawStartMenu_hook
DoDrawStartMenu_hook:
push {r4-r7}
bl DoDrawStartMenu_Case3
pop {r4-r7}
ldr r1, =0x0806F09C|1
bx r1


	.text
	.align 1
    .thumb

//.global StartCB_HandleInput_hook
//StartCB_HandleInput_hook:
//push {r0-r7}
//
//bl StartCB_HandleInput
//
//pop {r0-r7}
//mov r0, #1
//and r0, r1
//cmp r0, #0
//beq ret_2
//ldr r0, =0x0806F32C|1
//bx r0
//
//ret_2:
//ldr r0, =0x0806F378|1
//bx r0
//
//
//.global DoDrawStartMenu_hook
//DoDrawStartMenu_hook:
//push {r4-r7}
//bl DoDrawStartMenu_Case3
//pop {r4-r7}
//ldr r1, =0x0806F09C|1
//bx r1


.global bcc_RunSomethingEveryFrame
bcc_RunSomethingEveryFrame:
push {lr}
bl bcc_TimerCallback
ldr r0, =0x03000E7C
ldrb r0, [r0]
cmp r0, #1
bne _ret_080548C4
ldr r0, =0x08054876 | 1
bx r0

_ret_080548C4:
pop {r0}
bx r0

.pool

.global HandleInputChooseAction_editedcase_hook
HandleInputChooseAction_editedcase_hook:
bl HandleInputChooseAction_editedcase
cmp r0, #0
bne diff_return
ldr r1, =0x802E616 | 1
bx r1

diff_return:
ldr r0, =0x0802E61A | 1;
bx r0

.pool


.equ battle_tower_flag, 0x2322 // flag for in battle tower disables everything here
.equ bcc_flag, 0x2342
.equ skip_whiteout_flag, 0x236f

.global ContinueScriptOverWhiteout
ContinueScriptOverWhiteout:
push {r0,r2}
ldr r0, =battle_tower_flag
ldr r2, =0x0806E6D1
bl bx_r2
cmp r0, #0x1
beq sub_flag_on
ldr r0, =bcc_flag
ldr r2, =0x0806E6D1
bl bx_r2
cmp r0, #0x1
beq sub_flag_on
beq sub_flag_on
ldr r0, =skip_whiteout_flag
ldr r2, =0x0806E6D1
bl bx_r2
cmp r0, #0x1
beq sub_flag_on


pop {r0,r2}
mov r0, #0x1 @Original response
pop {r1}
bx r1

sub_flag_on:
pop {r0, r2}
mov r0, #0x0 @Hacked response
pop {r1}
bx r1

.pool

.align 2

bx_r2:
	bx r2

.thumb

.global updateNPCPal
updateNPCPal:
push {r4-r6,lr}
mov r4, #0
ldr r5, =0x203ff00
ldr r6, =0x203fd00

loop:
ldrb r0, [r5]
cmp r0, #0
beq next
bl update

next:
add r4, #1
add r5, #4
cmp r4, #16
blo loop

end:
pop {r4-r6,pc}


update:
lsl r2, r4, #5
ldr r1, =0x20373f8
add r0, r6, r2
add r1, r2
mov r2, #16
swi #0xb
mov r0, r4
ldr r1, =0x8083598+1
bx r1

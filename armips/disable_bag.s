.gba
.thumb

.open "test.gba", 0x08000000

.org 0x080143D4

ldr r0, =0x2322
bl 0x0806E6D0 // checkflag
beq 0x08014428
nop
nop

.org 0x08014410
.pool

.close

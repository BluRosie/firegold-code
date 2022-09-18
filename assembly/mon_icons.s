.thumb
.align 2

.global PrintMonIcons_hook
PrintMonIcons_hook:
    mov r1, #2
    bl 0x08003F20
    mov r0, #2
    mov r1, #3
    bl 0x08003F20
    
    //bl PrintMonIcons
    
    ldr r0, =0x0800C994|1
    bx r0

.pool

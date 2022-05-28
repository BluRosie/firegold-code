.force_thumb
.align 2

.global GenerateUnownFormSelectively_hook
GenerateUnownFormSelectively_hook:
    mov r0, r6
    ldr r3, =(GenerateUnownFormSelectively+1)
    bl bx_r3
    pop {r4-r6}
    pop {r0}
    bx r0

bx_r3:
    bx r3

.pool

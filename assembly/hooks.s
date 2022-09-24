.text
.align 2
.thumb

.global CalculateBaseDamage_hook
CalculateBaseDamage_hook:
pop {r5-r6}
push {lr}
bl CalculateBaseDamage
pop {pc}

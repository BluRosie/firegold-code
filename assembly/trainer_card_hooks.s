.force_thumb
.align 2


.global SetDataFromTrainerCard_edits_hook
SetDataFromTrainerCard_edits_hook:
bl SetDataFromTrainerCard_edits
pop {r4-r5}
pop {r0}
bx r0

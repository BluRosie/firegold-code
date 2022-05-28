.force_thumb
.align 2


.global SetDataFromTrainerCard_edits_hook
SetDataFromTrainerCard_edits_hook:
bl SetDataFromTrainerCard_edits
pop {r4-r5}
pop {r0}
bx r0

.global SaveStatToString_case_badges_hook
SaveStatToString_case_badges_hook:
mov r0, r5
bl SaveStatToString_case_badges
pop {r4-r7}
pop {r0}
bx r0

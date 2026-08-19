
// hook from 0805E7C0 using r6 which is just literally free at this point
.global costume_overworldHook
costume_overworldHook:
strb r1, [r4, #3]
ldr r0, [r5, #0x1C]
bl grabCostumeImagesPtrBasedOnOriginal
str r0, [r4, #0xC]
mov r3, r0
ldr r0, [r5, #0x18]
ldr r1, =0x0805F100 | 1
bx r1


.global costume_paletteHook
costume_paletteHook:
push {r1-r3}
bl grabCostumePalTagBasedOnOriginal
pop {r1-r3}
ldr r1, =0x0805F544 | 1
bx r1


.global costume_trainerSpriteHook
costume_trainerSpriteHook:
cmp r4, #135 // TRAINER_PIC_RED
beq _costumeFrontSpriteHandling
cmp r4, #136 // TRAINER_PIC_LEAF
beq _costumeFrontSpriteHandling
lsl r0, r4, #3
ldr r1, =0x0823957C
add r0, r0, r1
_postSpriteHandling:
mov r1, r5
ldr r2, =0x0810BC34 | 1
bx r2

_costumeFrontSpriteHandling:
mov r0, r4
mov r1, #0 // front sprite handling
mov r2, #0 // sprite pointer
bl GrabSpriteCostumePointer
// ptr return in r0
b _postSpriteHandling

.global costume_trainerPalHook
costume_trainerPalHook:
cmp r0, #135 // TRAINER_PIC_RED
beq _costumeFrontSpritePalHandling
cmp r0, #136 // TRAINER_PIC_LEAF
beq _costumeFrontSpritePalHandling
ldr r1, =0x08239a1c // gTrainerFrontPicPaletteTable
lsl r0, #3
add r0, r1
ldr r0, [r0]
b _costumeFrontSpritePalReturn

_costumeFrontSpritePalHandling:
// r0 is already TRAINER_PIC_*
mov r1, #0 // front sprite handling
mov r2, #1 // palette pointer
bl GrabSpriteCostumePointer

_costumeFrontSpritePalReturn:
ldr r1, =0x0810BD6C | 1
bx r1


.global costume_trainerPalHofHook
costume_trainerPalHofHook:
cmp r4, #135
beq _costumeFrontSpritePalHandlingHof
cmp r4, #136
beq _costumeFrontSpritePalHandlingHof
ldr r1, =0x08239a1c // gTrainerFrontPicPaletteTable
lsl r0, r4, #3
add r0, r1
ldr r0, [r0]
b _costumeFrontSpritePalHandlingHofReturn

_costumeFrontSpritePalHandlingHof:
mov r0, r4 // id
mov r1, #0 // front sprite handling
mov r2, #1 // palette pointer
bl GrabSpriteCostumePointer

_costumeFrontSpritePalHandlingHofReturn:
ldr r2, =0x0810BD00 | 1
bx r2


.global costume_trainerBackHook
costume_trainerBackHook:
bl AdjustBackspriteTemplateAsNeeded
ldr r1, =0x08239F74
lsl r0, r4, #2
add r0, r0, r1
ldr r0, [r0]
ldr r2, =0x0803F898 | 1
bx r2


// this is for the animated portion of the sprite
.global costume_trainerBackPalHook
costume_trainerBackPalHook:
// r0 is already gender
add r0, #135 // TRAINER_PIC_RED used for GrabSpriteCostumePointer
mov r1, #1 // back
mov r2, #1 // palette
bl GrabSpriteCostumePointer
lsr r4, #0x14
ldr r2, =0x08033530 | 1
bx r2

// this is for the nonanimated portion of the sprite
.global costume_trainerBackPalHook2
costume_trainerBackPalHook2:
// need to return to 0803475E with the palette address in r0
cmp r0, #1
bhi _defaultBackPalHandling
push {r1}
add r0, #135
mov r1, #1 // back
mov r2, #1 // palette
bl GrabSpriteCostumePointer
pop {r1}
b _returnBackPalHandling

_defaultBackPalHandling:
lsl r0, r0, #3
ldr r2, =0x08239fd4 // gTrainerBackPicPaletteTable
add r0, r2
ldr r0, [r0]

_returnBackPalHandling:
lsl r1, #0x18
ldr r2, =0x0803475E | 1
bx r2


// now battle transition mugshot.  this one will do both sprite and palette
.global costume_mugShotSpriteHook
costume_mugShotSpriteHook:
lsr r0, r4, #3 // move the id back down anosther 3

// this part still needs to be done
ldr r3, =0x08239a1c // gTrainerFrontPicPaletteTable
mov r8, r3
add r8, r4
ldr r3, =0x0823957c // gTrainerFrontPicTable
add r4, r3

cmp r0, #135
beq _costumeMugShotSpriteHandling
cmp r0, #136
beq _costumeMugShotSpriteHandling

// default handling - still need
mov r0, r8
mov r1, r7
ldr r2, =0x0800ec5c | 1 // LoadCompressedSpritePaletteOverrideBuffer
bl bx_r2
mov r0, r4
mov r1, r7
ldr r2, =0x0800ec00 | 1 // LoadCompressedSpriteSheetOverrideBuffer
bl bx_r2

b _costumeMugShotSpriteHandlingReturn

_costumeMugShotSpriteHandling:
// r0 is already id
mov r4, r0
mov r1, #0 // front sprite handling
mov r2, #1 // palette pointer
bl GrabSpriteCostumePointer
mov r1, r7
ldr r2, =0x0800ec5c | 1 // LoadCompressedSpritePaletteOverrideBuffer
bl bx_r2
mov r0, r4
mov r1, #0 // front sprite handling
mov r2, #0 // sprite pointer
bl GrabSpriteCostumePointer
mov r1, r7
ldr r2, =0x0800ec00 | 1 // LoadCompressedSpriteSheetOverrideBuffer
bl bx_r2


_costumeMugShotSpriteHandlingReturn:
ldr r1, =0x0808389A | 1
bx r1

bx_r2:
bx r2


.pool



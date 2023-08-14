@ the whole headbutt tree system
@ it implements jpan's behavior byte hack as well as the headbutt system in the space that the old routine took up.  when he said it was overly inefficient, he meant it!
@ compile this and then go to the offset 0x806D1F0 in the resulting .bin output.  copy everything there until the next block of zeros.  paste it to offset 0x6D1F0 in your rom.
@ there are various parameters you can play around with.  most of these are primarily the tables halfway through this.
@ i tried to comment it throughout!

@ now, in amap, there's the one field that is primarily used in wild encounter spots.  it's 2 when wild grass and 4 when surfing on water encounters.
@ because we won't be walking on the headbutt tree, we can use this field to our advantage.
@ cur_mapdata_block_get_field_at(s16 x, s16 y, u8 field) references a bunch of other routines, but eventually, it boils down to a bunch of preset fields or with the header info.
@ the first is 0x1FF, or the 9 least significant bits.  this is the behavior byte itself.
@ the second is 0x3E00, or the next 5 bits in terms of significance.  this allows for 2^5 (32) bits for use for our table.
@ note that the entry entered in this table should be multiplied by 2 because of the way that amap (incorrectly) displays the data.  this allows the code below to reference it properly.
@ screens are given in the post.

.text
.align 2
.thumb
.thumb_func

.include "event.inc"

@ this assembly routine is a modded version of jpan's behavior byte hack that decreases space required for the table while slightly increasing what's needed for the code
onpress_a_get_script_tile:
	lsl r1, r1, #0x18
	lsr r0, r1, #0x18
	cmp r0, #0x80
	blt _not_governed @ we do not care about entries less than h80
	sub r0, r0, #0x80
	lsl r0, r0, #0x2
	ldr r1, behavior_table_ref @ load the table pointer here
	add r0, r0, r1
	ldr r0, [r0] @ load the script pointer here
	b _return_loc
_not_governed:
	mov r0, #0
_return_loc:
	mov pc, lr

.align 2

behavior_table_ref:
	.word behavior_table

behavior_table: @ for the playerfacing behaviors
	.word 0
	.word 0x081A7606 @ bookshelf
	.word 0x081A760F @ market shelf
	.word 0x081A6955 @ pc
	.word 0
	.word 0x081A6C32 @ town map
	.word 0x081A764E @ tv
	.word 0x081A76E7 @ pokemon center
	.word 0x081A76DE @ pokemon mart
	.word 0x081A7657 @ cabinet
	.word 0x081A7660 @ cooking smells great!
	.word 0x081A7669 @ dresser
	.word 0x081A7672 @ snacks
	.word 0x081BBFD8 @ wireless
	.word 0x081BB8A7 @ not available
	.word 0x081A7702 @ questionnaire
	@ 0x90
	.word 0x081A7618 @ fridge
	.word 0x081A76F0 @ indigo plateau
	.word 0x081A76F9 @ indigo plateau 2
	.word 0x081A763C @ blueprint
	.word 0x081A767B @ pokemon pics
	.word 0x081A7684 @ complex machine.  better not touch it!
	.word 0x081A768D @ telephone
	.word 0x081A762A @ complex numbers
	.word 0x081A7696 @ ads
	.word 0x081A769F @ tasty food
	.word 0x081A76A8 @ trash can
	.word 0x081A76B1 @ cup
	.word 0
	.word 0
	.word 0x081A76CC @ lights
	.word 0x081A76D5 @ tools
	@ 0xA0
	.word 0x081A7633 @ random machine
	.word 0x081A7621 @ consoles
	.word 0x081A7645 @ robbery
	.word 0x081C549C @ timer
@ now, i personally added headbutt_script here, but it can go in any one of the zeros above.  just make sure that you note the entry correctly!
	.word 0x08CFBAC8 @ headbutt tree behavior byte (0xA4)
	.word EventScript_UseRockClimb @0xA5
	.word EventScript_UseWhirlpool @0xA6


.data

.global EventScript_UseRockClimb
EventScript_UseRockClimb:
	lockall
	checkpartymove 0x188
	compare_var_to_value 0x800D, 6
	goto_if_eq EventScript_CantRockClimb
	bufferpartymonnick 0, 0x800D
	setfieldeffectargument 0, 0x800D
	msgbox Text_WantToRockClimb, MSGBOX_YESNO
	compare_var_to_value 0x800D, NO
	goto_if_eq EventScript_EndRockClimb
	msgbox Text_MonUsedRockClimb, MSGBOX_DEFAULT
	closemessage
	dofieldeffect 70 @FLDEFF_USE_ROCK_CLIMB
	waitstate
	goto EventScript_EndRockClimb
	
EventScript_CantRockClimb:
	msgbox Text_CantRockClimb, MSGBOX_DEFAULT
	
EventScript_EndRockClimb:
	releaseall
	end

@Text_WantToRockClimb:
@    .string "The cliff is steep.\n"
@    .string "Would you like to use Rock Climb?$"
@    
@Text_MonUsedRockClimb:
@    .string "{STR_VAR_1} used Rock Climb!$"
@    
@Text_CantRockClimb:
@    .string "The cliff is steep.\n"
@    .string "A Pokémon may be able to climb it.$"

.global EventScript_UseWhirlpool
EventScript_UseWhirlpool:
	lockall
	checkpartymove 0xfa
	compare_var_to_value 0x800D, 6
	goto_if_eq EventScript_CantWhirlpool
	bufferpartymonnick 0, 0x800D
	setfieldeffectargument 0, 0x800D
	msgbox Text_WantToWhirlpool, MSGBOX_YESNO
	compare_var_to_value 0x800D, NO
	goto_if_eq EventScript_EndWhirlpool
	msgbox Text_MonUsedWhirlpool, MSGBOX_DEFAULT
	closemessage
	dofieldeffect 72 @FLDEFF_WHIRLPOOL_DISAPPEAR
	waitstate
	goto EventScript_EndWhirlpool
	
EventScript_CantWhirlpool:
	msgbox Text_CantWhirlpool, MSGBOX_DEFAULT
	
EventScript_EndWhirlpool:
	releaseall
	end

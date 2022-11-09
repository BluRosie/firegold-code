.thumb
.thumb_func
.align 2


.equ NUM_OF_EASY_MODE_SPREADS, 75
.equ NUM_OF_HARD_MODE_SPREADS, 530

.equ VAR_BATTLE_TOWER_TYPE, 0x43CB
.equ VAR_BATTLE_TOWER_TRAINER_CLASS, 0x43DE
.equ NUM_TRAINER_NAMES_PER_CLASS, 5

.equ BATTLE_TOWER_TYPE_NONE, 0
.equ BATTLE_TOWER_TYPE_SINGLE_EASY, 1
.equ BATTLE_TOWER_TYPE_SINGLE_HARD, 2
.equ BATTLE_TOWER_TYPE_DOUBLE_EASY, 3
.equ BATTLE_TOWER_TYPE_DOUBLE_HARD, 4
.equ BATTLE_TOWER_TYPE_MULTI_EASY, 5
.equ BATTLE_TOWER_TYPE_MULTI_HARD, 6

.equ BATTLE_TOWER_TYPE_EASY_BIT, 0x01




/* misc defines */

/* trainer classes */
.equ hexmaniac, 0xa
.equ pokemaniac, 0x3f
.equ cooltrainerm, 0x56
.equ cooltrainerf, 0x56
.equ expertm, 0x1c
.equ expertf, 0x1c
.equ gentleman, 0x16
.equ pkmnbreederm, 0x65
.equ pkmnbreederf, 0x65
.equ dragontamer, 0x21

/* trainer pics */
.equ hexmaniac_pic, 0xa
.equ pokemaniac_pic, 0x58
.equ cooltrainerm_pic, 0x6e
.equ cooltrainerf_pic, 0x6f
.equ expertm_pic, 0x22
.equ expertf_pic, 0x23
.equ gentleman_pic, 0x7b
.equ pkmnbreederm_pic, 0x3a
.equ pkmnbreederf_pic, 0x3b
.equ dragontamer_pic, 0x2d

/* trainer genders */
.equ male, 0x1
.equ female, 0x0

/* moves */
.equ none, 0x0
.equ pound, 0x1
.equ karatechop, 0x2
.equ doubleslap, 0x3
.equ cometpunch, 0x4
.equ megapunch, 0x5
.equ payday, 0x6
.equ firepunch, 0x7
.equ icepunch, 0x8
.equ thunderpunch, 0x9
.equ scratch, 0xa
.equ visegrip, 0xb
.equ guillotine, 0xc
.equ razorwind, 0xd
.equ swordsdance, 0xe
.equ cut, 0xf
.equ gust, 0x10
.equ wingattack, 0x11
.equ whirlwind, 0x12
.equ fly, 0x13
.equ bind, 0x14
.equ slam, 0x15
.equ vinewhip, 0x16
.equ stomp, 0x17
.equ doublekick, 0x18
.equ megakick, 0x19
.equ jumpkick, 0x1a
.equ rollingkick, 0x1b
.equ sandattack, 0x1c
.equ headbutt, 0x1d
.equ hornattack, 0x1e
.equ furyattack, 0x1f
.equ horndrill, 0x20
.equ tackle, 0x21
.equ bodyslam, 0x22
.equ wrap, 0x23
.equ takedown, 0x24
.equ thrash, 0x25
.equ doubleedge, 0x26
.equ tailwhip, 0x27
.equ poisonsting, 0x28
.equ twineedle, 0x29
.equ pinmissile, 0x2a
.equ leer, 0x2b
.equ bite, 0x2c
.equ growl, 0x2d
.equ roar, 0x2e
.equ sing, 0x2f
.equ supersonic, 0x30
.equ sonicboom, 0x31
.equ disable, 0x32
.equ acid, 0x33
.equ ember, 0x34
.equ flamethrower, 0x35
.equ mist, 0x36
.equ watergun, 0x37
.equ hydropump, 0x38
.equ surf, 0x39
.equ icebeam, 0x3a
.equ blizzard, 0x3b
.equ psybeam, 0x3c
.equ bubblebeam, 0x3d
.equ aurorabeam, 0x3e
.equ hyperbeam, 0x3f
.equ peck, 0x40
.equ drillpeck, 0x41
.equ submission, 0x42
.equ lowkick, 0x43
.equ counter, 0x44
.equ seismictoss, 0x45
.equ strength, 0x46
.equ absorb, 0x47
.equ megadrain, 0x48
.equ leechseed, 0x49
.equ growth, 0x4a
.equ razorleaf, 0x4b
.equ solarbeam, 0x4c
.equ poisonpowder, 0x4d
.equ stunspore, 0x4e
.equ sleeppowder, 0x4f
.equ petaldance, 0x50
.equ stringshot, 0x51
.equ dragonrage, 0x52
.equ firespin, 0x53
.equ thundershock, 0x54
.equ thunderbolt, 0x55
.equ thunderwave, 0x56
.equ thunder, 0x57
.equ rockthrow, 0x58
.equ earthquake, 0x59
.equ fissure, 0x5a
.equ dig, 0x5b
.equ toxic, 0x5c
.equ confusion, 0x5d
.equ psychic, 0x5e
.equ hypnosis, 0x5f
.equ meditate, 0x60
.equ agility, 0x61
.equ quickattack, 0x62
.equ rage, 0x63
.equ teleport, 0x64
.equ nightshade, 0x65
.equ mimic, 0x66
.equ screech, 0x67
.equ doubleteam, 0x68
.equ recover, 0x69
.equ harden, 0x6a
.equ minimize, 0x6b
.equ smokescreen, 0x6c
.equ confuseray, 0x6d
.equ withdraw, 0x6e
.equ defensecurl, 0x6f
.equ barrier, 0x70
.equ lightscreen, 0x71
.equ haze, 0x72
.equ reflect, 0x73
.equ focusenergy, 0x74
.equ bide, 0x75
.equ metronome, 0x76
.equ mirrormove, 0x77
.equ selfdestruct, 0x78
.equ eggbomb, 0x79
.equ lick, 0x7a
.equ smog, 0x7b
.equ sludge, 0x7c
.equ boneclub, 0x7d
.equ fireblast, 0x7e
.equ waterfall, 0x7f
.equ clamp, 0x80
.equ swift, 0x81
.equ skullbash, 0x82
.equ spikecannon, 0x83
.equ constrict, 0x84
.equ amnesia, 0x85
.equ kinesis, 0x86
.equ softboiled, 0x87
.equ highjumpkick, 0x88
.equ glare, 0x89
.equ dreameater, 0x8a
.equ poisongas, 0x8b
.equ barrage, 0x8c
.equ leechlife, 0x8d
.equ lovelykiss, 0x8e
.equ skyattack, 0x8f
.equ transform, 0x90
.equ bubble, 0x91
.equ dizzypunch, 0x92
.equ spore, 0x93
.equ flash, 0x94
.equ psywave, 0x95
.equ splash, 0x96
.equ acidarmor, 0x97
.equ crabhammer, 0x98
.equ explosion, 0x99
.equ furyswipes, 0x9a
.equ bonemerang, 0x9b
.equ rest, 0x9c
.equ rockslide, 0x9d
.equ hyperfang, 0x9e
.equ sharpen, 0x9f
.equ conversion, 0xa0
.equ triattack, 0xa1
.equ superfang, 0xa2
.equ slash, 0xa3
.equ substitute, 0xa4
.equ struggle, 0xa5
.equ sketch, 0xa6
.equ triplekick, 0xa7
.equ thief, 0xa8
.equ spiderweb, 0xa9
.equ mindreader, 0xaa
.equ nightmare, 0xab
.equ flamewheel, 0xac
.equ snore, 0xad
.equ curse, 0xae
.equ flail, 0xaf
.equ conversion2, 0xb0
.equ aeroblast, 0xb1
.equ cottonspore, 0xb2
.equ reversal, 0xb3
.equ spite, 0xb4
.equ powdersnow, 0xb5
.equ protect, 0xb6
.equ machpunch, 0xb7
.equ scaryface, 0xb8
.equ feintattack, 0xb9
.equ sweetkiss, 0xba
.equ bellydrum, 0xbb
.equ sludgebomb, 0xbc
.equ mudslap, 0xbd
.equ octazooka, 0xbe
.equ spikes, 0xbf
.equ zapcannon, 0xc0
.equ foresight, 0xc1
.equ destinybond, 0xc2
.equ perishsong, 0xc3
.equ icywind, 0xc4
.equ detect, 0xc5
.equ bonerush, 0xc6
.equ lockon, 0xc7
.equ outrage, 0xc8
.equ sandstorm, 0xc9
.equ gigadrain, 0xca
.equ endure, 0xcb
.equ charm, 0xcc
.equ rollout, 0xcd
.equ falseswipe, 0xce
.equ swagger, 0xcf
.equ milkdrink, 0xd0
.equ spark, 0xd1
.equ furycutter, 0xd2
.equ steelwing, 0xd3
.equ meanlook, 0xd4
.equ attract, 0xd5
.equ sleeptalk, 0xd6
.equ healbell, 0xd7
.equ return, 0xd8
.equ present, 0xd9
.equ frustration, 0xda
.equ safeguard, 0xdb
.equ painsplit, 0xdc
.equ sacredfire, 0xdd
.equ magnitude, 0xde
.equ dynamicpunch, 0xdf
.equ megahorn, 0xe0
.equ dragonbreath, 0xe1
.equ batonpass, 0xe2
.equ encore, 0xe3
.equ pursuit, 0xe4
.equ rapidspin, 0xe5
.equ sweetscent, 0xe6
.equ irontail, 0xe7
.equ metalclaw, 0xe8
.equ vitalthrow, 0xe9
.equ morningsun, 0xea
.equ synthesis, 0xeb
.equ moonlight, 0xec
.equ hiddenpower, 0xed
.equ crosschop, 0xee
.equ twister, 0xef
.equ raindance, 0xf0
.equ sunnyday, 0xf1
.equ crunch, 0xf2
.equ mirrorcoat, 0xf3
.equ psychup, 0xf4
.equ extremespeed, 0xf5
.equ ancientpower, 0xf6
.equ shadowball, 0xf7
.equ futuresight, 0xf8
.equ rocksmash, 0xf9
.equ whirlpool, 0xfa
.equ beatup, 0xfb
.equ fakeout, 0xfc
.equ uproar, 0xfd
.equ stockpile, 0xfe
.equ spitup, 0xff
.equ swallow, 0x100
.equ heatwave, 0x101
.equ hail, 0x102
.equ torment, 0x103
.equ flatter, 0x104
.equ willowisp, 0x105
.equ memento, 0x106
.equ facade, 0x107
.equ focuspunch, 0x108
.equ smellingsalts, 0x109
.equ followme, 0x10a
.equ naturepower, 0x10b
.equ charge, 0x10c
.equ taunt, 0x10d
.equ helpinghand, 0x10e
.equ trick, 0x10f
.equ roleplay, 0x110
.equ wish, 0x111
.equ assist, 0x112
.equ ingrain, 0x113
.equ superpower, 0x114
.equ magiccoat, 0x115
.equ recycle, 0x116
.equ revenge, 0x117
.equ brickbreak, 0x118
.equ yawn, 0x119
.equ knockoff, 0x11a
.equ endeavor, 0x11b
.equ eruption, 0x11c
.equ skillswap, 0x11d
.equ imprison, 0x11e
.equ refresh, 0x11f
.equ grudge, 0x120
.equ snatch, 0x121
.equ secretpower, 0x122
.equ dive, 0x123
.equ armthrust, 0x124
.equ camouflage, 0x125
.equ tailglow, 0x126
.equ lusterpurge, 0x127
.equ mistball, 0x128
.equ featherdance, 0x129
.equ teeterdance, 0x12a
.equ blazekick, 0x12b
.equ mudsport, 0x12c
.equ iceball, 0x12d
.equ needlearm, 0x12e
.equ slackoff, 0x12f
.equ hypervoice, 0x130
.equ poisonfang, 0x131
.equ crushclaw, 0x132
.equ blastburn, 0x133
.equ hydrocannon, 0x134
.equ meteormash, 0x135
.equ astonish, 0x136
.equ weatherball, 0x137
.equ aromatherapy, 0x138
.equ faketears, 0x139
.equ aircutter, 0x13a
.equ overheat, 0x13b
.equ odorsleuth, 0x13c
.equ rocktomb, 0x13d
.equ silverwind, 0x13e
.equ metalsound, 0x13f
.equ grasswhistle, 0x140
.equ tickle, 0x141
.equ cosmicpower, 0x142
.equ waterspout, 0x143
.equ signalbeam, 0x144
.equ shadowpunch, 0x145
.equ extrasensory, 0x146
.equ skyuppercut, 0x147
.equ sandtomb, 0x148
.equ sheercold, 0x149
.equ muddywater, 0x14a
.equ bulletseed, 0x14b
.equ aerialace, 0x14c
.equ iciclespear, 0x14d
.equ irondefense, 0x14e
.equ block, 0x14f
.equ howl, 0x150
.equ dragonclaw, 0x151
.equ frenzyplant, 0x152
.equ bulkup, 0x153
.equ bounce, 0x154
.equ mudshot, 0x155
.equ poisontail, 0x156
.equ covet, 0x157
.equ volttackle, 0x158
.equ magicalleaf, 0x159
.equ watersport, 0x15a
.equ calmmind, 0x15b
.equ leafblade, 0x15c
.equ dragondance, 0x15d
.equ rockblast, 0x15e
.equ shockwave, 0x15f
.equ waterpulse, 0x160
.equ doomdesire, 0x161
.equ psychoboost, 0x162
.equ psyshieldbash, 0x163
.equ airslash, 0x164
.equ aquajet, 0x165
.equ aquatail, 0x166
.equ aurasphere, 0x167
.equ avalanche, 0x168
.equ bravebird, 0x169
.equ bugbuzz, 0x16a
.equ bulletpunch, 0x16b
.equ chargebeam, 0x16c
.equ closecombat, 0x16d
.equ crosspoison, 0x16e
.equ darkpulse, 0x16f
.equ discharge, 0x170
.equ dracometeor, 0x171
.equ dragonpulse, 0x172
.equ drainpunch, 0x173
.equ earthpower, 0x174
.equ energyball, 0x175
.equ focusblast, 0x176
.equ forcepalm, 0x177
.equ gigaimpact, 0x178
.equ grassknot, 0x179
.equ gunkshot, 0x17a
.equ hammerarm, 0x17b
.equ headsmash, 0x17c
.equ iceshard, 0x17d
.equ ironhead, 0x17e
.equ lavaplume, 0x17f
.equ mgnetbomb, 0x180
.equ mudbomb, 0x181
.equ nastyplot, 0x182
.equ nightslash, 0x183
.equ ominouswind, 0x184
.equ powergem, 0x185
.equ powerwhip, 0x186
.equ psychocut, 0x187
.equ rockclimb, 0x188
.equ rockpolish, 0x189
.equ rockwrecker, 0x18a
.equ roost, 0x18b
.equ seedbomb, 0x18c
.equ shadowclaw, 0x18d
.equ shadowsneak, 0x18e
.equ vacuumwave, 0x18f
.equ xscissor, 0x190
.equ zenheadbutt, 0x191
.equ move_x192, 0x192
.equ drillrun, 0x193
.equ bulldoze, 0x194
.equ electroweb, 0x195
.equ flamecharge, 0x196
.equ frostbreath, 0x197
.equ heartstamp, 0x198
.equ honeclaws, 0x199
.equ hornleech, 0x19a
.equ coil, 0x19b
.equ hurricane, 0x19c
.equ iciclecrash, 0x19d
.equ workup, 0x19e
.equ quiverdance, 0x19f
.equ leaftornado, 0x1a0
.equ lowsweep, 0x1a1
.equ snarl, 0x1a2
.equ strugglebug, 0x1a3
.equ steamroller, 0x1a4
.equ stormthrow, 0x1a5
.equ venoshock, 0x1a6
.equ wildcharge, 0x1a7
.equ poisonjab, 0x1a8
.equ acidspray, 0x1a9
.equ move_x1aa, 0x1aa
.equ clearsmog, 0x1ab
.equ leafstorm, 0x1ac
.equ stoneedge, 0x1ad
.equ payback, 0x1ae
.equ firefang, 0x1af
.equ icefang, 0x1b0
.equ thunderfang, 0x1b1
.equ flareblitz, 0x1b2
.equ inferno, 0x1b3
.equ hex, 0x1b4
.equ move_x1b5, 0x1b5
.equ doublehit, 0x1b6
.equ cottonguard, 0x1b7
.equ acrobatics, 0x1b8
.equ move_x1b9, 0x1b9
.equ uturn, 0x1ba
.equ voltswitch, 0x1bb
.equ dragontail, 0x1bc
.equ circlethrow, 0x1bd
.equ mirrorshot, 0x1be
.equ woodhammer, 0x1bf
.equ healpulse, 0x1c0
.equ flashcannon, 0x1c1
.equ bugbite, 0x1c2
.equ pluck, 0x1c3
.equ shellsmash, 0x1c4
.equ ragepowder, 0x1c5
.equ wakeupslap, 0x1c6
.equ razorshell, 0x1c7
.equ copycat, 0x1c8
.equ foulplay, 0x1c9
.equ suckerpunch, 0x1ca
.equ scald, 0x1cb
.equ brine, 0x1cc
.equ fairywind, 0x1cd
.equ babydolleyes, 0x1ce
.equ playrough, 0x1cf
.equ moonblast, 0x1d0
.equ drainkiss, 0x1d1
.equ dazzlinggleam, 0x1d2
.equ disarmvoice, 0x1d3
.equ stealthrock, 0x1d4
.equ toxicspikes, 0x1d5
.equ poweruppunch, 0x1d6
.equ liquidation, 0x1d7
.equ mysticalfire, 0x1d8
.equ direclaw, 0x1d9
.equ trickroom, 0x1da
.equ tailwind, 0x1db
.equ gastroacid, 0x1dc
.equ infernalparade, 0x1dd
.equ flowerguard, 0x1de
.equ ragingfury, 0x1df
.equ chloroblast, 0x1e0
.equ stickyweb, 0x1e1
.equ storedpower, 0x1e2
.equ acupressure, 0x1e3
.equ punishment, 0x1e4
.equ assurance, 0x1e5
.equ petalblizzard, 0x1e6
.equ headlongrush, 0x1e7
.equ nuzzle, 0x1e8
.equ stoneaxe, 0x1e9
.equ hihorsepower, 0x1ea
.equ bodypress, 0x1eb
.equ dragonrush, 0x1ec
.equ meteorassault, 0x1ed
.equ shadowbone, 0x1ee
.equ dragonhammer, 0x1ef
.equ strangesteam, 0x1f0
.equ ironbash, 0x1f1
.equ shellsidearm, 0x1f2
.equ eeriespell, 0x1f3
.equ eerieimpulse, 0x1f4
.equ freezeglare, 0x1f5
.equ thunderkick, 0x1f6
.equ fierywrath, 0x1f7
.equ auroraveil, 0x1f8
.equ toxicthread, 0x1f9
.equ barbbarrage, 0x1fa
.equ freezedry, 0x1fb
.equ smartstrike, 0x1fc
.equ psyshock, 0x1fd
.equ psystrike, 0x1fe

/* letters for names */
.equ A, 0xBB
.equ B, 0xBC
.equ C, 0xBD
.equ D, 0xBE
.equ E, 0xBF
.equ F, 0xC0
.equ G, 0xC1
.equ H, 0xC2
.equ I, 0xC3
.equ J, 0xC4
.equ K, 0xC5
.equ L, 0xC6
.equ M, 0xC7
.equ N, 0xC8
.equ O, 0xC9
.equ P, 0xCA
.equ Q, 0xCB
.equ R, 0xCC
.equ S, 0xCD
.equ T, 0xCE
.equ U, 0xCF
.equ V, 0xD0
.equ W, 0xD1
.equ X, 0xD2
.equ Y, 0xD3
.equ Z, 0xD4

.equ a, 0xD5
.equ b, 0xD6
.equ c, 0xD7
.equ d, 0xD8
.equ e, 0xD9
.equ f, 0xDA
.equ g, 0xDB
.equ h, 0xDC
.equ i, 0xDD
.equ j, 0xDE
.equ k, 0xDF
.equ l, 0xE0
.equ m, 0xE1
.equ n, 0xE2
.equ o, 0xE3
.equ p, 0xE4
.equ q, 0xE5
.equ r, 0xE6
.equ s, 0xE7
.equ t, 0xE8
.equ u, 0xE9
.equ v, 0xEA
.equ w, 0xEB
.equ x, 0xEC
.equ y, 0xED
.equ z, 0xEE

.equ Space, 0x0
.equ Exclamation, 0xAB
.equ Question, 0xAC
.equ Period, 0xAD
.equ Apostrophe, 0xB4
.equ Comma, 0xB8
.equ Colon, 0xF0
.equ NewLine, 0xFE
.equ Button, 0xFB
.equ Done, 0xFF

.equ Zero, 0xA1
.equ One, 0xA2
.equ Two, 0xA3
.equ Three, 0xA4
.equ Four, 0xA5
.equ Five, 0xA6
.equ Six, 0xA7
.equ Seven, 0xA8
.equ Eight, 0xA9
.equ Nine, 0xAA

/* species */
.equ none, 0x0 
.equ bulbasaur, 0x1 
.equ ivysaur, 0x2 
.equ venusaur, 0x3 
.equ charmander, 0x4 
.equ charmeleon, 0x5 
.equ charizard, 0x6 
.equ squirtle, 0x7 
.equ wartortle, 0x8 
.equ blastoise, 0x9 
.equ caterpie, 0xa 
.equ metapod, 0xb 
.equ butterfree, 0xc 
.equ weedle, 0xd 
.equ kakuna, 0xe 
.equ beedrill, 0xf 
.equ pidgey, 0x10 
.equ pidgeotto, 0x11 
.equ pidgeot, 0x12 
.equ rattata, 0x13 
.equ raticate, 0x14 
.equ spearow, 0x15 
.equ fearow, 0x16 
.equ ekans, 0x17 
.equ arbok, 0x18 
.equ pikachu, 0x19 
.equ raichu, 0x1a 
.equ sandshrew, 0x1b 
.equ sandslash, 0x1c 
.equ nidoranf, 0x1d 
.equ nidorina, 0x1e 
.equ nidoqueen, 0x1f 
.equ nidoranm, 0x20 
.equ nidorino, 0x21 
.equ nidoking, 0x22 
.equ clefairy, 0x23 
.equ clefable, 0x24 
.equ vulpix, 0x25 
.equ ninetales, 0x26 
.equ jigglypuff, 0x27 
.equ wigglytuff, 0x28 
.equ zubat, 0x29 
.equ golbat, 0x2a 
.equ oddish, 0x2b 
.equ gloom, 0x2c 
.equ vileplume, 0x2d 
.equ paras, 0x2e 
.equ parasect, 0x2f 
.equ venonat, 0x30 
.equ venomoth, 0x31 
.equ diglett, 0x32 
.equ dugtrio, 0x33 
.equ meowth, 0x34 
.equ persian, 0x35 
.equ psyduck, 0x36 
.equ golduck, 0x37 
.equ mankey, 0x38 
.equ primeape, 0x39 
.equ growlithe, 0x3a 
.equ arcanine, 0x3b 
.equ poliwag, 0x3c 
.equ poliwhirl, 0x3d 
.equ poliwrath, 0x3e 
.equ abra, 0x3f 
.equ kadabra, 0x40 
.equ alakazam, 0x41 
.equ machop, 0x42 
.equ machoke, 0x43 
.equ machamp, 0x44 
.equ bellsprout, 0x45 
.equ weepinbell, 0x46 
.equ victreebel, 0x47 
.equ tentacool, 0x48 
.equ tentacruel, 0x49 
.equ geodude, 0x4a 
.equ graveler, 0x4b 
.equ golem, 0x4c 
.equ ponyta, 0x4d 
.equ rapidash, 0x4e 
.equ slowpoke, 0x4f 
.equ slowbro, 0x50 
.equ magnemite, 0x51 
.equ magneton, 0x52 
.equ farfetchd, 0x53 
.equ doduo, 0x54 
.equ dodrio, 0x55 
.equ seel, 0x56 
.equ dewgong, 0x57 
.equ grimer, 0x58 
.equ muk, 0x59 
.equ shellder, 0x5a 
.equ cloyster, 0x5b 
.equ gastly, 0x5c 
.equ haunter, 0x5d 
.equ gengar, 0x5e 
.equ onix, 0x5f 
.equ drowzee, 0x60 
.equ hypno, 0x61 
.equ krabby, 0x62 
.equ kingler, 0x63 
.equ voltorb, 0x64 
.equ electrode, 0x65 
.equ exeggcute, 0x66 
.equ exeggutor, 0x67 
.equ cubone, 0x68 
.equ marowak, 0x69 
.equ hitmonlee, 0x6a 
.equ hitmonchan, 0x6b 
.equ lickitung, 0x6c 
.equ koffing, 0x6d 
.equ weezing, 0x6e 
.equ rhyhorn, 0x6f 
.equ rhydon, 0x70 
.equ chansey, 0x71 
.equ tangela, 0x72 
.equ kangaskhan, 0x73 
.equ horsea, 0x74 
.equ seadra, 0x75 
.equ goldeen, 0x76 
.equ seaking, 0x77 
.equ staryu, 0x78 
.equ starmie, 0x79 
.equ mrmime, 0x7a 
.equ scyther, 0x7b 
.equ jynx, 0x7c 
.equ electabuzz, 0x7d 
.equ magmar, 0x7e 
.equ pinsir, 0x7f 
.equ tauros, 0x80 
.equ magikarp, 0x81 
.equ gyarados, 0x82 
.equ lapras, 0x83 
.equ ditto, 0x84 
.equ eevee, 0x85 
.equ vaporeon, 0x86 
.equ jolteon, 0x87 
.equ flareon, 0x88 
.equ porygon, 0x89 
.equ omanyte, 0x8a 
.equ omastar, 0x8b 
.equ kabuto, 0x8c 
.equ kabutops, 0x8d 
.equ aerodactyl, 0x8e 
.equ snorlax, 0x8f 
.equ articuno, 0x90 
.equ zapdos, 0x91 
.equ moltres, 0x92 
.equ dratini, 0x93 
.equ dragonair, 0x94 
.equ dragonite, 0x95 
.equ mewtwo, 0x96 
.equ mew, 0x97 
.equ chikorita, 0x98 
.equ bayleef, 0x99 
.equ meganium, 0x9a 
.equ cyndaquil, 0x9b 
.equ quilava, 0x9c 
.equ typhlosion, 0x9d 
.equ totodile, 0x9e 
.equ croconaw, 0x9f 
.equ feraligatr, 0xa0 
.equ sentret, 0xa1 
.equ furret, 0xa2 
.equ hoothoot, 0xa3 
.equ noctowl, 0xa4 
.equ ledyba, 0xa5 
.equ ledian, 0xa6 
.equ spinarak, 0xa7 
.equ ariados, 0xa8 
.equ crobat, 0xa9 
.equ chinchou, 0xaa 
.equ lanturn, 0xab 
.equ pichu, 0xac 
.equ cleffa, 0xad 
.equ igglybuff, 0xae 
.equ togepi, 0xaf 
.equ togetic, 0xb0 
.equ natu, 0xb1 
.equ xatu, 0xb2 
.equ mareep, 0xb3 
.equ flaaffy, 0xb4 
.equ ampharos, 0xb5 
.equ bellossom, 0xb6 
.equ marill, 0xb7 
.equ azumarill, 0xb8 
.equ sudowoodo, 0xb9 
.equ politoed, 0xba 
.equ hoppip, 0xbb 
.equ skiploom, 0xbc 
.equ jumpluff, 0xbd 
.equ aipom, 0xbe 
.equ sunkern, 0xbf 
.equ sunflora, 0xc0 
.equ yanma, 0xc1 
.equ wooper, 0xc2 
.equ quagsire, 0xc3 
.equ espeon, 0xc4 
.equ umbreon, 0xc5 
.equ murkrow, 0xc6 
.equ slowking, 0xc7 
.equ misdreavus, 0xc8 
.equ unown, 0xc9 
.equ wobbuffet, 0xca 
.equ girafarig, 0xcb 
.equ pineco, 0xcc 
.equ forretress, 0xcd 
.equ dunsparce, 0xce 
.equ gligar, 0xcf 
.equ steelix, 0xd0 
.equ snubbull, 0xd1 
.equ granbull, 0xd2 
.equ qwilfish, 0xd3 
.equ scizor, 0xd4 
.equ shuckle, 0xd5 
.equ heracross, 0xd6 
.equ sneasel, 0xd7 
.equ teddiursa, 0xd8 
.equ ursaring, 0xd9 
.equ slugma, 0xda 
.equ magcargo, 0xdb 
.equ swinub, 0xdc 
.equ piloswine, 0xdd 
.equ corsola, 0xde 
.equ remoraid, 0xdf 
.equ octillery, 0xe0 
.equ delibird, 0xe1 
.equ mantine, 0xe2 
.equ skarmory, 0xe3 
.equ houndour, 0xe4 
.equ houndoom, 0xe5 
.equ kingdra, 0xe6 
.equ phanpy, 0xe7 
.equ donphan, 0xe8 
.equ porygon2, 0xe9 
.equ stantler, 0xea 
.equ smeargle, 0xeb 
.equ tyrogue, 0xec 
.equ hitmontop, 0xed 
.equ smoochum, 0xee 
.equ elekid, 0xef 
.equ magby, 0xf0 
.equ miltank, 0xf1 
.equ blissey, 0xf2 
.equ raikou, 0xf3 
.equ entei, 0xf4 
.equ suicune, 0xf5 
.equ larvitar, 0xf6 
.equ pupitar, 0xf7 
.equ tyranitar, 0xf8 
.equ lugia, 0xf9 
.equ hooh, 0xfa 
.equ celebi, 0xfb 
.equ rattattaalolan, 0xfc
.equ raticatealolan, 0xfd
.equ raichualolan, 0xfe
.equ sandshrewalolan, 0xff
.equ sandslashalolan, 0x100
.equ vulpixalolan, 0x101
.equ ninetalesalolan, 0x102
.equ diglettalolan, 0x103
.equ dugtrioalolan, 0x104
.equ meowthalolan, 0x105
.equ persianalolan, 0x106
.equ geodudealolan, 0x107
.equ graveleralolan, 0x108
.equ golemalolan, 0x109
.equ grimeralolan, 0x10a
.equ mukalolan, 0x10b
.equ exeggutoralolan, 0x10c
.equ marowakalolan, 0x10d
.equ meowthgalarian, 0x10e
.equ ponytagalarian, 0x10f
.equ rapidashgalarian, 0x110
.equ slowpokegalarian, 0x111
.equ slowbrogalarian, 0x112
.equ slowkinggalarian, 0x113
.equ farfetchdgalarian, 0x114
.equ qwilfishhisuian, 0x11e
.equ overqwil, 0x11f
.equ sneaselhisuian, 0x120
.equ sneasler, 0x121
.equ typhlosionhisuian, 0x122
.equ growlithehisuian, 0x123
.equ arcaninehisuian, 0x124
.equ voltorbhisuian, 0x125
.equ electrodehisuian, 0x126
.equ ambipom, 0x13b
.equ mismagius, 0x13c
.equ honchkrow, 0x13d
.equ ursaluna, 0x141
.equ perrserker, 0x145
.equ sirfetchd, 0x146
.equ weezinggalarian, 0x147
.equ mrrime, 0x149
.equ weavile, 0x15c
.equ gliscor, 0x15d
.equ leafeon, 0x160
.equ glaceon, 0x161
.equ sylveon, 0x162
.equ rhyperior, 0x16c
.equ electivire, 0x16d
.equ magmortar, 0x16e
.equ porygonz, 0x16f
.equ togekiss, 0x172
.equ magnezone, 0x173
.equ lickilicky, 0x174
.equ tangrowth, 0x175
.equ yanmega, 0x176
.equ mamoswine, 0x177
.equ wyrdeer, 0x17b
.equ kleavor, 0x17c
.equ articunogalarian, 0x17d
.equ zapdosgalarian, 0x17e
.equ moltresgalarian, 0x17f
.equ cursola, 0x180

/* items */
.equ masterball, 0x1
.equ ultraball, 0x2
.equ greatball, 0x3
.equ pokeball, 0x4
.equ safariball, 0x5
.equ lureball, 0x6
.equ heavyball, 0x7
.equ loveball, 0x8
.equ friendball, 0x9
.equ levelball, 0xa
.equ moonball, 0xb
.equ fastball, 0xc
.equ potion, 0xd
.equ antidote, 0xe
.equ burnheal, 0xf
.equ iceheal, 0x10
.equ awakening, 0x11
.equ parlyzheal, 0x12
.equ fullrestore, 0x13
.equ maxpotion, 0x14
.equ hyperpotion, 0x15
.equ superpotion, 0x16
.equ fullheal, 0x17
.equ revive, 0x18
.equ maxrevive, 0x19
.equ freshwater, 0x1a
.equ sodapop, 0x1b
.equ lemonade, 0x1c
.equ moomoomilk, 0x1d
.equ energypowder, 0x1e
.equ energyroot, 0x1f
.equ healpowder, 0x20
.equ revivalherb, 0x21
.equ ether, 0x22
.equ maxether, 0x23
.equ elixir, 0x24
.equ maxelixir, 0x25
.equ lavacookie, 0x26
.equ blueflute, 0x27
.equ yellowflute, 0x28
.equ redflute, 0x29
.equ blackflute, 0x2a
.equ whiteflute, 0x2b
.equ berryjuice, 0x2c
.equ sacredash, 0x2d
.equ ragecandybar, 0x2e
.equ pewtercrunchy, 0x2f
.equ redshard, 0x30
.equ blueshard, 0x31
.equ yellowshard, 0x32
.equ greenshard, 0x33
.equ peatblock, 0x34
.equ blackaugurite, 0x35
.equ galaricacuff, 0x36
.equ galaricawreath, 0x37
.equ dragonscale, 0x38
.equ upgrade, 0x39
.equ dubiousdisc, 0x3a
.equ ovalstone, 0x3b
.equ protector, 0x3c
.equ electirizer, 0x3d
.equ magmarizer, 0x3e
.equ hpup, 0x3f
.equ protein, 0x40
.equ iron, 0x41
.equ carbos, 0x42
.equ calcium, 0x43
.equ rarecandy, 0x44
.equ ppup, 0x45
.equ zinc, 0x46
.equ ppmax, 0x47
.equ linkingcord, 0x48
.equ guardspec, 0x49
.equ direhit, 0x4a
.equ xattack, 0x4b
.equ xdefend, 0x4c
.equ xspeed, 0x4d
.equ xaccuracy, 0x4e
.equ xspecial, 0x4f
.equ pokedoll, 0x50
.equ razorclaw, 0x51
.equ razorfang, 0x52
.equ superrepel, 0x53
.equ maxrepel, 0x54
.equ escaperope, 0x55
.equ repel, 0x56
.equ metalcoat, 0x56
.equ kingsrock, 0x56
.equ sunstone, 0x5d
.equ moonstone, 0x5e
.equ firestone, 0x5f
.equ thunderstone, 0x60
.equ waterstone, 0x61
.equ leafstone, 0x62
.equ shinystone, 0x62
.equ duskstone, 0x62
.equ dawnstone, 0x62
.equ icestone, 0x62
.equ tinymushroom, 0x67
.equ bigmushroom, 0x68
.equ bignugget, 0x69
.equ pearl, 0x6a
.equ bigpearl, 0x6b
.equ stardust, 0x6c
.equ starpiece, 0x6d
.equ nugget, 0x6e
.equ heartscale, 0x6f
.equ orangemail, 0x79
.equ harbormail, 0x7a
.equ glittermail, 0x7b
.equ mechmail, 0x7c
.equ woodmail, 0x7d
.equ wavemail, 0x7e
.equ beadmail, 0x7f
.equ shadowmail, 0x80
.equ tropicmail, 0x81
.equ dreammail, 0x82
.equ fabmail, 0x83
.equ retromail, 0x84
.equ cheriberry, 0x85
.equ chestoberry, 0x86
.equ pechaberry, 0x87
.equ rawstberry, 0x88
.equ aspearberry, 0x89
.equ leppaberry, 0x8a
.equ oranberry, 0x8b
.equ persimberry, 0x8c
.equ lumberry, 0x8d
.equ sitrusberry, 0x8e
.equ figyberry, 0x8f
.equ wikiberry, 0x90
.equ magoberry, 0x91
.equ aguavberry, 0x92
.equ iapapaberry, 0x93
.equ chilanberry, 0x94
.equ occaberry, 0x95
.equ passhoberry, 0x96
.equ wacanberry, 0x97
.equ rindoberry, 0x98
.equ yacheberry, 0x99
.equ chopleberry, 0x9a
.equ kebiaberry, 0x9b
.equ shucaberry, 0x9c
.equ cobaberry, 0x9d
.equ payapaberry, 0x9e
.equ tangaberry, 0x9f
.equ chartiberry, 0xa0
.equ kasibberry, 0xa1
.equ habanberry, 0xa2
.equ colburberry, 0xa3
.equ babiriberry, 0xa4
.equ roseliberry, 0xa5
.equ liechiberry, 0xa8
.equ ganlonberry, 0xa9
.equ salacberry, 0xaa
.equ petayaberry, 0xab
.equ apicotberry, 0xac
.equ lansatberry, 0xad
.equ starfberry, 0xae
.equ enigmaberry, 0xaf
.equ flameorb, 0xb0
.equ toxicorb, 0xb1
.equ weaknesspolicy, 0xb2
.equ brightpowder, 0xb3
.equ whiteherb, 0xb4
.equ machobrace, 0xb5
.equ expshare, 0xb6
.equ quickclaw, 0xb7
.equ soothebell, 0xb8
.equ mentalherb, 0xb9
.equ choiceband, 0xba
.equ silverpowder, 0xbc
.equ amuletcoin, 0xbd
.equ cleansetag, 0xbe
.equ souldew, 0xbf
.equ deepseatooth, 0xc0
.equ deepseascale, 0xc1
.equ smokeball, 0xc2
.equ everstone, 0xc3
.equ focusband, 0xc4
.equ luckyegg, 0xc5
.equ scopelens, 0xc6
.equ leftovers, 0xc8
.equ lightball, 0xca
.equ softsand, 0xcb
.equ hardstone, 0xcc
.equ miracleseed, 0xcd
.equ blackglasses, 0xce
.equ blackbelt, 0xcf
.equ magnet, 0xd0
.equ mysticwater, 0xd1
.equ sharpbeak, 0xd2
.equ poisonbarb, 0xd3
.equ nevermeltice, 0xd4
.equ spelltag, 0xd5
.equ twistedspoon, 0xd6
.equ charcoal, 0xd7
.equ dragonfang, 0xd8
.equ silkscarf, 0xd9
.equ shellbell, 0xdb
.equ seaincense, 0xdc
.equ laxincense, 0xdd
.equ luckypunch, 0xde
.equ metalpowder, 0xdf
.equ thickclub, 0xe0
.equ stick, 0xe1
.equ choicespecs, 0xe2
.equ choicescarf, 0xe3
.equ lifeorb, 0xe4
.equ rockyhelmet, 0xe5
.equ blacksludge, 0xe6
.equ assaultvest, 0xe7
.equ eviolite, 0xe8
.equ expertbelt, 0xe9
.equ widelens, 0xea
.equ berserkgene, 0xeb
.equ muscleband, 0xec
.equ wiseglasses, 0xed
.equ focussash, 0xee
.equ heatrock, 0xef
.equ damprock, 0xf0
.equ smoothrock, 0xf1
.equ icyrock, 0xf2
.equ lightclay, 0xf3
.equ laggingtail, 0xf4
.equ powerherb, 0xf5
.equ powerweight, 0xf6
.equ powerbracer, 0xf7
.equ powerbelt, 0xf8
.equ poweranklet, 0xf9
.equ powerlens, 0xfa
.equ powerband, 0xfb
.equ slowpoketail, 0xfc
.equ blueapricorn, 0xfd
.equ blackapricorn, 0xfe
.equ pinkapricorn, 0xff
.equ greenapricorn, 0x100
.equ redapricorn, 0x101
.equ yellowapricorn, 0x102
.equ whiteapricorn, 0x103
.equ coincase, 0x104
.equ itemfinder, 0x105
.equ oldrod, 0x106
.equ goodrod, 0x107
.equ superrod, 0x108
.equ ssticket, 0x109
.equ oldseamap, 0x112
.equ unownreport, 0x113
.equ gsball, 0x114
.equ letter, 0x115
.equ mysteryegg, 0x116
.equ bluecard, 0x117
.equ squirtbottle, 0x118
.equ secretpotion, 0x119
.equ redscale, 0x11a
.equ basementkey, 0x11b
.equ clearbell, 0x11c
.equ silverwing, 0x11d
.equ machineparts, 0x11e
.equ lostitem, 0x11f
.equ pass, 0x120
.equ tm01, 0x121
.equ tm02, 0x122
.equ tm03, 0x123
.equ tm04, 0x124
.equ tm05, 0x125
.equ tm06, 0x126
.equ tm07, 0x127
.equ tm08, 0x128
.equ tm09, 0x129
.equ tm10, 0x12a
.equ tm11, 0x12b
.equ tm12, 0x12c
.equ tm13, 0x12d
.equ tm14, 0x12e
.equ tm15, 0x12f
.equ tm16, 0x130
.equ tm17, 0x131
.equ tm18, 0x132
.equ tm19, 0x133
.equ tm20, 0x134
.equ tm21, 0x135
.equ tm22, 0x136
.equ tm23, 0x137
.equ tm24, 0x138
.equ tm25, 0x139
.equ tm26, 0x13a
.equ tm27, 0x13b
.equ tm28, 0x13c
.equ tm29, 0x13d
.equ tm30, 0x13e
.equ tm31, 0x13f
.equ tm32, 0x140
.equ tm33, 0x141
.equ tm34, 0x142
.equ tm35, 0x143
.equ tm36, 0x144
.equ tm37, 0x145
.equ tm38, 0x146
.equ tm39, 0x147
.equ tm40, 0x148
.equ tm41, 0x149
.equ tm42, 0x14a
.equ tm43, 0x14b
.equ tm44, 0x14c
.equ tm45, 0x14d
.equ tm46, 0x14e
.equ tm47, 0x14f
.equ tm48, 0x150
.equ tm49, 0x151
.equ tm50, 0x152
.equ hm01, 0x153
.equ hm02, 0x154
.equ hm03, 0x155
.equ hm04, 0x156
.equ hm05, 0x157
.equ hm06, 0x158
.equ hm07, 0x159
.equ hm08, 0x15a
.equ oaksparcel, 0x15d
.equ pokeflute, 0x15e
.equ secretkey, 0x15f
.equ bikevoucher, 0x160
.equ megaring, 0x161
.equ oldamber, 0x162
.equ cardkey, 0x163
.equ liftkey, 0x164
.equ helixfossil, 0x165
.equ domefossil, 0x166
.equ silphscope, 0x167
.equ bicycle, 0x168
.equ townmap, 0x169
.equ vsseeker, 0x16a
.equ famechecker, 0x16b
.equ tmcase, 0x16c
.equ berrypouch, 0x16d
.equ teachytv, 0x16e
.equ tripass, 0x16f
.equ rainbowpass, 0x170
.equ tea, 0x171
.equ mysticticket, 0x172
.equ auroraticket, 0x173
.equ powderjar, 0x174
.equ ruby, 0x175
.equ sapphire, 0x176

/* natures */
.equ random, 0x0
.equ lonely, 0x1
.equ brave, 0x2
.equ adamant, 0x3
.equ naughty, 0x4
.equ bold, 0x5
.equ docile, 0x6
.equ relaxed, 0x7
.equ impish, 0x8
.equ lax, 0x9
.equ timid, 0xa
.equ hasty, 0xb
.equ serious, 0xc
.equ jolly, 0xd
.equ naive, 0xe
.equ modest, 0xf
.equ mild, 0x10
.equ quiet, 0x11
.equ bashful, 0x12
.equ rash, 0x13
.equ calm, 0x14
.equ gentle, 0x15
.equ sassy, 0x16
.equ careful, 0x17
.equ quirky, 0x18

/* ability slots */
.equ abilityone, 0x0
.equ abilitytwo, 0x1

/* types for hidden power */
.equ normal, 0x0
.equ fighting, 0x1
.equ flying, 0x2
.equ poison, 0x3
.equ ground, 0x4
.equ rock, 0x5
.equ bug, 0x6
.equ ghost, 0x7
.equ steel, 0x8
.equ fairy, 0x9
.equ fire, 0xa
.equ water, 0xb
.equ grass, 0xc
.equ electric, 0xd
.equ psychic, 0xe
.equ ice, 0xf
.equ dragon, 0x10
.equ dark, 0x11
.equ maxivs, 0x1f





.include "battle_tower_easy_mode_spreads.inc"
.include "battle_tower_hard_mode_spreads.inc"
.include "battle_tower_trainer_definitions.inc"





/* Put 00 4A 10 47 XX XX XX 08 at 0x43680 (hook via r2)*/

/*
----------------------------------------------------------
This routine will check to see if we are using Trainer 0.

If we are, then we will load custom Trainer Data into a
free RAM space and we will use that data instead of what
is normally supposed to be in the table.

We will randomly determine the Trainer Class here, give
them a random appropriate name, give them the proper
sprite, and give them a randomly determined party.

At this point, r0 = Trainer ID.

First, we check to see if the current Trainer ID is 0x0.
If not, then we load the Trainer Class from the regular
table and then we leave.

If so, then we get a random number between 0 and 10, which
will be the index number of the entry in a table which
determines the Trainer class, gender and sprite.

Then, we determine six unique random numbers between 0 and
18, which will determine which Pokemon the Trainer has in
their party. We always generate six Pokemon, if we are in
3v3 mode, the party length is set to three and the game
only uses the first three Pokemon generated.
----------------------------------------------------------
*/

read_trainer_data_if_zero:
    push {lr}
    cmp r0, #0x0        /* Battle Tower Trainer */
    beq GenerateData
    ldr r2, .TrainerData
    push {r0-r7}
    b GoByeBye

GenerateData:
    ldr r2, .TowerData
    push {r0-r7}
    mov r6, r2
    mov r1, #0x3
    strb r1, [r6]       /* Unknown Byte */
    
GetTrainerClass:
    //bl RandomNumber
    //mov r1, #0xA        /* # of Trainer Classes */
    //bl Modulus2
    ldr r0, =VAR_BATTLE_TOWER_TRAINER_CLASS
    bl VarGet_r7
    ldr r1, .ClassTable
    mov r8, r0          /* r8 = Entry of Class table */
    lsl r0, r0, #0x2    /* Multiply by four */
    add r1, r1, r0
    ldrb r2, [r1]       /* r2 = Trainer Class */
    ldrb r3, [r1, #0x1] /* r3 = Gender */
    ldrb r4, [r1, #0x2] /* r4 = Sprite ID */
    strb r2, [r6, #0x1] /* Trainer Class */
    strb r3, [r6, #0x2] /* Gender */
    strb r4, [r6, #0x3] /* Sprite ID */

GetName:
    push {r1-r3}
    bl RandomNumber
    mov r1, #NUM_TRAINER_NAMES_PER_CLASS
    bl Modulus2
    mov r1, #NUM_TRAINER_NAMES_PER_CLASS
    mov r2, r8
    mul r2, r1
    add r0, r2          /* trainer class * 5 + rand() % 5 = entry in names table */
    pop {r1-r3} 
    ldr r1, .NamesTable

NameLoopStart:
    mov r2, #0xC        /* Name length */
    mul r2, r0
    add r1, r1, r2
    add r6, r6, #0x4    /* Trainer Name */
    mov r3, #0x0        /* Counter */

NameLoop:
    ldrb r0, [r1]
    strb r0, [r6]
    add r1, r1, #0x1
    add r6, r6, #0x1        
    cmp r3, #0xB
    beq SetHeldItems
    add r3, r3, #0x1
    b NameLoop

SetHeldItems:
    mov r0, #0x0        /* No Items */
    strh r0, [r6]       /* 0x10 = Item 1 */
    strh r0, [r6, #0x2] /* 0x12 = Item 2 */
    strh r0, [r6, #0x4] /* 0x14 = Item 3 */
    strh r0, [r6, #0x8] /* 0x16 = Item 4 */

SetBattleType:
    mov r0, #0x0
    add r6, r6, #0x8
    str r0, [r6]        /* 0x18 = Battle Type */
    
SetAIScripts:
    mov r0, #0x3F       /* First Three Scripts */
    add r6, r6, #0x4
    str r0, [r6]        /* 0x1C = AI Scripts */

PartyLengthSet:
    ldr r0, .ModeFlag   /* Flag 0x200, if set use six Pokemon */
    bl FlagCheck
    cmp r0, #0x0
    beq SetThree
    mov r0, #0x6
    b GenerateParty

SetThree:
    ldr r0, =VAR_BATTLE_TOWER_TYPE
    bl VarGet_r7
    cmp r0, #BATTLE_TOWER_TYPE_DOUBLE_EASY
    bge SetFour
    mov r0, #0x3
    b GenerateParty

SetFour:                /* multi battles still require 4 mons */
    mov r0, #0x4

GenerateParty:
    add r6, r6, #0x4
    str r0, [r6]        /* 0x20 = Party Length */
    ldr r0, .PokemonData
    add r6, r6, #0x4
    str r0, [r6]        /* 0x24 = Party Pointer */
    push {r0-r1,r4-r7}
    bl GetRandomPokemon
    mov r2, r0
    
GetSecond:
    bl GetRandomPokemon
    cmp r0, r2
    beq GetSecond
    mov r3, r0

GetThird:
    bl GetRandomPokemon
    cmp r0, r2
    beq GetThird
    cmp r0, r3
    beq GetThird
    mov r4, r0

GetFourth:
    bl GetRandomPokemon
    cmp r0, r2
    beq GetFourth
    cmp r0, r3
    beq GetFourth
    cmp r0, r4
    beq GetFourth
    mov r5, r0

GetFifth:
    bl GetRandomPokemon
    cmp r0, r2
    beq GetFifth
    cmp r0, r3
    beq GetFifth
    cmp r0, r4
    beq GetFifth
    cmp r0, r5
    beq GetFifth
    mov r6, r0

GetSixth:
    bl GetRandomPokemon
    cmp r0, r2
    beq GetSixth
    cmp r0, r3
    beq GetSixth
    cmp r0, r4
    beq GetSixth
    cmp r0, r5
    beq GetSixth
    cmp r0, r6
    beq GetSixth
    mov r7, r0

PutTogether:
    lsl r2, r2, #0x10
    lsl r3, r3, #0x8
    orr r2, r3
    orr r2, r4
    lsl r5, r5, #0x10
    lsl r6, r6, #0x8
    orr r5, r6
    orr r5, r7
    mov r3, r5
    pop {r0-r1,r4-r7}
    mov r4, r2          /* First Three Numbers */
    mov r7, #0x0

LoadThePokemon:
    //ldr r1, .ClassTable
    //mov r0, r8
    //lsl r0, r0, #0x2    /* Multiply by four */
    //add r1, r1, r0
    //mov r1, #0 //ldrb r1, [r1, #0x3] /* Pokemon Pool Entry */
    //mov r0, #0x90
    //lsl r0, r0, #0x1    /* 0x120 = 0x10 * 0x12, Entry * Length = Offset */
    //mul r0, r1

    ldr r0, =VAR_BATTLE_TOWER_TYPE
    bl VarGet_r6
    cmp r0, #BATTLE_TOWER_TYPE_DOUBLE_EASY
    beq LoadEasyTable
    cmp r0, #BATTLE_TOWER_TYPE_SINGLE_EASY
    beq LoadEasyTable
    cmp r0, #BATTLE_TOWER_TYPE_MULTI_EASY
    beq LoadEasyTable
    ldr r1, .PokemonTableHard
    b afterTable

LoadEasyTable:
    ldr r1, .PokemonTable

afterTable:
    add r0, r0, r1      /* Table to get data from */
    lsl r1, r4, #0x18
    lsr r1, r1, #0x18   /* Rightmost */
    ldr r2, .PokemonData /* RAM Address to store to */
    mov r5, #0x30
    mul r5, r7
    add r2, r2, r5
    bl StoreTheParty
    lsl r1, r4, #0x10
    lsr r1, r1, #0x18   /* Middle */
    add r2, r2, #0x10
    bl StoreTheParty
    lsr r1, r4, #0x10   /* Leftmost */
    add r2, r2, #0x10
    bl StoreTheParty
    cmp r7, #0x1
    beq GoByeBye
    mov r7, #0x1
    mov r4, r3
    b LoadThePokemon

GoByeBye:
    pop {r0-r7}
    lsl r1, r0, #0x2
    add r1, r1, r0
    lsl r1, r1, #0x3
    add r1, r1, r2
    ldrb r1, [r1, #0x2] /* Trainer Class */
    mov r0, #0x7F
    and r0, r1
    pop {pc}

RandomNumber:
    ldr r7, .Random
    bx r7

Modulus2:
    ldr r7, .Modulus2
    bx r7

FlagCheck:
    ldr r7, .FlagCheck
    bx r7

VarGet_r6:
    ldr r6, =0x806E568 | 1 // VarGet
    bx r6

VarGet_r7:
    ldr r7, =0x806E568 | 1 // VarGet
    bx r7

GetRandomPokemon:
    push {r2-r7, lr}
    ldr r0, =VAR_BATTLE_TOWER_TYPE
    bl VarGet_r6
    cmp r0, #BATTLE_TOWER_TYPE_DOUBLE_EASY
    beq LoadEasyDenom
    cmp r0, #BATTLE_TOWER_TYPE_SINGLE_EASY
    beq LoadEasyDenom
    cmp r0, #BATTLE_TOWER_TYPE_MULTI_EASY
    beq LoadEasyDenom
    bl RandomNumber
    ldr r1, =NUM_OF_HARD_MODE_SPREADS
    b afterLoadDenom
LoadEasyDenom:
    bl RandomNumber
    mov r1, #NUM_OF_EASY_MODE_SPREADS
afterLoadDenom:
    bl Modulus2
    pop {r2-r7, pc}

StoreTheParty:
    push {r0-r7, lr}
    mov r4, #0x10
    mul r1, r4
    add r1, r1, r0
    ldrh r4, [r1]       /* EV Spread */
    strh r4, [r2]
    ldrh r4, [r1, #0x2] /* Level */
    strh r4, [r2, #0x2] 
    ldrh r4, [r1, #0x4] /* Species */
    strh r4, [r2, #0x4] 
    ldrh r4, [r1, #0x6] /* Held Item */
    strh r4, [r2, #0x6]
    ldrh r4, [r1, #0x8] /* Move 1 */
    strh r4, [r2, #0x8]
    ldrh r4, [r1, #0xA] /* Move 2 */
    strh r4, [r2, #0xA]
    ldrh r4, [r1, #0xC] /* Move 3 */
    strh r4, [r2, #0xC]
    ldrh r4, [r1, #0xE] /* Move 4 */
    strh r4, [r2, #0xE] 
    pop {r0-r7, pc}

.align 2
.TrainerData:           .word 0x0823EAC8
.TowerData:             .word 0x0203C028
.Random:                .word 0x08044EC9
.Modulus2:              .word 0x081E4685
.ClassTable:            .word ClassTableStart
.NamesTable:            .word NamesStart
//.FemaleNames:           .word FemaleNamesStart
.ModeFlag:              .word 0x00000200
.FlagCheck:             .word 0x0806E6D1
.PokemonData:           .word 0x0203C050
.PokemonTable:          .word PokemonTableStartEasyMode
.PokemonTableHard:      .word PokemonTableStartHardMode

.pool

.align 2



/* Put 08 1C 06 1C 03 E0 at 0x115F6 */
/* Put 00 48 00 47 XX XX XX 08 at 0x1162C (hook via r0) */
/* Put 2E E0 at 0x3DC70 */

.align 2

/*
-----------------------------------------------------
Originally written by DoesntKnowHowToPlay.

This routine allows for Trainer Pokemon to have
custom EVs, IVs, Abilities and Natures. These are
loaded from a table included at the bottom of the
routine.

In this routine, we use the IV Field to determine the
Type of Hidden Power. If it is set to 0x1F (31), then
we just use max IVs for all the stats. Otherwise, if
it is set to a Type, then it gives the correct IVs
to yield that Hidden Power Type.

This routine also sets the Friendship points to 255
so that Return can be used correctly.
-----------------------------------------------------
*/

LoadItem:
    add r5, #0x6
    add r0, r4, #0x0
    mov r1, #0xC
    add r2, r5, #0x0
    bl Encrypt

LoadHPEV:
    cmp r0, #BATTLE_TOWER_TYPE_DOUBLE_EASY
    beq LoadEasyOne
    cmp r0, #BATTLE_TOWER_TYPE_SINGLE_EASY
    beq LoadEasyOne
    cmp r0, #BATTLE_TOWER_TYPE_MULTI_EASY
    beq LoadEasyOne
    ldr r2, .PokemonDataHardSpreads
    b LoadEasyOne_after
LoadEasyOne:
    ldr r2, .PokemonDataEasySpreads
LoadEasyOne_after:
    lsl r0, r6, #0x4
    add r2, r0
    add r2, #0x5
    mov r1, #0x1A       /* HP EV */
    mov r0, r4
    bl Encrypt

LoadAtkEV:
    cmp r0, #BATTLE_TOWER_TYPE_DOUBLE_EASY
    beq LoadEasyTwo
    cmp r0, #BATTLE_TOWER_TYPE_SINGLE_EASY
    beq LoadEasyTwo
    cmp r0, #BATTLE_TOWER_TYPE_MULTI_EASY
    beq LoadEasyTwo
    ldr r2, .PokemonDataHardSpreads
    b LoadEasyThree_after
LoadEasyTwo:
    ldr r2, .PokemonDataEasySpreads
LoadEasyTwo_after:
    lsl r0, r6, #0x4
    add r2, r0
    add r2, #0x6
    mov r1, #0x1B       /* Attack EV */
    mov r0, r4
    bl Encrypt

LoadDefEV:
    cmp r0, #BATTLE_TOWER_TYPE_DOUBLE_EASY
    beq LoadEasyThree
    cmp r0, #BATTLE_TOWER_TYPE_SINGLE_EASY
    beq LoadEasyThree
    cmp r0, #BATTLE_TOWER_TYPE_MULTI_EASY
    beq LoadEasyThree
    ldr r2, .PokemonDataHardSpreads
    b LoadEasyThree_after
LoadEasyThree:
    ldr r2, .PokemonDataEasySpreads
LoadEasyThree_after:
    lsl r0, r6, #0x4
    add r2, r0
    add r2, #0x7
    mov r1, #0x1C       /* Defence EV */
    mov r0, r4
    bl Encrypt

LoadSpeedEV:
    cmp r0, #BATTLE_TOWER_TYPE_DOUBLE_EASY
    beq LoadEasyFour
    cmp r0, #BATTLE_TOWER_TYPE_SINGLE_EASY
    beq LoadEasyFour
    cmp r0, #BATTLE_TOWER_TYPE_MULTI_EASY
    beq LoadEasyFour
    ldr r2, .PokemonDataHardSpreads
    b LoadEasyFour_after
LoadEasyFour:
    ldr r2, .PokemonDataEasySpreads
LoadEasyFour_after:
    lsl r0, r6, #0x4
    add r2, r0
    add r2, #0x8
    mov r1, #0x1D       /* Speed EV */
    mov r0, r4
    bl Encrypt

LoadSAtkEV:
    cmp r0, #BATTLE_TOWER_TYPE_DOUBLE_EASY
    beq LoadEasyFive
    cmp r0, #BATTLE_TOWER_TYPE_SINGLE_EASY
    beq LoadEasyFive
    cmp r0, #BATTLE_TOWER_TYPE_MULTI_EASY
    beq LoadEasyFive
    ldr r2, .PokemonDataHardSpreads
    b LoadEasyFive_after
LoadEasyFive:
    ldr r2, .PokemonDataEasySpreads
LoadEasyFive_after:
    lsl r0, r6, #0x4
    add r2, r0
    add r2, #0x9
    mov r1, #0x1E       /* Special Attack EV */
    mov r0, r4
    bl Encrypt

LoadSDefEV:
    cmp r0, #BATTLE_TOWER_TYPE_DOUBLE_EASY
    beq LoadEasySix
    cmp r0, #BATTLE_TOWER_TYPE_SINGLE_EASY
    beq LoadEasySix
    cmp r0, #BATTLE_TOWER_TYPE_MULTI_EASY
    beq LoadEasySix
    ldr r2, .PokemonDataHardSpreads
    b LoadEasySix_after
LoadEasySix:
    ldr r2, .PokemonDataEasySpreads
LoadEasySix_after:
    lsl r0, r6, #0x4
    add r2, r0
    add r2, #0xA
    mov r1, #0x1F       /* Special Defence EV */
    mov r0, r4
    bl Encrypt

LoadBall:
    cmp r0, #BATTLE_TOWER_TYPE_DOUBLE_EASY
    beq LoadEasySeven
    cmp r0, #BATTLE_TOWER_TYPE_SINGLE_EASY
    beq LoadEasySeven
    cmp r0, #BATTLE_TOWER_TYPE_MULTI_EASY
    beq LoadEasySeven
    ldr r2, .PokemonDataHardSpreads
    b LoadEasySeven_after
LoadEasySeven:
    ldr r2, .PokemonDataEasySpreads
LoadEasySeven_after:
    lsl r0, r6, #0x4
    add r2, r0
    add r2, #0xB
    mov r1, #0x26       /* Poke Ball Type */
    mov r0, r4
    bl Encrypt

LoadAbility:
    cmp r0, #BATTLE_TOWER_TYPE_DOUBLE_EASY
    beq LoadEasyEight
    cmp r0, #BATTLE_TOWER_TYPE_SINGLE_EASY
    beq LoadEasyEight
    cmp r0, #BATTLE_TOWER_TYPE_MULTI_EASY
    beq LoadEasyEight
    ldr r2, .PokemonDataHardSpreads
    b LoadEasyEight_after
LoadEasyEight:
    ldr r2, .PokemonDataEasySpreads
LoadEasyEight_after:
    lsl r0, r6, #0x4
    add r2, r0
    add r2, #0xC
    mov r1, #0x2E       /* Ability Bit */
    mov r0, r4
    bl Encrypt

StartNatureLoop:
    cmp r0, #BATTLE_TOWER_TYPE_DOUBLE_EASY
    beq LoadEasyNine
    cmp r0, #BATTLE_TOWER_TYPE_SINGLE_EASY
    beq LoadEasyNine
    cmp r0, #BATTLE_TOWER_TYPE_MULTI_EASY
    beq LoadEasyNine
    ldr r2, .PokemonDataHardSpreads
    b LoadEasyNine_after
LoadEasyNine:
    ldr r2, .PokemonDataEasySpreads
LoadEasyNine_after:
    lsl r0, r6, #0x4
    add r2, r0
    ldrb r5, [r2, #0x0]
    cmp r5, #0x0
    beq LoadIVs
    ldr r0, [r4, #0x0]
    ldr r1, [r4, #0x4]
    eor r1, r0, r1
    str r1, [r4, #0x4]

NatureLoop:
    ldr r0, [r4, #0x0]
    add r0, r0, #0x18
    str r0, [r4, #0x0]
    mov r1, #0x19
    bl Modulus
    cmp r0, r5
    bne NatureLoop

EndNatureLoop:
    ldr r0, [r4, #0x0]
    ldr r1, [r4, #0x4]
    eor r1, r0, r1
    str r1, [r4, #0x4]

LoadIVs:
    cmp r0, #BATTLE_TOWER_TYPE_DOUBLE_EASY
    beq LoadEasyTen
    cmp r0, #BATTLE_TOWER_TYPE_SINGLE_EASY
    beq LoadEasyTen
    cmp r0, #BATTLE_TOWER_TYPE_MULTI_EASY
    beq LoadEasyTen
    ldr r2, .PokemonDataHardSpreads
    b LoadEasyTen_after
LoadEasyTen:
    ldr r2, .PokemonDataEasySpreads
LoadEasyTen_after:
    lsl r0, r6, #0x4
    add r2, r2, r0
    ldrb r6, [r2, #0x4]
    push {r6}
    cmp r6, #0x1F       /* Max IVs */
    beq StartIVLoop
    
GetType:
    mov r5, #0x6
    mul r5, r6
    ldr r6, .HiddenTable
    add r6, r6, r5
    mov r5, #0x27       /* HP IV */
    
TableLoop:
    mov r0, r4
    mov r1, r5
    ldrb r2, [r6]       /* IV in Table */
    push {r2}
    mov r2, sp
    bl Encrypt
    pop {r2}
    add r5, r5, #0x1
    add r6, r6, #0x1
    cmp r5, #0x2D
    beq SetFriendship
    b TableLoop

StartIVLoop:
    mov r5, #0x27       /* HP IV */

IVLoop:
    mov r0, r4
    mov r1, r5
    mov r2, sp
    bl Encrypt
    add r5, r5, #0x1
    cmp r5, #0x2D
    bne IVLoop

SetFriendship:
    mov r0, r4
    mov r1, #0x20       /* Friendship Points */
    mov r2, #0xFF       /* 255 = Max Friendship */
    push {r2}
    mov r2, sp
    bl Encrypt
    pop {r2}

End:
    pop {r6}
    bl RecalculateStats
    ldr r1, .Return
    bx r1

Encrypt:
    ldr r3, .Encrypt
    bx r3

RecalculateStats:
    mov r0, r4
    ldr r1, .Recalculate
    bx r1

Modulus:
    ldr r3, .Modulus
    bx r3

.align 2
.Return:                    .word 0x08011639
.PokemonDataEasySpreads:    .word PokemonTableStartEasyModeSpreads
.PokemonDataHardSpreads:    .word PokemonTableStartHardModeSpreads
.Encrypt:                   .word 0x0804037D
.Recalculate:               .word 0x0803E47D
.Modulus:                   .word 0x081E4685
.HiddenTable:               .word HiddenPowerTable

/* --------------------------------- */

.align 2

HiddenPowerTable:
    .byte 31, 31, 30, 30, 30, 30        /* Fighting */
    .byte 31, 31, 31, 30, 30, 30        /* Flying */
    .byte 31, 31, 30, 31, 30, 30        /* Poison */
    .byte 31, 31, 31, 31, 30, 30        /* Ground */
    .byte 31, 31, 30, 30, 31, 30        /* Rock */
    .byte 31, 31, 31, 30, 31, 30        /* Bug */
    .byte 31, 30, 31, 31, 31, 30        /* Ghost */
    .byte 31, 31, 31, 31, 31, 30        /* Steel */
    .byte 31, 30, 31, 30, 30, 31        /* Fire */
    .byte 31, 31, 31, 30, 30, 31        /* Water */
    .byte 30, 31, 31, 31, 30, 31        /* Grass */
    .byte 31, 31, 31, 31, 30, 31        /* Electric */
    .byte 30, 31, 31, 30, 31, 31        /* Psychic */
    .byte 31, 31, 31, 30, 31, 31        /* Ice */
    .byte 30, 31, 31, 31, 31, 31        /* Dragon */
    .byte 31, 31, 31, 31, 31, 31        /* Dark */

.align 2

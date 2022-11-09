.thumb
.thumb_func
.align 2


/* --------------------------------- */

ClassTableStart:
//.byte class, gender, image, 0
.byte /* Youngster */          0x39,   male,  82, 0
.byte /* Lass */               0x3B, female,  84, 0
.byte /* School Kid[m] */      0x19,   male,  29, 0
.byte /* Camper */             0x3D,   male,  86, 0
.byte /* Picnicker */          0x3E, female,  87, 0
.byte /* Guitarist */          0x11,   male,  17, 0
.byte /* Pokéfan[m] */         0x1B,   male,  32, 0
.byte /* Pokéfan[f] */         0x1B, female,  33, 0
.byte /* Bug Catcher */        0x3A,   male,  83, 0
.byte /* Fisherman */          0x45,   male,  94, 0
.byte /* Ruin Maniac */        0x68,   male, 145, 0
.byte /* Beauty */             0x49, female,  98, 0
.byte /* Bird Keeper */        0x4F,   male, 104, 0
.byte /* Sailor */             0x3C,   male,  85, 0
.byte /* Hiker */              0x41,   male,  90, 0
.byte /* Blackbelt */          0x50,   male, 105, 0
.byte /* Crush Girl */         0x63, female, 139, 0
.byte /* Psychic[m] */         0x15,   male, 100, 0
.byte /* Psychic[f] */         0x15, female, 138, 0
.byte /* Pokémon Breeder[f] */ 0x65, female, 141, 0
.byte /* Gentleman */          0x58,   male, 123, 0
.byte /* Scientist */          0x52,   male, 107, 0
.byte /* Cool Trainer[m] */    0x56,   male, 110, 0
.byte /* Cool Trainer[f] */    0x56, female, 111, 0
.byte /* Pokémon Ranger[m] */  0x66,   male, 142, 0
.byte /* Pokémon Ranger[f] */  0x66, female, 143, 0
.byte /* Juggler */            0x4D,   male, 102, 0
.byte /* Officer */            0x09,   male,   8, 0
.byte /* Gamer */              0x48,   male,  97, 0
.byte /* Pokémaniac */         0x3F,   male,  88, 0
.byte /* Lady */               0x69, female, 146, 0


//.byte cooltrainerm, male, cooltrainerm_pic, 0
//.byte cooltrainerf, female, cooltrainerf_pic, 0
//.byte expertm, male, expertm_pic, 1
//.byte expertf, female, expertf_pic, 1
//.byte gentleman, male, gentleman_pic, 2
//.byte pokemaniac, male, pokemaniac_pic, 3
//.byte pkmnbreederm, male, pkmnbreederm_pic, 4
//.byte pkmnbreederf, female, pkmnbreederf_pic, 4
//.byte dragontamer, male, dragontamer_pic, 5
//.byte hexmaniac, female, hexmaniac_pic, 6




/* --------------------------------- */

.align 2

/*12 bytes per name, 5 names per class*/

NamesStart:
/* Youngster */
.byte J, i, m, Done, Done, Done, Done, Done, Done, Done, Done, Done
.byte E, r, r, o, l, l, Done, Done, Done, Done, Done, Done
.byte C, a, s, i, m, i, r, Done, Done, Done, Done, Done
.byte K, a, i, d, e, n, Done, Done, Done, Done, Done, Done
.byte K, o, l, b, y, Done, Done, Done, Done, Done, Done, Done

/* Lass */
.byte C, a, m, e, r, o, n, Done, Done, Done, Done, Done
.byte P, e, a, c, h, e, s, Done, Done, Done, Done, Done
.byte Y, a, s, m, i, n, Done, Done, Done, Done, Done, Done
.byte K, a, r, i, s, s, a, Done, Done, Done, Done, Done
.byte L, i, l, i, a, n, a, Done, Done, Done, Done, Done

/* School Kid[m] */
.byte F, o, s, t, e, r, Done, Done, Done, Done, Done, Done
.byte K, e, n, Done, Done, Done, Done, Done, Done, Done, Done, Done
.byte O, w, e, n, Done, Done, Done, Done, Done, Done, Done, Done
.byte J, o, n, a, s, Done, Done, Done, Done, Done, Done, Done
.byte K, e, o, n, Done, Done, Done, Done, Done, Done, Done, Done

/* Camper */
.byte B, e, r, n, a, r, d, Done, Done, Done, Done, Done
.byte H, e, r, b, e, r, t, Done, Done, Done, Done, Done
.byte C, o, l, b, e, r, t, Done, Done, Done, Done, Done
.byte F, r, e, d, d, y, Done, Done, Done, Done, Done, Done
.byte A, n, d, r, e, Done, Done, Done, Done, Done, Done, Done

/* Picnicker */
.byte M, a, g, g, i, e, Done, Done, Done, Done, Done, Done
.byte M, e, l, a, n, i, e, Done, Done, Done, Done, Done
.byte A, n, n, Done, Done, Done, Done, Done, Done, Done, Done, Done
.byte I, g, n, a, Done, Done, Done, Done, Done, Done, Done, Done
.byte T, o, n, y, a, Done, Done, Done, Done, Done, Done, Done

/* Guitarist */
.byte M, a, l, c, o, l, m, Done, Done, Done, Done, Done
.byte T, a, d, Done, Done, Done, Done, Done, Done, Done, Done, Done
.byte C, o, n, c, o, r, d, Done, Done, Done, Done, Done
.byte B, e, r, n, i, e, Done, Done, Done, Done, Done, Done
.byte C, u, r, t, i, s, Done, Done, Done, Done, Done, Done

/* Pokéfan[m] */
.byte E, w, a, n, Done, Done, Done, Done, Done, Done, Done, Done
.byte K, a, n, e, Done, Done, Done, Done, Done, Done, Done, Done
.byte T, h, e, o, Done, Done, Done, Done, Done, Done, Done, Done
.byte S, i, m, o, n, Done, Done, Done, Done, Done, Done, Done
.byte T, u, r, n, e, r, Done, Done, Done, Done, Done, Done

/* Pokéfan[f] */
.byte A, l, e, x, i, a, Done, Done, Done, Done, Done, Done
.byte L, u, n, a, Done, Done, Done, Done, Done, Done, Done, Done
.byte C, e, l, e, n, e, Done, Done, Done, Done, Done, Done
.byte E, u, r, o, p, a, Done, Done, Done, Done, Done, Done
.byte P, a, n, d, o, r, a, Done, Done, Done, Done, Done

/* Bug Catcher */
.byte F, l, o, y, d, Done, Done, Done, Done, Done, Done, Done
.byte H, o, f, f, m, a, n, Done, Done, Done, Done, Done
.byte A, m, a, d, e, u, s, Done, Done, Done, Done, Done
.byte C, a, m, u, i, Done, Done, Done, Done, Done, Done, Done
.byte O, r, l, a, n, d, o, Done, Done, Done, Done, Done

/* Fisherman */
.byte K, i, e, f, e, r, Done, Done, Done, Done, Done, Done
.byte B, a, s, i, l, Done, Done, Done, Done, Done, Done, Done
.byte F, a, r, l, e, y, Done, Done, Done, Done, Done, Done
.byte M, a, r, k, Done, Done, Done, Done, Done, Done, Done, Done
.byte D, e, l, a, n, e, y, Done, Done, Done, Done, Done

/* Ruin Maniac */
.byte H, e, r, n, i, k, Done, Done, Done, Done, Done, Done
.byte A, u, b, r, y, Done, Done, Done, Done, Done, Done, Done
.byte S, a, m, u, e, l, Done, Done, Done, Done, Done, Done
.byte P, e, n, n, Done, Done, Done, Done, Done, Done, Done, Done
.byte I, s, a, d, o, r, e, Done, Done, Done, Done, Done

/* Beauty */
.byte T, i, f, f, a, n, y, Done, Done, Done, Done, Done
.byte B, r, i, t, n, e, y, Done, Done, Done, Done, Done
.byte H, a, r, m, o, n, y, Done, Done, Done, Done, Done
.byte N, a, d, i, a, Done, Done, Done, Done, Done, Done, Done
.byte B, e, c, k, y, Done, Done, Done, Done, Done, Done, Done

/* Bird Keeper */
.byte B, e, r, n, i, e, Done, Done, Done, Done, Done, Done
.byte C, u, r, t, i, s, Done, Done, Done, Done, Done, Done
.byte S, h, a, w, n, Done, Done, Done, Done, Done, Done, Done
.byte K, e, n, n, i, t, h, Done, Done, Done, Done, Done
.byte S, a, l, l, y, Done, Done, Done, Done, Done, Done, Done

/* Sailor */
.byte L, a, y, t, o, n, Done, Done, Done, Done, Done, Done
.byte G, o, d, w, i, n, Done, Done, Done, Done, Done, Done
.byte C, a, s, p, e, r, Done, Done, Done, Done, Done, Done
.byte D, e, r, r, i, a, n, Done, Done, Done, Done, Done
.byte C, a, r, l, o, Done, Done, Done, Done, Done, Done, Done

/* Hiker */
.byte E, v, e, r, e, t, t, Done, Done, Done, Done, Done
.byte R, a, i, d, e, n, Done, Done, Done, Done, Done, Done
.byte M, o, n, t, y, Done, Done, Done, Done, Done, Done, Done
.byte R, o, c, k, y, Done, Done, Done, Done, Done, Done, Done
.byte L, y, l, e, Done, Done, Done, Done, Done, Done, Done, Done

/* Blackbelt */
.byte C, l, e, m, e, n, t, Done, Done, Done, Done, Done
.byte M, a, s, o, n, Done, Done, Done, Done, Done, Done, Done
.byte J, e, r, i, c, h, o, Done, Done, Done, Done, Done
.byte H, a, r, r, i, s, Done, Done, Done, Done, Done, Done
.byte S, o, r, e, n, Done, Done, Done, Done, Done, Done, Done

/* Crush Girl */
.byte K, o, d, i, Done, Done, Done, Done, Done, Done, Done, Done
.byte A, i, l, e, e, n, Done, Done, Done, Done, Done, Done
.byte T, r, i, n, a, Done, Done, Done, Done, Done, Done, Done
.byte A, l, t, a, Done, Done, Done, Done, Done, Done, Done, Done
.byte I, n, g, r, i, d, Done, Done, Done, Done, Done, Done

/* Psychic[m] */
.byte A, l, p, h, a, Done, Done, Done, Done, Done, Done, Done
.byte B, e, t, a, Done, Done, Done, Done, Done, Done, Done, Done
.byte E, s, s, i, e, Done, Done, Done, Done, Done, Done, Done
.byte D, e, n, v, e, r, Done, Done, Done, Done, Done, Done
.byte B, e, r, k, l, e, y, Done, Done, Done, Done, Done

/* Psychic[f] */
.byte A, m, e, l, i, a, Done, Done, Done, Done, Done, Done
.byte C, e, l, i, n, e, Done, Done, Done, Done, Done, Done
.byte J, i, l, i, a, n, Done, Done, Done, Done, Done, Done
.byte I, r, e, n, e, Done, Done, Done, Done, Done, Done, Done
.byte S, y, l, v, i, e, Done, Done, Done, Done, Done, Done

/* Pokémon Breeder[f] */
.byte A, d, r, i, a, n, a, Done, Done, Done, Done, Done
.byte S, o, n, y, a, Done, Done, Done, Done, Done, Done, Done
.byte T, a, t, y, a, n, a, Done, Done, Done, Done, Done
.byte Z, o, r, y, a, Done, Done, Done, Done, Done, Done, Done
.byte A, n, t, o, n, i, a, Done, Done, Done, Done, Done

/* Gentleman */
.byte Z, a, n, t, e, Done, Done, Done, Done, Done, Done, Done
.byte G, i, l, i, a, m, Done, Done, Done, Done, Done, Done
.byte J, o, a, c, h, i, m, Done, Done, Done, Done, Done
.byte K, a, r, s, t, o, n, Done, Done, Done, Done, Done
.byte B, o, y, c, e, Done, Done, Done, Done, Done, Done, Done

/* Scientist */
.byte J, e, a, n, Done, Done, Done, Done, Done, Done, Done, Done
.byte B, r, a, d, Done, Done, Done, Done, Done, Done, Done, Done
.byte I, r, w, i, n, Done, Done, Done, Done, Done, Done, Done
.byte F, l, y, n, n, Done, Done, Done, Done, Done, Done, Done
.byte T, y, r, e, l, l, Done, Done, Done, Done, Done, Done

/* Cool Trainer[m] */
.byte Y, a, r, d, l, e, y, Done, Done, Done, Done, Done, Done
.byte S, t, a, v, r, o, s, Done, Done, Done, Done, Done, Done
.byte Z, a, n, e, Done, Done, Done, Done, Done, Done, Done, Done
.byte G, a, r, v, y, Done, Done, Done, Done, Done, Done, Done
.byte C, r, u, z, Done, Done, Done, Done, Done, Done, Done, Done

/* Cool Trainer[f] */
.byte K, i, m, Done, Done, Done, Done, Done, Done, Done, Done, Done
.byte M, a, c, y, Done, Done, Done, Done, Done, Done, Done, Done
.byte F, a, u, n, Done, Done, Done, Done, Done, Done, Done, Done
.byte P, a, m, e, l, a, Done, Done, Done, Done, Done, Done
.byte D, a, n, i, e, l, a, Done, Done, Done, Done, Done

/* Pokémon Ranger[m] */
.byte D, o, y, l, e, Done, Done, Done, Done, Done, Done, Done
.byte D, u, k, e, Done, Done, Done, Done, Done, Done, Done, Done
.byte D, e, a, c, o, n, Done, Done, Done, Done, Done, Done
.byte F, i, o, r, e, Done, Done, Done, Done, Done, Done, Done
.byte A, l, m, i, a, Done, Done, Done, Done, Done, Done, Done

/* Pokémon Ranger[f] */
.byte M, e, n, a, Done, Done, Done, Done, Done, Done, Done, Done
.byte M, e, r, c, y, Done, Done, Done, Done, Done, Done, Done
.byte E, v, i, t, a, Done, Done, Done, Done, Done, Done, Done
.byte O, b, l, i, v, i, a, Done, Done, Done, Done, Done
.byte A, l, m, i, a, Done, Done, Done, Done, Done, Done, Done

/* Juggler */
.byte F, r, a, n, c, i, s, Done, Done, Done, Done, Done
.byte P, r, e, s, c, o, t, Done, Done, Done, Done, Done
.byte F, r, a, n, k, Done, Done, Done, Done, Done, Done, Done
.byte A, l, m, a, Done, Done, Done, Done, Done, Done, Done, Done
.byte E, l, i, s, e, Done, Done, Done, Done, Done, Done, Done

/* Officer */
.byte H, u, g, h, Done, Done, Done, Done, Done, Done, Done, Done
.byte K, e, g, a, n, Done, Done, Done, Done, Done, Done, Done
.byte R, e, g, g, i, e, Done, Done, Done, Done, Done, Done
.byte K, e, g, a, n, Done, Done, Done, Done, Done, Done, Done
.byte C, h, e, s, t, e, r, Done, Done, Done, Done, Done

/* Gamer */
.byte N, e, i, l, Done, Done, Done, Done, Done, Done, Done, Done
.byte S, e, r, g, e, i, Done, Done, Done, Done, Done
.byte R, a, l, p, h, Done, Done, Done, Done, Done, Done, Done
.byte C, o, n, w, a, y, Done, Done, Done, Done, Done, Done
.byte R, i, v, e, r, Done, Done, Done, Done, Done, Done, Done

/* Pokémaniac */
.byte U, p, t, o, n, Done, Done, Done, Done, Done, Done, Done
.byte E, m, i, l, Done, Done, Done, Done, Done, Done, Done, Done
.byte M, a, r, q, u, e, z, Done, Done, Done, Done, Done
.byte A, r, n, o, l, d, Done, Done, Done, Done, Done, Done
.byte L, e, r, o, y, Done, Done, Done, Done, Done, Done, Done

/* Lady */
.byte I, s, a, b, e, l, Done, Done, Done, Done, Done, Done
.byte N, i, c, h, o, l, e, Done, Done, Done, Done, Done
.byte J, u, a, n, i, t, a, Done, Done, Done, Done, Done
.byte A, m, o, r, y, Done, Done, Done, Done, Done, Done, Done
.byte J, u, l, i, a, n, a, Done, Done, Done, Done, Done



// old names:
//    .byte L, E, O, N, A, R, D, O, Done, Done, Done, Done
//    .byte A, L, E, X, A, N, D, E, R, Done, Done, Done
//    .byte H, E, C, T, O, R, Done, Done, Done, Done, Done, Done
//    .byte D, W, I, G, H,T, Done, Done, Done, Done, Done, Done
//    .byte P, E, T, E, R, Done, Done, Done, Done, Done, Done, Done
//    .byte R, O, B, E, R, T, Done, Done, Done, Done, Done, Done
//    .byte K, O, B, E, Done, Done, Done, Done, Done, Done, Done, Done
//    .byte O, R, I, O, N, Done, Done, Done, Done, Done, Done, Done
//    .byte J, A, S, P, E, R, Done, Done, Done, Done, Done, Done
//    .byte Q, U, I, N, C, Y, Done, Done, Done, Done, Done, Done
//    .byte A, K, I, H, I, T, O, Done, Done, Done, Done, Done
//    .byte T, E, R, R, A, N, C, E, Done, Done, Done, Done
//    .byte S, U, M, A, N, Done, Done, Done, Done, Done, Done, Done
//    .byte O, M, A, R, Done, Done, Done, Done, Done, Done, Done, Done
//    .byte J, A, C, K, S, O, N, Done, Done, Done, Done, Done
//    .byte K, E, V, I, N, Done, Done, Done, Done, Done, Done, Done
//    .byte J, O, S, E, P, H, Done, Done, Done, Done, Done, Done
//    .byte M, A, T, T, H, E, W, Done, Done, Done, Done, Done
//    .byte D, A, R, I, U, S, Done, Done, Done, Done, Done, Done
//    .byte C, A, L, V, I, N, Done, Done, Done, Done, Done, Done
//    .byte T, A, Y, S, H, A, W, N, Done, Done, Done, Done
//    .byte M, E, L, Done, Done, Done, Done, Done, Done, Done, Done, Done
//    .byte D, A, V, E, Done, Done, Done, Done, Done, Done, Done, Done
//    .byte V, I, N, C, E, N, T, Done, Done, Done, Done, Done
//    .byte E, R, N, E, S, T, O, Done, Done, Done, Done, Done
//    .byte E, T, H, A, N, Done, Done, Done, Done, Done, Done, Done
//    .byte G, E, O, F, F, E, R, Y, Done, Done, Done, Done
//    .byte B, A, R, B, A, R, O, Done, Done, Done, Done, Done
//    .byte N, E, L, S, O, N, Done, Done, Done, Done, Done, Done
//    .byte L, A, R, S, Done, Done, Done, Done, Done, Done, Done, Done
//    .byte T, A, K, U, M, I, Done, Done, Done, Done, Done, Done
//    .byte M, I, K, E, Done, Done, Done, Done, Done, Done, Done, Done
//
//.align 2
//
///* --------------------------------- */
//
//.align 2
//
//FemaleNamesStart:
//    /* 12 bytes per name, 
//    .byte A, M, A, N, D, A, Done, Done, Done, Done, Done, Done
//    .byte T, E, N, I, L, L, E, Done, Done, Done, Done, Done
//    .byte A, R, I, E, L, L, A, Done, Done, Done, Done, Done
//    .byte B, I, A, N, C, A, Done, Done, Done, Done, Done, Done
//    .byte R, E, B, E, C, C, A, Done, Done, Done, Done, Done
//    .byte T, E, N, K, O, Done, Done, Done, Done, Done, Done, Done
//    .byte R, E, I, M, U, Done, Done, Done, Done, Done, Done, Done
//    .byte L, U, C, I, L, L, E, Done, Done, Done, Done, Done
//    .byte J, U, N, E, Done, Done, Done, Done, Done, Done, Done, Done
//    .byte P, R, U, N, E, L, L, A, Done, Done, Done, Done
//    .byte W, E, N, D, Y, Done, Done, Done, Done, Done, Done, Done
//    .byte P, E, T, R, A, Done, Done, Done, Done, Done, Done, Done
//    .byte A, N, U, J, A, Done, Done, Done, Done, Done, Done, Done
//    .byte H, A, R, R, I, E, T, T, E, Done, Done, Done
//    .byte J, O, R, D, A, N, N, A, Done, Done, Done, Done
//    .byte H, A, N, N, A, H, Done, Done, Done, Done, Done, Done
//    .byte M, A, C, K, E, N, Z, I, E, Done, Done, Done
//    .byte S, O, R, I, E, L, Done, Done, Done, Done, Done, Done
//    .byte D, A, R, I, A, Done, Done, Done, Done, Done, Done, Done
//    .byte Y, O, L, A, N, D, A, Done, Done, Done, Done, Done
//    .byte A, L, E, X, A, N, D, R, A, Done, Done, Done
//    .byte B, R, I, A, N, N, E, Done, Done, Done, Done, Done
//    .byte C, A, R, O, L, I, N, E, Done, Done, Done, Done
//    .byte O, C, T, A, V, I, A, Done, Done, Done, Done, Done
//    .byte J, A, S, M, I, N, E, Done, Done, Done, Done, Done
//    .byte F, A, T, I, M, A, Done, Done, Done, Done, Done, Done
//    .byte M, I, R, A, N, D, A, Done, Done, Done, Done, Done
//    .byte B, O, N, N, I, E, Done, Done, Done, Done, Done, Done
//    .byte J, E, S, S, I, C, A, Done, Done, Done, Done, Done
//    .byte A, M, B, E, R, Done, Done, Done, Done, Done, Done, Done
//    .byte S, A, M, A, N, T, H, A, Done, Done, Done, Done
//    .byte U, M, A, Done, Done, Done, Done, Done, Done, Done, Done, Done

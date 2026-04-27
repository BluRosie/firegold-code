#include "../include/global.h"

enum {
    COSTUME_ORIGINAL,
    COSTUME_RETRO,
    COSTUME_ROCKET,
    COSTUME_ATHLETE,
    COSTUME_HOENN,
    COSTUME_MAX
};

#define VAR_COSTUME 0x43FB

// addresses are per-gender
u32 sCostumeToAddress[][COSTUME_MAX] = {
    // male costumes
    {
        [COSTUME_ORIGINAL] = 0x87525D0,
        [COSTUME_RETRO] = 0x9E0F440,
        [COSTUME_ROCKET] = 0x9E1CBD0,
        [COSTUME_ATHLETE] = 0x9E2A360,
        [COSTUME_HOENN] = 0x9E37AF0,
    },
    // female costumes
    {
        [COSTUME_ORIGINAL] = 0x8752A78,
        [COSTUME_RETRO] = 0x9E0F6A8,
        [COSTUME_ROCKET] = 0x9E1CE38,
        [COSTUME_ATHLETE] = 0x9E3796C,
        [COSTUME_HOENN] = 0x9E37D58,
    },
};

u16 sCostumeToPalTag[][COSTUME_MAX] = {
    // male costumes
    {
        [COSTUME_ORIGINAL] = 0x1135,
        [COSTUME_RETRO] = 0x1131,
        [COSTUME_ROCKET] = 0x1136,
        [COSTUME_ATHLETE] = 0x1142,
        [COSTUME_HOENN] = 0x114c,
    },
    // female costumes
    {
        [COSTUME_ORIGINAL] = 0x1138,
        [COSTUME_RETRO] = 0x1134,
        [COSTUME_ROCKET] = 0x1137,
        [COSTUME_ATHLETE] = 0x1143,
        [COSTUME_HOENN] = 0x114d,
    },
};

u32 grabCostumeImagesPtrBasedOnOriginal(u32 address)
{
    if (address == 0x087525D0) {
        address = sCostumeToAddress[0][VarGet(VAR_COSTUME)];
    }
    return address;
}

u32 grabCostumePalTagBasedOnOriginal(u32 original)
{
    if (original == 0x1135) {
        VarSet(VAR_COSTUME, VarGet(VAR_COSTUME) + 1);
        if (VarGet(VAR_COSTUME) >= COSTUME_MAX) {
            VarSet(VAR_COSTUME, 0);
        }
        original = sCostumeToPalTag[0][VarGet(VAR_COSTUME)];
    }
    return original;
}

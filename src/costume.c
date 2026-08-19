#include "../include/global.h"
#include "../include/sprite.h"

enum {
    COSTUME_ORIGINAL,
    COSTUME_RETRO,
    COSTUME_ROCKET,
    COSTUME_ATHLETE,
    COSTUME_HOENN,
    COSTUME_MAX
};

enum {
    STATE_WALKING_RUNNING,
    STATE_BIKING,
    STATE_SURFING,
    STATE_FIELD_MOVE,
    STATE_FISHING,
    STATE_VS_SEEKER,
    STATE_VS_SEEKER_BIKING,
    STATE_MAX
};

#define VAR_COSTUME 0x43FB

#define GENDER MALE

// addresses are per-gender
u32 sCostumeToAddress[2][STATE_MAX][COSTUME_MAX] = {
    // male costumes
    {
        [STATE_WALKING_RUNNING] = {
            [COSTUME_ORIGINAL] = 0x87525D0,
            [COSTUME_RETRO] = 0x9E0F440,
            [COSTUME_ROCKET] = 0x9E1CBD0,
            [COSTUME_ATHLETE] = 0x9E37AF0,
            [COSTUME_HOENN] = 0x9E37AF0,
        },
        [STATE_BIKING] = {
            [COSTUME_ORIGINAL] = 0x87528B0,
            [COSTUME_RETRO] = 0x9E0F4E0,
            [COSTUME_ROCKET] = 0x9E1CC70,
            [COSTUME_ATHLETE] = 0x9E2A400,
            [COSTUME_HOENN] = 0x9E37B90,
        },
        [STATE_SURFING] = {
            [COSTUME_ORIGINAL] = 0x87528F8,
            [COSTUME_RETRO] = 0x9E0F528,
            [COSTUME_ROCKET] = 0x9E1CCB8,
            [COSTUME_ATHLETE] = 0x9E2A448,
            [COSTUME_HOENN] = 0x9E37BD8,
        },
        [STATE_FIELD_MOVE] = {
            [COSTUME_ORIGINAL] = 0x8752958,
            [COSTUME_RETRO] = 0x9E0F588,
            [COSTUME_ROCKET] = 0x9E1CD18,
            [COSTUME_ATHLETE] = 0x9E2A4A8,
            [COSTUME_HOENN] = 0x9E37C38,
        },
        [STATE_FISHING] = {
            [COSTUME_ORIGINAL] = 0x87529A0,
            [COSTUME_RETRO] = 0x9E0F5D0,
            [COSTUME_ROCKET] = 0x9E1CD60,
            [COSTUME_ATHLETE] = 0x9E2A4F0,
            [COSTUME_HOENN] = 0x9E37C80,
        },
        [STATE_VS_SEEKER] = {
            [COSTUME_ORIGINAL] = 0x8752A00,
            [COSTUME_RETRO] = 0x9E0F630,
            [COSTUME_ROCKET] = 0x9E1CDC0,
            [COSTUME_ATHLETE] = 0x9E2A550,
            [COSTUME_HOENN] = 0x9E37CE0,
        },
        [STATE_VS_SEEKER_BIKING] = {
            [COSTUME_ORIGINAL] = 0x8752A48,
            [COSTUME_RETRO] = 0x9E0F678,
            [COSTUME_ROCKET] = 0x9E1CE08,
            [COSTUME_ATHLETE] = 0x9E2A598,
            [COSTUME_HOENN] = 0x9E37D28,
        },
    },
    // female costumes
    {
        [STATE_WALKING_RUNNING] = {
            [COSTUME_ORIGINAL] = 0x8752A78,
            [COSTUME_RETRO] = 0x9E0F6A8,
            [COSTUME_ROCKET] = 0x9E1CE38,
            [COSTUME_ATHLETE] = 0x9E2A5C8,
            [COSTUME_HOENN] = 0x9E37D58,
        },
        [STATE_BIKING] = {
            [COSTUME_ORIGINAL] = 0x8752B18,
            [COSTUME_RETRO] = 0x9E0F748,
            [COSTUME_ROCKET] = 0x9E1CED8,
            [COSTUME_ATHLETE] = 0x9E2A668,
            [COSTUME_HOENN] = 0x9E37DF8,
        },
        [STATE_SURFING] = {
            [COSTUME_ORIGINAL] = 0x8752B60,
            [COSTUME_RETRO] = 0x9E0F790,
            [COSTUME_ROCKET] = 0x9E1CF20,
            [COSTUME_ATHLETE] = 0x9E2A6B0,
            [COSTUME_HOENN] = 0x9E37E40,
        },
        [STATE_FIELD_MOVE] = {
            [COSTUME_ORIGINAL] = 0x8752BC0,
            [COSTUME_RETRO] = 0x9E0F7F0,
            [COSTUME_ROCKET] = 0x9E1CF80,
            [COSTUME_ATHLETE] = 0x9E2A710,
            [COSTUME_HOENN] = 0x9E37EA0,
        },
        [STATE_FISHING] = {
            [COSTUME_ORIGINAL] = 0x8752C08,
            [COSTUME_RETRO] = 0x9E0F838,
            [COSTUME_ROCKET] = 0x9E1CFC8,
            [COSTUME_ATHLETE] = 0x9E2A758,
            [COSTUME_HOENN] = 0x9E37EE8,
        },
        [STATE_VS_SEEKER] = {
            [COSTUME_ORIGINAL] = 0x8752C68,
            [COSTUME_RETRO] = 0x9E0F898,
            [COSTUME_ROCKET] = 0x9E1D028,
            [COSTUME_ATHLETE] = 0x9E2A7B8,
            [COSTUME_HOENN] = 0x9E37F48,
        },
        [STATE_VS_SEEKER_BIKING] = {
            [COSTUME_ORIGINAL] = 0x8752CB0,
            [COSTUME_RETRO] = 0x9E0F8E0,
            [COSTUME_ROCKET] = 0x9E1D070,
            [COSTUME_ATHLETE] = 0x9E2A800,
            [COSTUME_HOENN] = 0x9E37F90,
        },
    },
};




// this one won't need a per-state thing at all so should be good
u16 sCostumeToPalTag[2][COSTUME_MAX] = {
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

// male/female/index in each entry...  but we do not care about index.  just need 
extern u32 gFrontSpriteCostumeTable[COSTUME_MAX][3];
extern u32 gBackSpriteCostumeTable[COSTUME_MAX][3];

extern struct SpriteTemplate gMultiuseSpriteTemplate;

u32 grabCostumeImagesPtrBasedOnOriginal(u32 address)
{
    int i;
    for (i = 0; i < STATE_MAX; i++)
    {
        // if equal to initial entry, grab real entry from the table
        if (address == sCostumeToAddress[GENDER][i][0]) {
            address = sCostumeToAddress[GENDER][i][VarGet(VAR_COSTUME)];
            break;
        }
    }
    return address;
}

u32 grabCostumePalTagBasedOnOriginal(u32 original)
{
    // if equal to initial entry, grab real entry from the table
    if (original == sCostumeToPalTag[GENDER][0]) {
        if ((~(*(u16 *)0x04000130)) & 1) // a button being pressed
        {
            VarSet(VAR_COSTUME, VarGet(VAR_COSTUME) + 1);
            if (VarGet(VAR_COSTUME) >= COSTUME_MAX) {
                VarSet(VAR_COSTUME, 0);
            }
        }
        original = sCostumeToPalTag[GENDER][VarGet(VAR_COSTUME)];
    }
    return original;
}

u32 GrabSpriteCostumePointer(u32 id, u32 isBackSprite, u32 palette)
{
    u32 gender = (id == 136); // female if true, male if false
    u32 costume = VarGet(VAR_COSTUME);
    if (isBackSprite)
    {
        return gBackSpriteCostumeTable[2*costume + gender][palette]; // BackPicTable!  not actual sprites.  but this is perfect
    }
    else
    {
        if (palette == 0)
            return (u32)&gFrontSpriteCostumeTable[2*costume + gender][0];
        else
            return gFrontSpriteCostumeTable[2*costume + gender][1];
    }
}

void AdjustBackspriteTemplateAsNeeded(void)
{
    u32 id = 0;
    if (((u32)gMultiuseSpriteTemplate.images) == 0x08234718) // male
    {
        id = 135;
    }
    else if (((u32)gMultiuseSpriteTemplate.images) == 0x08234740) // female
    {
        id = 136;
    }
    if (id != 0)
    {
        gMultiuseSpriteTemplate.images = (struct SpriteFrameImage *)GrabSpriteCostumePointer(id, 1, 0);
    }
}

#include "../include/gba/types.h"
#include "../include/palette.h"
#include "../include/pokemon.h"
#include "../include/sprite.h"

#define REG_OFFSET_DISPCNT 0
#define REG_OFFSET_WINOUT 0x4a

#define DISPCNT_OBJWIN_ON       0x8000
#define WINOUT_WINOBJ_OBJ   (1 << 12)

u16 coords_menu[][2] = {
    {132+16,    4+16},
    {132+16+48, 4+16},
    {132+16,    4+16+28},
    {132+16+48, 4+16+28},
    {132+16,    4+16+58},
    {132+16+48, 4+16+58},
};

void PrintMonIcons(void)
{
    LoadMonIconPalettes();
    //ResetSpriteData();
    for (int i = 0; i < 6; i++)
    {
        void *mon = &gPlayerParty[i];
        u16 species = GetMonData(mon, MON_DATA_SPECIES);
        u16 pid = GetMonData(mon, MON_DATA_PERSONALITY);

        if (species != 0)
        {
            u8 spriteId;
            spriteId = CreateMonIcon(species, 0x0809718d, 96+16, 40+16, 0, pid, 0);
            gSprites[spriteId].oam.priority = 0;
            gSprites[spriteId].invisible = 0;
            gSprites[spriteId].pos1.x = 0;
            gSprites[spriteId].pos1.y = 0;
            gSprites[spriteId].pos2.x = coords_menu[i][0];
            gSprites[spriteId].pos2.y = coords_menu[i][1];
            //gSprites[spriteId].oam.objMode = ST_OAM_OBJ_WINDOW;
        }
    }

    SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_OBJWIN_ON);
    SetGpuRegBits(REG_OFFSET_WINOUT, WINOUT_WINOBJ_OBJ);
    
    for (int i = 0; i < 6; i++)
    {
        void *mon = &gPlayerParty[i];
        u16 species = GetMonData(mon, MON_DATA_SPECIES);
        u16 pid = GetMonData(mon, MON_DATA_PERSONALITY);

        if (species != 0)
        {
            u8 spriteId;
            spriteId = CreateMonIcon(species, 0x0809718d, 96+16, 40+16, 0, pid, 0);
            gSprites[spriteId].oam.priority = 0;
            gSprites[spriteId].invisible = 0;
            gSprites[spriteId].pos1.x = 0;
            gSprites[spriteId].pos1.y = 0;
            gSprites[spriteId].pos2.x = coords_menu[i][0];
            gSprites[spriteId].pos2.y = coords_menu[i][1];
            gSprites[spriteId].oam.objMode = ST_OAM_OBJ_WINDOW;
        }
    }

}


void Task_WaitFadeAndPrintMainMenuText(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        Task_PrintMainMenuText(taskId);
        PrintMonIcons();
    }
}

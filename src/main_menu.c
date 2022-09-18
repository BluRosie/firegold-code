#include "../include/gba/types.h"
#include "../include/pokemon.h"
#include "../include/sprite.h"

void PrintMonIcons(void)
{
        FillWindowPixelBuffer(MAIN_MENU_WINDOW_CONTINUE, PIXEL_FILL(10));
        FillWindowPixelBuffer(MAIN_MENU_WINDOW_NEWGAME, PIXEL_FILL(10));
        AddTextPrinterParameterized3(MAIN_MENU_WINDOW_CONTINUE, FONT_2, 2, 2, sTextColor1, -1, gText_Continue);
        AddTextPrinterParameterized3(MAIN_MENU_WINDOW_NEWGAME, FONT_2, 2, 2, sTextColor1, -1, gText_NewGame);
        PrintContinueStats();
        MainMenu_DrawWindow(&sWindowTemplate[MAIN_MENU_WINDOW_CONTINUE]);
        MainMenu_DrawWindow(&sWindowTemplate[MAIN_MENU_WINDOW_NEWGAME]);
        PutWindowTilemap(MAIN_MENU_WINDOW_CONTINUE);
        PutWindowTilemap(MAIN_MENU_WINDOW_NEWGAME);
        CopyWindowToVram(MAIN_MENU_WINDOW_CONTINUE, COPYWIN_GFX);
        CopyWindowToVram(MAIN_MENU_WINDOW_NEWGAME, COPYWIN_FULL);
    
    //for (int i = 0; i < 6; i++)
    int i = 0;
    //{
    //    void *mon = &gPlayerParty[i];
    //    u16 species = GetMonData(mon, MON_DATA_SPECIES);
    //    u16 pid = GetMonData(mon, MON_DATA_PERSONALITY);
    //    u8 spriteId;
    //    ResetSpriteData();
    //    LoadMonIconPalettes();
    //    spriteId = CreateMonIcon(25, SpriteCallbackDummy, 200+16, 130+16, 0, pid, 1);
    //    gSprites[spriteId].oam.priority = 0;
    //}
}

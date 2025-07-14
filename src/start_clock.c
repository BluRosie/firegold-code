#include "../include/gba/defines.h"
#include "../include/gba/io_reg.h"
#include "../include/gba/types.h"
#include "../include/main.h"
#include "../include/menu.h"
#include "../include/save.h"
#include "../include/sound.h"
#include "../include/strings.h"
#include "../include/string_util.h"
#include "../include/text.h"
#include "../include/window.h"

#define CLOCK_WINDOW_WIDTH 70

#define sSafariZoneStatsWindowId *((u8*)0x02037101)

static const struct WindowTemplate sClockWindowTemplate = {0, 1, 1, 9, 2, 0xF, 8};

// i love fire red not having funcs that emerald does
int GetStringWidthDifference(int fontId, const u8 *str, int totalWidth, int letterSpacing)
{
    int stringWidth = GetStringWidth(fontId, str, letterSpacing);
    if (totalWidth > stringWidth)
        return totalWidth - stringWidth;
    else
        return 0;
}

#define GetStringRightAlignXOffset(fontId, str, totalWidth) GetStringWidthDifference(fontId, str, totalWidth, 0)
#define gCurrentTimeDayOfWeek *((u8*)0x03005541)

void ShowTimeWindow(void)
{
    const u8 *suffix;
    const u8 *timeofday;
    u8 alignedSuffix[16];
    u8 str[0x20];
    u8* ptr;

    // print window
    sSafariZoneStatsWindowId = AddWindow(&sClockWindowTemplate);
    PutWindowTilemap(sSafariZoneStatsWindowId);
    DrawStdWindowFrame(sSafariZoneStatsWindowId, 0);

    if (gCurrentTimeHours < 12)
        suffix = gText_AM;
    else
        suffix = gText_PM;

    switch (gCurrentTimeDayOfWeek)
    {
    case 0:
        StringExpandPlaceholders(gStringVar4, gText_Sun);
        break;
    case 1:
        StringExpandPlaceholders(gStringVar4, gText_Mon);
        break;
    case 2:
        StringExpandPlaceholders(gStringVar4, gText_Tue);
        break;
    case 3:
        StringExpandPlaceholders(gStringVar4, gText_Wed);
        break;
    case 4:
        StringExpandPlaceholders(gStringVar4, gText_Thu);
        break;
    case 5:
        StringExpandPlaceholders(gStringVar4, gText_Fri);
        break;
    case 6:
        StringExpandPlaceholders(gStringVar4, gText_Sat);
        break;
    }
    //StringExpandPlaceholders(gStringVar4, gText_ContinueMenuTime);
    AddTextPrinterParameterized(sSafariZoneStatsWindowId, 1, gStringVar4, 0, 1, 0xFF, 0); // prints "Time"

    ptr = ConvertIntToDecimalStringN(gStringVar4, gCurrentTimeHours, STR_CONV_MODE_LEFT_ALIGN, 3);
    *ptr = 0xF0;

    ConvertIntToDecimalStringN(ptr + 1, gCurrentTimeMins, STR_CONV_MODE_LEADING_ZEROS, 2);
    AddTextPrinterParameterized(sSafariZoneStatsWindowId, 1, gStringVar4, GetStringRightAlignXOffset(1, suffix, CLOCK_WINDOW_WIDTH) - (CLOCK_WINDOW_WIDTH - GetStringRightAlignXOffset(1, gStringVar4, CLOCK_WINDOW_WIDTH) + 3), 1, 0xFF, NULL); // print time

    AddTextPrinterParameterized(sSafariZoneStatsWindowId, 1, suffix, GetStringRightAlignXOffset(1, suffix, CLOCK_WINDOW_WIDTH), 1, 0xFF, NULL); // print am/pm

    CopyWindowToVram(sSafariZoneStatsWindowId, 2);
}

// hook these
// will also destroy our window.  take out flag check, it's always created
void DestroySafariZoneStatsWindow(void)
{
    //if (GetSafariZoneFlag())
    {
        ClearStdWindowAndFrameToTransparent(sSafariZoneStatsWindowId, FALSE);
        CopyWindowToVram(sSafariZoneStatsWindowId, COPYWIN_GFX);
        RemoveWindow(sSafariZoneStatsWindowId);
    }
}

u8 CreateStartMenuWindow(u8 num);
u32 GetSafariZoneFlag(void);
void DrawSafariZoneStatsWindow(void);
u32 PrintStartMenuItems(u8 *, u8);
u32 DrawHelpMessageWindowWithText(const u8* const);
void PrintTextOnHelpMessageWindow(const u8* const, u32);
u32 StartMenuPokedexSanityCheck();
void StartMenu_FadeScreenIfLeavingOverworld();
void DestroyHelpMessageWindow_();
void CloseStartMenu();
void SetUpStartMenu();
u8 GetStartMenuWindowId();

extern const u8 *const sStartMenuDescPointers[];

#define OPTIONS_BUTTON_MODE_HELP 0

void DoDrawStartMenu_Case3(void)
{
//    switch (sDrawStartMenuState[0])
//    {
// ...
//    case 3:
        if (GetSafariZoneFlag())
            DrawSafariZoneStatsWindow();
        // new:  draw time clock otherwise
        else
            ShowTimeWindow();
// ...
}

/*bool8*/ void StartCB_HandleInput(void)
{
    //if (JOY_NEW(DPAD_UP))
    //{
    //    PlaySE(SE_SELECT);
    //    sStartMenuCursorPos = Menu_MoveCursor(-1);
    //    if (!MenuHelpers_LinkSomething() && InUnionRoom() != TRUE && gSaveBlock2->optionsButtonMode == OPTIONS_BUTTON_MODE_HELP)
    //    {
    //        PrintTextOnHelpMessageWindow(sStartMenuDescPointers[sStartMenuOrder[sStartMenuCursorPos]], 2);
    //    }
    //}
    //if (JOY_NEW(DPAD_DOWN))
    //{
    //    PlaySE(SE_SELECT);
    //    sStartMenuCursorPos = Menu_MoveCursor(+1);
    //    if (!MenuHelpers_LinkSomething() && InUnionRoom() != TRUE && gSaveBlock2->optionsButtonMode == OPTIONS_BUTTON_MODE_HELP)
    //    {
    //        PrintTextOnHelpMessageWindow(sStartMenuDescPointers[sStartMenuOrder[sStartMenuCursorPos]], 2);
    //    }
    //}
    //if (JOY_NEW(A_BUTTON))
    //{
    //    PlaySE(SE_SELECT);
    //    if (!StartMenuPokedexSanityCheck())
    //        return FALSE;
    //    sStartMenuCallback = sStartMenuActionTable[sStartMenuOrder[sStartMenuCursorPos]].func.u8_void;
    //    StartMenu_FadeScreenIfLeavingOverworld();
    //    return FALSE;
    //}
    //if (JOY_NEW(B_BUTTON | START_BUTTON))
    //{
    //    DestroySafariZoneStatsWindow();
    //    DestroyHelpMessageWindow_();
    //    CloseStartMenu();
    //    return TRUE;
    //}
    //return FALSE;
    if (!GetSafariZoneFlag() && gCurrentTimeSeconds == 0) 
    {
        DestroySafariZoneStatsWindow();
        ShowTimeWindow();
    }
}

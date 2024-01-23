#ifndef GUARD_MENU_H
#define GUARD_MENU_H

#include "task.h"
#include "text.h"
#include "window.h"

struct MenuAction
{
    const u8 *text;
    union {
        void (*void_u8)(u8);
        u8 (*u8_void)(void);
    } func;
};

void AddTextPrinterParameterized3(u8 windowId, u8 fontId, u8 left, u8 top, const u8 *color, s8 speed, const u8 *str);
void ResetTempTileDataBuffers(void);
void *DecompressAndCopyTileDataToVram(u8 bgId, const void *src, u32 size, u16 offset, u8 mode);
void AddTextPrinterParameterized4(u8 windowId, u8 fontId, u8 x, u8 y, u8 letterSpacing, u8 lineSpacing, const u8 *color, s8 speed, const u8 *str);
u8 Menu_MoveCursor(s8 cursorDelta);
u32 MenuHelpers_LinkSomething(void);
u32 InUnionRoom(void);

#endif // GUARD_MENU_H
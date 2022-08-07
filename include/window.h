#ifndef GUARD_WINDOW_H
#define GUARD_WINDOW_H

#define PIXEL_FILL(num) ((num) | ((num) << 4))

// Mode for CopyWindowToVram, CopyWindowRectToVram and CopyWindowToVram8Bit
enum {
    COPYWIN_NONE,
    COPYWIN_MAP,
    COPYWIN_GFX,
    COPYWIN_FULL,
};

struct WindowTemplate
{
    u8 bg;
    u8 tilemapLeft;
    u8 tilemapTop;
    u8 width;
    u8 height;
    u8 paletteNum;
    u16 baseBlock;
};

#define DUMMY_WIN_TEMPLATE          \
{                                   \
    0xFF,                           \
    0,                              \
    0,                              \
    0,                              \
    0,                              \
    0,                              \
    0,                              \
}

struct Window
{
    struct WindowTemplate window;
    u8 *tileData;
};

bool16 InitWindows(const struct WindowTemplate *templates);
void FreeAllWindowBuffers(void);
void CopyWindowToVram(u8 windowId, u8 mode);
void PutWindowTilemap(u8 windowId);
void ClearWindowTilemap(u8 windowId);
void FillWindowPixelBuffer(u8 windowId, u8 fillValue);
u8 AddWindow(struct WindowTemplate *temp);
void DrawStdWindowFrame(u8 id, u32 boole);
void ClearStdWindowAndFrameToTransparent(u32 id, u32 boole);
void RemoveWindow(u32 id);
void LoadStdWindowFrameGfx(void);

#endif // GUARD_WINDOW_H
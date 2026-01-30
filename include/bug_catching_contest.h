#include "global.h"
#include "constants/flags.h"

#define INITIAL_BALL_QUANTITY 20

#define X_POS_MON_TO_SWAP 56
#define Y_POS_MON_TO_SWAP 36

#define X_POS_MON_SWAPPING (56)
#define Y_POS_MON_SWAPPING (84)

#define X_POS_MON_PAUSE_MENU (56-32)
#define Y_POS_MON_PAUSE_MENU (16)

#define IS_IN_BUG_CATCHING_CONTEST (FlagGet(FLAG_BUG_CATCHING_CONTEST))
#define IS_BCC_MON_INVALID (((u32 *)(&gBccGlobalStruct.caughtMon))[0] == 0)

#define CLOCK_WINDOW_WIDTH 70

#define sSafariZoneStatsWindowId *((u8*)0x02037101)

// bug catching contest stuff
#define SECONDS_IN_CONTEST (20 * 60) // 20 minute total time
#define FRAMES_PER_SECOND 60 // 60 frames per second

struct BugCatchingContestGlobalStruct
{
    //struct Sprite *monIconSprites[2];
    //struct Pokemon caughtMon;
    u8 caughtMon[0x64]; // my shit don't line up exact!  oh well
    u8 spriteIds[4]; // index of gSprites
    u8 windowIds[2];
    u16 secondTimer;
    u8 frameTimer;
    u8 cursorPos;
    u8 activated;
    u8 initStep;
    u8 palReloadTimer;
    u8 balls;
}; // size = 0x72

extern struct BugCatchingContestGlobalStruct gBccGlobalStruct;

#include "../include/global.h"

#include "../include/bg.h"
#include "../include/event_data.h"
#include "../include/menu.h"
#include "../include/sound.h"
#include "../include/string_util.h"
#include "../include/task.h"
#include "../include/trainer_card.h"

// check out bytereplacement for the two functions that had their sizeof edited

// change the way that the trainer card stores the bits for each badge
void SetDataFromTrainerCard_edits(void)
{
    u16 flags[NUM_BADGES] = {FLAG_BADGE_VIOLET, FLAG_BADGE_AZALEA, FLAG_BADGE_GOLDENROD, FLAG_BADGE_ECRUTEAK, FLAG_BADGE_CIANWOOD, FLAG_BADGE_OLIVINE, FLAG_BADGE_MAHOGANY, FLAG_BADGE_BLACKTHORN,
                             FLAG_BADGE_PEWTER, FLAG_BADGE_CERULEAN, FLAG_BADGE_VERMILION, FLAG_BADGE_CELADON, FLAG_BADGE_FUCHSIA, FLAG_BADGE_SAFFRON, FLAG_BADGE_CINNABAR, FLAG_BADGE_VIRIDIAN};
    
    sTrainerCardDataPtr->badgeBitfield = 0;
    
    for (int i = 0; i < NUM_BADGES; i++)
    {
        if (FlagGet(flags[i]))
            sTrainerCardDataPtr->badgeBitfield |= (1 << i);
    }
}


#define BASE_BADGE_TILE 192
#define BASE_BADGE_TILE_OFFSET_BG_3 0


// change the way that the badges are drawn to the screen
void DrawStarsAndBadgesOnCard(void)
{
    s16 i, x, y = 14;
    u16 tileNum = BASE_BADGE_TILE;
    u8 palNum = 3;

    FillBgTilemapBufferRect(3, 143, 15, sStarYOffsets[sTrainerCardDataPtr->cardType], sTrainerCardDataPtr->trainerCard.rse.stars, 1, 4);
    if (!sTrainerCardDataPtr->isLink)
    {
        x = 5;
        for (i = 0; i < NUM_BADGES; i++, tileNum += 2, x += 3)
        {
            if (sTrainerCardDataPtr->badgeBitfield & (1 << i))
            {
                FillBgTilemapBufferRect(3,      tileNum,     x,     y, 1, 1, palNum);
                FillBgTilemapBufferRect(3,  tileNum + 1, x + 1,     y, 1, 1, palNum);
                FillBgTilemapBufferRect(3, tileNum + 32,     x, y + 1, 1, 1, palNum);
                FillBgTilemapBufferRect(3, tileNum + 33, x + 1, y + 1, 1, 1, palNum);
            }
            if (i == 7) // reset x to 4, add 2 to y
            {
                x = 2;
                y += 3;
            }
        }
    }

    CopyBgTilemapBufferToVram(3);
}


bool8 Task_SetCardFlipped(struct Task* task)
{
    sTrainerCardDataPtr->allowDMACopy = FALSE;

    // If on back of card, draw front of card because its being flipped.  also load the badges in again
    if (sTrainerCardDataPtr->onBack)
    {
        DrawTrainerCardWindow(2);
        DrawCardScreenBackground(sTrainerCardDataPtr->bgTilemap);
        DrawCardFrontOrBack(sTrainerCardDataPtr->frontTilemap);
        LoadBgTiles(3, sTrainerCardDataPtr->badgeTiles, 0x80 * NUM_BADGES, 0);
        DrawStarsAndBadgesOnCard();
    }
    else // load in icons before the flip is allowed to happen fully
    {
        LoadMonIconGfx();
    }

    DrawTrainerCardWindow(1);
    sTrainerCardDataPtr->onBack ^= 1;
    task->data[0]++; // tflippingstate
    sTrainerCardDataPtr->allowDMACopy = TRUE;
    PlaySE(243); // SE_CARD_FLIPPING
    return FALSE;
}


// change the way that the badges are counted for the save screen
void SaveStatToString_case_badges(u8 *dest)
{
    u16 flags[NUM_BADGES] = {FLAG_BADGE_VIOLET, FLAG_BADGE_AZALEA, FLAG_BADGE_GOLDENROD, FLAG_BADGE_ECRUTEAK, FLAG_BADGE_CIANWOOD, FLAG_BADGE_OLIVINE, FLAG_BADGE_MAHOGANY, FLAG_BADGE_BLACKTHORN,
                             FLAG_BADGE_PEWTER, FLAG_BADGE_CERULEAN, FLAG_BADGE_VERMILION, FLAG_BADGE_CELADON, FLAG_BADGE_FUCHSIA, FLAG_BADGE_SAFFRON, FLAG_BADGE_CINNABAR, FLAG_BADGE_VIRIDIAN};
    u8 nBadges = 0;
    
    for (int i = 0; i < NUM_BADGES; i++)
    {
        if (FlagGet(flags[i]))
        {
            nBadges++;
        }
    }
    
    if (nBadges >= 10)
        *dest++ = (nBadges / 10) + 0xA1;
    *dest++ = (nBadges % 10) + 0xA1;
    *dest++ = 10;
    *dest++ = 0xFF;
}


const u8 sTextColor2[] = { 10,  1, 12 };
const u8 gText_Badges[] = {0xBC, 0xD5, 0xD8, 0xDB, 0xD9, 0xE7, 0xFF};
const u8 gTextJPDummy_Ko[] = {0xFF};

// change the way the badges are counted for the continue screen
void PrintBadgeCount(void)
{
    u16 flags[NUM_BADGES] = {FLAG_BADGE_VIOLET, FLAG_BADGE_AZALEA, FLAG_BADGE_GOLDENROD, FLAG_BADGE_ECRUTEAK, FLAG_BADGE_CIANWOOD, FLAG_BADGE_OLIVINE, FLAG_BADGE_MAHOGANY, FLAG_BADGE_BLACKTHORN,
                             FLAG_BADGE_PEWTER, FLAG_BADGE_CERULEAN, FLAG_BADGE_VERMILION, FLAG_BADGE_CELADON, FLAG_BADGE_FUCHSIA, FLAG_BADGE_SAFFRON, FLAG_BADGE_CINNABAR, FLAG_BADGE_VIRIDIAN};
    u8 strbuf[30];
    u8 *ptr;
    u8 nbadges = 0;
    for (int i = 0; i < NUM_BADGES; i++)
    {
        if (FlagGet(flags[i]))
            nbadges++;
    }
    AddTextPrinterParameterized3(1, 2, 2, 66, sTextColor2, -1, gText_Badges);
    ptr = ConvertIntToDecimalStringN(strbuf, nbadges, 0, 2);
    StringAppend(ptr, gTextJPDummy_Ko);
    AddTextPrinterParameterized3(1, 2, 62, 66, sTextColor2, -1, strbuf);
}

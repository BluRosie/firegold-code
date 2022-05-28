#include "../include/global.h"

#include "../include/bg.h"
#include "../include/event_data.h"
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


// change the way that the badges are drawn to the screen
void DrawStarsAndBadgesOnCard(void)
{
    s16 i, x, y = 14;
    u16 tileNum = 192; // how do we know
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

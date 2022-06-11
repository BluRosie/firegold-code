#include "../include/global.h"

#include "../include/event_data.h"
#include "../include/fly_spot.h"

//void SetFlyWarpDestination(u16 mapsec)
//{
//    u16 idx = mapsec - 0x58;
//    
//    if (idx == 0x1A || idx == 0x1B) // lake of rage is target
//    {
//        if (FlagGet(0x2195) // gyarados has been defeated
//         && gDayOfWeek == 3) // wednesday
//            idx = 0x1b;
//        else
//            idx = 0x1a;
//    }
//    
//    if (sMapFlyDestinations[idx][2])
//    {
//        SetWarpDestinationToHealLocation(sMapFlyDestinations[idx][2]);
//        SetUsedFlyQuestLogEvent(sMapFlyDestinations[idx]);
//    }
//    else
//    {
//        SetWarpDestinationToMapWarp(sMapFlyDestinations[idx][0], sMapFlyDestinations[idx][1], -1);
//    }
//    ReturnToFieldFromFlyMapSelect();
//}

struct HealLocation
{
    s8 group;
    s8 map;
    s16 x;
    s16 y;
};

void SetWarpDestinationToHealLocation(u8 healLocationId)
{
    const struct HealLocation *warp = GetHealLocation(healLocationId);
    struct HealLocation warpInStack;
    
    warpInStack.group = warp->group;
    warpInStack.map = warp->map;
    
    if (warp)
    {
        if (warp->group == 43 && warp->map == 27 && gDayOfWeek == 3 && FlagGet(0x2195))
            warpInStack.map = 29; // change to dry
        SetWarpDestination(warpInStack.group, warpInStack.map, -1, warp->x, warp->y);
    }
}

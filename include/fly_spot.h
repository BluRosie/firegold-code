#ifndef FLY_SPOT_H
#define FLY_SPOT_H

extern const u8 sMapFlyDestinations[][3];
extern u8 gDayOfWeek;

//void SetWarpDestinationToHealLocation(u8 a0);
void SetUsedFlyQuestLogEvent(const u8 *healLocCtrlData);
void SetWarpDestinationToMapWarp(s8 mapGroup, s8 mapNum, s8 warpNum);
void ReturnToFieldFromFlyMapSelect(void);
const struct HealLocation *GetHealLocation(u32 loc);
void SetWarpDestination(s8 mapGroup, s8 mapNum, s8 warpId, s8 x, s8 y);

#endif // FLY_SPOT_H
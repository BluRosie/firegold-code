#ifndef GUARD_OVERWORLD_H
#define GUARD_OVERWORLD_H

#define invokedFromOW data[3]

void CB2_ReturnToField(void);
void CB2_ReturnToBag(void);
void PrepareOverworldReturn();
void FreeOverworldBGs();
void GetInFrontOfPlayerPosition(struct MapPosition * position);
void MapGridGetMetatileAttributeAt(s16 x, s16 y);

#endif // GUARD_OVERWORLD_H

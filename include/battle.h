#ifndef GUARD_BATTLE_H
#define GUARD_BATTLE_H

extern const u8 *gBattlescriptCurrInstr;

extern u8 gMoveNames[][13];
extern u8 gActionSelectionCursor[4];
extern u8 gDisplayedStringBattle[];
extern u32 gActiveBattler;

void (*gBattlerControllerFuncs[4])(void);

#endif // GUARD_BATTLE_H

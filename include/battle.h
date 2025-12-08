#ifndef GUARD_BATTLE_H
#define GUARD_BATTLE_H

const u8 *gBattlescriptCurrInstr;

extern u8 gMoveNames[][13];
extern u8 gActionSelectionCursor[4];
extern u8 gDisplayedStringBattle[];
extern u32 gActiveBattler;
extern u8 gBattlerByTurnOrder[4];
extern u8 gCurrentTurnActionNumber;
extern u8 gBattlerAttacker;
extern u8 gBattlerTarget;
extern u16 gBattle_BG0_X;
extern u16 gBattle_BG0_Y;
extern u16 gLastUsedItem;
extern u16 gUsedBall;
extern u8 gCurrentActionFuncId;
extern u8 gNumSafariBalls;

void (*gBattlerControllerFuncs[4])(void);

const u8 *const gBattlescriptsForBallThrow[];
const u8 BattleScript_ThrowBall[];

#endif // GUARD_BATTLE_H

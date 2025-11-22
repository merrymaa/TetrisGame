#ifndef FSM_H
#define FSM_H

#include "backend.h"
#include "objects.h"

void stateStart(GameInfoExtended_t *gameInfoEx, UserAction_t action);
void stateSpawn(GameInfoExtended_t *gameInfoEx);
void stateMoving(GameInfoExtended_t *gameInfoEx, UserAction_t action);
void stateAttaching(GameInfoExtended_t *gameInfoEx);
void stateGameOver(GameInfoExtended_t *gameInfoEx);

#endif
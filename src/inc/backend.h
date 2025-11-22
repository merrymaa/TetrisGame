#ifndef BACKEND_H
#define BACKEND_H

#include <sys/time.h>
#include <time.h>

#include "defines.h"
#include "fsm.h"
#include "objects.h"
#include "tetris.h"

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();
void funcFSM(UserAction_t action);
GameInfoExtended_t *getInfoEx();
int **createMatrix(int rows, int cols);
void freeMatrix(int **matrix, int rows);
void createCurrentFigure(Figure_t *figure);
int createNextFigure(int **next);
void copyNextToCurrent(GameInfoExtended_t *game);
int canMove(GameInfoExtended_t *game, UserAction_t action);
void rotateFigure(GameInfoExtended_t *game);
void rotateType_2(GameInfoExtended_t *game);
void rotateType_4(GameInfoExtended_t *game);
int canRotate(GameInfoExtended_t *game, int tmp[][5]);
int typeFigure(int number);
int destroyRows(int **field);
int isFullRow(const int *row);
int delRow(int **field, int current_row);
long long getCurrentTime();
int calculateLevel(GameInfoExtended_t *gameInfoEx);
int calculateSpeed(GameInfoExtended_t *gameInfoEx);
int pauseEnableDisable();
void clearField(GameInfoExtended_t *gameInfoEx);
int readHighScore();
void writeHighScore(int score);
#endif
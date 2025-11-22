#ifndef FRONTEND_H
#define FRONTEND_H

#include <ncurses.h>
#include <string.h>

#include "backend.h"
#include "defines.h"
#include "objects.h"

void gameLoop();
void printGameField(WINDOW *win, int **field);
void printInfo(WINDOW *win, GameInfo_t snapshot);
void printGameField(WINDOW *win, int **field);

#endif
#include "../../inc/fsm.h"

/**
 * @brief статус игры СТАРТ. задает начальные значения параметров игры
 * @param gameInfoEx указатель на статус игры
 * @param action действие игрока
 */
void stateStart(GameInfoExtended_t *gameInfoEx, UserAction_t action) {
  if (action == Start) {
    clearField(gameInfoEx);
    gameInfoEx->gameInfo.score = 0;
    gameInfoEx->gameInfo.high_score = readHighScore();
    gameInfoEx->gameInfo.level = 1;
    gameInfoEx->gameInfo.speed = 0;
    gameInfoEx->gameInfo.pause = 0;
    gameInfoEx->state = STATE_SPAWN;
  }
}

/**
 * @brief осуществляет генерацию фигур
 * @param gameInfoEx статус игры
 */
void stateSpawn(GameInfoExtended_t *gameInfoEx) {
  static int firstStart = 0;
  if (!firstStart) {
    createCurrentFigure(&gameInfoEx->currentFigure);
    gameInfoEx->typeNextFigure = createNextFigure(gameInfoEx->gameInfo.next);
    firstStart = 1;
  }
  copyNextToCurrent(gameInfoEx);
  gameInfoEx->typeNextFigure = createNextFigure(gameInfoEx->gameInfo.next);

  gameInfoEx->state = STATE_MOVING;
}

/**
 * @brief осуществляет перемещение фигур
 * @param gameInfoEx указатель на статус игры
 * @param action действие игрока
 */
void stateMoving(GameInfoExtended_t *gameInfoEx, UserAction_t action) {
  switch (action) {
    case Pause:
      gameInfoEx->gameInfo.pause = pauseEnableDisable();
      break;
    case Action:
      if (!gameInfoEx->gameInfo.pause) rotateFigure(gameInfoEx);
      break;
    case Up:
      break;
    case Left:
      if (canMove(gameInfoEx, action) && !gameInfoEx->gameInfo.pause) {
        gameInfoEx->currentFigure.x -= 1;
      }
      break;
    case Right:
      if (canMove(getInfoEx(), action) && !gameInfoEx->gameInfo.pause) {
        gameInfoEx->currentFigure.x += 1;
      }
      break;
    case Down:
      if (!canMove(gameInfoEx, action) && !gameInfoEx->gameInfo.pause)
        gameInfoEx->state = STATE_ATTACHING;
      if (canMove(gameInfoEx, action) && !gameInfoEx->gameInfo.pause) {
        gameInfoEx->currentFigure.y += 1;
      } else
        break;
    default:
      break;
  }
}

/**
 * @brief определяет столкновение фигур и очистку строк при заполнении
 * @param gameInfoEx указатель на статус игры
 */
void stateAttaching(GameInfoExtended_t *gameInfoEx) {
  if (gameInfoEx->currentFigure.y < 0)
    gameInfoEx->state = STATE_GAME_OVER;
  else {
    // если нельзя сместиться вниз
    int x = gameInfoEx->currentFigure.x;
    int y = gameInfoEx->currentFigure.y;

    for (int i = 0; i < FIG_SIZE_H; i++) {
      for (int j = 0; j < FIG_SIZE_W; j++) {
        if (gameInfoEx->currentFigure.fig[i][j]) {
          int new_x = x + j;
          int new_y = y + i;

          if (new_y == 19 ||
              gameInfoEx->gameInfo
                  .field[new_y + 1][new_x]) {  // если фигура дошла до низа или
                                               // до другой фигуры

            int x1 = gameInfoEx->currentFigure.x;
            int y1 = gameInfoEx->currentFigure.y;
            for (int r = 0; r < 4; r++) {  // копирую текущую фигуру на поле
              for (int c = 0; c < 4; c++) {
                if (gameInfoEx->currentFigure.fig[r][c]) {
                  gameInfoEx->gameInfo.field[r + y1][c + x1] =
                      gameInfoEx->currentFigure.fig[r][c];
                  gameInfoEx->currentFigure.fig[r][c] =
                      0;  // удаляю текущую фигуру
                }
              }
            }
            gameInfoEx->state = STATE_SPAWN;
            break;
          }
        }
      }
    }
    gameInfoEx->gameInfo.score += destroyRows(gameInfoEx->gameInfo.field);
  }
  gameInfoEx->gameInfo.level = calculateLevel(gameInfoEx);
}

/**
 * @brief завершает текущую игровую сессию, сохраняет результат
 * @param gameInfoEx указатель на игровой статус
 */
void stateGameOver(GameInfoExtended_t *gameInfoEx) {
  clearField(gameInfoEx);
  gameInfoEx->state = STATE_START;
  gameInfoEx->gameInfo.field[4][5] = 2;  /// TEST
  writeHighScore(gameInfoEx->gameInfo.score);
}

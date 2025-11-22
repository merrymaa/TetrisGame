#include "../../inc/backend.h"

/**
 * @brief принимает ввод от пользователя и передает его в бэк
 * @param action действие пользователя
 * @param hold флаг удержания клавиши
 */
void userInput(UserAction_t action, bool hold) {
  if (!hold) funcFSM(action);
}

/**
 * @brief функция определяет текущее состояние FSM и, в зависимости
 * от действия определяет дальнейшие действи игры
 * @param action действие пользователя
 */
void funcFSM(UserAction_t action) {
  static GameInfoExtended_t *gameInfoEx = NULL;

  if (action == Terminate) {
    freeMatrix(gameInfoEx->gameInfo.field, FIELD_H);
    freeMatrix(gameInfoEx->gameInfo.next, FIG_SIZE_H);

  } else {
    if (!gameInfoEx) {
      srand(time(NULL));
      gameInfoEx = getInfoEx();
      gameInfoEx->state = STATE_START;
    }

    switch (gameInfoEx->state) {
      case STATE_START:
        stateStart(gameInfoEx, action);
        break;
      case STATE_SPAWN:
        stateSpawn(gameInfoEx);
        break;
      case STATE_MOVING:
        stateMoving(gameInfoEx, action);
        break;
      case STATE_ATTACHING:
        stateAttaching(gameInfoEx);
        break;
      case STATE_GAME_OVER:
        stateGameOver(gameInfoEx);
        break;
      default:
        break;
    }
  }
}

/**
 * @brief определяет текущий статус игры
 * @return указатель на расширенную структура о статусе игры
 */
GameInfoExtended_t *getInfoEx() {
  static int firstTime = 0;

  static GameInfoExtended_t *ptr = NULL;
  static GameInfoExtended_t game = {0};
  if (!firstTime) {
    game.gameInfo.field = createMatrix(FIELD_H, FIELD_W);
    game.gameInfo.next = createMatrix(FIG_SIZE_H, FIG_SIZE_W);
    firstTime = 1;
  }

  ptr = &game;

  return ptr;
}

/**
 * @brief выделяет память под матрицу размером rows, cols
 * @param rows количество строк
 * @param cols количество столбцов
 * @return указатель на двумерную матрицу
 */
int **createMatrix(int rows, int cols) {
  int **matrix = (int **)malloc(rows * sizeof(int *));
  for (int i = 0; i < rows; ++i) {
    matrix[i] = (int *)calloc(cols, sizeof(int));
  }
  return matrix;
}

/**
 * @brief очищает выделенную память
 * @param matrix указатель на двумерный массив
 * @param rows количество строк
 */
void freeMatrix(int **matrix, int rows) {
  for (int i = 0; i < rows; i++) {
    free(matrix[i]);
    matrix[i] = NULL;
  }
  free(matrix);
}

/**
 * @brief обновляет статус игры
 * @return возвращает снимок GameInfo_t
 */
GameInfo_t updateCurrentState() {
  static GameInfo_t snapshot;
  static long long timeFirstPoint = 0, timeSecondPoint = 0;

  if (!snapshot.field) {
    snapshot.field = createMatrix(FIELD_H, FIELD_W);
    snapshot.next = createMatrix(FIG_SIZE_H, FIG_SIZE_W);
  }

  // копирую поле на снимок
  for (int i = 0; i < FIELD_H; i++) {
    for (int j = 0; j < FIELD_W; j++) {
      snapshot.field[i][j] = getInfoEx()->gameInfo.field[i][j];
    }
  }

  // копирую next
  for (int i = 0; i < FIG_SIZE_H; i++) {
    for (int j = 0; j < FIG_SIZE_W; j++) {
      snapshot.next[i][j] = getInfoEx()->gameInfo.next[i][j];
    }
  }

  snapshot.score = getInfoEx()->gameInfo.score;
  snapshot.high_score = getInfoEx()->gameInfo.high_score;
  snapshot.level = getInfoEx()->gameInfo.level;
  snapshot.pause = getInfoEx()->gameInfo.pause;

  int y = getInfoEx()->currentFigure.y;
  int x = getInfoEx()->currentFigure.x;
  for (int i = 0; i < FIG_SIZE_H; i++) {
    for (int j = 0; j < FIG_SIZE_W; j++) {
      if (getInfoEx()->currentFigure.fig[i][j]) {
        snapshot.field[i + y][j + x] = getInfoEx()->currentFigure.fig[i][j];
      }
    }
  }

  timeSecondPoint = getCurrentTime();
  int speed = calculateSpeed(getInfoEx());
  getInfoEx()->gameInfo.speed = speed;
  if ((timeSecondPoint - timeFirstPoint > speed) &&
      !getInfoEx()->gameInfo.pause) {
    timeFirstPoint = timeSecondPoint;
    funcFSM(Down);
  }

  snapshot.speed = getInfoEx()->gameInfo.speed;

  return snapshot;  // return copy GameInfo_t
}

/**
 * @brief создает текущую фигуру
 * @param figure указатель на Figure_t
 */
void createCurrentFigure(Figure_t *figure) {
  int figures[7][5][5] = {FIG_O, FIG_I, FIG_Z, FIG_S, FIG_J, FIG_L, FIG_T};
  int range = 7;

  int r_1 = rand() % range;  // [0; range)

  for (int i = 0; i < FIG_SIZE_H; i++) {
    for (int j = 0; j < FIG_SIZE_W; j++) {
      figure->fig[i][j] = figures[r_1][i][j];
    }
  }

  figure->type = typeFigure(r_1);

  // start position
  figure->x = START_POS_FIG_X;
  figure->y = START_POS_FIG_Y;
}

/**
 * @brief определяет тип фигуры
 * @param number номер фигуры из списка
 * @return тип фигуры: 1 тип - 1 положение, 2 тип - 2 положения, 4 тип - 4
 * положения
 */

int typeFigure(int number) {
  int type = 0;
  switch (number) {
    case 0:
      type = 1;
      break;
    case 1:
    case 2:
    case 3:
      type = 2;
      break;
    case 4:
    case 5:
    case 6:
      type = 4;
      break;
    default:
      break;
  }
  return type;
}

/**
 * @brief определяет можно ли сместить фигуру
 * @param game - указатель на игровой статус
 * @param action - действие игрока
 * @return 1 - можно сместить, 0 - нельзя
 */
int canMove(GameInfoExtended_t *game, UserAction_t action) {
  int result = 1;

  int x = game->currentFigure.x;  // текущие координаты
  int y = game->currentFigure.y;

  switch (action) {
    case Left:
      x -= 1;
      break;
    case Right:
      x += 1;
      break;
    case Down:
      y += 1;
      break;
    default:
      break;
  }

  for (int i = 0; i < FIG_SIZE_H && result; i++) {
    for (int j = 0; j < FIG_SIZE_W && result; j++) {
      if (game->currentFigure.fig[i][j]) {
        int new_x = j + x;
        int new_y = i + y;

        if (new_x < 0 || new_x >= FIELD_W || new_y < 0 || new_y >= FIELD_H) {
          result = 0;
        }

        else if (game->gameInfo.field[new_y][new_x]) {
          result = 0;
        }
      }
    }
  }

  return result;
}

/**
 * @brief создает следующую фигуру
 * @param next указатель на двумерный массив
 * @return возвращает тип новой фигуры
 */
int createNextFigure(int **next) {
  int range = 7;
  int r_1 = rand() % range;  // [0; range)

  int figures[7][5][5] = {FIG_O, FIG_I, FIG_Z, FIG_S, FIG_J, FIG_L, FIG_T};

  for (int i = 0; i < FIG_SIZE_H; i++) {
    for (int j = 0; j < FIG_SIZE_W; j++) {
      next[i][j] = figures[r_1][i][j];
    }
  }

  return typeFigure(r_1);
}

/**
 * @brief копирует следующую фигуру в текущую
 * @param gameInfoEx указатель на игровой статус
 */
void copyNextToCurrent(GameInfoExtended_t *gameInfoEx) {
  for (int i = 0; i < FIG_SIZE_H; i++) {
    for (int j = 0; j < FIG_SIZE_W; j++) {
      gameInfoEx->currentFigure.fig[i][j] = gameInfoEx->gameInfo.next[i][j];
    }
  }
  gameInfoEx->currentFigure.x = START_POS_FIG_X;
  gameInfoEx->currentFigure.y = START_POS_FIG_Y;

  gameInfoEx->currentFigure.type = gameInfoEx->typeNextFigure;
}

/**
 * @brief осуществляет ротацию фигуры, если это возможно
 * @param game указатель на игровой статус
 */
void rotateFigure(GameInfoExtended_t *game) {
  switch (game->currentFigure.type) {
    case 1:
      break;
    case 2:
      rotateType_2(game);
      break;
    case 4:
      rotateType_4(game);
      break;
    default:
      break;
  }
}

/**
 * @brief осуществляет ротацию фигур 2 типа
 * @param game указатель на игровой статус
 */
void rotateType_2(GameInfoExtended_t *game) {
  int tmp[FIG_SIZE_H][FIG_SIZE_W] = {0};
  // фигура I горизонтальная
  {
    if (game->currentFigure.fig[2][0] == 1 &&
        game->currentFigure.fig[2][1] == 1 &&
        game->currentFigure.fig[2][2] == 1 &&
        game->currentFigure.fig[2][3] == 1) {
      // в вертикальное
      tmp[0][2] = 1;
      tmp[1][2] = 1;
      tmp[2][2] = 1;
      tmp[3][2] = 1;
    }

    // фигура I вертикальная
    if (game->currentFigure.fig[0][2] == 1 &&
        game->currentFigure.fig[1][2] == 1 &&
        game->currentFigure.fig[2][2] == 1 &&
        game->currentFigure.fig[3][2] == 1) {
      // в горизонтальное
      tmp[2][0] = 1;
      tmp[2][1] = 1;
      tmp[2][2] = 1;
      tmp[2][3] = 1;
    }

    // фигура Z горизонтальная
    if (game->currentFigure.fig[2][1] == 1 &&
        game->currentFigure.fig[2][2] == 1 &&
        game->currentFigure.fig[3][2] == 1 &&
        game->currentFigure.fig[3][3] == 1) {
      // в вертикальное
      tmp[1][3] = 1;
      tmp[2][2] = 1;
      tmp[2][3] = 1;
      tmp[3][2] = 1;
    }

    // фигура Z вертикальное
    if (game->currentFigure.fig[1][3] == 1 &&
        game->currentFigure.fig[2][2] == 1 &&
        game->currentFigure.fig[2][3] == 1 &&
        game->currentFigure.fig[3][2] == 1) {
      // в горизонтальное
      tmp[2][1] = 1;
      tmp[2][2] = 1;
      tmp[3][2] = 1;
      tmp[3][3] = 1;
    }

    // фигура S горизонтальное
    if (game->currentFigure.fig[2][2] == 1 &&
        game->currentFigure.fig[2][3] == 1 &&
        game->currentFigure.fig[3][1] == 1 &&
        game->currentFigure.fig[3][2] == 1) {
      // в вертикальное
      tmp[1][2] = 1;
      tmp[2][2] = 1;
      tmp[2][3] = 1;
      tmp[3][3] = 1;
    }

    // фигура S вертикальное
    if (game->currentFigure.fig[1][2] == 1 &&
        game->currentFigure.fig[2][2] == 1 &&
        game->currentFigure.fig[2][3] == 1 &&
        game->currentFigure.fig[3][3] == 1) {
      // в горизонтальное
      tmp[2][2] = 1;
      tmp[2][3] = 1;
      tmp[3][1] = 1;
      tmp[3][2] = 1;
    }
  }

  if (canRotate(game, tmp)) {
    for (int i = 0; i < FIG_SIZE_H; i++) {
      for (int j = 0; j < FIG_SIZE_W; j++) {
        game->currentFigure.fig[i][j] = tmp[i][j];
      }
    }
  }
}

/**
 * @brief осуществляет ротацию фигур 24типа
 * @param game указатель на игровой статус
 */
void rotateType_4(GameInfoExtended_t *game) {
  int tmp[FIG_SIZE_H][FIG_SIZE_W] = {0};
  for (int y = 0; y < FIG_SIZE_H; y++) {
    for (int x = 0; x < FIG_SIZE_W; x++) {
      tmp[x][FIG_SIZE_W - 1 - y] = game->currentFigure.fig[y][x];
    }
  }

  if (canRotate(game, tmp)) {
    for (int i = 0; i < FIG_SIZE_H; i++) {
      for (int j = 0; j < FIG_SIZE_W; j++) {
        game->currentFigure.fig[i][j] = tmp[i][j];
      }
    }
  }
}

/**
 * @brief определяет можно ли осуществить ротацию
 * @param game указатель на статус игры
 * @param tmp двумерный массив
 * @return 1 - можно, 2 - нельзя
 */
int canRotate(GameInfoExtended_t *game, int tmp[][5]) {
  int result = 1;

  int x = game->currentFigure.x;
  int y = game->currentFigure.y;

  for (int i = 0; i < FIG_SIZE_H; i++) {
    for (int j = 0; j < FIG_SIZE_W; j++) {
      if (tmp[i][j] == 1) {
        int new_x = j + x;
        int new_y = i + y;

        if (new_x < 0 || new_x >= FIELD_W || new_y < 0 || new_y >= FIELD_H) {
          result = 0;
        } else if (game->gameInfo.field[new_y][new_x]) {
          result = 0;
        }
      }
    }
  }

  return result;
}

/**
 * @brief убирает заполненный строки
 * @param field - указатель на игровое поле
 * @return возвращает количество удаленных строк
 */
int destroyRows(int **field) {
  int result = 0;
  int count = 0;

  for (int row = FIELD_H - 1; row > 0; row--) {
    if (isFullRow(field[row])) {
      count += delRow(field, row);
      row++;
    }
  }

  switch (count) {
    case 1:
      result = 100;
      break;
    case 2:
      result = 300;
      break;
    case 3:
      result = 700;
      break;
    case 4:
      result = 1500;
      break;
    default:
      break;
  }
  return result;
}

/**
 * @brief определяет заполнена ли строка
 * @param row номер строки
 * @return 1 - заполнена, 0 - нет
 */
int isFullRow(const int *row) {
  int result = 1;
  for (int col = 0; col < FIELD_W; col++)
    if (!row[col]) result = 0;
  return result;
}

/**
 * @brief удаляет строку и смещает верхние вниз
 * @param field поле
 * @param current_row номер текущей строки
 * @return возвращает 1
 */
int delRow(int **field, int current_row) {
  for (int i = current_row; i > 1; i--) {
    for (int j = 0; j < FIELD_W; j++) {
      field[i][j] = field[i - 1][j];
    }
  }
  return 1;
}

/**
 * @briefопределяет текущее время
 * @return текущее время в мс
 */
long long getCurrentTime() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (long long)(tv.tv_sec) * 1000 + (tv.tv_usec / 1000);
}

/**
 * @brief рассчитывает уровень в зависимости от набранных очков
 * @param gameInfoEx указатель на игровой статус
 * @return уровень
 */
int calculateLevel(GameInfoExtended_t *gameInfoEx) {
  int level = gameInfoEx->gameInfo.score / 600 + 1;
  if (level > 10) {
    level = 10;
  }
  return level;
}

/**
 * @brief рассчитывает скорость падения блоков
 * @param gameInfoEx указатель на статус игры
 * @return время задержки
 */
int calculateSpeed(GameInfoExtended_t *gameInfoEx) {
  return 1050 - gameInfoEx->gameInfo.level * 100;
}

/**
 * @brief включает/выключает паузу
 * @return 1 - пауза, 0 не пауза
 */
int pauseEnableDisable() {
  static int pause = 0;
  pause = 1 - pause;
  return pause;
}

/**
 * @brief очищает поле перед новой игрой
 * @param gameInfoEx указатель на игровой статус
 */
void clearField(GameInfoExtended_t *gameInfoEx) {
  for (int i = 0; i < FIELD_H; i++) {
    for (int j = 0; j < FIELD_W; j++) gameInfoEx->gameInfo.field[i][j] = 0;
  }
}

/**
 * @brief считывает рекордный балл
 * @return рекордный балл
 */
int readHighScore() {
  int result = 0;

  FILE *fp = fopen("score.txt", "r");
  if (fp != NULL) {
    fscanf(fp, "%d", &result);
    fclose(fp);
  }
  return result;
}

/**
 * @brief записывает наивысший балл
 * @param score наивсший балл
 */
void writeHighScore(int score) {
  FILE *fp = fopen("score.txt", "w+");
  if (fp != NULL) {
    int tmp = 0;
    fscanf(fp, "%d", &tmp);
    if (score > tmp) {
      fseek(fp, 0, SEEK_SET);
      fprintf(fp, "%d", score);
    }
    fclose(fp);
  }
}

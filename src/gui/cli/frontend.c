#include "../../inc/frontend.h"

/**
 * @brief отрисовка всего интерфейса
 */
void gameLoop() {
  initscr();
  nodelay(stdscr, TRUE);
  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);

  UserAction_t action = 0;
  WINDOW *gameField = newwin(GAME_FIELD_H, GAME_FIELD_W, 0, 0);
  WINDOW *infoPanel = newwin(INFO_FIELD_H, INFO_FIELD_W, 0, 24);

  while (action != Terminate) {
    GameInfo_t snapshot = {};
    box(gameField, 0, 0);
    box(infoPanel, 0, 0);
    keypad(gameField, 1);
    nodelay(gameField, 1);
    wrefresh(gameField);
    wrefresh(infoPanel);
    int ch = wgetch(gameField);

    if (ch != ERR) {
      switch (ch) {
        case KEY_LEFT:
          action = Left;
          userInput(action, false);
          break;
        case KEY_RIGHT:
          action = Right;
          userInput(action, false);
          break;
        case KEY_DOWN:
          action = Down;
          userInput(action, false);
          break;
        case KEY_UP:
          action = Up;
          userInput(action, false);
          break;
        case '\n':
          action = Start;
          userInput(action, false);
          break;
        case 'P':
        case 'p':
          action = Pause;
          userInput(action, false);
          break;
        case ' ':
          action = Action;
          userInput(action, false);
          break;
        case 'Q':
        case 'q':
          action = Terminate;
          break;
        default:
          break;
      }
    }

    if (!snapshot.pause) snapshot = updateCurrentState();

    printGameField(gameField, snapshot.field);
    printInfo(infoPanel, snapshot);
    wrefresh(gameField);
    wrefresh(infoPanel);
    werase(gameField);
    werase(infoPanel);
    napms(50);

    if (action == Terminate) userInput(action, false);
  }
  delwin(gameField);
  delwin(infoPanel);
}

/**
 * @brief отрисовка игрового поля
 * @param win указатель на окно
 * @param field указатель на игровое поле
 */
void printGameField(WINDOW *win, int **field) {
  for (int i = 0; i < FIELD_H; i++) {
    for (int j = 0; j < FIELD_W; j++) {
      if (field[i][j] == 1) {
        wattron(win, COLOR_PAIR(field[i][j]));
        mvwaddch(win, i + 1, j * 2 + 1, ACS_CKBOARD);
        mvwaddch(win, i + 1, j * 2 + 2, ACS_CKBOARD);
        wattroff(win, COLOR_PAIR(field[i][j]));
      }
    }
  }

  for (int i = 0; i < FIELD_H; i++) {
    for (int j = 0; j < FIELD_W; j++) {
      if (field[i][j] == 2) {
        mvwprintw(win, 10, 5, "GAME OVER");
        mvwprintw(win, 11, 4, "Press ENTER");
        break;
      }
    }
  }
}

/**
 * @brief отрисовка параметров игры
 * @param win указатель на окно
 * @param snapshot текущий снимок игры
 */
void printInfo(WINDOW *win, GameInfo_t snapshot) {
  for (int i = 0; i < FIG_SIZE_H; i++) {
    for (int j = 0; j < FIG_SIZE_W; j++) {
      if (snapshot.next[i][j] == 1) {
        wattron(win, COLOR_PAIR(snapshot.next[i][j]));
        mvwaddch(win, i, j * 2 + 5, ACS_CKBOARD);
        mvwaddch(win, i, j * 2 + 6, ACS_CKBOARD);
        wattroff(win, COLOR_PAIR(snapshot.next[i][j]));
      }
    }
  }

  wmove(win, 5, 3);
  wprintw(win, "High score = %d", snapshot.high_score);
  wmove(win, 6, 3);
  wprintw(win, "Score = %d", snapshot.score);
  wmove(win, 7, 3);
  wprintw(win, "Level = %d", snapshot.level);
  wmove(win, 8, 3);

  wmove(win, 11, 4);
  wprintw(win, "Control keys");
  wmove(win, 13, 2);
  wprintw(win, "ENTER - start game");
  wmove(win, 14, 2);
  wprintw(win, "P - pause");
  wmove(win, 15, 2);
  wprintw(win, "Q - exit");
  wmove(win, 16, 2);
  wprintw(win, "LEFT - on left");
  wmove(win, 17, 2);
  wprintw(win, "RIGHT - on right");
  wmove(win, 18, 2);
  wprintw(win, "Down - on floor");
  wmove(win, 19, 2);
  wprintw(win, "SPACE - rotate");
}

#ifndef OBJECTS_H
#define OBJECTS_H

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
  } GameInfo_t;

typedef enum {
  STATE_START,
  STATE_SPAWN,
  STATE_MOVING,
  STATE_SHIFTING,
  STATE_ATTACHING,
  STATE_GAME_OVER
} GameState_t;

typedef struct {
  int fig[5][5];
  int x, y;
  int type;
} Figure_t;

typedef struct {
  Figure_t currentFigure;
  GameInfo_t gameInfo;
  GameState_t state;
  int timeInterval;
  int typeNextFigure;
} GameInfoExtended_t;

#endif
#ifndef DEFINES_H
#define DEFINES_H

#define GAME_FIELD_H 22
#define GAME_FIELD_W 22

#define INFO_FIELD_H 22
#define INFO_FIELD_W 22

#define FIELD_H 20
#define FIELD_W 10

#define FIG_SIZE_H 5
#define FIG_SIZE_W 5

#define START_POS_FIG_X 3
#define START_POS_FIG_Y -2

#define FIG_O                                                             \
  {                                                                       \
    {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 1, 1, 0, 0}, {0, 1, 1, 0, 0}, { \
      0, 0, 0, 0, 0                                                       \
    }                                                                     \
  }  // O, type = 1
#define FIG_I                                                             \
  {                                                                       \
    {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {1, 1, 1, 1, 0}, {0, 0, 0, 0, 0}, { \
      0, 0, 0, 0, 0                                                       \
    }                                                                     \
  }  // I, type = 2
#define FIG_Z                                                             \
  {                                                                       \
    {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 1, 1, 0, 0}, {0, 0, 1, 1, 0}, { \
      0, 0, 0, 0, 0                                                       \
    }                                                                     \
  }  // Z, type = 2
#define FIG_S                                                             \
  {                                                                       \
    {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 1, 1, 0}, {0, 1, 1, 0, 0}, { \
      0, 0, 0, 0, 0                                                       \
    }                                                                     \
  }  // S, type = 2
#define FIG_J                                                             \
  {                                                                       \
    {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 1, 1, 1, 0}, {0, 0, 0, 1, 0}, { \
      0, 0, 0, 0, 0                                                       \
    }                                                                     \
  }  // J, type = 4
#define FIG_L                                                             \
  {                                                                       \
    {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 1, 1, 1, 0}, {0, 1, 0, 0, 0}, { \
      0, 0, 0, 0, 0                                                       \
    }                                                                     \
  }  // L, type = 4
#define FIG_T                                                             \
  {                                                                       \
    {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 1, 1, 1, 0}, {0, 0, 1, 0, 0}, { \
      0, 0, 0, 0, 0                                                       \
    }                                                                     \
  }  // T, type = 4

#endif

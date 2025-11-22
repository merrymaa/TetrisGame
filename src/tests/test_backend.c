
#include "tests.h"

START_TEST(test_1_updateCurrentState) {
  GameInfo_t gameInfo = updateCurrentState();

  ck_assert_ptr_nonnull(gameInfo.field);
  ck_assert_ptr_nonnull(gameInfo.next);
  ck_assert_int_eq(gameInfo.score, 0);
  ck_assert_int_eq(gameInfo.high_score, 0);
  ck_assert_int_eq(gameInfo.level, 0);
  ck_assert_int_eq(gameInfo.pause, 0);
}
END_TEST

START_TEST(test_2_Start) {
  funcFSM(Start);
  GameInfoExtended_t *game = getInfoEx();

  ck_assert_ptr_nonnull(game->gameInfo.field);
  ck_assert_ptr_nonnull(game->gameInfo.next);
  ck_assert_int_eq(game->gameInfo.score, 0);
  ck_assert_int_eq(game->gameInfo.high_score, readHighScore());
  ck_assert_int_eq(game->gameInfo.level, 1);
  ck_assert_int_eq(game->gameInfo.pause, 0);
  ck_assert_int_eq(game->state, STATE_SPAWN);
}
END_TEST

START_TEST(test_3_State_Spawn) {
  funcFSM(Start);
  GameInfoExtended_t *game = getInfoEx();
  funcFSM(Down);

  ck_assert_ptr_nonnull(game->gameInfo.field);
  ck_assert_ptr_nonnull(game->gameInfo.next);
  ck_assert_int_eq(game->gameInfo.score, 0);
  ck_assert_int_eq(game->gameInfo.high_score, readHighScore());
  ck_assert_int_eq(game->gameInfo.level, 1);
  ck_assert_int_eq(game->gameInfo.pause, 0);
  ck_assert_int_eq(game->state, STATE_MOVING);
  // funcFSM(Terminate);
}
END_TEST

START_TEST(test_4_State_Moving) {
  funcFSM(Start);
  GameInfoExtended_t *game = getInfoEx();
  funcFSM(Down);
  funcFSM(Down);

  ck_assert_ptr_nonnull(game->gameInfo.field);
  ck_assert_ptr_nonnull(game->gameInfo.next);
  ck_assert_int_eq(game->gameInfo.score, 0);
  ck_assert_int_eq(game->gameInfo.high_score, readHighScore());
  ck_assert_int_eq(game->gameInfo.level, 1);
  ck_assert_int_eq(game->gameInfo.pause, 0);
  ck_assert_int_eq(game->currentFigure.x, 3);
  ck_assert_int_eq(game->currentFigure.y, 1);
  ck_assert_int_eq(game->state, STATE_MOVING);
  // funcFSM(Terminate);
}
END_TEST

START_TEST(test_5_Left) {
  funcFSM(Start);
  GameInfoExtended_t *game = getInfoEx();
  funcFSM(Left);

  ck_assert_ptr_nonnull(game->gameInfo.field);
  ck_assert_ptr_nonnull(game->gameInfo.next);
  ck_assert_int_eq(game->gameInfo.score, 0);
  ck_assert_int_eq(game->gameInfo.high_score, readHighScore());
  ck_assert_int_eq(game->gameInfo.level, 1);
  ck_assert_int_eq(game->gameInfo.pause, 0);
  ck_assert_int_eq(game->currentFigure.x, 2);
  ck_assert_int_eq(game->currentFigure.y, 1);
  ck_assert_int_eq(game->state, STATE_MOVING);
  // funcFSM(Terminate);
}
END_TEST

START_TEST(test_6_Right) {
  funcFSM(Start);
  GameInfoExtended_t *game = getInfoEx();
  funcFSM(Right);

  ck_assert_ptr_nonnull(game->gameInfo.field);
  ck_assert_ptr_nonnull(game->gameInfo.next);
  ck_assert_int_eq(game->gameInfo.score, 0);
  ck_assert_int_eq(game->gameInfo.high_score, readHighScore());
  ck_assert_int_eq(game->gameInfo.level, 1);
  ck_assert_int_eq(game->gameInfo.pause, 0);
  ck_assert_int_eq(game->currentFigure.x, 3);
  ck_assert_int_eq(game->currentFigure.y, 1);
  ck_assert_int_eq(game->state, STATE_MOVING);
  // funcFSM(Terminate);
}
END_TEST

START_TEST(test_7_Rotate) {
  funcFSM(Start);
  funcFSM(Down);
  GameInfoExtended_t *game = getInfoEx();

  funcFSM(Action);

  ck_assert_ptr_nonnull(game->gameInfo.field);
  ck_assert_ptr_nonnull(game->gameInfo.next);
  ck_assert_int_eq(game->gameInfo.score, 0);
  ck_assert_int_eq(game->gameInfo.high_score, readHighScore());
  ck_assert_int_eq(game->gameInfo.level, 1);
  ck_assert_int_eq(game->gameInfo.pause, 0);
  ck_assert_int_eq(game->currentFigure.x, 3);
  ck_assert_int_eq(game->currentFigure.y, 2);
  ck_assert_int_eq(game->state, STATE_MOVING);
  // ck_assert_ptr_ne();
  // funcFSM(Terminate);
}
END_TEST

START_TEST(test_8_Pause) {
  GameInfoExtended_t *game = getInfoEx();
  funcFSM(Pause);

  ck_assert_ptr_nonnull(game->gameInfo.field);
  ck_assert_ptr_nonnull(game->gameInfo.next);
  ck_assert_int_eq(game->gameInfo.score, 0);
  ck_assert_int_eq(game->gameInfo.high_score, readHighScore());
  ck_assert_int_eq(game->gameInfo.level, 1);
  ck_assert_int_eq(game->gameInfo.pause, 1);
  ck_assert_int_eq(game->currentFigure.x, 3);
  ck_assert_int_eq(game->currentFigure.y, 2);
  ck_assert_int_eq(game->state, STATE_MOVING);
  // funcFSM(Terminate);
}
END_TEST

START_TEST(test_9_userInput) {
  GameInfoExtended_t *game = getInfoEx();
  userInput(Down, false);

  ck_assert_ptr_nonnull(game->gameInfo.field);
  ck_assert_ptr_nonnull(game->gameInfo.next);
  ck_assert_int_eq(game->gameInfo.score, 0);
  ck_assert_int_eq(game->gameInfo.high_score, readHighScore());
  ck_assert_int_eq(game->gameInfo.level, 1);
  ck_assert_int_eq(game->gameInfo.pause, 1);
  ck_assert_int_eq(game->currentFigure.x, 3);
  ck_assert_int_eq(game->currentFigure.y, 2);
  ck_assert_int_eq(game->state, STATE_MOVING);
}
END_TEST

START_TEST(test_10_stateAttaching) {
  GameInfoExtended_t *game = getInfoEx();
  game->state = STATE_ATTACHING;

  funcFSM(Down);

  ck_assert_int_eq(game->state, 4);
}
END_TEST

START_TEST(test_11_GameOver) {
  GameInfoExtended_t *game = getInfoEx();
  game->state = STATE_GAME_OVER;
  funcFSM(Down);
  ck_assert_int_eq(game->state, 0);
}
END_TEST

START_TEST(test_12_calculateLevel) {
  GameInfoExtended_t *game = getInfoEx();
  game->gameInfo.score = 20000;
  int level = calculateLevel(game);

  ck_assert_int_eq(level, 10);
}
END_TEST

START_TEST(test_13_destroyRows) {
  GameInfoExtended_t *game = getInfoEx();

  for (int i = 18; i > 15; i--) {
    for (int j = 0; j < 10; j++) {
      game->gameInfo.field[i][j] = 1;
    }
  }
  int result = destroyRows(game->gameInfo.field);

  ck_assert_int_eq(result, 700);
}
END_TEST

START_TEST(test_14_destroyRows) {
  GameInfoExtended_t *game = getInfoEx();

  for (int i = 18; i > 16; i--) {
    for (int j = 0; j < 10; j++) {
      game->gameInfo.field[i][j] = 1;
    }
  }
  int result = destroyRows(game->gameInfo.field);

  ck_assert_int_eq(result, 300);
}
END_TEST

START_TEST(test_15_destroyRows) {
  GameInfoExtended_t *game = getInfoEx();

  for (int i = 18; i > 17; i--) {
    for (int j = 0; j < 10; j++) {
      game->gameInfo.field[i][j] = 1;
    }
  }
  int result = destroyRows(game->gameInfo.field);

  ck_assert_int_eq(result, 100);
}
END_TEST

START_TEST(test_16_destroyRows) {
  GameInfoExtended_t *game = getInfoEx();

  for (int i = 18; i > 14; i--) {
    for (int j = 0; j < 10; j++) {
      game->gameInfo.field[i][j] = 1;
    }
  }
  int result = destroyRows(game->gameInfo.field);

  ck_assert_int_eq(result, 1500);
}
END_TEST

START_TEST(test_17_Rotate) {
  GameInfoExtended_t *game = getInfoEx();

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) game->currentFigure.fig[i][j] = 0;
  }
  game->currentFigure.fig[2][0] = 1;  // fig I horizont
  game->currentFigure.fig[2][1] = 1;
  game->currentFigure.fig[2][2] = 1;
  game->currentFigure.fig[2][3] = 1;
  game->currentFigure.y = 5;
  game->state = STATE_MOVING;
  game->currentFigure.type = 2;
  rotateFigure(game);

  ck_assert_int_eq(game->currentFigure.fig[0][2], 1);
  ck_assert_int_eq(game->currentFigure.fig[1][2], 1);
  ck_assert_int_eq(game->currentFigure.fig[2][2], 1);
  ck_assert_int_eq(game->currentFigure.fig[3][2], 1);
}
END_TEST

START_TEST(test_18_Rotate) {
  GameInfoExtended_t *game = getInfoEx();

  rotateFigure(game);
  ck_assert_int_eq(game->currentFigure.fig[2][0], 1);
  ck_assert_int_eq(game->currentFigure.fig[2][1], 1);
  ck_assert_int_eq(game->currentFigure.fig[2][2], 1);
  ck_assert_int_eq(game->currentFigure.fig[2][3], 1);
}
END_TEST

START_TEST(test_19_Rotate) {
  GameInfoExtended_t *game = getInfoEx();

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) game->currentFigure.fig[i][j] = 0;
  }
  game->currentFigure.fig[1][3] = 1;  // fig Z vertical
  game->currentFigure.fig[2][2] = 1;
  game->currentFigure.fig[2][3] = 1;
  game->currentFigure.fig[3][2] = 1;
  game->currentFigure.y = 5;
  game->state = STATE_MOVING;
  game->currentFigure.type = 2;
  rotateFigure(game);

  ck_assert_int_eq(game->currentFigure.fig[2][1], 1);
  ck_assert_int_eq(game->currentFigure.fig[2][2], 1);
  ck_assert_int_eq(game->currentFigure.fig[3][2], 1);
  ck_assert_int_eq(game->currentFigure.fig[3][3], 1);
}
END_TEST

START_TEST(test_20_Rotate) {
  GameInfoExtended_t *game = getInfoEx();

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) game->currentFigure.fig[i][j] = 0;
  }
  game->currentFigure.fig[2][1] = 1;  // fig Z horizont
  game->currentFigure.fig[2][2] = 1;
  game->currentFigure.fig[3][2] = 1;
  game->currentFigure.fig[3][3] = 1;

  game->currentFigure.y = 5;
  game->state = STATE_MOVING;
  game->currentFigure.type = 2;
  rotateFigure(game);

  ck_assert_int_eq(game->currentFigure.fig[1][3], 1);
  ck_assert_int_eq(game->currentFigure.fig[2][2], 1);
  ck_assert_int_eq(game->currentFigure.fig[2][3], 1);
  ck_assert_int_eq(game->currentFigure.fig[3][2], 1);
}
END_TEST

START_TEST(test_21_Rotate) {
  GameInfoExtended_t *game = getInfoEx();

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) game->currentFigure.fig[i][j] = 0;
  }
  game->currentFigure.fig[1][3] = 1;  // fig Z vertical
  game->currentFigure.fig[2][2] = 1;
  game->currentFigure.fig[2][3] = 1;
  game->currentFigure.fig[3][2] = 1;

  game->currentFigure.y = 5;
  game->state = STATE_MOVING;
  game->currentFigure.type = 4;
  rotateFigure(game);

  ck_assert_int_eq(game->currentFigure.fig[2][1], 1);
  ck_assert_int_eq(game->currentFigure.fig[2][2], 1);
  ck_assert_int_eq(game->currentFigure.fig[3][2], 1);
  ck_assert_int_eq(game->currentFigure.fig[3][3], 1);
}
END_TEST

START_TEST(test_22_Rotate) {
  GameInfoExtended_t *game = getInfoEx();

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) game->currentFigure.fig[i][j] = 0;
  }
  game->currentFigure.fig[1][2] = 1;  // fig S vertical
  game->currentFigure.fig[2][2] = 1;
  game->currentFigure.fig[2][3] = 1;
  game->currentFigure.fig[3][3] = 1;

  game->currentFigure.y = 5;
  game->state = STATE_MOVING;
  game->currentFigure.type = 4;
  rotateFigure(game);

  ck_assert_int_eq(game->currentFigure.fig[2][2], 1);
  ck_assert_int_eq(game->currentFigure.fig[2][3], 1);
  ck_assert_int_eq(game->currentFigure.fig[3][1], 1);
  ck_assert_int_eq(game->currentFigure.fig[3][2], 1);
}
END_TEST

START_TEST(test_23_Rotate) {
  GameInfoExtended_t *game = getInfoEx();

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) game->currentFigure.fig[i][j] = 0;
  }
  game->currentFigure.fig[2][2] = 1;  // fig S horizont
  game->currentFigure.fig[2][3] = 1;
  game->currentFigure.fig[3][1] = 1;
  game->currentFigure.fig[3][2] = 1;

  game->currentFigure.y = 5;
  game->state = STATE_MOVING;
  game->currentFigure.type = 2;
  rotateFigure(game);

  ck_assert_int_eq(game->currentFigure.fig[1][2], 1);
  ck_assert_int_eq(game->currentFigure.fig[2][2], 1);
  ck_assert_int_eq(game->currentFigure.fig[2][3], 1);
  ck_assert_int_eq(game->currentFigure.fig[3][3], 1);
}
END_TEST

START_TEST(test_24_Rotate) {
  GameInfoExtended_t *game = getInfoEx();

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) game->currentFigure.fig[i][j] = 0;
  }
  game->currentFigure.fig[1][2] = 1;  // fig S horizont
  game->currentFigure.fig[2][2] = 1;
  game->currentFigure.fig[2][3] = 1;
  game->currentFigure.fig[3][3] = 1;

  game->currentFigure.y = 5;
  game->state = STATE_MOVING;
  game->currentFigure.type = 2;
  rotateFigure(game);

  ck_assert_int_eq(game->currentFigure.fig[2][2], 1);
  ck_assert_int_eq(game->currentFigure.fig[2][3], 1);
  ck_assert_int_eq(game->currentFigure.fig[3][1], 1);
  ck_assert_int_eq(game->currentFigure.fig[3][2], 1);
}
END_TEST

START_TEST(test_25_Attaching) {
  GameInfoExtended_t *game = getInfoEx();
  game->currentFigure.y = 16;
  game->state = STATE_ATTACHING;
  funcFSM(Down);
  ck_assert_int_eq(game->state, STATE_SPAWN);
}
END_TEST

START_TEST(test_Terminate) {
  GameInfoExtended_t *game = getInfoEx();
  funcFSM(Terminate);
  ck_assert_int_eq(game->gameInfo.pause, 1);
}
END_TEST

Suite *test_backend() {
  Suite *s = suite_create("\033[33m TESTS BACKEND \033[0m");
  TCase *tc = tcase_create("\033[31m tests backend \033[0m");

  tcase_add_test(tc, test_1_updateCurrentState);
  tcase_add_test(tc, test_2_Start);
  tcase_add_test(tc, test_3_State_Spawn);
  tcase_add_test(tc, test_4_State_Moving);
  tcase_add_test(tc, test_5_Left);
  tcase_add_test(tc, test_6_Right);
  tcase_add_test(tc, test_7_Rotate);
  tcase_add_test(tc, test_8_Pause);
  tcase_add_test(tc, test_9_userInput);
  tcase_add_test(tc, test_10_stateAttaching);
  tcase_add_test(tc, test_11_GameOver);
  tcase_add_test(tc, test_12_calculateLevel);
  tcase_add_test(tc, test_13_destroyRows);
  tcase_add_test(tc, test_14_destroyRows);
  tcase_add_test(tc, test_15_destroyRows);
  tcase_add_test(tc, test_16_destroyRows);
  tcase_add_test(tc, test_17_Rotate);
  tcase_add_test(tc, test_18_Rotate);
  tcase_add_test(tc, test_19_Rotate);
  tcase_add_test(tc, test_20_Rotate);
  tcase_add_test(tc, test_21_Rotate);
  tcase_add_test(tc, test_22_Rotate);
  tcase_add_test(tc, test_23_Rotate);
  tcase_add_test(tc, test_24_Rotate);
  tcase_add_test(tc, test_25_Attaching);
  tcase_add_test(tc, test_Terminate);

  suite_add_tcase(s, tc);
  return s;
}
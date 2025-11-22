#include "tests.h"

int main() {
  Suite *tests[] = {test_backend(), NULL};

  for (int i = 0; tests[i] != NULL; i++) {
    SRunner *sr = srunner_create(tests[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    srunner_free(sr);
  }

  return 0;
}

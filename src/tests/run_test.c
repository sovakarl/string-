#include "test.h"

int main(void) {
  int fc = 1;
  runTest(s21_sprintf_suite(), &fc);
  runTest(s21_twenty_func_suite(), &fc);
  runTest(s21_sharp_suite(), &fc);
  return fc;
}

void runTest(Suite *suit, int *fc) {
  SRunner *sr = srunner_create(suit);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  int f = srunner_ntests_failed(sr);
  if (*fc != 0) *fc = f;
  srunner_free(sr);
}
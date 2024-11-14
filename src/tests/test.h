#ifndef SRC_TESTS_H
#define SRC_TESTS_H

#include <check.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>


#include "../s21_string.h"

Suite *s21_sprintf_suite();
Suite *s21_twenty_func_suite();
Suite *s21_sharp_suite();

void runTest(Suite *suit, int *fc);

#endif  //  SRC_TESTS_H

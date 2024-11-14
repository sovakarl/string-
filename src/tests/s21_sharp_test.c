#include "test.h"

START_TEST(sharp_check) {
  char str[15] = "ooOaaAAmm";
  char str1[15] = "OOOAAAAMM";

  char *ptr1 = s21_to_upper(str);
  ck_assert_str_eq(str1, ptr1);

  char str2[15] = "OOOAAAAMM";
  char str3[15] = "oooaaaamm";

  char *ptr2 = s21_to_lower(str2);
  ck_assert_str_eq(str3, ptr2);

  char str4[15] = "ogOGogo";
  char str5[15] = "mda";
  char str6[15] = "ogOmdaGogo";
  char str7[15] = "oaoamM";
  char str8[5] = "ok";
  char str9[15] = "oaoamMok";

  char *ptr3 = s21_insert(str4, str5, 3);
  ck_assert_str_eq(ptr3, str6);

  char *ptr4 = s21_insert(str7, str8, 6);
  ck_assert_str_eq(ptr4, str9);

  char str10[15] = "yyya ne loxxxx";
  char str11[5] = "yx";
  char str12[15] = "a ne lo";
  char str13[15] = "yyya ne loxxxx";
  char str15[15] = "yanelox";
  char str16[15] = " ne ";

  char *ptr5 = s21_trim(str10, str11);
  ck_assert_str_eq(ptr5, str12);

  char *ptr6 = s21_trim(str13, str15);
  ck_assert_str_eq(ptr6, str16);
}
END_TEST

Suite *s21_sharp_suite() {
  Suite *s = suite_create("sharp_suite");
  TCase *tc = tcase_create("sharp_test");
  tcase_add_test(tc, sharp_check);
  suite_add_tcase(s, tc);
  return s;
}
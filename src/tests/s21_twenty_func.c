#include "test.h"

START_TEST(twenty_func_check) {
  char *str = NULL;
  char *str1 = NULL;
  char src[15] = "1234567890";
  char dst[15] = "1234567890";

  str = s21_memchr(src, '4', 10);
  str1 = memchr(src, '4', 10);
  ck_assert_ptr_eq(str, str1);

  char src1[15] = "";
  char dst1[15] = "";
  str = NULL;
  str1 = NULL;
  s21_memcpy(dst, src1, 10);
  memcpy(dst, dst1, 10);
  ck_assert_str_eq(dst1, src1);

  char src3[15] = "1234567890";
  char dst3[15] = "1234567890";
  memset(src3, '1', 10);
  s21_memset(dst3, '1', 10);
  ck_assert_str_eq(dst3, src3);

  // char src4[15] = "1234567890";
  // char dst4[15] = "1234567890";
  // char plus[10] = "333";
  // strcat(src4, plus);
  // s21_strcat(dst4, plus);
  // ck_assert_str_eq(dst4, src4);

  char src5[15] = "1234567890";
  char dst5[15] = "1234567890";
  char plus1[10] = "333";
  strncat(src5, plus1, 2);
  s21_strncat(dst5, plus1, 2);
  ck_assert_str_eq(dst5, src5);

  char dst6[15] = "1234567890";
  char ch = '7';
  char *qwe;
  char *qwe1;
  qwe = s21_strchr(dst6, ch);
  qwe1 = strchr(dst6, ch);
  ck_assert_ptr_eq(qwe, qwe1);

  char src8[15] = "1234567890";
  char dst8[15] = "1234567890";

  int eq3 = s21_strncmp(src8, dst8, 5);
  int eq4 = strncmp(src8, dst8, 5);
  ck_assert_int_eq(eq3, eq4);

  //   char str7[16] = "abc";
  //   char str8[16] = "qwe";
  //   char str9[16] = "qwe";
  //   s21_strcpy(str8, str7);
  //   strcpy(str9, str7);
  //   ck_assert_str_eq(str8, str9);

  //   char srcq[] = "Floppa!!!";
  //   char resq[5 + 15] = "";
  //   char expected1[5 + 15] = "";
  //   s21_strcpy(resq, srcq);
  //   strcpy(expected1, srcq);
  //   ck_assert_str_eq(resq, expected1);

  //   char src32[] = "";
  //   char res23[5 + 15] = "";
  //   char expected2[5 + 15] = "";
  //   s21_strcpy(res23, src32);
  //   strcpy(expected2, src32);
  //   ck_assert_str_eq(res23, expected2);

  s21_size_t n2 = 5;
  char b2[1024] = "1111111111";
  char b22[1024] = "1111111111";
  char str_2_2[1024] = "12345\0006789";
  ck_assert_pstr_eq(strncpy(b2, str_2_2, n2), s21_strncpy(b22, str_2_2, n2));

  s21_size_t n1 = 3;
  char b1[1024] = "";
  char b11[1024] = "";
  char str_1_2[1024] = "SPARTAK THE BEST!";
  ck_assert_pstr_eq(memcpy(b1, str_1_2, n1), s21_memcpy(b11, str_1_2, n1));

  char b123[1024] = "";
  char str_1_2_3[1024] = "SPARTAK THE BEST!";
  ck_assert_int_eq(memcmp(b123, str_1_2_3, n2),
                   s21_memcmp(b123, str_1_2_3, n2));

  ck_assert_pstr_eq(s21_strerror(1), strerror(1));

  char st3[] = {'q', 'r', 's', 't', 'w', 's', 'a', 's', '\0'};
  ck_assert_int_eq(strcspn(st3, "zx"), s21_strcspn(st3, "zx"));

  char sr1c[] = "gora";
  char re1s[] = "";
  ck_assert_int_eq(s21_strcspn(re1s, sr1c), strcspn(re1s, sr1c));

  char sr[] = "this_is_a_";
  ck_assert_pstr_eq(strpbrk(sr, "369"), s21_strpbrk(sr, "369"));

  char sr2[] = "john.smith@mic\0rosoft.com";
  ck_assert_pstr_eq(strpbrk(sr2, "fzx"), s21_strpbrk(sr2, "fzx"));

  char str3[] = {'q', 'r', 's', 't', 'w', 's', 'a', 's', '\0'};
  ck_assert_pstr_eq(strpbrk(str3, "saq"), s21_strpbrk(str3, "saq"));

  char s11[] = "";
  char str2 = '\0';
  ck_assert_pstr_eq(s21_strrchr(s11, str2), strrchr(s11, str2));

  char str123[] = "";
  char str22 = 'f';
  ck_assert_pstr_eq(s21_strrchr(str123, str22), strrchr(str123, str22));

  char tr1[] = "poki doki";
  char tr2 = 'o';
  ck_assert_pstr_eq(s21_strrchr(tr1, tr2), strrchr(tr1, tr2));

  {
    char haystack[] = "";
    char needle[] = "";
    ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
  }

  {
    char haystack[] = "";
    char needle[] = "123546 qwerty";
    ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
  }

  {
    char haystack[] = "123546 qwerty";
    char needle[] = "";
    ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
  }

  {
    char haystack[] = "You are toxic!";
    char needle[] = "toxic";
    ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
  }

  {
    char haystack[] = "mama mila ramu";
    char needle[] = "mila";
    ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
  }

  {
    char haystack[] = "mila";
    char needle[] = "mama mila ramu";
    ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
  }

  {
    char haystack[] = "mama mila ramu";
    char needle[] = "papa";
    ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
  }

  char test1[50] = "mama mila ramu";
  char test2[50] = "mama mila ramu";
  char test3[5] = " ,.";
  char *resS21 = s21_strtok(test1, test3);
  char *res = strtok(test2, test3);
  ck_assert_pstr_eq(resS21, res);
  while (res != s21_NULL && resS21 != s21_NULL) {
    resS21 = s21_strtok(s21_NULL, test3);
    res = strtok(s21_NULL, test3);
    ck_assert_pstr_eq(resS21, res);
  }
}
END_TEST

Suite *s21_twenty_func_suite() {
  Suite *s = suite_create("twenty_func_suite");
  TCase *tc = tcase_create("twenty_func_test");
  tcase_add_test(tc, twenty_func_check);
  suite_add_tcase(s, tc);
  return s;
}

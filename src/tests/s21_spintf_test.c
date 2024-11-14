#include "test.h"

START_TEST(sprintf_check) {
  char buff1[10000];
  char buff2[10000];
  char *buff3 =
      "%+12.1s %-3.3u %- 3.3i %+- 3.3f %+- 3.3d %3.3ld %3.3hd %3.3lu %3.3hu ";
  int alfa = -10000;
  char *ps = "qwerty";
  float beta = 1745.123311;
  int two = -017234234234;
  int three = -0121231233;

  ck_assert_int_eq(
      sprintf(buff1, buff3, ps, alfa, alfa, beta, alfa, two, three, two, alfa),
      s21_sprintf(buff2, buff3, ps, alfa, alfa, beta, alfa, two, three, two,
                  alfa));
  ck_assert_pstr_eq(buff1, buff2);

  char str1cch[100];
  char str2cch[100];
  char *str3cch = "%+- 010.0u test: %+ 18.1i %-+ 9.7s";
  int valcch = 012;
  int val2cch = 017;
  char *numsssq = "qwerty";
  ck_assert_int_eq(sprintf(str1cch, str3cch, valcch, val2cch, numsssq),
                   s21_sprintf(str2cch, str3cch, valcch, val2cch, numsssq));
  ck_assert_pstr_eq(str1cch, str2cch);

  char str1sss[400];
  char str2sss[400];
  char *str3sss = "test: %-+18.0s\ntest: % +-10.s\ntest: %- 25.0s!";
  char *numsss = "qwerty";
  ck_assert_int_eq(sprintf(str1sss, str3sss, numsss, numsss, numsss),
                   s21_sprintf(str2sss, str3sss, numsss, numsss, numsss));
  ck_assert_pstr_eq(str1sss, str2sss);

  char str1rrrs[400];
  char str2rrrs[400];
  char *str3rrrs = "test: %+- 010.2f!\ntest: %- 025.7f\ntest: %-+ 18.4f!";
  double numrrrs = 7648938790.756589;
  ck_assert_int_eq(sprintf(str1rrrs, str3rrrs, numrrrs, numrrrs, numrrrs),
                   s21_sprintf(str2rrrs, str3rrrs, numrrrs, numrrrs, numrrrs));
  ck_assert_pstr_eq(str1rrrs, str2rrrs);

  char str1ee[400];
  char str2ee[400];
  char *str3ee = "test: %10.4f\ntest: %- 9.5f!";
  double numee = -76.756589;
  ck_assert_int_eq(sprintf(str1ee, str3ee, numee, numee, numee),
                   s21_sprintf(str2ee, str3ee, numee, numee, numee));
  ck_assert_pstr_eq(str1ee, str2ee);

  char str1xx[200];
  char str2xx[200];
  char *str3xx = "%f TEST %.f TEST %4.0f TEST %4.f TEST %-+ 5.10f!";
  double num = 76.756589367;
  ck_assert_int_eq(sprintf(str1xx, str3xx, num, num, num, num, num),
                   s21_sprintf(str2xx, str3xx, num, num, num, num, num));
  ck_assert_pstr_eq(str1xx, str2xx);

  char str1cc[100];
  char str2cc[100];
  char *str3cc = "%+- 04.0d test: %- 05.7d";
  int valcc = -76;
  int val2cc = -76;
  sprintf(str1cc, str3cc, valcc, val2cc),
      s21_sprintf(str2cc, str3cc, valcc, val2cc);
  ck_assert_pstr_eq(str1cc, str2cc);

  char str144[100];
  char str244[100];
  char *str344 = "%s %s %s %% %d";
  char *val44 = "This";
  char *val244 = "\0";
  int val344 = 65;
  char *val444 = "string";
  ck_assert_int_eq(sprintf(str144, str344, val44, val244, val444, val344),
                   s21_sprintf(str244, str344, val44, val244, val444, val344));
  ck_assert_pstr_eq(str144, str244);

  char str155[200];
  char str255[200];
  char *str355 = "%0s Test %0.s Test %5.0s TEST %0s GOD %.s";
  char *val55 = "WHAT IS THIS";
  char *val255 = "i don't care anymore, really";
  char *val355 = "PPAP";
  char *val455 = "I don't feel so good";
  char *val555 = "What is lovin'?!";
  ck_assert_int_eq(
      sprintf(str155, str355, val55, val255, val355, val455, val555),
      s21_sprintf(str255, str355, val55, val255, val355, val455, val555));
  ck_assert_pstr_eq(str155, str255);

  char str1ty[200];
  char str2ty[200];
  char *str3ty = "% -10.5s Test % 23s Test %+3.s";
  char *valty = "WHAT IS THIS";
  char *val2ty = "i don't care anymore, really";
  char *val3ty = "PPAP";
  char *val4ty = "I don't feel so good";
  ck_assert_int_eq(sprintf(str1ty, str3ty, valty, val2ty, val3ty, val4ty),
                   s21_sprintf(str2ty, str3ty, valty, val2ty, val3ty, val4ty));
  ck_assert_pstr_eq(str1ty, str2ty);

  char str132[200];
  char str232[200];
  char *str332 = "%s Test %5s Test %10s";
  char *val32 = "WHAT IS THIS";
  char *val232 = "i don't care anymore";
  char *val332 = "PPAP";
  ck_assert_int_eq(sprintf(str132, str332, val32, val232, val332),
                   s21_sprintf(str232, str332, val32, val232, val332));
  ck_assert_pstr_eq(str132, str232);

  char str1qwe[300];
  char str2qwe[300];

  ck_assert_int_eq(s21_sprintf(str1qwe, "%s", "Drop Sega PLS"),
                   sprintf(str2qwe, "%s", "Drop Sega PLS"));
  ck_assert_pstr_eq(str1qwe, str2qwe);

  char str1kqqq[300];
  char str2kqqq[300];

  ck_assert_int_eq(s21_sprintf(str1kqqq, "%s%s%s", "Drop", " ", "Sega"),
                   sprintf(str2kqqq, "%s%s%s", "Drop", " ", "Sega"));

  ck_assert_pstr_eq(str1kqqq, str2kqqq);

  char str1kqq[300];
  char str2kqq[300];

  char *formats = "%s%s%s%s";
  char *vals =
      "69 IS MY FAVORITE NUMBER THIS IS SUPPOSED TO BE A VERY LONG STRING";
  char *s1s = "";
  char *s2s = "87418347813748913749871389480913";
  char *s3s = "HAHAABOBASUCKER";
  ck_assert_int_eq(s21_sprintf(str1kqq, formats, vals, s1s, s2s, s3s),
                   sprintf(str2kqq, formats, vals, s1s, s2s, s3s));

  ck_assert_str_eq(str1kqq, str2kqq);

  char str1kq[300];
  char str2kq[300];
  char *str3kq = "%- lu Test %10.5lu Test %+ 10hu GOD";
  long int valkq = LONG_MAX;
  short int val3kq = SHRT_MAX;
  int val5kq = INT_MAX;
  ck_assert_int_eq(sprintf(str1kq, str3kq, valkq, val3kq, val5kq),
                   s21_sprintf(str2kq, str3kq, valkq, val3kq, val5kq));
  ck_assert_pstr_eq(str1kq, str2kq);

  char str17[200];
  char str27[200];
  char *str37 = "% 10lu Test %3.lu Test %5.7lu TEST %10hu  %-lu %+u %.hu % .u";
  int val7 = 0;
  ck_assert_int_eq(
      sprintf(str17, str37, val7, val7, val7, val7, val7, val7, val7, val7),
      s21_sprintf(str27, str37, val7, val7, val7, val7, val7, val7, val7, val7,
                  val7));
  ck_assert_pstr_eq(str17, str27);

  char str10[200];
  char str20[200];
  char *str30 = "%+15u Test % -15lu sdasda %+ 15u sdsad %- hu";
  int val0 = -3231;
  int val20 = -3231;
  int val30 = 3231;
  int val40 = 3231;
  ck_assert_int_eq(sprintf(str10, str30, val0, val20, val30, val40),
                   s21_sprintf(str20, str30, val0, val20, val30, val40));
  ck_assert_pstr_eq(str10, str20);

  char str1p[200];
  char str2p[200];
  char *str3p = "%-10.5u Test %-.8u Test % -.7u TEST %-.u";
  int valp = -3015;
  int val2p = -712;
  int val3p = -99;
  int val4p = -2939;
  ck_assert_int_eq(sprintf(str1p, str3p, valp, val2p, val3p, val4p),
                   s21_sprintf(str2p, str3p, valp, val2p, val3p, val4p));
  ck_assert_pstr_eq(str1p, str2p);

  char str1k[300];
  char str2k[300];
  char *str3k = "%- ld Test %10.5ld Test %+ 10hd GOD %hd tt %d tt %d";
  long int valk = LONG_MAX;
  long val2k = LONG_MIN;
  short int val3k = SHRT_MAX;
  short val4k = SHRT_MIN;
  int val5k = INT_MAX;
  int val6k = INT_MIN;
  ck_assert_int_eq(
      sprintf(str1k, str3k, valk, val2k, val3k, val4k, val5k, val6k),
      s21_sprintf(str2k, str3k, valk, val2k, val3k, val4k, val5k, val6k));
  ck_assert_pstr_eq(str1k, str2k);

  char str1n[100];
  char str2n[100];
  char *formatn = "%-16.9hi";
  short int valn = 6958;
  ck_assert_int_eq(s21_sprintf(str1n, formatn, valn),
                   sprintf(str2n, formatn, valn));

  ck_assert_str_eq(str1n, str2n);

  char str1o[100];
  char str2o[100];

  char *formato = "%+5.31li";
  long int valo = 698518581899;
  ck_assert_int_eq(s21_sprintf(str1o, formato, valo),
                   sprintf(str2o, formato, valo));

  ck_assert_str_eq(str1o, str2o);

  char str1i[400];
  char str2i[400];
  char *str3i = "%.7c Test % -.7c Test %- 050c Test %- 54c Test %-0188c";
  int ai = 45;
  ck_assert_int_eq(sprintf(str1i, str3i, ai, ai, ai, ai, ai),
                   s21_sprintf(str2i, str3i, ai, ai, ai, ai, ai));
  ck_assert_pstr_eq(str1i, str2i);

  char str1m[100];
  char str2m[100];
  char *str3m = "%-6.4c Test % +10.5c";
  int am = 74;
  unsigned long int bm = '\0';
  ck_assert_int_eq(sprintf(str1m, str3m, am, bm),
                   s21_sprintf(str2m, str3m, am, bm));
  ck_assert_pstr_eq(str1m, str2m);

  char str1u[100];
  char str2u[100];
  char *str3u = "%c Test %c Test %c Test %c Test %c";
  int au = 60;
  int bu = 50;
  int cu = 1744;
  int du = 386;
  int eu = 257;
  ck_assert_int_eq(sprintf(str1u, str3u, au, bu, cu, du, eu),
                   s21_sprintf(str2u, str3u, au, bu, cu, du, eu));
  ck_assert_pstr_eq(str1u, str2u);

  char str1v[100];
  char str2v[100];
  char *str3v = "%c";
  char av = 45;
  ck_assert_int_eq(sprintf(str1v, str3v, av),
                   s21_sprintf(str2v, str3v, av, av));
  ck_assert_pstr_eq(str1v, str2v);

  char str1b[100];
  char str2b[100];
  char *str3b = "%c Test %c Test %c Test %c Test %c";
  ck_assert_int_eq(sprintf(str1b, str3b, 'Y', '\0', 123, '\0', 'J'),
                   s21_sprintf(str2b, str3b, 'Y', '\0', 123, '\0', 'J'));
  ck_assert_pstr_eq(str1b, str2b);

  char str1x[400];
  char str2x[400];
  char *str3x = "%.7c Test % -.7c Test %- 050c Test %- 54c Test %-0188c";
  int ax = 45;
  ck_assert_int_eq(sprintf(str1x, str3x, ax, ax, ax, ax, ax),
                   s21_sprintf(str2x, str3x, ax, ax, ax, ax, ax));
  ck_assert_pstr_eq(str1x, str2x);

  char str1z[200];
  char str2z[200];
  char *str3z = "%-10.5d Test %-.8d Test %-7d TEST %-.d";
  int valz = -3015;
  int val2z = -712;
  int val3z = -99;
  int val4z = -2939;
  ck_assert_int_eq(sprintf(str1z, str3z, valz, val2z, val3z, val4z),
                   s21_sprintf(str2z, str3z, valz, val2z, val3z, val4z));
  ck_assert_pstr_eq(str1z, str2z);

  char str1e[200];
  char str2e[200];
  char *str3e = "%0d Test %0.d Test %0.0d TEST %0d GOD %.d";
  int vale = -3015;
  int val2e = -712;
  int val3e = -99;
  int val4e = -2939;
  int val5e = -0123;
  ck_assert_int_eq(sprintf(str1e, str3e, vale, val2e, val3e, val4e, val5e),
                   s21_sprintf(str2e, str3e, vale, val2e, val3e, val4e, val5e));
  ck_assert_pstr_eq(str1e, str2e);

  char str1w[200];
  char str2w[200];
  char *str3w = "%d Test %3.d Test %5.7d TEST %10d  %-d %+d %.d % .d";
  int valw = 0;
  ck_assert_int_eq(
      sprintf(str1w, str3w, valw, valw, valw, valw, valw, valw, valw, valw),
      s21_sprintf(str2w, str3w, valw, valw, valw, valw, valw, valw, valw, valw,
                  valw));
  ck_assert_pstr_eq(str1w, str2w);

  char strq1[200];
  char strq2[200];
  char *strq3 = "%-0.0d Test %-0.0u Test %-05u TEST %-0.d";
  int pe = -3015;
  int pe2 = -712;
  int pe3 = -99;
  int pe4 = -2939;
  ck_assert_int_eq(sprintf(strq1, strq3, pe, pe2, pe3, pe4),
                   s21_sprintf(strq2, strq3, pe, pe2, pe3, pe4));
  ck_assert_pstr_eq(strq1, strq2);

  char qwe1[200];
  char qwe2[200];
  char *qwe3 = "%6.5d Test %.23d Test %3.7u TEST %.d %.6d";
  int qwerty = -3015;
  int qwerty2 = -712;
  int qwerty3 = -99;
  int qwerty4 = -38;
  int qwerty5 = -100;
  ck_assert_int_eq(
      sprintf(qwe1, qwe3, qwerty, qwerty2, qwerty3, qwerty4, qwerty5),
      s21_sprintf(qwe2, qwe3, qwerty, qwerty2, qwerty3, qwerty4, qwerty5));
  ck_assert_pstr_eq(qwe1, qwe2);

  char qaz[100];
  char qaz1[100];
  char *qaz2 = "%ld Test %ld Test %hd GOD %hd";
  long int val12 = 3088675747373646;
  long val21 = 33030030303;
  short int val31 = 22600;
  short val41 = -120;
  ck_assert_int_eq(sprintf(qaz, qaz2, val12, val21, val31, val41),
                   s21_sprintf(qaz1, qaz2, val12, val21, val31, val41));
  ck_assert_pstr_eq(qaz, qaz1);

  char sqtr1[100];
  char sqtr2[100];
  char *sqtr3 = "%3d Test %5d Test %10d";
  int val = -3015;
  int val2 = -11234;
  int val3 = -99;
  ck_assert_int_eq(sprintf(sqtr1, sqtr3, val, val2, val3),
                   s21_sprintf(sqtr2, sqtr3, val, val2, val3));
  ck_assert_pstr_eq(sqtr1, sqtr2);

  char str[1000] = {'\0'};
  char str1[1000] = {'\0'};
  int res = s21_sprintf(str, "%3c %.1d %5s", 's', 4, "asd");
  int res1 = sprintf(str1, "%3c %.1d %5s", 's', 4, "asd");
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++) str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%.3s %10hd %c", "asdqwe", 42323, 's');
  res1 = sprintf(str1, "%.3s %10hd %c", "asdqwe", 42323, 's');
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++)  //!!!!
    str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%3hu %10.10li %4s", 's', 1234322242323, "asdqwe");
  res1 = sprintf(str1, "%3hu %10.10li %4s", 's', 1234322242323, "asdqwe");
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++) str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%ld", 123332123123);
  res1 = sprintf(str1, "%ld", 123332123123);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++) str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%-3u %10li %4s", 's', 1234322242323, "asdqwe");
  res1 = sprintf(str1, "%-3u %10li %4s", 's', 1234322242323, "asdqwe");
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++) str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%+10d", 323);
  res1 = sprintf(str1, "%+10d", 323);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++) str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%-10hd", 7788123);
  res1 = sprintf(str1, "%-10hd", 7788123);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++) str[i] = str1[i] = 0;
  res = s21_sprintf(str, "% d", 123);
  res1 = sprintf(str1, "% d", 123);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++) str[i] = str1[i] = 0;
  res = s21_sprintf(str, "% f", 123.2);
  res1 = sprintf(str1, "% f", 123.2);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++) str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%d", 123);
  res1 = sprintf(str1, "%d", 123);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++) str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%+20f", 30.03);
  res1 = sprintf(str1, "%+20f", 30.03);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++) str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%.10f", -98765.56789);
  res1 = sprintf(str1, "%.10f", -98765.56789);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++) str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%lu %s", 102123321456456, "string");
  res1 = sprintf(str1, "%lu %s", 102123321456456, "string");
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++) str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%.2f", 1.999);
  res1 = sprintf(str1, "%.2f", 1.999);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++) str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%.2f", 99.999);
  res1 = sprintf(str1, "%.2f", 99.999);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++) str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%.2f", 0.998);
  res1 = sprintf(str1, "%.2f", 0.998);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++) str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%i %-10.2s", 10212, "string");
  res1 = sprintf(str1, "%i %-10.2s", 10212, "string");
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++) str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%hi", 123);
  res1 = sprintf(str1, "%hi", 123);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++) str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%.9f", -98765.56789);
  res1 = sprintf(str1, "%.9f", -98765.56789);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++) str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%.10f", -98765.56789);
  res1 = sprintf(str1, "%.10f", -98765.56789);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++) str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%.11f", -98765.56789);
  res1 = sprintf(str1, "%.11f", -98765.56789);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++) str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%+10.10f", -98765.56789);
  res1 = sprintf(str1, "%+10.10f", -98765.56789);
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);

  for (int i = 0; i < 1000; i++) str[i] = str1[i] = 0;
  res = s21_sprintf(str, "%-3c %.1d %5s", 's', 4, "asd");
  res1 = sprintf(str1, "%-3c %.1d %5s", 's', 4, "asd");
  ck_assert_str_eq(str, str1);
  ck_assert_int_eq(res, res1);
}
END_TEST

Suite *s21_sprintf_suite() {
  Suite *s = suite_create("sprintf_suite");
  TCase *tc = tcase_create("sprintf_test");
  tcase_add_test(tc, sprintf_check);
  suite_add_tcase(s, tc);
  return s;
}

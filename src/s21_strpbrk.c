#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  s21_size_t len = s21_strlen(str1);
  const char *res = s21_NULL;
  for (s21_size_t i = 0; i < len; i++) {
    if (s21_strchr(str2, str1[i])) {
      res = (str1 + i);
      break;
    }
  }
  return (char *)res;
}
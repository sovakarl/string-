#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t len = s21_strlen(str1);
  s21_size_t res = 0;
  for (res = 0; res < len; res++) {
    if (s21_strchr(str2, str1[res])) break;
  }
  return res;
}
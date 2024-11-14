#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int result = 0;
  const char *p1 = (char *)str1;
  const char *p2 = (char *)str2;
  for (int i = 0; i < (int)n; i++) {
    if (p1[i] != p2[i]) {
      result = (p1[i] - p2[i]);
      break;
    }
  }
  return result;
}

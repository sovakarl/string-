#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  char *result = s21_NULL;
  for (int i = 0; i < (int)n; i++) {
    if ((*(char *)(str + i)) == c) {
      result = (char *)(str + i);
      break;
    }
  }
  return result;
}

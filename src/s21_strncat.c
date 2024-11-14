#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  for (int i = 0; i < (int)n; i++) {
    *(char *)(dest + s21_strlen(dest)) = *(char *)(src + i);
  }
  return dest;
}
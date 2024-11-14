#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  int i = 0;
  char *result = s21_NULL;

  while (str[i] != c && str[i] != '\0') {
    i++;
  }

  if (str[i] == c) {
    result = (char *)str + i;
  }

  return result;
}

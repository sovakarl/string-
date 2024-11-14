#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *pos = s21_NULL;
  int err = 0;
  char *chaystack = (char *)haystack;
  if (s21_strlen(needle) == 0) {
    pos = chaystack;
  } else {
    for (int i = 0; i < (int)s21_strlen(chaystack); i++) {
      if (chaystack[i] == needle[0]) {
        pos = &chaystack[i];
        for (int j = i, k = 0; j < (int)s21_strlen(needle) + i; j++, k++) {
          if (chaystack[j] != needle[k]) {
            err = 1;
          }
        }
        if (err == 0) {
          break;
        } else {
          pos = s21_NULL;
          err = 0;
          continue;
        }
      }
    }
  }
  return pos;
}
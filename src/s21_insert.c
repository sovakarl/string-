#include <stdlib.h>

#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  int flag = 0;
  char *res = s21_NULL;
  if (src == s21_NULL || str == s21_NULL || start_index > s21_strlen(src)) {
    flag = 1;
  } else {
    s21_size_t src_len = s21_strlen(src);
    s21_size_t str_len = s21_strlen(str);

    res = malloc((src_len + str_len + 1) * sizeof(char));

    s21_memcpy(res, src, start_index);
    s21_memcpy(res + start_index, str, str_len);
    s21_memcpy(res + start_index + str_len, src + start_index,
               src_len - start_index);
    res[src_len + str_len] = '\0';
  }
  return flag == 1 ? s21_NULL : (void *)res;
}
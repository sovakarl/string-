#include "s21_string.h"

int s21_sscanf(const char *str, const char *format, ...) {
  int n = 0, ret = 0;
  int arr_index = 0;
  form *arr = s21_NULL;
  arr = calloc(25, sizeof(form));
  reset_form(arr);
  if (format_parser(format, arr, &arr_index, &n)) {
    str_parser(str, arr, arr_index);
    va_list args;
    va_start(args, format);
    for (int i = 0; i < arr_index; i++) {
      if (!get_args(&args, &arr[i], &n, &ret) && arr[i + 1].spec != 'n') break;
    }
    va_end(args);
  }
  free(arr);
  return ret;
}

int format_parser(const char *format, form *arr, int *arr_index, int *n) {
  int flag = 1;
  char *c = (char *)format;
  while (*c != '%') {
    chtoarr(arr[*arr_index].first_delim, *c);
    c++;
    (*n)++;
  }
  for (; *c; c++) {
    if (*c == '%') {
      c++;
      width_proc(&c, &arr[*arr_index]);
      length_proc(&c, &arr[*arr_index]);
      spec_proc(&c, &arr[*arr_index], &flag);
      find_delim(&c, &arr[*arr_index]);
      (*arr_index)++;
    }
  }
  return flag;
}

void width_proc(char **c, form *elem) {
  if (**c == '*') {
    elem->no_assignment = 1;
    (*c)++;
  } else if (**c >= 48 && **c <= 57) {
    char width[96] = "\0";
    while (**c >= 48 && **c <= 57) {
      chtoarr(width, **c);
      (*c)++;
    }
    elem->width = atoi(width);
  }
}

void length_proc(char **c, form *elem) {
  if (s21_strchr("hlL", **c) != s21_NULL) {
    elem->length[0] = **c;
    (*c)++;
    if (elem->length[0] == 'l' && **c == 'l') {
      elem->length[1] = 'l';
      (*c)++;
    }
  }
}

void spec_proc(char **c, form *elem, int *flag) {
  if (s21_strchr("cdieEfgGosuxXpn%", **c) != s21_NULL) {
    elem->spec = **c;
  } else
    *flag = 0;
}

void find_delim(char **c, form *elem) {
  int i = 1;
  for (; *(*c + i) != 37 && *(*c + i); i++) {
    chtoarr(elem->delim, *(*c + i));
  }
}

void str_parser(const char *str, form *arr, int index) {
  char *c = (char *)str;
  s21_size_t len_str = s21_strlen(str);
  s21_size_t first_len = s21_strlen(arr[0].first_delim);
  if (s21_strncmp(arr[0].first_delim, str, first_len) == 0) c += first_len;
  for (int i = 0; i < index; i++) {
    int delen = s21_strlen(arr[i].delim);
    if (*c == '\0') break;
    while (*c < 32) {
      c++;
    }
    get_value(&c, &arr[i], len_str);
    if (s21_strncmp(arr[i].delim, c, delen) == 0) c += delen;
  }
}

void chtoarr(char *array, char elem) {
  int i = 0;
  for (; *(array + i); i++)
    ;
  array[i] = elem;
}

void get_value(char **c, form *elem, int len) {
  int i = 0;
  int width = elem->width ? elem->width : len + 1;
  switch (elem->spec) {
    case 'i':
    case 'd':
    case 'u':
    case 'f':
    case 'x':
    case 'X':
    case 'o':
    case 'p':
    case 'e':
    case 'E':
    case 'g':
    case 'G':
      get_number(c, elem, width);
      break;
    case 'c':
      if (**c) {
        elem->value[0] = **c;
        (*c)++;
      }
      break;
    case 's':
      while (**c == 32) (*c)++;
      while (**c != 32 && **c != 10 && i <= width && **c) {
        chtoarr(elem->value, **c);
        (*c)++;
        i++;
      }
      break;
    case '%':
      if (**c == '%') {
        chtoarr(elem->value, **c);
        (*c)++;
      }
  }
}

void get_number(char **c, form *elem, int width) {
  int dot = 0, e = 0, counter = 0;
  while (**c == 10 || **c == 32) (*c)++;
  if ((**c == 45 || **c == 43) && *(*c + 1) >= 48 && *(*c + 1) <= 57) {
    chtoarr(elem->value, **c);
    (*c)++;
    counter++;
  }
  if (s21_strchr("pxXoi", elem->spec) != s21_NULL && **c == '0') {
    chtoarr(elem->value, **c);
    (*c)++;
    counter++;
    if ((**c == 'x' || **c == 'X') && elem->spec != 'o' && counter != width) {
      chtoarr(elem->value, **c);
      (*c)++;
      counter++;
      elem->spec = 'x';
    } else if (elem->spec != 'p')
      elem->spec = 'o';
  }
  while (elem->spec == 'o' && **c >= 48 && **c <= 55) {
    if (counter == width) break;
    chtoarr(elem->value, **c);
    (*c)++;
    counter++;
  }
  while (s21_strchr("pxX", elem->spec) != s21_NULL &&
         ((**c >= 48 && **c <= 57) || (**c >= 65 && **c <= 70) ||
          (**c >= 97 && **c <= 102))) {
    if (counter == width) break;
    chtoarr(elem->value, **c);
    (*c)++;
    counter++;
  }
  while (s21_strchr("dui", elem->spec) != s21_NULL && **c >= 48 && **c <= 57) {
    if (counter == width) break;
    chtoarr(elem->value, **c);
    (*c)++;
    counter++;
  }
  while (
      s21_strchr("feEgG", elem->spec) != s21_NULL &&
      (((**c >= 48 && **c <= 57) ||
        (s21_strchr("eE", **c) != s21_NULL && **c) || (**c == 46 && e == 0)) &&
       dot < 2 && e < 2)) {
    if (counter == width) break;
    chtoarr(elem->value, **c);
    (*c)++;
    counter++;
    if (**c == 46) dot++;
    if (s21_strchr("eE", **c) != s21_NULL) {
      e++;
      if (*(*c + 1) == 45) {
        (*c)++;
        chtoarr(elem->value, **c);
        (*c)++;
        counter++;
        if (counter == width) break;
      }
    }
  }
}

int get_args(va_list *args, form *elem, int *n, int *ret) {
  int res = 1;
  if (elem->no_assignment == 0) {
    switch (elem->spec) {
      case 'd':
      case 'i':
        if (!assign_di(*elem, args, n)) res = 0;
        break;
      case 'c':
        if (!assign_c(*elem, args, n)) res = 0;
        break;
      case 's':
        if (!assign_s(*elem, args, n)) res = 0;
        break;
      case 'e':
      case 'E':
      case 'g':
      case 'G':
      case 'f':
        if (!assign_gef(*elem, args, n)) res = 0;
        break;
      case 'X':
      case 'x':
      case 'o':
        if (!assign_xo(*elem, args, n)) res = 0;
        break;
      case 'u':
        if (!assign_u(*elem, args, n)) res = 0;
        break;
      case 'p':
        if (!assign_p(*elem, args, n)) res = 0;
        break;
      case 'n':
        assign_n(args, n);
        break;
    }
  }
  if (res && elem->spec != '%' && elem->no_assignment != 1 && elem->spec != 'n')
    (*ret)++;
  return res;
}

int assign_di(form elem, va_list *args, int *n) {
  int res = 1;
  if (s21_strncmp(elem.length, "h", 2) == 0) {
    short int *addr_hdi = va_arg(*args, short int *);
    *addr_hdi = atoi(elem.value);
    if (*addr_hdi == 0 && elem.value[0] != '0') res = 0;
  } else if (s21_strncmp(elem.length, "l", 2) == 0) {
    long int *addr_ldi = va_arg(*args, long int *);
    *addr_ldi = atol(elem.value);
    if (*addr_ldi == 0 && elem.value[0] != '0') res = 0;
  } else if (s21_strncmp(elem.length, "ll", 2) == 0) {
    long long int *addr_lldi = va_arg(*args, long long int *);
    long long int value = (long long int)atol(elem.value);
    *addr_lldi = value;
    if (*addr_lldi == 0 && elem.value[0] != '0') res = 0;
  } else {
    int *addr_di = va_arg(*args, int *);
    *(int *)addr_di = atoi(elem.value);
    if (*addr_di == 0 && elem.value[0] != '0') res = 0;
  }
  if (res) sup_n(elem, n);
  return res;
}

int assign_c(form elem, va_list *args, int *n) {
  int res = 1;
  if (elem.value[0] != '\0') {
    if (s21_strncmp(elem.length, "l", 2) == 0) {
      wchar_t *addr_lc = va_arg(*args, wchar_t *);
      *addr_lc = elem.value[0];
      if (addr_lc == s21_NULL) res = 0;
    } else {
      char *addr_c = va_arg(*args, char *);
      *addr_c = elem.value[0];
      if (addr_c == s21_NULL) res = 0;
    }
    if (res) sup_n(elem, n);
  } else
    res = 0;
  return res;
}

int assign_s(form elem, va_list *args, int *n) {
  int res = 1;
  if (s21_strncmp(elem.length, "l", 2) == 0) {
    wchar_t *addr_ls = va_arg(*args, wchar_t *);
    mbstowcs(addr_ls, elem.value, s21_strlen(elem.value) + 1);
    if (addr_ls == s21_NULL) res = 0;
  } else {
    char *addr_s = va_arg(*args, char *);
    s21_strncpy(addr_s, elem.value, s21_strlen(elem.value));
    if (addr_s == s21_NULL) res = 0;
  }
  if (res) sup_n(elem, n);
  return res;
}

int assign_gef(form elem, va_list *args, int *n) {
  int res = 1;
  if (s21_strncmp(elem.length, "l", 2) == 0) {
    double *addr_lgef = va_arg(*args, double *);
    *addr_lgef = strtod(elem.value, s21_NULL);
    if (*addr_lgef == 0 && elem.value[0] != '0') res = 0;
  } else if (s21_strncmp(elem.length, "L", 2) == 0) {
    long double *addr_Lgef = va_arg(*args, long double *);
    *addr_Lgef = (long double)strtod(elem.value, s21_NULL);
    if (*addr_Lgef == 0 && elem.value[0] != '0') res = 0;
  } else {
    float *addr_gef = va_arg(*args, float *);
    *addr_gef = (float)strtod(elem.value, s21_NULL);
    if (*addr_gef == 0 && elem.value[0] != '0') res = 0;
  }
  if (res) sup_n(elem, n);
  return res;
}

int assign_xo(form elem, va_list *args, int *n) {
  int res = 1;
  char *ptr = s21_NULL;
  long unsigned int num = strtoul(elem.value, &ptr, elem.spec == 'o' ? 8 : 16);
  if (s21_strncmp(elem.length, "h", 2) == 0) {
    short unsigned int *addr_hxo = va_arg(*args, short unsigned int *);
    *addr_hxo = (short unsigned int)num;
    if (addr_hxo == s21_NULL) res = 0;
  } else if (s21_strncmp(elem.length, "l", 2) == 0) {
    long unsigned int *addr_lxo = va_arg(*args, long unsigned int *);
    *addr_lxo = num;
    if (addr_lxo == s21_NULL) res = 0;
  } else if (s21_strncmp(elem.length, "ll", 2) == 0) {
    long long unsigned int *addr_llxo = va_arg(*args, long long unsigned int *);
    *addr_llxo = num;
    if (addr_llxo == s21_NULL) res = 0;
  } else {
    unsigned int *addr_xo = va_arg(*args, unsigned int *);
    *addr_xo = (unsigned int)num;
    if (addr_xo == s21_NULL) res = 0;
  }
  if (res) sup_n(elem, n);
  return res;
}

int assign_u(form elem, va_list *args, int *n) {
  int res = 1;
  if (s21_strncmp(elem.length, "h", 2) == 0) {
    short unsigned int *addr_hu = va_arg(*args, short unsigned int *);
    *addr_hu = (short unsigned int)atoi(elem.value);
    if (*addr_hu == 0 && elem.value[0] != '0') res = 0;
  } else if (s21_strncmp(elem.length, "l", 2) == 0) {
    long unsigned int *addr_lu = va_arg(*args, long unsigned int *);
    *addr_lu = (long unsigned int)atol(elem.value);
    if (*addr_lu == 0 && elem.value[0] != '0') res = 0;

  } else if (s21_strncmp(elem.length, "ll", 2) == 0) {
    long long unsigned int *addr_llu = va_arg(*args, long long unsigned int *);
    *addr_llu = (long long unsigned int)atol(elem.value);
    if (*addr_llu == 0 && elem.value[0] != '0') res = 0;

  } else {
    unsigned int *addr_u = va_arg(*args, unsigned int *);
    *addr_u = (unsigned int)atoi(elem.value);
    if (*addr_u == 0 && elem.value[0] != '0') res = 0;
  }
  if (res) sup_n(elem, n);
  return res;
}

int assign_p(form elem, va_list *args, int *n) {
  int res = 1;
  char *ptr = s21_NULL;
  long unsigned int num = strtoul(elem.value, &ptr, 16);
  long unsigned int *addr_p = va_arg(*args, long unsigned int *);
  *addr_p = num;
  if (*addr_p == 0 && elem.value[0] != '0') res = 0;
  if (res) sup_n(elem, n);
  return res;
}

void assign_n(va_list *args, int *n) {
  int *addr_n = va_arg(*args, int *);
  *addr_n = *n;
}

void sup_n(form elem, int *n) {
  *n += s21_strlen(elem.value);
  *n += s21_strlen(elem.delim);
}

void reset_form(form *arr) {
  for (int i = 0; i < 25; i++) {
    arr[i].spec = 0;
    arr[i].width = 0;
    arr[i].length[0] = '\0';
    arr[i].value[0] = '\0';
    arr[i].no_assignment = 0;
    arr[i].delim[0] = '\0';
    arr[i].first_delim[0] = '\0';
  }
}
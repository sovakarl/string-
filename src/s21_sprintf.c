#include <stdio.h>

#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  char *start = str;
  va_list parametr;
  va_start(parametr, format);
  int flag = 1;
  char spec[] = {"cdieEfgGosuxXpn%"};
  char flags[] = "-+ #0";
  char length[] = "hlL";
  for (char *c = (char *)format; *c; c++) {
    if (flag) {
      if (*c != '%') {
        nspec(*c);
        *str = *c;
        str++;
      } else
        flag = 0;
    } else {
      Sprin head = {0};
      if (s21_strchr(flags, *c) != NULL) {  // запись флага при наличии
        head.ff = 1;
        while (s21_strchr(flags, *c) != NULL) {
          switch (*c) {
            case '-':
              head.flag[0] = *c;
              c++;
              break;
            case '+':
              head.flag[1] = *c;
              c++;
              break;
            case ' ':
              head.flag[2] = *c;
              c++;
              break;
            case '#':
              head.flag[3] = *c;
              c++;
              break;
            case '0':
              head.flag[4] = *c;
              c++;
              break;
          }
        }
      }
      if ((*c >= 48 && *c <= 57) || *c == '*') {  // запись ширины при наличии
        char width[100];
        if (*c == '*') {
          head.width = (va_arg(parametr, int));
          c++;
        } else {
          int z = 0;
          while (*c >= 48 && *c <= 57) {
            width[z] = *c;
            z++;
            c++;
          }
          width[z] = '\0';
          head.width = s21_atoi(width);
        }
        if (head.width < 0) {
          head.width *= -1;
          head.flag[0] = '-';
          head.ff = 1;
        }
        head.fw = 1;
      }
      if (*c == '.') {  // запись точности при наличии
        c++;
        char accuracy[100];
        int f = 0;
        if (*c != '*') {
          while (*c >= 48 && *c <= 57) {
            accuracy[f] = *c;
            f++;
            c++;
          }
          accuracy[f] = '\0';
          head.accuracy = s21_atoi(accuracy);
        } else {
          head.accuracy = (va_arg(parametr, int));
          c++;
        }
        head.fa = 1;
        if (head.accuracy < 0) head.accuracy *= -1;
      }
      if (s21_strchr(length, *c) != NULL) {  // запись длины при наличи
        head.len = *c;
        c++;
      }
      if (s21_strchr(spec, *c) != NULL) {  // запись спецификатора
        head.spec = *c;
      }
      str = solut(head, str, parametr);
      flag = 1;
    }
  }
  va_end(parametr);
  return (int)s21_strlen(start);
}

char *solut(Sprin head, char *str, va_list parametr) {  // обработка
  if (head.spec == 'c')
    str = cspec(va_arg(parametr, int), str, head);  // работает
  if (head.spec == 'd' || head.spec == 'i') {       // работает
    long long a = 0;
    if (head.len == '\0')
      a = va_arg(parametr, int);
    else if (head.len == 'h')
      a = (short)va_arg(parametr, int);
    else
      a = va_arg(parametr, long long);
    str = dspec(a, str, head);
  }
  if (head.spec == 'u') {  // работает
    unsigned long long a = 0;
    if (head.len == '\0')
      a = (unsigned)va_arg(parametr, int);
    else if (head.len == 'h')
      a = (unsigned short)va_arg(parametr, int);
    else
      a = (unsigned long long)va_arg(parametr, long long);
    str = dspec(a, str, head);
  }
  if (head.spec == 'e' || head.spec == 'E') {  // работает
    long double a = 0;
    if (head.len == 'L')
      a = (va_arg(parametr, long double));
    else
      a = (double)(va_arg(parametr, double));
    str = espec(a, str, head);
  }
  if (head.spec == 'f') {  // работает
    long double a = 0;
    if (head.len == 'h' || head.len == 'l' || head.len == '\0')
      a = (double)va_arg(parametr, double);
    else
      a = va_arg(parametr, long double);
    str = fspec(a, str, head);
  }
  if (head.spec == 'g' || head.spec == 'G') {
    long double a = 0;
    if (head.len == 'h' || head.len == 'l' || head.len == '\0')
      a = (double)va_arg(parametr, double);
    else
      a = va_arg(parametr, long double);
    str = gspec(a, str, head);
  }
  if (head.spec == 'o') {  // работает
    long long a = 0;
    if (head.len == '\0')
      a = (unsigned)va_arg(parametr, int);
    else if (head.len == 'h')
      a = (unsigned short)va_arg(parametr, int);
    else if (head.len == 'l')
      a = (unsigned long long)va_arg(parametr, long long);
    str = ospec(a, str, head);
  }
  if (head.spec == 's')
    str = spec(va_arg(parametr, char *), str, head);  // работает
  if (head.spec == 'x' || head.spec == 'X') {         // работает
    long long a = 0;
    if (head.len == '\0')
      a = (unsigned)va_arg(parametr, int);
    else if (head.len == 'h')
      a = (unsigned short)va_arg(parametr, int);
    else if (head.len == 'l')
      a = (unsigned long long)va_arg(parametr, long long);
    str = ospec(a, str, head);
  }
  if (head.spec == 'p')
    str = pspec(va_arg(parametr, void *), str, head);  // работает
  if (head.spec == '%') str = procent(str);            // работает
  return str;
}

void decimal(double a, char **arr) {
  *arr = calloc(1, sizeof(char));
  int count = 0;
  a -= (long int)a;
  if (a < 0) a *= -1;
  while (count < (int)sizeof(double) * 8) {
    a *= 10;
    *(*arr + count) = (int)a + '0';
    a -= (int)a;
    count++;
    *arr = realloc(*arr, count + 1);
  }
  *(*arr + count) = '\0';
}

void rounding(int accuracy, char *arr, char *pi) {
  if (accuracy <= 0) accuracy = 0;
  int fl = 0;
  if (arr[accuracy] >= '5') fl = 1;
  arr[accuracy] = '\0';
  int len = s21_strlen(arr);
  for (int i = len - 1; i >= 0; i--) {
    if (fl == 1) {
      if (arr[i] != '9') {
        arr[i] += 1;
        fl = 0;
      } else {
        arr[i] = '0';
        fl = 1;
      }
    } else
      break;
  }
  len = s21_strlen(pi);
  for (int i = len - 1; i >= 0; i--) {
    if (fl == 1) {
      if (pi[i] != '9') {
        pi[i] += 1;
        fl = 0;
      } else {
        pi[i] = '0';
        fl = 1;
      }
    } else
      break;
  }
}
char *espec(long double x, char *str, Sprin head) {  // научная запись
  int sign = 0;
  char INT[300] = {0};
  char *DECIMAL = NULL;
  char data[500] = {0};
  char *pd = data;
  Sprin empty = {0};  // пустая структура заглушка
  if (x < 0) {
    x *= -1;
    sign = 1;
    INT[0] = '-';
  } else if (head.flag[2] == ' ') {
    sign = 1;
    INT[0] = ' ';
  } else if (head.flag[1] == '+') {
    sign = 1;
    INT[0] = '+';
  }
  int count = 0;
  char echar[] = "e-";
  if (head.spec == 'E') echar[0] = 'E';
  int accuracy = 6;
  if (head.fa == 1) accuracy = head.accuracy;
  long long len = leni(x);
  if (len >= 1) echar[1] = '+';
  if (x != 0) {
    while (leni(x) != 1) {
      if (len >= 1)
        x /= 10;
      else
        x *= 10;
      count++;
    }
  }
  s21_itoa(x, INT, 1);
  decimal(x, &DECIMAL);
  rounding(accuracy, DECIMAL, INT);
  if (accuracy > 0)
    INT[s21_strlen(INT)] = '.';
  else if (head.flag[3] == '#')
    INT[s21_strlen(INT)] = '.';
  pd = addchar(INT, pd);
  pd = addchar(DECIMAL, pd);
  pd = magic(count, pd, echar);
  if (head.flag[0] != '-' && head.flag[4] != '0')
    str = zero((int)s21_strlen(data), head.width, str,
               ' ');  // пробелы слева от числа
  if (head.flag[4] == '0' && head.flag[0] != '-') {
    if (sign == 1) str = cspec(data[0], str, empty);
    str = zero((int)s21_strlen(data), head.width, str, '0');
    str = addchar(data + 1, str);
  } else
    str = addchar(data, str);
  if (head.flag[0] == '-')
    str = zero((int)s21_strlen(data), head.width, str, ' ');
  free(DECIMAL);
  return str;
}

char *magic(int len, char *str, char *e) {
  Sprin empty = {.accuracy = 2, .fa = 1};
  str = addchar(e, str);
  str = dspec(len, str, empty);
  return str;
}

char *ospec(long long a, char *str, Sprin head) {  // o спецификатор
  Sprin empty = {0};
  int count = 0;
  long long b = a;
  long long int len = 0;
  char data[500] = {0};
  char *pd = data;
  int accuracy = 1;
  if (head.fa == 1)
    accuracy = head.accuracy;
  else
    head.accuracy = accuracy;
  if (head.flag[3] == '#') pd = cspec('0', data, empty);
  while (b != 0) {
    b /= 8;
    len++;
  }
  if (len < accuracy) pd = zero(len, accuracy, data, '0');
  char arr[250] = {0};
  while (a != 0) {
    arr[count] = (char)(a % 8 + 48);
    count++;
    a /= 8;
  }
  for (int i = 0; i < len / 2; i++) {
    char ch = arr[i];
    arr[i] = arr[len - i - 1];
    arr[len - i - 1] = ch;
  }
  addchar(arr, pd);
  if (head.flag[4] != '0' && head.flag[0] != '-')
    str = zero((int)s21_strlen(data), head.width, str, ' ');
  else if (head.flag[4] == '0')
    str = zero((int)s21_strlen(data), head.width, str, '0');
  str = addchar(data, str);
  if (head.flag[0] == '-')
    str = zero((int)s21_strlen(data), head.width, str, ' ');
  return str;
}

char *xspec(long a, char *str, Sprin head) {  // x спецификатор
  char *pd = NULL;
  int count = 0;
  long long b = a;
  long long int len = 0;
  char data[500] = {0};
  pd = data;
  int accuracy = 1;
  if (head.fa == 1)
    accuracy = head.accuracy;
  else
    head.accuracy = accuracy;
  if (head.flag[3] == '#' && head.spec == 'x') pd = addchar("0x", data);
  if (head.flag[3] == '#' && head.spec == 'X') pd = addchar("0X", data);
  while (b != 0) {
    b /= 16;
    len++;
  }
  if (len < accuracy && head.fa == 1) pd = zero(len, accuracy, data, '0');
  char arr[250] = {0};
  if (a != 0) {
    while (a != 0) {
      int x = 48;
      if (a % 16 >= 10) x = 55;
      arr[count] = (char)(a % 16 + x);
      count++;
      a /= 16;
    }
  } else
    arr[0] = '0';
  for (int i = 0; i < len / 2; i++) {
    char ch = arr[i];
    arr[i] = arr[len - i - 1];
    arr[len - i - 1] = ch;
  }
  addchar(arr, pd);
  if (head.flag[4] != '0' && head.flag[0] != '-')
    str = zero((int)s21_strlen(data), head.width, str, ' ');
  else if (head.flag[4] == '0')
    str = zero((int)s21_strlen(data), head.width, str, '0');
  str = addchar(data, str);
  if (head.flag[0] == '-')
    str = zero((int)s21_strlen(data), head.width, str, ' ');
  return str;
}

char *spec(const char *data, char *str, Sprin head) {  // s спецификатор
  int len = s21_strlen(data);
  if (head.fa == 1 && len > head.accuracy) len = head.accuracy;
  if (head.ff == 0) str = zero(len, head.width, str, ' ');
  for (int i = 0; i < len; i++) {
    *str = data[i];
    str++;
  }
  if (head.flag[0] == '-') str = zero(s21_strlen(data), head.width, str, ' ');
  return str;
}

char *pspec(void *pointer, char *str, Sprin head) {  // p спецификатор
  s21_uintptr_t adress = (s21_intptr_t)pointer;
  Sprin empty = {.flag[3] = '#',
                 .ff = 1,
                 .spec = 'x',
                 .width = head.width,
                 .accuracy = head.accuracy,
                 .fa = head.fa,
                 .flag[0] = head.flag[0]};
  char data[100];
  xspec(adress, data, empty);
  int len = s21_strlen(data);
  for (int i = 0; i < len; i++) {
    if (data[i] > 65 && data[i] < 90) data[i] += 32;
  }
  str = addchar(data, str);
  return str;
}
char *procent(char *str) {  // % спецификатор
  str = addchar("%", str);
  return str;
}

int nspec(char ch) {  // n спецификатор
  static int count = 0;
  if (ch != '\n') count++;
  return count;
}

char *fspec(long double x, char *str, Sprin head) {
  char *pointer = NULL;
  char data[500] = {0};
  char INT[300] = {0};  // указатель для хранения числа в массиве
  int accuracy = 6;
  if (head.fa == 1)
    accuracy = head.accuracy;  // перезапись точности при наличии
  else
    head.accuracy = accuracy;
  Sprin empty = {.accuracy = 0,
                 .fa = 0,
                 .ff = 0,
                 .fw = 0,
                 .len = '\0',
                 .spec = '\0',
                 .width = 0};  // пустая структура заглушка
  if (x < 0) {                 // вывод знака
    x *= -1;
    INT[0] = '-';
  } else if (head.flag[1] == '+')
    INT[0] = '+';
  else if (head.flag[2] == ' ')
    INT[0] = ' ';
  s21_itoa(x, INT, 1);
  decimal(x, &pointer);
  rounding(accuracy, pointer, INT);
  multi(INT, pointer, data, head);
  if (head.fw == 1 && head.flag[0] != '-')
    str = zero((int)s21_strlen(data), head.width, str, ' ');
  str = addchar(INT, str);
  if (accuracy > 0) {
    str = cspec('.', str, empty);
    str = addchar(pointer, str);
  } else if (head.flag[3] == '#')
    str = cspec('.', str, empty);
  if (head.fw == 1 && head.flag[0] == '-')
    str = zero((int)s21_strlen(data), head.width, str, ' ');
  free(pointer);
  return str;
}
void multi(char *INT, char *pointer, char *data, Sprin head) {
  Sprin empty = {0};
  data = addchar(INT, data);
  if (head.accuracy > 0) {
    data = cspec('.', data, empty);
    data = addchar(pointer, data);
  } else if (head.flag[3] == '#')
    data = cspec('.', data, empty);
}

char *dspec(long long x, char *str, Sprin head) {
  char INT[250] = {0};  // указатель для хранения числа в массиве
  int accuracy = 1;
  if (head.fa == 1)
    accuracy = head.accuracy;  // перезапись точности при наличии
  Sprin empty = {.accuracy = 0,
                 .fa = 0,
                 .ff = 0,
                 .fw = 0,
                 .len = '\0',
                 .spec = '\0',
                 .width = 0};  // пустая структура заглушка
  int sign = 0;                // наличие знака
  int width = 0;               // ширина вывода
  if (x < 0) {                 // вывод знака
    x *= -1;
    sign = 1;
    INT[0] = '-';
  } else if (head.flag[1] == '+') {
    INT[0] = '+';
    sign = 1;
  } else if (head.flag[2] == ' ') {
    INT[0] = ' ';
    sign = 1;
  }
  s21_itoa(x, INT, accuracy);  // считывание и запись целого числа
  if (head.fw == 1) width = head.width;  // задание ширины при наличии
  if (head.flag[0] != '-' && head.flag[4] != '0')
    str =
        zero((int)s21_strlen(INT), width, str, ' ');  // пробелы слева от числа
  if (head.flag[4] == '0') {
    if (sign == 1) str = cspec(INT[0], str, empty);
    str = zero(leni(x), width - sign, str, '0');  // обработка флага 0
    str = addchar(INT + sign, str);

  } else {
    str = addchar(INT, str);  // запись целого числа
  }
  if (head.flag[0] == '-')
    str = zero((int)s21_strlen(INT), width, str, ' ');  // пробелы справа
  return str;
}

char *cspec(char ch, char *str, Sprin head) {  // с спецификатор
  int width = 0;
  if (head.fw == 1) width = head.width;
  if (head.ff == 0) str = zero(1, width, str, ' ');
  *str = ch;
  str++;
  if (head.flag[0] == '-') str = zero(1, width, str, ' ');
  return str;
}

void s21_itoa(long long num, char *arr, int accuracy) {  // число в строку
  if (*arr == '+' || *arr == ' ' || *arr == '-') arr++;
  int count = leni(num);
  if (count == 0) count = 1;
  arr = zero(count, accuracy, arr, '0');
  for (int i = 0; i < count; arr++) {
    *arr = 48 + (num / s21_pow(10, count - i - 1));
    num %= s21_pow(10, count - i - 1);
    i++;
  }
  *arr = '\0';
}

char *zero(int count, int accuracy, char *str, char ch) {
  if (count < accuracy) {
    int len = accuracy - count;
    char zero[len + 1];
    zero[len] = '\0';
    for (int i = 0; i < len; i++) zero[i] = ch;
    str = addchar(zero, str);
  }
  return str;
}

int leni(long int num) {
  long int b = num;
  int count = 0;
  while (b != 0) {
    b /= 10;
    count++;
  }
  return count;
}

char *addchar(const char *data, char *str) {  // добавляет строку с идекса
  int len = s21_strlen(data);
  for (int i = 0; i < len; i++) {
    nspec(data[i]);
    *str = data[i];
    str++;
  }
  *str = '\0';
  return str;
}

char *gspec(double x, char *str, Sprin head) {
  Sprin empty = {.accuracy = head.accuracy, .fa = head.fa, .ff = head.ff};
  if (head.ff == 1) {
    if (head.flag[2] == ' ')
      empty.flag[2] = ' ';
    else if (head.flag[1] == '+')
      empty.flag[1] = '+';
  }
  if (head.spec == 'G') empty.spec = 'E';
  int accuracy = 6;
  if (head.fa == 1) accuracy = head.accuracy;
  char edata[100] = {0};
  char fdata[100] = {0};
  char result[250] = {0};
  fspec(x, fdata, empty);
  espec(x, edata, empty);
  if (x < 0) x *= -1;
  if ((x > 1e-4 && x < 1e+6) || x == 0) {
    significant(accuracy, fdata, result);
  } else
    eignificant(6, edata, result);
  if (head.ff == 1 && head.flag[4] == '0') {
    int flag = 0;
    if (result[0] == '-' || result[0] == '+' || result[0] == ' ') {
      *str = result[0];
      str++;
      flag = 1;
    }
    str = zero((int)s21_strlen(result), head.width, str, '0');
    str = addchar(result + flag, str);
  } else if (head.fw == 1 && head.flag[4] != '0' && head.flag[0] != '-') {
    str = zero((int)s21_strlen(result), head.width, str, ' ');
    str = addchar(result, str);
  } else
    str = addchar(result, str);
  if (head.flag[0] == '-')
    str =
        zero((int)s21_strlen(result), head.width, str, ' ');  // пробелы справа)
  return str;
}
void eignificant(int accuracy, char *edata, char *result) {
  int e = s21_strlen(edata) - 1;
  char magic[5] = {0};
  addchar(s21_strpbrk(edata, "eE"), magic);
  while (edata[e] != 'e' && edata[e] != 'E') e--;
  edata[e] = '\0';
  significant(accuracy, edata, result);
  addchar(magic, result + s21_strlen(result));
}
void significant(int accuracy, char *fdata, char *result) {
  int slice = 0;
  int i = 0;
  int rounding = 0;
  int count = 0;
  int len = s21_strlen(fdata);
  while (fdata[i] != '.') {
    if (fdata[i] == '+' || fdata[i] == '-' || fdata[i] == ' ') {
      i++;
      continue;
    }
    i++;
    count++;
  }
  if (count < accuracy) {
    slice = i + accuracy - count + 1;
    if (fdata[slice] >= '5') rounding = 1;
    fdata[slice] = '\0';

    for (int k = slice - 1; i + 1 < k; k--) {
      if (fdata[k] == '0')
        fdata[k] = '\0';
      else
        break;
    }
    if (fdata[i + 1] == '\0') fdata[i] = '\0';
  } else
    fdata[i + 1] = '\0';
  len = s21_strlen(fdata);
  for (int i = len - 1; i >= 0; i--) {
    if (fdata[i] == '.') continue;
    if (fdata[i] == '+' || fdata[i] == '-' || fdata[i] == ' ') break;
    if (rounding == 1) {
      if (fdata[i] != '9') {
        fdata[i] += 1;
        rounding = 0;
      } else {
        fdata[i] = '0';
        rounding = 1;
      }
    } else
      break;
  }
  addchar(fdata, result);
}

int s21_atoi(const char *str) {  // запись строки в число
  int len = s21_strlen(str);
  int i = 0;
  int res = 0;
  int sign = 1;
  if (str[0] == '-') {
    sign = -1;
    i++;
  }
  for (; i < len; i++) {
    res += ((int)str[i] - 48) * (int)s21_pow(10, len - i - 1);
  }
  return sign * res;
}

long int s21_pow(long int a, int b) {
  long int result = 1;
  if (b != 0) {
    for (int i = 0; i < b; i++) result *= a;
  }
  return result;
}
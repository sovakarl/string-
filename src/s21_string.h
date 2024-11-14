#ifndef S21_STRING_H
#define S21_STRING_H
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

typedef struct {
  char spec;          // спецификатор
  int width;          // ширина
  char length[4];     // длина
  char value[2048];   // значение
  int no_assignment;  // разрешение на присваивание
  char delim[1024];   // разделитель
  char first_delim[1024];
} form;

typedef struct sprintf {
  char flag[5];  // флаги
  int ff;
  char spec;     // спецификаторы
  int width;     // ширина
  int fw;        // флаг ширины
  int accuracy;  // точность
  int fa;        // флаг точности
  char len;      //длина
} Sprin;

// #define TYPE (int)
#define SIZE 100

#define s21_NULL ((void *)0)
typedef unsigned long s21_size_t;
typedef unsigned long s21_uintptr_t;
typedef long s21_intptr_t;
int s21_sprintf(char *str, const char *format, ...);
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
// s21_size_t s21_strspn(const char *str1, const char *str2);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
int s21_atoi(const char *str);

char *cspec(char ch, char *str, Sprin head);
char *dspec(long long x, char *str, Sprin head);
char *espec(long double x, char *str, Sprin head);
char *fspec(long double x, char *str, Sprin head);
char *gspec(double x, char *str, Sprin head);
char *ospec(long long a, char *str, Sprin head);
char *spec(const char *data, char *str, Sprin head);
char *xspec(long a, char *str, Sprin head);
void eignificant(int accuracy, char *edata, char *result);

char *addchar(const char *data, char *str);
int leni(long int num);
void s21_itoa(long long num, char *arr, int accuracy);

char *solut(Sprin head, char *str, va_list parametr);
char *pspec(void *pointer, char *str, Sprin head);
char *procent(char *str);
char *magic(int len, char *str, char *e);
int nspec(char ch);
char *zero(int count, int accuracy, char *str, char ch);
void rounding(int accuracy, char *arr, char *pi);
void decimal(double a, char **arr);
void significant(int accuracy, char *str, char *result);
long int s21_pow(long int a, int b);
void multi(char *INT, char *pointer, char *data, Sprin head);

int s21_sscanf(const char *str, const char *format, ...);
int format_parser(const char *format, form *arr, int *arr_index, int *n);
void str_parser(const char *str, form *arr, int index);
void width_proc(char **c, form *elem);
void length_proc(char **c, form *elem);
void spec_proc(char **c, form *elem, int *flag);
void find_delim(char **c, form *elem);
void chtoarr(char *array, char elem);
void get_value(char **c, form *elem, int len);
void get_number(char **c, form *elem, int width);
int get_args(va_list *args, form *elem, int *n, int *ret);
int assign_di(form elem, va_list *args, int *n);
int assign_c(form elem, va_list *args, int *n);
int assign_s(form elem, va_list *args, int *n);
int assign_gef(form elem, va_list *args, int *n);
int assign_xo(form elem, va_list *args, int *n);
int assign_u(form elem, va_list *args, int *n);
int assign_p(form elem, va_list *args, int *n);
void assign_n(va_list *args, int *n);
void sup_n(form elem, int *n);
void reset_form(form *arr);

#endif
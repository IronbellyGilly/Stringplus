#include <float.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wchar.h>

#include "s21_sprintf_specifier.h"
#include "s21_string.h"
#define FLAG_ONLY_ONE 0
#define FLAGS_MULTIPLE 1

int Analysis_percent_alloc(char **out, char **c, va_list *factor,
                           s21_size_t char_count);
char find_flag(char **c, flags *flag, s21_size_t cnt, int multy);
void find_unsignedinteger(int *val, char **c, va_list *factor, parametrs *par);

int s21_sprintf(char *str, const char *format, ...) {
  char *c = s21_NULL, *out = s21_NULL, *try = s21_NULL, *fragment = s21_NULL;
  va_list factor;  // указатель на необязательный параметр
  va_start(factor, format);  // устанавливаем указатель
  int isError = 0;
  for (c = (char *)format; *c; c++) {
    if (*c != '%')
      try = strappend_alloc(try, c, 1);
    else {
      c++;
      if (!(isError = Analysis_percent_alloc(
                &fragment, &c, &factor, s21_strlen(try) + s21_strlen(out)))) {
        try = strappend_alloc(try, fragment, s21_strlen(fragment));
        out = strappend_alloc(out, try, s21_strlen(try));
      }
      free_char_pointer_NULL(&fragment);
      free_char_pointer_NULL(&try);
    }
    if (isError) break;
  }
  if (try) {
    out = strappend_alloc(out, try, s21_strlen(try));
    free_char_pointer_NULL(&try);
  }
  s21_strcpy(str, out);
  free(out);
  // CHECK ERROR AS IN outside ;) EXAMPLE !!!
  return s21_strlen(str);
}

/*Если найден спец символ % то эта функция анализирует что после.
если указатель out realloc до нужного результата (0 - succesful)*/
int Analysis_percent_alloc(char **out, char **c, va_list *factor,
                           s21_size_t char_count) {
  int isError = 0;
  if (!*out) {
    // char *starchar = (*c);
    flags f_show[] = {{'-', 0, s21_NULL},
                      {'+', 0, "diuf"},
                      {32, 0, "diuf"},
                      {'#', 0, "oxXeEfgG"},
                      {'0', 0, s21_NULL}};
    flags f_len[] = {
        {'h', 0, s21_NULL}, {'l', 0, s21_NULL}, {'L', 0, s21_NULL}};
    parametrs par = {.show = f_show,
                     .wdt = -1,
                     .prc = -1,
                     .len = '\0',
                     .cnt = sizeof(f_show) / sizeof(f_show[0]),
                     .char_cnt = char_count,
                     .spec = '\0'};
    find_flag(c, par.show, par.cnt, FLAGS_MULTIPLE);
    find_unsignedinteger(&(par.wdt), c, factor, &par);
    if (**c == charPoint) {
      (*c)++;
      find_unsignedinteger(&(par.prc), c, factor, &par);
      if (par.prc < 0) par.prc = 0;
    }
    par.len =
        find_flag(c, f_len, sizeof(f_len) / sizeof(f_len[0]), FLAG_ONLY_ONE);
    collection collect[] = {{'d', d_func}, {'i', d_func}, {'u', u_func},
                            {'f', f_func}, {'c', c_func}, {'s', s_func},
                            {'n', n_func} /*, {'%', pct_func}*/};
    s21_size_t i = 0;
    for (i = 0; i < sizeof(collect) / sizeof(collect[0]); i++)
      if (**c == collect[i].specifier) {
        par.spec = **c;
        isError += collect[i].operation_alloc(out, factor, &par);
        break;
      }
    if (i == sizeof(collect) / sizeof(collect[0])) {
      par.spec = **c;
      unknown_func(out, factor, &par);
    }
    // for (char *p = starchar - 1; p <= *c; p++)
    //   *out = strappend_alloc(*out, p, 1);
  }
  return isError;
}

/*Поиск в строке спец.символов флагов начиная с символа "*c"
multy = 1 - поиск несколько флагов
return последний найденный спец.символ флага.*/
char find_flag(char **c, flags *flag, s21_size_t cnt, int multy) {
  char lastflag = '\0';
  int contin = 1;
  while (contin) {
    contin = 0;
    for (s21_size_t i = 0; i < cnt; i++) {
      if (flag[i].symbol == **c) {
        flag[i].value += 1;
        lastflag = **c;
        (*c)++;
        contin++;
        // if (flag[i].symbol == 32) setflagstatus(flag, cnt, '+', 0);
        // if (flag[i].symbol == '+') setflagstatus(flag, cnt, 32, 0);
        break;
      }
    }
    contin *= multy;
  }
  return lastflag;
}

/* Для ширины и точность. Начиная с "*c" в строке
считывается целые положительные числа */
void find_unsignedinteger(int *val, char **c, va_list *factor, parametrs *par) {
  int status = 1;
  if (**c == '*') {
    *val = va_arg(*factor, int);  // if (*val < 0) *val = 0;
    (*c)++;
  } else {
    if (**c == '-') {
      (*c)++;
      // setflagstatus(par, '-', 1);
      *val = status = 0;
    }
    for (; (char0 <= **c) && (**c <= char9); (*c)++) {
      if (*val < 0) *val = 0;
      (*val) = (*val) * 10 + (int)(**c - char0);
    }
    *val *= status;
  }
}

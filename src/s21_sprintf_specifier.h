#ifndef SRC_S21_SPRINTF_SPECIFIER_H_
#define SRC_S21_SPRINTF_SPECIFIER_H_
#include <float.h>
#include <math.h>
#include <wchar.h>

#include "s21_string.h"

#define char0 48
#define char9 57
#define charPoint 46

typedef struct flags {
  char symbol; /* char */
  int value;
  char *sp_list; /* применимость этого флага для спецификаторов */
} flags;

/* %[flag_show][width].[precision][flag_length] */
typedef struct parametrs {
  struct flags *show;  /* flag_show (multy) */
  s21_size_t cnt;      /* count of flag_show*/
  int wdt;             /* width */
  int prc;             /* precision */
  char len;            /*f flag_length (only one) */
  s21_size_t char_cnt; /* for %n*/
  char spec;           /* current specificator */
} parametrs;

typedef struct collection {
  char specifier;
  int (*operation_alloc)(char **out, va_list *factor, parametrs *par);
} collection;

char *strappend_alloc(char *dest, const char *src, s21_size_t n);
char *strbegin_alloc(char *dest, const char *src, s21_size_t n);
char *strAddCharsInFront(char *dest, char symbol, s21_size_t times);
char *strinvers(char *in);
void ShowStrValue(char **out, unsigned isnegative, parametrs *par);
void free_char_pointer_NULL(char **p);
int getflagstatus(parametrs *par, char c);
// void setflagstatus(flags *flag, int cnt, char c, int val);

char *IntToUnsignedStr(unsigned long long int d, int prc);
char *FloatToUnsignedStr(long double f, parametrs *par);
char *FloatToUnsignedStr2(long double f, parametrs *par);

int d_func(char **out, va_list *factor, parametrs *par);
int u_func(char **out, va_list *factor, parametrs *par);
int f_func(char **out, va_list *factor, parametrs *par);
int c_func(char **out, va_list *factor, parametrs *par);
int s_func(char **out, va_list *factor, parametrs *par);
int n_func(char **out, va_list *factor, parametrs *par);
int unknown_func(char **out, va_list *factor, parametrs *par);

#endif  // SRC_S21_SPRINTF_SPECIFIER_H_
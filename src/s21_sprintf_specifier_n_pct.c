#include "s21_sprintf_specifier.h"

int n_func(char **out, va_list *factor, parametrs *par) {
  if (!(*out)) {
    s21_size_t *n = (s21_size_t *)va_arg(*factor, s21_size_t *);
    *n = par->char_cnt;
  }
  return 0;
}

// int pct_func(char **out, va_list *factor, parametrs *par) {
//   if (!(*out)) {
//     char c = '%';
//     *out = strappend_alloc(*out, &c, 1);
//     ShowStrValue(out, 0, par);
//   }
//   if (par->cnt > 0) par->cnt *= 1;
//   return 0;
// }

int unknown_func(char **out, va_list *factor, parametrs *par) {
  if (!(*out)) {
    char c = par->spec;
    *out = strappend_alloc(*out, &c, 1);
    ShowStrValue(out, 0, par);
  }
  if (par->cnt > 0) par->cnt *= 1;
  return 0;
}
#include "s21_sprintf_specifier.h"

int u_func(char **out, va_list *factor, parametrs *par) {
  if (!(*out)) {
    unsigned long long int ul = (par->len == 'l')
                                    ? va_arg(*factor, unsigned long long int)
                                    : va_arg(*factor, unsigned int);
    *out = IntToUnsignedStr(ul, par->prc);
    ShowStrValue(out, 0, par);
  }
  return 0;
}

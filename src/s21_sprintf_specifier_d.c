#include "s21_sprintf_specifier.h"

int d_func(char **out, va_list *factor, parametrs *par) {
  if (!(*out)) {
    long long int d = (par->len == 'l') ? va_arg(*factor, long long int)
                                        : va_arg(*factor, int);
    int isnegative = (d < 0);
    if (isnegative) d *= (-1);
    *out = IntToUnsignedStr(d, par->prc);
    ShowStrValue(out, isnegative, par);
  }
  return 0;
}

/* Warning: alloc */
char *IntToUnsignedStr(unsigned long long int d, int prc) {
  char *out = s21_NULL;
  char c = 0;
  if (!(prc == 0 && d == 0)) {
    while (d > 9) {
      c = char0 + (d % 10);
      out = strappend_alloc(out, &c, 1);
      d = (unsigned long long int)(d / 10);
    }
    c = char0 + (d % 10);
    out = strappend_alloc(out, &c, 1);
    out = strinvers(out);
    if (prc > (int)s21_strlen(out))
      out = strAddCharsInFront(out, '0', prc - s21_strlen(out));
  }
  return out;
}

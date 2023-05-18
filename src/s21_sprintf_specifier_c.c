#include "s21_sprintf_specifier.h"

/* символ return 0 - успешно*/
int c_func(char **out, va_list *factor, parametrs *par) {
  if (!(*out)) {
    char cm[5] = {'\0', '\0', '\0', '\0', '\0'};
    if (par->len == 'l') {
      wchar_t wc[2];
      wc[0] = va_arg(*factor, wchar_t);
      wc[1] = (wchar_t)L'\0';
      s21_size_t len = wcstombs(cm, wc, 5);
      if (len > 0u) cm[len] = '\0';
    } else {
      cm[0] = (char)va_arg(*factor, int);
    }
    *out = strappend_alloc(*out, cm, s21_strlen(cm));
    ShowStrValue(out, 0, par);
  }
  return 0;
}
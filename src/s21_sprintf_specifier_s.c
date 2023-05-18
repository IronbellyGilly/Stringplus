#include "s21_sprintf_specifier.h"

/* Warning: string (re)alloc ; int 0..N - count wrote wchars, err=-1.. -n*/
int wchar2chr(char **cs, wchar_t *wcs) {
  s21_size_t i = 0;
  for (; i < wcslen(wcs); i++) {
    wchar_t wc[] = {wcs[i], L'\0'};
    char buff[] = {'\0', '\0', '\0', '\0', '\0'};
    wcstombs(buff, wc, wcslen(wc));
    if (s21_strlen(buff) == 0) {
      i *= (-1);
      break;
    }
    *cs = strappend_alloc(*cs, buff, s21_strlen(buff));
  }
  return i;
}

int s_func(char **out, va_list *factor, parametrs *par) {
  int isError = 0;
  char *snull = "(null)";
  if (!(*out)) {
    char *s = s21_NULL;
    if (par->len == 'l') {
      wchar_t *wc = va_arg(*factor, wchar_t *);
      if (wc)
        isError = wchar2chr(&s, wc) <= 0;
      else {
        wchar_t *wcnull = L"(null)";
        isError = wchar2chr(&s, wcnull) <= 0;
      }
    } else {
      s = va_arg(*factor, char *);
      if (!s) s = snull;
    }
    if (!isError) {
      *out = strappend_alloc(*out, s, s21_strlen(s));
      if (par->len == 'l') free(s);

      s21_size_t len = s21_strlen(*out);
      if ((par->prc >= 0) && ((par->prc < (long int)len)))
        for (s21_size_t i = par->prc; i < len; i++) (*out)[i] = '\0';

      ShowStrValue(out, 0, par);
      // s21_size_t diff = (par->wdt > (int)s21_strlen(*out)) ? par->wdt -
      // (int)s21_strlen(*out): 0; char /*if (!getflagstatus(par, (c = '0')))*/
      // c = ' '; if(getflagstatus(par, '-'))
      //   for (s21_size_t i = 0; i < diff; i++) *out = strappend_alloc(*out,
      //   &c, 1);
      // else *out = strAddCharsInFront(*out, c, diff);
    }
  }
  return isError;
}
#include "s21_sprintf_specifier.h"

int f_func(char **out, va_list *factor, parametrs *par) {
  if (!(*out)) {
    long double f = 0;
    if (par->len == 'L')
      f = va_arg(*factor, long double);
    else
      f = (long double)va_arg(*factor, double);
    int isnegative = (f < 0);
    if (isnegative) f *= (-1);
    *out = FloatToUnsignedStr(f, par);
    ShowStrValue(out, isnegative, par);
  }
  return 0;
}

/* Warning: alloc */
char *FloatToUnsignedStr(long double f, parametrs *par) {
  if (par->prc == -1) par->prc = 6;
  char *out = s21_NULL, *prt = s21_NULL, c = 0;
  unsigned long long int whole_part, wh_part_pf = 0;
  long double pf = 0;
  if (f < 1E20) {
    whole_part = (unsigned long long int)f;
    pf = (f - whole_part) * powl(10, par->prc);
    wh_part_pf = (unsigned long long int)pf;
    if (pf - wh_part_pf > 0.5) wh_part_pf += 1;
    pf = wh_part_pf * powl(0.10000, par->prc);

    if (pf >= 1) {
      whole_part += 1;
      pf -= 1;
      wh_part_pf = pf * powl(10, par->prc);
    }

    out = IntToUnsignedStr(whole_part, 1);
  } else {
    // s21_size_t times = 0;
    // while (f > 1E20*powl(10, times)) times++;
    // times+=20;
    // s21_size_t step = 19;
    // s21_size_t next = 0;
    // while ((times > step) || (times > 0)){
    //   if (times < step) step = 0;
    //   next = times - step;
    //   whole_part = f *powl(0.1, next);
    //   prt = IntToUnsignedStr(whole_part, step>0? step: next);
    //   out = strappend_alloc(out, prt, s21_strlen(prt));
    //   free_char_pointer_NULL(&prt);
    //   f -=  whole_part*powl(10, next);
    //   if (f<0) f = 0;
    //   times = next;
    //   if (step == 0) times = 0;
    // }
  }
  if ((par->prc > 0) || (getflagstatus(par, '#'))) {
    c = '.';
    out = strappend_alloc(out, &c, 1);
  }
  if (par->prc > 0) {
    prt = IntToUnsignedStr(wh_part_pf, par->prc);
    out = strappend_alloc(out, prt, s21_strlen(prt));
    free_char_pointer_NULL(&prt);
  }
  return out;
}
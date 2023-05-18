#include "s21_sprintf_specifier.h"
#include "s21_string.h"

void free_char_pointer_NULL(char** p) {
  free(*p);
  *p = s21_NULL;
}

/* Warning: alloc dest. */
char* strappend_alloc(char* dest, const char* src, s21_size_t n) {
  n = (s21_strlen(src) > n ? n : s21_strlen(src));
  if (n > 0) {
    if (!dest) {
      dest = (char*)malloc(sizeof(char) * 1);
      dest[0] = '\0';
    }
    s21_size_t oldsize = s21_strlen(dest);
    dest = (char*)realloc(dest, sizeof(char) * (oldsize + n + 1));
    for (s21_size_t i = oldsize; i < oldsize + n + 1; i++) dest[i] = '\0';
    s21_strncat(dest, src, n);
  }
  return dest;
}

char* strbegin_alloc(char* dest, const char* src, s21_size_t n) {
  char* temp = s21_NULL;
  temp = strinvers(strappend_alloc(temp, src, n));
  dest = strappend_alloc(strinvers(dest), temp, s21_strlen(temp));
  free(temp);
  return strinvers(dest);
}

// void ShowStrValue(char** out, unsigned isnegative, parametrs* par) {
//   char c = '-';
//   if (par->spec != 'u'){
//     if (isnegative)
//       *out = strbegin_alloc(*out, &c, 1);
//     else if (getflagstatus(par, (c = ' ')))
//       *out = strbegin_alloc(*out, &c, 1);
//     else if (getflagstatus(par, (c = '+')))
//       *out = strbegin_alloc(*out, &c, 1);
//   }
//   s21_size_t diff =
//       (par->wdt > (int)s21_strlen(*out)) ? par->wdt - (int)s21_strlen(*out) :
//       0;
//   c = '0';
//   if (!getflagstatus(par, '0')) c = ' ';

//   if (getflagstatus(par, '-')){
//     c = ' ';
//     for (s21_size_t i = 0; i < diff; i++)
//       *out = strappend_alloc(*out, &c, 1);
//   } else {
//     c = '0';
//     if (!getflagstatus(par, '0')) c = ' ';
//     *out = strAddCharsInFront(*out, c, diff);
//   }
// }

void addsign(char** out, unsigned isnegative, parametrs* par) {
  char c = '-';
  if (par->spec != 'u') {
    if (isnegative)
      *out = strbegin_alloc(*out, &c, 1);
    else if (getflagstatus(par, (c = '+')))
      *out = strbegin_alloc(*out, &c, 1);
    else if (getflagstatus(par, (c = ' ')))
      *out = strbegin_alloc(*out, &c, 1);
  }
}

void ShowStrValue(char** out, unsigned isnegative, parametrs* par) {
  int needaddsign =
      (isnegative + getflagstatus(par, ' ') + getflagstatus(par, '+') > 0);
  if (par->wdt > 0) par->wdt -= (par->spec != 'u') * needaddsign;

  s21_size_t diff =
      (par->wdt > (int)s21_strlen(*out)) ? par->wdt - (int)s21_strlen(*out) : 0;
  char c = '0';
  if (getflagstatus(par, '-')) {
    addsign(out, isnegative, par);
    c = ' ';
    for (s21_size_t i = 0; i < diff; i++) *out = strappend_alloc(*out, &c, 1);
  } else {
    addsign(out, isnegative, par);
    c = ' ';
    // if (s21_strchr("s", par->spec))  c = ' ';
    if (getflagstatus(par, '0') && !needaddsign) c = '0';
    *out = strAddCharsInFront(*out, c, diff);
  }
}

char* strAddCharsInFront(char* dest, char symbol, s21_size_t times) {
  if (times > 0) {
    char* prefix = (char*)calloc(times + 1, sizeof(char));
    for (s21_size_t i = 0; i < times; i++) prefix[i] = symbol;
    dest = strbegin_alloc(dest, prefix, s21_strlen(prefix));
    free(prefix);
  }
  return dest;
}

char* strinvers(char* in) {
  char* out = s21_NULL;
  int status = 0;
  s21_size_t len = s21_strlen(in);
  if (len) out = (char*)calloc(len + 1, sizeof(char));
  if (out) {
    for (s21_size_t i = 0; i < len; i++) out[i] = in[len - i - 1];
    for (s21_size_t i = 0; i < len; i++) in[i] = out[i];
    free(out);
    status++;
  }
  return in;
}

int getflagstatus(parametrs* par, char c) {
  int status = 0;
  if (par && par->show)
    for (s21_size_t i = 0; i < par->cnt; i++)
      if ((par->show[i].symbol == c) && (par->show[i].value) &&
          (!par->show[i].sp_list ||
           (s21_strchr(par->show[i].sp_list, par->spec))))
        status++;
  return status;
}

// void setflagstatus(flags* flag, int cnt, char c, int val) {
//   if (flag)
//     for (s21_size_t i = 0; i < cnt; i++)
//       if (flag[i].symbol == c) flag[i].value = val;
// }

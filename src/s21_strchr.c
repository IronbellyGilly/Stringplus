#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *s = (char *)str;
  int n = s21_strlen(str);
  while (n > 0 && *s != c) {
    s++;
    n--;
  }
  return !n ? s21_NULL : s;
}

#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *new;
  if (str) {
    new = str;
    while (s21_strchr(delim, *new)) *new ++ = '\0';
  }
  int endofnew = 0;
  if (!*new) {
    endofnew = 1;
  } else {
    str = new;
    while (*new && !s21_strchr(delim, *new)) new ++;
    while (*new &&s21_strchr(delim, *new)) *new ++ = '\0';
  }
  return endofnew ? s21_NULL : str;
}

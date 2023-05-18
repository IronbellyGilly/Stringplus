#include "s21_string.h"

void *s21_to_upper(const char *str) {
  s21_size_t i = 0;
  s21_size_t len = 0;
  char *buff = s21_NULL;
  if (str) {
    len = s21_strlen(str);
    buff = (char *)calloc(len + 1, sizeof(char));
  }
  if (str) {
    while (i <= len) {
      if (str[i] >= 97 && str[i] <= 122) {
        buff[i] = str[i] - 32;
      } else {
        buff[i] = str[i];
      }
      i++;
    }
  }
  return buff;
}

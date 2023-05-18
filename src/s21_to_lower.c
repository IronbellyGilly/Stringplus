#include "s21_string.h"

void* s21_to_lower(const char* str) {
  s21_size_t i = 0;
  s21_size_t len = s21_strlen(str);
  char* buff = s21_NULL;
  buff = (char*)calloc(len + 1, sizeof(char));

  if (str) {
    while (i <= len) {
      if (str[i] >= 65 && str[i] <= 90) {
        buff[i] = str[i] + 32;
      } else {
        buff[i] = str[i];
      }
      i++;
    }
  }
  return buff;
}

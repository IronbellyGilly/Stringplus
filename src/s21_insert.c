#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  int src_len = s21_strlen(src);
  int str_len = s21_strlen(str);
  int total_len = src_len + str_len;

  if ((int)start_index > src_len || (int)start_index < 0) return s21_NULL;

  char *buff = (char *)malloc(sizeof(char *) * (total_len) + 1);

  if (buff) {
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < (int)start_index) {
      buff[i] = src[i];
      i++;
      k++;
    }

    while (i < (int)start_index + str_len) {
      buff[i] = str[j];
      i++;
      j++;
    }

    while (i < total_len) {
      buff[i] = src[k];
      i++;
      k++;
    }

    buff[i] = '\0';
  }

  return buff;
}

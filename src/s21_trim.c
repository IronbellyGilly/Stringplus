#include "s21_string.h"

int first_occur(const char *src, const char *totrim, int offset);
int endwith(const char *src, const char *totrim, int offset);

void *s21_trim(const char *src, const char *trim_chars) {
  char *buff = s21_NULL;
  if (src) {
    if (trim_chars && trim_chars[0]) {
      buff = calloc(s21_strlen(src) + 1, 1);
      s21_size_t first = 0, end = s21_strlen(src);
      while (first_occur(src, trim_chars, first)) {
        first++;
      }
      if (first != end) {
        while (endwith(src, trim_chars, end)) end--;
      } else {
        *buff = '\0';
      }
      for (int i = 0; first < end; i++) {
        buff[i] = src[first];
        first++;
      }
    } else {
      buff = s21_trim(src, "\t\n ");
      ;
    }
  }
  return buff;
}

int first_occur(const char *src, const char *totrim, int offset) {
  int res = 0;
  int size = s21_strlen(totrim);
  for (int i = 0; i < size; i++) {
    if (src[offset] == totrim[i]) res = 1;
  }
  return res;
}

int endwith(const char *src, const char *totrim, int offset) {
  int res = 0;
  offset--;
  int size = s21_strlen(totrim);
  for (int i = 0; i < size; i++) {
    if (src[offset] == totrim[i]) res = 1;
  }
  return res;
}

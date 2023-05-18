#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  char *ptr = (char *)str;
  void *out = s21_NULL;
  for (s21_size_t i = 0; i < n && ptr; i++) {
    if (*ptr == (char)c) {
      out = ptr;
      break;
    }
    ptr++;
  }
  return out;
}

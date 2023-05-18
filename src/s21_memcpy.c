#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *stat = (char *)dest;
  char *copy = (char *)src;

  for (s21_size_t i = 0; i < n; i++) {
    stat[i] = copy[i];
  }
  return dest;
}

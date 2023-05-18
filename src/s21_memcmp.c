#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *st1 = (const unsigned char *)str1;
  const unsigned char *st2 = (const unsigned char *)str2;
  int result = 0;
  for (s21_size_t i = 0; i < n; i++) {
    result = *st1 - *st2;
    if (*st1 != *st2) break;
    st1++;
    st2++;
  }
  return result;
}

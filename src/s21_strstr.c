#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  const char *tmp = needle;
  while (*haystack) {
    const char *out = haystack;
    while (*(haystack++) == *(needle++)) {
      if (!(*needle)) return (char *)out;
      if (!(*haystack)) return s21_NULL;
    }
    needle = tmp;
  }
  return s21_NULL;
}
#include "s21_string.h"

s21_size_t s21_strlen(const char* str) {
  const char* end = str;
  for (; (end) && (*end != '\0');) ++end;
  return end - str;
}

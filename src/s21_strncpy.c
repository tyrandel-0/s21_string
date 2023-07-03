#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t len = s21_strlen(src);
  for (s21_size_t i = 0; i < len + 1 && i < n; i++) dest[i] = src[i];
  return dest;
}

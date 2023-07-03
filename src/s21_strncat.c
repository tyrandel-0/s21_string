#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  size_t dest_len = s21_strlen(dest);
  size_t src_len = s21_strlen(src);
  for (s21_size_t i = 0, j = dest_len; i < src_len + 1 && i < n; i++)
    dest[j + i] = src[i];
  return dest;
}
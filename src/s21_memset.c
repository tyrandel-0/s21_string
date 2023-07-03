#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  char *temp = str;
  for (s21_size_t i = 0; i < n; i++) {
    temp[i] = c;
  }
  return temp;
}
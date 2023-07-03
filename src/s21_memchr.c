#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  void *res = S21_NULL;
  char *temp = (char *)str;
  int break_for = 1;
  for (s21_size_t i = 0; i < n && break_for; i++) {
    if (*(char *)(temp + i) == c) {
      res = temp + i;
      break_for = 0;
    }
  }
  return res;
}
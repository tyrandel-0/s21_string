#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *temp = (char *)str;
  void *res = ((char)c == '\0') ? "\0" : S21_NULL;
  s21_size_t i = 0;
  // to the end of str
  while (*(temp + i) != '\0' && *(temp + i) != c) i++;
  if (*(temp + i) != '\0') res = temp + i;
  return res;
}
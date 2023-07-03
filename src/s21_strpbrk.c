#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = S21_NULL;
  for (int i = 0; str1[i]; i++) {
    if (s21_strchr(str2, str1[i])) {
      result = (char *)str1 + i;
      break;
    }
  }
  return result;
}
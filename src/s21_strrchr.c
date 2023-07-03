#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *res = S21_NULL;
  int found = -1;
  for (int i = 0; str[i]; i++) {
    if (str[i] == c) {
      found = i;
    }
  }
  if (found > -1) res = (char *)str + found;
  return c != '\0' ? res : "";
}
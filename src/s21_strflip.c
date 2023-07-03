#include "s21_string.h"

void s21_strflip(char* str) {
  int len = s21_strlen(str);
  char tmp;
  for (int i = 0; i < len / 2; i++) {
    tmp = str[i];
    str[i] = str[len - i - 1];
    str[len - i - 1] = tmp;
  }
}
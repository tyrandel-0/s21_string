#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  char *str = (char *)str1, *pattern = (char *)str2;
  s21_size_t i = 0;
  int flag = 1;
  //по символам строки str
  for (; *(str + i) != '\0' && flag; i++) {
    for (s21_size_t j = 0; *(pattern + j) != '\0' && flag; j++) {
      // сравниваем каждый символ строки str
      if (*(str + i) == *(pattern + j)) {
        flag = 0;
        i--;
      }
    }
  }
  return i;
}
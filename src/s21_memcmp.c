#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int res = 0, flag = 1;
  char *temp1 = (char *)str1, *temp2 = (char *)str2;
  for (s21_size_t i = 0; i < n && flag; i++) {
    if ((temp1[i]) != temp2[i]) {
      flag = 0;
      res += (temp1[i]) - (temp2[i]);
    }
  }
  return res;
}
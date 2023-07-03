#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *str_long = (char *)haystack, *str_small = (char *)needle,
       *res = S21_NULL;
  s21_size_t i = 0;
  int breakf = 1;
  // идем по символам строки 1
  for (; *(str_long + i) != '\0' && breakf; i++) {
    int inside = 1;
    for (s21_size_t j = 0; *(str_small + j) != '\0' && inside; j++) {
      // сравниваем каждый символ строки 1 со всеми символами стр 2
      if (*(str_long + i + j) != *(str_small + j)) inside = 0;
    }
    // если значение флага не изменилось, значит эта строка
    // содержится в большой с i элемента
    if (inside) {
      breakf = 0;
      res = str_long + i;
    }
  }
  return *needle || *haystack ? res : "";
}

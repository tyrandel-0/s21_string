#include "s21_string.h"

void *s21_to_upper(const char *str) {
  char *tmp = (char *)str;
  char *string = S21_NULL;
  if (tmp) {
    string = calloc(s21_strlen(str) + 1, sizeof(char));
    if (string) {
      for (int i = 0; tmp[i] != '\0'; i++) {
        if (tmp[i] >= 97 && tmp[i] <= 122)
          string[i] = tmp[i] - 32;
        else
          string[i] = tmp[i];
      }
    }
  }
  return (void *)string;
}

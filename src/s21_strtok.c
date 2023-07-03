#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *original_string = S21_NULL;
  if (str) original_string = str;
  char *token = S21_NULL, *tmp = original_string;
  if (original_string) {
    while (s21_strchr(delim, *tmp) && *tmp++)
      ;
    if (*tmp) token = tmp;
    while (!s21_strchr(delim, *tmp) && *tmp++)
      ;
    if (*tmp) {
      *tmp = '\0';
      original_string = tmp + 1;
    } else {
      original_string = S21_NULL;
    }
    if (*str == *delim) {
      token = S21_NULL;
    }
  }
  return token;
}
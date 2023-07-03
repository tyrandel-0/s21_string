#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_id) {
  s21_size_t lg_src = (src) ? s21_strlen(src) : 0;
  s21_size_t lg_str = (str) ? s21_strlen(str) : 0;
  char *tmp1 = (char *)src;
  char *tmp2 = (char *)str;
  char *string = S21_NULL;
  if (tmp1 && tmp2 && start_id <= s21_strlen(src)) {
    string = calloc(lg_src + lg_str + 1, sizeof(char));
    if (string) {
      for (s21_size_t i = 0; i < start_id; i++) string[i] = tmp1[i];
      for (s21_size_t i = start_id; i < start_id + lg_str; i++)
        string[i] = tmp2[i - start_id];
      for (s21_size_t i = start_id + lg_str; i < lg_src + lg_str; i++)
        string[i] = tmp1[i - lg_str];
    }
  }
  return (void *)string;
}

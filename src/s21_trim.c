#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_ch) {
  char *res = S21_NULL;
  if (src != S21_NULL) {
    if (trim_ch == NULL || trim_ch[0] == '\0') {
      trim_ch = " ";
    }
    s21_size_t len = s21_strlen(src);
    if (len) {
      int start = -1, end = -1, flagf = 1, flagl = 1, flag_break = 1;
      for (s21_size_t i = 0, j = len - 1; i < len && flag_break; i++, j--) {
        if (s21_strchr(trim_ch, src[i]) == S21_NULL && flagf) {
          start = i;
          flagf = 0;
        }
        if (s21_strchr(trim_ch, src[j]) == S21_NULL && flagl) {
          end = j;
          flagl = 0;
        }
        if (!flagf && !flagl) {
          flag_break = 0;
        }
      }
      res = calloc(end - start + 2, sizeof(char));
      if (res != S21_NULL) {
        for (int i = start, j = 0; i <= end; i++, j++) {
          res[j] = src[i];
        }
      }
    } else {
      res = calloc(2, sizeof(char));
    }
  }
  return res;
}
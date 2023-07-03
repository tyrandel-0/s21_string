#include "s21_string.h"

void *s21_memmove(void *destination, const void *source, s21_size_t num) {
  unsigned char *dest = (unsigned char *)destination;
  const unsigned char *src = (const unsigned char *)source;
  for (s21_size_t i = num; i > 0; --i) {
    dest[i - 1] = src[i - 1];
  }
  return destination;
}

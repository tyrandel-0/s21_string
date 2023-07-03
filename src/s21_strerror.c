#include "s21_errlist.h"
#include "s21_sprintf.h"
#include "s21_string.h"

char *s21_strerror(int errnum) {
  static char error[50];
  ERRORS;
  if (errnum >= 0 && errnum <= ERR_MAX)
    s21_sprintf(error, "%s", error_list[errnum]);
  else
    s21_sprintf(error, "%s%d", UNKNOWN_ERROR, errnum);
  return error;
}

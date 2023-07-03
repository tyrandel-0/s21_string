#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

#include "s21_string.h"

#ifndef S21_SPRINTF
#define S21_SPRINTF

#define ASCII_NUM_SHIFT 48
#define ASCII_CAP_ALPH_SHIFT 55
#define ASCII_ALPH_SHIFT 87

#define VAR_BUFF 256
#define STD_PRC 6

#define SWAP_IF_NEGATIVE(var) (var < 0 ? ((var) = -(var), 1) : 0)
#define S21_ISDIGIT(ch) ((ch) >= '0' && (ch) <= '9')
#define FLAGS spec_elems->flags

enum Flags {
  MINUS_FLAG = (1 << 0),
  PLUS_FLAG = (1 << 1),
  SPACE_FLAG = (1 << 2),
  OCTOTHORPE_FLAG = (1 << 3),
  ZERO_FLAG = (1 << 4),

  PRECISION = (1 << 5),

  H_LENGTH = (1 << 6),
  L_LENGTH = (1 << 7),
  LL_LENGTH = (1 << 8),
  LF_LENGTH = (1 << 9),

  REFLECT = (1 << 10),
  C_TYPE = (1 << 11),
  S_TYPE = (1 << 12),
  F_TYPE = (1 << 13),
  D_TYPE = (1 << 14),
  U_TYPE = (1 << 15),
  X_TYPE = (1 << 16),
  O_TYPE = (1 << 17),
  P_TYPE = (1 << 18),
  CAPITAL = (1 << 19)
};

typedef unsigned long s21_size_t;

typedef struct {
  unsigned int flags;
  int width;
  int prc;
} SpecElems;

// main function

int s21_sprintf(char* str, const char* format, ...);

// specifier parse functions

const char* set_flags(const char* src, SpecElems* spec_elems);
const char* set_width(const char* src, va_list arg_list, SpecElems* spec_elems);
const char* set_precision(const char* src, va_list arg_list,
                          SpecElems* spec_elems);
const char* set_length(const char* src, SpecElems* spec_elems);
const char* set_type(const char* src, SpecElems* spec_elems);

// variable processing functions

char* get_var(va_list arg_list, SpecElems* spec_elems);
char* format_var(char* dst, char* src, SpecElems* spec_elems);

// variable to string functions

void itoa(long long int var, char* buff);
void uitoa(unsigned long long int var, char* buff);
void itoax(unsigned long long int var, char* buff, _Bool is_capital);
void itoao(unsigned long long int var, char* buff);
void ftoal(long double var, char* buff, int prc, _Bool octothorpe);

// string to variable functions

unsigned long long s21_strtoull(const char* nptr);

// float processing functions

int fstatenl(long double var, char* buf, s21_size_t bsize);
long double froundl(long double var, int prc);

#endif

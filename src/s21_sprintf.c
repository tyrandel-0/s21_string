#include "s21_sprintf.h"

int s21_sprintf(char* str, const char* format, ...) {
  SpecElems spec_elems = {0};
  va_list arg_list;
  char* str_ptr = str;
  va_start(arg_list, format);
  while (*format) {
    if (*format == '%') {
      format++;
      format = set_flags(format, &spec_elems);
      format = set_width(format, arg_list, &spec_elems);
      format = set_precision(format, arg_list, &spec_elems);
      format = set_length(format, &spec_elems);
      format = set_type(format, &spec_elems);
      char* var = get_var(arg_list, &spec_elems);
      str_ptr = format_var(str_ptr, var, &spec_elems);
      if (var) free(var);
      spec_elems = (SpecElems){0};
    } else {
      *(str_ptr++) = *format++;
    }
  }
  *str_ptr = '\0';
  va_end(arg_list);
  return (int)s21_strlen(str);
}

const char* set_flags(const char* src, SpecElems* spec_elems) {
  while (1) {
    if (*src == ' ')
      FLAGS |= SPACE_FLAG;
    else if (*src == '-')
      FLAGS |= MINUS_FLAG;
    else if (*src == '+')
      FLAGS |= PLUS_FLAG;
    else if (*src == '#')
      FLAGS |= OCTOTHORPE_FLAG;
    else if (*src == '0')
      FLAGS |= ZERO_FLAG;
    else
      break;
    src++;
  }
  return src;
}

const char* set_width(const char* src, va_list arg_list,
                      SpecElems* spec_elems) {
  if (*src == '*') {
    spec_elems->width = (unsigned long long)va_arg(arg_list, int);
    src++;
  } else if ((spec_elems->width = s21_strtoull(src)))
    src++;
  while (S21_ISDIGIT(*src)) src++;
  return src;
}

const char* set_precision(const char* src, va_list arg_list,
                          SpecElems* spec_elems) {
  if (*src == '.') {
    src++;
    spec_elems->flags |= PRECISION;
    if (*src == '*') {
      spec_elems->prc = (unsigned long long)va_arg(arg_list, int);
      src++;
    } else if ((spec_elems->prc = s21_strtoull(src)))
      src++;
  } else
    spec_elems->prc = STD_PRC;
  while (S21_ISDIGIT(*src)) src++;
  return src;
}

unsigned long long s21_strtoull(const char* nptr) {
  unsigned long long num = 0;
  while (S21_ISDIGIT(*nptr)) {
    num = (num * 10) + (*nptr - ASCII_NUM_SHIFT);
    nptr++;
  }
  return num;
}

const char* set_length(const char* src, SpecElems* spec_elems) {
  if (*src == 'h')
    FLAGS |= H_LENGTH;
  else if (*src == 'L')
    FLAGS |= LF_LENGTH;
  else if (*src == 'l') {
    if (*(src + 1) != 'l')
      FLAGS |= L_LENGTH;
    else {
      FLAGS |= LL_LENGTH;
      src++;
    }
  }
  if (FLAGS & (H_LENGTH | L_LENGTH | LL_LENGTH | LF_LENGTH)) src++;
  return src;
}

const char* set_type(const char* src, SpecElems* spec_elems) {
  if (*src == 'c')
    FLAGS |= C_TYPE;
  else if (*src == 'd')
    FLAGS |= D_TYPE;
  else if (*src == 'f' || *src == 'F')
    FLAGS |= F_TYPE;
  else if (*src == 's')
    FLAGS |= S_TYPE;
  else if (*src == 'u')
    FLAGS |= U_TYPE;
  else if (*src == 'x')
    FLAGS |= X_TYPE;
  else if (*src == 'X')
    FLAGS |= (X_TYPE | CAPITAL);
  else if (*src == 'o')
    FLAGS |= O_TYPE;
  else if (*src == 'p')
    FLAGS |= P_TYPE;
  else if (*src == '%')
    FLAGS |= REFLECT;
  if (FLAGS & (REFLECT | C_TYPE | D_TYPE | F_TYPE | S_TYPE | U_TYPE | X_TYPE |
               O_TYPE | P_TYPE | CAPITAL))
    src++;
  return src;
}

char* get_var(va_list arg_list, SpecElems* spec_elems) {
  char* var = (char*)calloc(VAR_BUFF, s21_sizeof(char));
  char* var_ptr = var;
  if (var_ptr) {
    switch (FLAGS & (REFLECT | C_TYPE | S_TYPE | D_TYPE | U_TYPE | X_TYPE |
                     O_TYPE | P_TYPE | F_TYPE)) {
      case REFLECT: {
        *(var_ptr++) = '%';
        break;
      }
      case C_TYPE: {
        *(var_ptr++) = (char)va_arg(arg_list, int);
        break;
      }
      case S_TYPE: {
        char* buff = va_arg(arg_list, char*);
        s21_strncpy(var_ptr, buff, VAR_BUFF);
        break;
      }
      case D_TYPE: {
        if (FLAGS & L_LENGTH)
          itoa(va_arg(arg_list, long), var_ptr);
        else if (FLAGS & LL_LENGTH)
          itoa(va_arg(arg_list, long long), var_ptr);
        else
          itoa(va_arg(arg_list, int), var_ptr);
        break;
      }
      case U_TYPE: {
        if (FLAGS & L_LENGTH)
          uitoa(va_arg(arg_list, unsigned long), var_ptr);
        else if (FLAGS & LL_LENGTH)
          uitoa(va_arg(arg_list, unsigned long long), var_ptr);
        else
          uitoa(va_arg(arg_list, unsigned int), var_ptr);
        break;
      }
      case X_TYPE: {
        itoax(va_arg(arg_list, s21_size_t), var_ptr, FLAGS & CAPITAL);
        break;
      }
      case O_TYPE: {
        itoao(va_arg(arg_list, s21_size_t), var_ptr);
        break;
      }
      case P_TYPE: {
        s21_strncpy(var_ptr, "0x", VAR_BUFF);
        itoax(va_arg(arg_list, s21_size_t), (var_ptr + 2), 0);
        break;
      }
      case F_TYPE: {
        long double lf = 0;
        if (FLAGS & LF_LENGTH)
          lf = va_arg(arg_list, long double);
        else
          lf = va_arg(arg_list, double);
        if (fstatenl(lf, var, VAR_BUFF)) {
          lf = froundl(lf, spec_elems->prc);
          ftoal(lf, var, spec_elems->prc, FLAGS & OCTOTHORPE_FLAG);
        }
        break;
      }
    }
  }
  return var;
}

char* format_var(char* dst, char* src, SpecElems* spec_elems) {
  char* dst_ptr = dst;
  int reserved_places = 0;
  if (spec_elems->width) reserved_places = spec_elems->width - s21_strlen(src);
  if (FLAGS & D_TYPE || FLAGS & F_TYPE) {
    if (FLAGS & PLUS_FLAG) {
      if (*src != '-') reserved_places--;
      *(dst++) = *src == '-' ? *(src++) : '+';
    } else if (FLAGS & SPACE_FLAG) {
      if (*src != '-') reserved_places--;
      *(dst++) = *src == '-' ? *(src++) : ' ';
    } else if (*src == '-') {
      *(dst++) = *(src++);
    }
  }
  if (FLAGS & OCTOTHORPE_FLAG) {
    if (FLAGS & X_TYPE) {
      *(dst++) = '0';
      if (FLAGS & CAPITAL)
        *(dst++) = 'X';
      else
        *(dst++) = 'x';
      reserved_places -= 2;
    } else if (FLAGS & O_TYPE) {
      *(dst++) = '0';
      reserved_places--;
    }
  }
  if (FLAGS & PRECISION &&
      (FLAGS & D_TYPE || FLAGS & U_TYPE || FLAGS & O_TYPE)) {
    spec_elems->prc -= (int)s21_strlen(src);
    if (FLAGS & O_TYPE && FLAGS & OCTOTHORPE_FLAG) spec_elems->prc--;
    while (spec_elems->prc-- > 0) {
      *(dst++) = '0';
      reserved_places--;
    }
  }
  if (FLAGS & ZERO_FLAG && !(FLAGS & O_TYPE))
    while (reserved_places-- > 0) *(dst++) = '0';
  while (*src) *(dst++) = *(src++);
  if (FLAGS & MINUS_FLAG)
    while (reserved_places-- > 0) *(dst++) = ' ';
  else if (reserved_places > 0) {
    s21_memmove(dst_ptr + reserved_places, dst_ptr, s21_strlen(dst_ptr));
    dst += reserved_places;
    while (reserved_places-- > 0) *(dst_ptr++) = ' ';
  }
  return dst;
}

void itoa(long long int var, char* buff) {
  char* buff_ptr = buff;
  if (buff_ptr) {
    if (SWAP_IF_NEGATIVE(var)) *(buff_ptr++) = '-';
    long int divider = 1;
    while (var / divider > 9) divider *= 10;
    while (divider != 0) {
      long int digit = var / divider;
      *(buff_ptr++) = digit + ASCII_NUM_SHIFT;
      var %= divider;
      divider /= 10;
    }
  }
}

void uitoa(unsigned long long int var, char* buff) {
  char* buff_ptr = buff;
  if (buff_ptr) {
    long int divider = 1;
    while (var / divider > 9) divider *= 10;
    while (divider != 0) {
      long int digit = var / divider;
      *(buff_ptr++) = digit + ASCII_NUM_SHIFT;
      var %= divider;
      divider /= 10;
    }
  }
}

void itoax(unsigned long long int var, char* buff, _Bool is_capital) {
  char* buff_ptr = buff;
  if (var) {
    int rem = 0;
    while (var) {
      rem = var % 16;
      if (rem < 10)
        *(buff_ptr++) = rem + ASCII_NUM_SHIFT;
      else
        *(buff_ptr++) =
            is_capital ? rem + ASCII_CAP_ALPH_SHIFT : rem + ASCII_ALPH_SHIFT;
      var /= 16;
    }
    s21_strflip(buff);
  }
}

void itoao(unsigned long long int var, char* buff) {
  char* buff_ptr = buff;
  if (var) {
    int rem = 0;
    while (var) {
      rem = var % 8;
      *(buff_ptr++) = rem + ASCII_NUM_SHIFT;
      var /= 8;
    }
    s21_strflip(buff);
  }
}

int fstatenl(long double var, char* buf, s21_size_t bsize) {
  int isnormal = 1;
  if (isnan(var)) {
    s21_strncpy(buf, "nan", bsize);
    isnormal = 0;
  } else if (isinf(var)) {
    var < 0 ? s21_strncpy(buf, "-inf", bsize) : s21_strncpy(buf, "inf", bsize);
    isnormal = 0;
  }
  return isnormal;
}

long double froundl(long double num, int prc) {
  long double multiplier = 1.0;
  for (int i = 0; i < prc; ++i) {
    multiplier *= 10.0;
  }
  return (num * multiplier + 0.5) / multiplier;
}

void ftoal(long double var, char* buff, int prc, _Bool octothorpe) {
  char* buff_ptr = buff;
  if (buff_ptr) {
    if (SWAP_IF_NEGATIVE(var)) *(buff_ptr++) = '-';
    long double integer = 0;
    long double fraction = modfl(var, &integer);
    itoa((int)integer, buff_ptr);
    buff_ptr += s21_strlen(buff_ptr);
    if (prc || octothorpe) *(buff_ptr++) = '.';
    while (prc--) {
      fraction *= 10;
      integer = truncl(fraction);
      *(buff_ptr++) = integer + ASCII_NUM_SHIFT;
      fraction -= truncl(fraction);
    }
  }
}

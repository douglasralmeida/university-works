#include "types.h"

uint atoui(const char *s) {
  uint n;

  n = 0;
  while ('0' <= *s && *s <= '9')
    n = n*10 + *s++ - '0';
  return n;
}

char* uitoa(uint value, char* str) {
  int i = 0;
  
  if (value > 10000) {
   str[i] = value / 10000 + '0';
   i++;
  }
   
  if (value > 1000) {
   str[i] = value / 1000 % 10 + '0';   
   i++;
  }
  
  if (value > 100) {
   str[i] = value / 100 % 10 + '0';
   i++;
  }

  if (value > 10) {
   str[i] = value / 10 % 10 + '0';
   i++;
  }

  str[i] = value % 10 + '0';
  str[i+1] = '\0';

  return str;
}

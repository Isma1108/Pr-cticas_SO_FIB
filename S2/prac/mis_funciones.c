#include "mis_funciones.h"

unsigned int char2int(char c) {
  return c - '0';
}

int mi_atoi(char *s) {
  int neg = 0;
  if (s[0] == '-') {
    neg = 1;
    ++s;
  }
  int i = 0;
  int prod = 1, total = 0;
  for (i; s[i] != '\0'; ++i) {
    total = total*prod + char2int(s[i]);
    if (prod == 1) prod = 10;
  }
  if (neg == 1) return total*(-1);
  else return total;
}

int esNumero(char *str)
{
  if (str != NULL) {
      if (str[0] == '-') ++str;
      int i;
      for (i = 0; str[i] != '\0'; ++i) {
	      if (str[i] < '0' || str[i] > '9') return 0;
	    }
      if (i > 0 && i <= MAX_SIZE) return 1;
  }
  return 0;
}

void Usage() {
  char buff[100];
  sprintf(buff, "Usage: suma arg1 arg2 [arg3..argn]\nEste programa escribe por su salida la suma de los argumentos que recibe\n");
  write(1, buff, strlen(buff));
}



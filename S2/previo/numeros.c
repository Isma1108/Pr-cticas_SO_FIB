#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_SIZE 8

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

int main(int argc, char *argv[])
{
  char buff[100];
  for (int i = 1; i < argc; ++i) {
    if (esNumero (argv[i])) sprintf(buff, "%s es un numero de 8 o menos cifras\n", argv[i]);
    else sprintf(buff, "%s o NO es un numero, o es nulo, o es un numero de mas de 8 cifras\n", argv[i]);
    write(1, buff, strlen (buff));
  }
  return 0;
}

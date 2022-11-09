#include "mis_funciones.h"

int main(int argc, char *argv[])
{
  char buff[100];
  if (argc <= 2) Usage();
  else {
    int total = 0, i = 1, correcto = 1;

    while (i < argc && correcto == 1) {
      if (esNumero(argv[i])) total += mi_atoi(argv[i]);
      else --correcto;
      ++i;
    }
    if (correcto != 1) {
      --i;
      sprintf(buff, "Error: el parámetro “%s” no es un número de 8 o menos cifras\n", argv[i]);    
    }
    else sprintf(buff, "La suma es %i\n", total);
    write(1, buff, strlen(buff));
  }
  return 0;
}

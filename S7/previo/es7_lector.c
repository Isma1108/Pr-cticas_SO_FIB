#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
  //Primero lo recuperamos e interpretamos correctamente su valor
  int num;
  read(0, &num, sizeof(int));
  
  //Luego lo convertimos a cadena de caracteres ASCII
  char buff[64];
  sprintf(buff,"%d\n", num);
  write(1, buff, strlen(buff));
}

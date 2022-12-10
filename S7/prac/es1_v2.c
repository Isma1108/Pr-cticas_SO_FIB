#include <unistd.h>
#include <string.h>
#include <stdio.h>

// Este codigo escribe todos los bytes que lee de la entrada std en la salida stda

int
main ()
{
  char c;
  char *buf = "fin ejecución\n";
  char buffer[1024];
  int ret;
  // USO
  sprintf (buffer, "................................................\n");
  write (2, buffer, strlen (buffer));
  sprintf (buffer,
           "Este programa escribe por la salida std todo lo que lee de la entrada std. Si no has redirigido la salida, lo que escribas en el teclado saldra por la pantalla\n");
  write (2, buffer, strlen (buffer));
  sprintf (buffer, "Para acabar CtrlD\n");
  write (2, buffer, strlen (buffer));
  sprintf (buffer, "................................................\n");
  write (2, buffer, strlen (buffer));

  char buff[256];
  ret = read (0, &buff, 256);
  buff[ret] = '\0';
  
  while (ret > 0) {
    write(1, buff, strlen(buff));
    ret = read(0, &buff, 256);
    buff[ret] = '\0';
  }
  write (1, buf, strlen (buf));
}

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>

void trat(int s) {
  if (s == SIGINT) printf("Se ha recibido un SIGINT\n");
}

int main ()
{
  char c;

  struct sigaction sa;
  sigemptyset(&sa.sa_mask);
  sa.sa_handler = &trat;
  sa.sa_flags = SA_RESTART;
  sigaction(SIGINT, &sa, NULL);

  int ret = read (0, &c, sizeof (char));
  if (errno == EINTR) printf("read interrumpido por signal\n");
  else if (ret == -1) printf("read con error\n");
  else printf("read correcto\n");
  write (1, &c, sizeof (char));
  printf("\n");
}

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
/* ESTE PROCESO PROGRAMA UN TEMPORIZADOR PARA  DENTRO DE 5 SEGUNDOS Y SE BLOQUEA A ESPERAR QUE LLEGUE */
/* LA ACCION POR DEFECTO DEL SIGALRM ES ACABAR EL PROCESO */
int
main (int argc, char *argv[])
{
  sigset_t mask;

  sigemptyset (&mask);
  sigaddset (&mask, SIGALRM);
  sigprocmask (SIG_BLOCK, &mask, NULL);

  alarm (5);
  sigfillset (&mask);
  sigdelset (&mask, SIGALRM);
  sigdelset (&mask, SIGINT);
  
  char buff[128];
  sprintf(buff, "I'm process %d\n", getpid());
  write(1, buff, strlen(buff));
  sigsuspend (&mask);
  exit (1);
}

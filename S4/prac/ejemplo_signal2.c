#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>


int hijos = 0;
int contador = 0;

void error_y_exit (char *msg, int exit_status) {
  perror (msg);
  exit (exit_status);
}

void trata_alarma (int s) {}

void finaliza_hijo(int s) {
  int status, pid;
  while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
    char buff[128];
    if (WIFEXITED(status)) {      
      sprintf(buff,"Termina el proceso %d por EXIT: exit_code: %d\n", pid, WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status)) {
      sprintf(buff,"Termina el proceso %d por SIGNAL: signal_code: %d\n", pid, WTERMSIG(status));
    }
	  write(1, buff, strlen(buff));
    --hijos;
  }
}

int main (int argc, char *argv[])
{
  int pid, res;
  int pid_hijos[10];
  char buff[256];
  struct sigaction sa;
  sigset_t mask;

  /* Evitamos recibir el SIGALRM fuera del sigsuspend */

  sigemptyset (&mask);
  sigaddset (&mask, SIGALRM);
  sigprocmask (SIG_BLOCK, &mask, NULL);

  for (hijos = 0; hijos < 10; hijos++)
    {
      sprintf (buff, "Creando el hijo numero %d\n", hijos);
      write (1, buff, strlen (buff));

      pid = fork ();
      if (pid == 0)             /* Esta linea la ejecutan tanto el padre como el hijo */
        {
          sigemptyset(&mask);
          sigaddset(&mask, SIGUSR1);
          sigprocmask(SIG_BLOCK, &mask, NULL);

          sa.sa_handler = &trata_alarma;
          sa.sa_flags = SA_RESTART;
          sigfillset (&sa.sa_mask);
          if (sigaction (SIGALRM, &sa, NULL) < 0)
            error_y_exit ("sigaction", 1);

          /* Escribe aqui el codigo del proceso hijo */
          sprintf (buff, "Hola, soy %d\n", getpid ());
          write (1, buff, strlen (buff));
          
          /*
          alarm(1);
          sigfillset (&mask);
          sigdelset (&mask, SIGALRM);
          sigdelset (&mask, SIGINT);
          sigdelset (&mask, SIGUSR1);
          sigsuspend (&mask);
          */

          /* Termina su ejecución */
          exit (0);
        }
      else if (pid < 0)
        {
          /* Se ha producido un error */
          error_y_exit ("Error en el fork", 1);
        }
      pid_hijos[hijos] = pid;
    }
  /* Esperamos que acaben los hijos */
 
  //Quito el signal de la lista de bloqueados (si es que está)
  sigfillset(&mask);
  sigaddset(&mask, SIGCHLD);
  sigprocmask(SIG_UNBLOCK, &mask, NULL);
 
  //Reprogramo la acción asociada al signal SIGCHLD (esto sólo lo ejecuta el padre)
  sa.sa_handler = &finaliza_hijo;
  sa.sa_flags = SA_RESTART;
  sigemptyset(&sa.sa_mask);
  if (sigaction (SIGCHLD, &sa, NULL) < 0)
    error_y_exit ("sigaction", 1);

  for (int i = 0; i < 10; ++i) {
    kill(pid_hijos[i], SIGUSR1);
    ++contador;
  }

  while (hijos > 0); //espera activa hasta que terminen todos los hijos.

  sprintf (buff, "Valor del contador %d\n", contador);
  write (1, buff, strlen (buff));
  return 0;
}

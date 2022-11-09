#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>

int segundos = 0;

void trat_signal(int s) {
  if (s == SIGUSR1) {
    char buff[128];
    sprintf(buff, "inicio tratamiento\n");
    write(1, buff, strlen(buff));
    kill(getpid(), SIGINT);
    sprintf(buff, "fin tratamiento\n");
    write(1, buff, strlen(buff));
  }
}

//borradas las alarmas y SIGUSR2 ya que son irrelevantes para
//el objetivo de este ejercicio (comprender el tratamiento 
//secuencial o anidado de los signals)

int main() {
  struct sigaction trat;
  trat.sa_handler = &trat_signal;
  trat.sa_flags = SA_RESTART;
  sigemptyset(&trat.sa_mask);
  //sigaddset(&trat.sa_mask, SIGINT);
  sigaction(SIGUSR1, &trat, NULL);
  
  while (1);
}

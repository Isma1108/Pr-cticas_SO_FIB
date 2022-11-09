#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>

int segundos = 0;

void trat_signal(int s) {
  if (s == SIGALRM) ++segundos;
  else if (s == SIGUSR1) segundos = 0;
  else if (s == SIGUSR2) {
    char buff[128];
    sprintf(buff, "Contador: %d\n", segundos);
    write(1, buff, strlen(buff));
  }
  else if (s == SIGINT) exit(1);
}

int main() {

  sigset_t mask;
  sigemptyset(&mask);
  sigaddset(&mask, SIGALRM);
  sigaddset(&mask, SIGUSR1);
  sigaddset(&mask, SIGUSR2);
  sigprocmask(SIG_BLOCK, &mask, NULL);
  
  struct sigaction trat;
  trat.sa_handler = &trat_signal;
  trat.sa_flags = 0;
  sigemptyset(&trat.sa_mask);
  sigaction(SIGALRM, &trat, NULL);
  sigaction(SIGUSR1, &trat, NULL);
  sigaction(SIGUSR2, &trat, NULL);
  
  while (1) {
    if (alarm(alarm(0)) == 0) alarm(1);
    sigfillset(&mask);
    sigdelset(&mask, SIGALRM);
    sigdelset(&mask, SIGUSR1);
    sigdelset(&mask, SIGUSR2);
    sigdelset(&mask, SIGINT);
    sigsuspend(&mask);
  }
}

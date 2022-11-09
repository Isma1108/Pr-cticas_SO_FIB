#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>

#define REGION_SIZE		4096

int *p;
int *last_p;

void trat(int s) {
  if (s == SIGSEGV) {
    char buff[128];
    sprintf(buff, "&p: %p, p value: %p, *last_p: %p\n", &p, p, &last_p);
    write(1, buff, strlen(buff));
    exit(1);
  }
}


int
main (int argc, char *argv[])
{
  int i = 0;
  char buff[256];

  struct sigaction sa;
  sa.sa_handler = &trat;
  sa.sa_flags = 0;
  sigfillset(&sa.sa_mask);
  sigaction(SIGSEGV, &sa, NULL);

  sprintf (buff, "Addresses:\n");
  write (1, buff, strlen (buff));
  sprintf (buff, "\tp: %p\n", &p);
  write (1, buff, strlen (buff));

  p = malloc(sizeof (int));

  if (p == NULL)
    {
      sprintf (buff, "ERROR en el malloc\n");
      write (2, buff, strlen (buff));
    }

  while (1)
    {
      *p = i;
      sprintf(buff, "\tProgram code -- p address: %p, p value: %p, *p: %d\n",
               &p, p, *p);
      write (1, buff, strlen (buff));
      last_p = p;
      p++;
      i++;
    }

}

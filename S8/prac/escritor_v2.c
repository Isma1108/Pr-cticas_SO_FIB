#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

int main() {
  int fd = open("myPipe", O_WRONLY | O_NONBLOCK);
  if (fd == -1 && errno == ENXIO) {
    printf("Estoy esperando un lector...\n");
    fd = open("myPipe", O_WRONLY);
  }

  printf("Ya hay un lector!! :-)\n");
  char c;
  while (read(0, &c, sizeof(char)) > 0) {
    write(fd, &c, 1);
  }
}

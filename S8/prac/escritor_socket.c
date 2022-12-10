#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "socketMng.c"

void error_i_exit(char* msg) {
  perror(msg);
  exit(1);
}

int main() {
  
  int c_fd = clientConnection("server");
  if (c_fd < 0) error_i_exit("Error establishing connection\n");

  char c;
  while (read(0, &c, 1) > 0) {
    write(c_fd, &c, 1);
  }
  closeConnection(c_fd);
}

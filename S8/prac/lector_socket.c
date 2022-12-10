#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "socketMng.c"

void error_i_exit(char *msg) {
  perror(msg);
  exit(1);
}

int main() {
  int s_fd = createSocket("server");
  if (s_fd < 0) error_i_exit("Error creating socket\n");

  int c_fd = serverConnection(s_fd);
  if (c_fd < 0) error_i_exit("Error establishing connection\n");
  
  char c;
  while (read(c_fd, &c, 1) > 0) {
    write(1, &c, 1);
  }

  closeConnection(c_fd);
  deleteSocket(s_fd, "server");
}

#include <unistd.h>
#include <fcntl.h>

int main() {
  int fd = open("myPipe", O_WRONLY);

  char c;
  while (read(0, &c, 1) > 0) {
    write(fd, &c, 1);
  }
}

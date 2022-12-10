#include <unistd.h>
#include <fcntl.h>

int main() {
  int fd = open("myPipe", O_RDONLY);
  
  char c;
  while (read(fd, &c, 1) > 0) {
    write(1, &c, 1);
  }
}

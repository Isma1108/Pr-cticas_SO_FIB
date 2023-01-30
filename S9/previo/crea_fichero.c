#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

void error_y_exit(char *msg) {
	perror(msg);
	exit(1);
}

int main() {
	char buffer[256];
	int fd = creat("salida.txt", O_CREAT|S_IRUSR|S_IWUSR);
	if (fd < 0) error_y_exit("Fallo en el creat");
	sprintf(buffer, "ABCD");
	write(fd, buffer, strlen(buffer));
}

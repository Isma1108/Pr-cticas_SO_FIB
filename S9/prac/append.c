#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFF_SIZE 128

void error_y_exit(char *msg) {
	perror(msg);
	exit(1);
}

int main() {
	int fd_write = open("file", O_WRONLY);
	if (fd_write < 0) error_y_exit("Error en el open\n");
	
	int fd_read = open("file", O_RDONLY);
	if (fd_read < 0) error_y_exit("Error en el open\n");
	
	char buff[BUFF_SIZE];

	int i = 0;
	while (read(fd_read, &buff[i], sizeof(char)) > 0) ++i;
	buff[i] = '\0';

	lseek(fd_write, -1, SEEK_END);
	for (int i = 0; buff[i] != '\0'; ++i) write(fd_write, &buff[i], sizeof(char));
}


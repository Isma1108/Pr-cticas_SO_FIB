#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 128

void Usage() {
	printf("./invirtiendo_fichero fichero\n");
}

void error_y_exit(char *msg) {
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[]) {
	if (argc != 2) Usage();
	int fd_read = open(argv[1], O_RDONLY);
	if (fd_read < 0) error_y_exit("Error en el open\n");

	char buffer[BUFF_SIZE];
	sprintf(buffer, "%s.inv", argv[1]);
	int fd_write = open(buffer, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd_write < 0) error_y_exit("Error en el open\n");

	char buff[BUFF_SIZE];
	int i = 1;
	buff[0] = '\0';
	while (read(fd_read, &buff[i], sizeof(char)) > 0) ++i;

	for (i; i >= 0; --i) write(fd_write, &buff[i], sizeof(char));
}


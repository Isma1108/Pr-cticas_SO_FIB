#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void error_y_exit(char *msg,int exit_status) {
	perror(msg);
	exit(exit_status);
}

int main(int argc, char *argv[]) {
	char buff[100];
	int pid = fork();
	if (pid == 0) {
		sprintf(buff, "Soy el proceso hijo con PID: %d y el parametro es %s\n", getpid(), argv[1]);
	}
	else if (pid < 0) error_y_exit("Error en fork",1);
	else {
		sprintf(buff, "Soy el proceso padre con PID: %d\n", getpid());
	}
	write(1, buff, strlen(buff));
	while (1);
	return 0;
}


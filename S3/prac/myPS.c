#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void error_y_exit(char *msg, int exit_status) {
	perror(msg);
	exit(exit_status);
}

/* Ejecuta el comando ps –u username mediante la llamada al sistema execlp */
/* Devuelve: el código de error en el caso de que no se haya podido mutar */
void muta_a_PS(char *username) {
	execlp("ps", "ps", "-u", username, (char*)NULL);
	error_y_exit("Ha fallado la mutación al ps", 1);
}

int main(int argc, char *argv[]) {
	char buff[100];
	int pid = fork();
	if (pid == 0) {
		sprintf(buff, "Soy el proceso HIJO con PID: %d y el parametro es %s\n", getpid(), argv[1]);
	}
	else if (pid < 0) error_y_exit("Error en fork",1);
	else sprintf(buff, "Soy el proceso PADRE con PID: %d\n", getpid());

	write(1, buff, strlen(buff));
	if (pid == 0) muta_a_PS(argv[1]);
	while (1);
	return 0;
}


#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

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
	for (int i = 1; i < argc; ++i) {
		int pid = fork();
		if (pid == 0) {
			sprintf(buff, "Soy el proceso HIJO con PID: %d y el usuario es %s\n", getpid(), argv[i]);
			write(1, buff, strlen(buff));
			muta_a_PS(argv[i]);
			//El hijo muta por lo que no es necesaria la llamada exit(0) para la ejecucion secuencial.
		}
		else if (pid < 0) error_y_exit("Error en fork",1);
		else {
			sprintf(buff, "Soy el proceso PADRE con PID: %d\n", getpid());
			write(1, buff, strlen(buff));
			waitpid(-1, NULL, 0);
		}
	}
	return 0;
}


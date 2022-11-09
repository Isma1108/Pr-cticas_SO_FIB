#include <sys/wait.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
	int pid = fork();
	if (pid == 0) execlp("./listaParametros", "listaParametros", "a", "b", (char *)0);
	pid = fork();
	if (pid == 0) execlp("./listaParametros", "listaParametros", (char *)0);
	pid = fork();
	if (pid == 0) execlp("./listaParametros", "listaParametros", "25", "4", (char *)0);
	pid = fork();
	if (pid == 0) execlp("./listaParametros", "listaParametros", "1024", "hola", "adios", (char *)0);

	while (waitpid(-1, NULL, 0) > 0);
	return 0;
}

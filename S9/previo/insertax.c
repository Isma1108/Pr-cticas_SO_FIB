#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void error_y_exit(char *msg) {
	perror(msg);
	exit(1);
}

int main() {
	char buff1[256];
	char buff2[256];
	
	int fd = open("salida.txt", O_RDWR);
	if (fd < 0) error_y_exit("Error en el open");
	
	//Primeramente colocamos el puntero l/e a la penúltima posicion (para poder leer el último car.)
	lseek(fd, -1, SEEK_END);
	//Leemos el último carácter y lo guardamos en un buffer.
	read(fd, buff1, sizeof(char));

	// Movemos el puntero l/e a una posicion anterior a la actual para escribir la letra 'X'.
	lseek(fd,-1,SEEK_CUR);
	
	//Escribimos la letra 'X'
	sprintf(buff2,"X");
	write(fd, buff2, strlen(buff2));

	//Añadimos el último carácter de nuevo.
	write(fd, buff1, strlen(buff1));
}

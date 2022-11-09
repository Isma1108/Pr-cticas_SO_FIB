#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define STDOUT 1

int main(int argc, char *argv[]) {
	char buffer[256];
	sprintf(buffer, "Esto es la prueba nº %d\n", 1);
	write(STDOUT, buffer, strlen(buffer));
}

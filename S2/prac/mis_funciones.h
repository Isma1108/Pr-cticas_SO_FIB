#ifndef MIS_FUNCIONES_HH
#define MIS_FUNCIONES_HH

#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_SIZE 8


// pre: El  carácter c se corresponde con el carácter de un número.
// post: Devuelve un unsigned integer correspondiente al carácter convertido a número.
unsigned int char2int(char c);

// pre: s es un string, y NO es un puntero a NULL.
// post: Devuelve un entero correspondiente al string convertido a número.
int mi_atoi(char *s);

// pre: str es un string.
// post: Devuelve 1 si el string str representa un número y tiene como mucho
// 			 8 cifras, y 0 en cualquier otro caso.
int esNumero(char *str);

// pre: cierto.
// post: Escribe por la salida estándard un mensaje que describe el funcionamiento del 
// 			 programa suma. 
void Usage();

#endif


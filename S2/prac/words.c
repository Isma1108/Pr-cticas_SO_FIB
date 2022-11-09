#include <unistd.h>
#include <string.h>
#include <stdio.h>

int is_space(char c) {
	return (c == ' ' || c == '.' || c == ',' || c == '\n');
}

int word_counter(char *str) {
	int t = 0, i = 0;
	for (i; str[i] != '\0'; ++i) {
		if (is_space(str[i]) == 1 && i != 0 && is_space(str[i-1]) == 0) ++t;
	}
	if (i > 0 && is_space(str[i-1]) == 0) ++t;
	return t;
}

int main(int argc, char *argv[]) {
	char buff[100];
	if (argc == 1) sprintf(buff, "Error: no se ha pasado ninguna palabra.\n");
	else {
		int words = word_counter(argv[1]);
		sprintf(buff, "%i palabras\n", words);
	}
	write(1, buff, strlen(buff));
	return 0;
}

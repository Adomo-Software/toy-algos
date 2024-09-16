#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	ssize_t read;

	FILE *stream;
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	stream = fopen(argv[1], "r");
	if (stream == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	nread = getline(&line, &len, stream);
	int jmp_amt = (int)sqrt(len);
	int i;
	for(i = 0; i <= len; i+=jmp_amt) {
		if(line[i] == '0') break;
	}
	for(i = i-jmp_amt; i <= len; i++) {
		if(line[i] == '0') break;
	}

	printf("%d", i);
	return 0;
}

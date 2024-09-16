#define _GNU_SOURCE
#include <stdio.h>
#include "c-vector/vec.h"

void swap(int* vec, size_t index) {
	int tmp = vec[index];
	vec[index] = vec[index + 1];
	vec[index + 1] = tmp;
}

void sort(int* vec) {
	size_t size = vector_size(vec);
	for(int iter = 0; iter < size; ++iter) {
		for(int i = 0; i < size - iter -1; ++i) {
			if (vec[i] > vec[i+1]) {
				swap(vec, i);
			}
		}
	}
}

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

	int* v = vector_create();
	

	while ((nread = getline(&line, &len, stream)) != -1) {

		int add = atoi(line);
		printf("%d ", add);
		vector_add(&v, add);
	}

	printf("\n");
	/*swap(v, 0);*/
	sort(v);
	for (vec_size_t i = 0; i < vector_size(v); ++i) {
		printf("%d ", v[i]);
	}


	printf("\n");
	return 0;
}

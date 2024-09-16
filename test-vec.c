#include <stdlib.h>
#include <stdio.h>
#include "vec.h"

void print_int(void* elem) {
    printf("%d ", elem);
}



int main(void) {
	char* char_vec = vector_create();

	int* int_vec = vector_create();
	// add an item
	vector_add(&char_vec, 'a');
	vector_add(&char_vec, 'b');
	vector_add(&char_vec, 'c');

	vector_add(&int_vec, 2);
	vector_add(&int_vec, 3);
	vector_add(&int_vec, 4);
	vector_add(&int_vec, 5);
	vector_add(&int_vec, 5);
	vector_add(&int_vec, 5);

	vector_print(int_vec, print_int);




	return 69;
}

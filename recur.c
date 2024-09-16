#include<stdio.h>
#include <stdlib.h>

int fib(int n) {
	if (n < 2) {
		return 1;
	} else {
		return fib(n - 1) + fib(n - 2);
	}
}
int sum(int n) {
	if (n == 1) {
		return 1;
	}
	return n + fib2(n - 1);
}

int main(int argc, char *argv[]) {
	int n = atoi(argv[1]); 
	/*if */
	printf("%d\n", sum(n));
}

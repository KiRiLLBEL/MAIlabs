#include <stdlib.h>
#include <stdio.h>

int main() {
	
	int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
	
	for (int i = 0; i < 10; i++) {
		printf("%d ", a[i]); 
	}

	int *b = (int *)malloc(10 * sizeof(int));
	for (int i = 0; i < 10; i++) {
		*(b + i) = i; // b[i] = i
		printf("%d ", b[i]); 
	}
	printf("\n");
	b = (int *)realloc(b, 20 * sizeof(int));
	for (int i = 0; i < 20; i++) {
		if (i >= 10)
			*(b + i) = i;
		printf("%d ", b[i]); 
	}
	free(b);
	printf("\n");
	return 0;
}

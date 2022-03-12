#include <stdlib.h>
#include <stdio.h>

int main() {
	
	int v = 10;
	int *pv = &v;
	int v1 = *pv;
	printf("%d %d\n", v, v1);
	v = 15;
	printf("%d %d %d\n", v, v1, *pv);

	return 0;
}

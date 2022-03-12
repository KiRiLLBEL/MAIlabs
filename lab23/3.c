#include <stdlib.h>
#include <stdio.h>

typedef struct _point {
	int x;
	int y;
} point;

point make_point(int x, int y) {
	point p;
	p.x = x;
	p.y = y;
	return p;
}

point *make_point_pointer(int x, int y) {
	point *p = (point*)malloc(sizeof(point));
	p->x = x;
	p->y = y;
	return p;
}

void change_point(point p) {
	p.x++;
	p.y++;
}

void change_point_pointer(point* p) {
	p->x++;
	p->y++;
}

void free_point(point *p) {
	free(p);
}

int main() {
	
	point p1 = make_point(10, 15);
	printf("%d %d\n", p1.x, p1.y);
	change_point(p1);
	printf("%d %d\n", p1.x, p1.y);

	point *p2 = make_point_pointer(10, 15);
	printf("%d %d\n", p2->x, p2->y);
	change_point_pointer(p2);
	printf("%d %d\n", p2->x, p2->y);
	free_point(p2);

	return 0;
}

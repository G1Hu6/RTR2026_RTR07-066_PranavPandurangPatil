#include <stdio.h>

typedef struct {
	int x;
	int y;
} Point;

typedef struct {
	Point p1;
	Point p2;
} Rectangle;

int main(void)
{
	//variable declaraions
	int len, width, a;
	Rectangle r = { { 3, 5 }, { 9, 12 } };

	//code
	len = r.p2.y - r.p1.y;
	if (len < 0)
		len = len * -1;

	width = r.p2.x - r.p1.x;
	if (width < 0)
		width = width * -1;

	a = len * width;

	printf("\n\n");
	printf("Length Of Rectangle = %d\n\n", len);
	printf("Breadth Of Rectangle = %d\n\n", width);
	printf("Area Of Rectangle = %d\n\n", a);

	return(0);
}


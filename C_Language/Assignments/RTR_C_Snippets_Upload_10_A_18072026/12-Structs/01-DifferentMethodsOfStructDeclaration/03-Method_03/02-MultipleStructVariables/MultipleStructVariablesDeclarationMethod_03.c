#include <stdio.h>

int main(void)
{
	//variable declaraions
	typedef struct {
		int x;
		int y;
	} Point;

	Point p1, p2, p3, p4, p5;

	//code
	p1.x = 5;
	p1.y = 0;

	p2.x = 2;
	p2.y = 4;

	p3.x = 6;
	p3.y = 3;

	p4.x = 7;
	p4.y = 1;

	p5.x = 10;
	p5.y = 5;

	printf("\n\n");
	printf("Co-ordinates (x, y) Of Point 'A' Are : (%d, %d)\n\n", p1.x, p1.y);
	printf("Co-ordinates (x, y) Of Point 'B' Are : (%d, %d)\n\n", p2.x, p2.y);
	printf("Co-ordinates (x, y) Of Point 'C' Are : (%d, %d)\n\n", p3.x, p3.y);
	printf("Co-ordinates (x, y) Of Point 'D' Are : (%d, %d)\n\n", p4.x, p4.y);
	printf("Co-ordinates (x, y) Of Point 'E' Are : (%d, %d)\n\n", p5.x, p5.y);

	return(0);
}


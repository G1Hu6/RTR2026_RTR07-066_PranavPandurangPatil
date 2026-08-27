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
	Rectangle r;

	//code
	printf("\n\n");
	printf("Enter Leftmost X-Coordinate Of Rectangle : ");
	scanf("%d", &r.p1.x);

	printf("\n\n");
	printf("Enter Bottommost Y-Coordinate Of Rectangle : ");
	scanf("%d", &r.p1.y);

	printf("\n\n");
	printf("Enter Rightmost X-Coordinate Of Rectangle : ");
	scanf("%d", &r.p2.x);

	printf("\n\n");
	printf("Enter Topmost Y-Coordinate Of Rectangle : ");
	scanf("%d", &r.p2.y);

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


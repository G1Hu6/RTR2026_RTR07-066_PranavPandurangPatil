#include <stdio.h>

typedef struct {
	int x;
	int y;
} Point;

int main(void)
{
	//variable declaraions
	Point p1, p2, p3, p4, p5;

	//code
	printf("\n\n");
	printf("Enter X-Coordinate For Point 'A' : ");
	scanf("%d", &p1.x);
	printf("Enter Y-Coordinate For Point 'A' : ");
	scanf("%d", &p1.y);

	printf("\n\n");
	printf("Enter X-Coordinate For Point 'B' : ");
	scanf("%d", &p2.x);
	printf("Enter Y-Coordinate For Point 'B' : ");
	scanf("%d", &p2.y);

	printf("\n\n");
	printf("Enter X-Coordinate For Point 'C' : ");
	scanf("%d", &p3.x);
	printf("Enter Y-Coordinate For Point 'C' : ");
	scanf("%d", &p3.y);

	printf("\n\n");
	printf("Enter X-Coordinate For Point 'D' : ");
	scanf("%d", &p4.x);
	printf("Enter Y-Coordinate For Point 'D' : ");
	scanf("%d", &p4.y);

	printf("\n\n");
	printf("Enter X-Coordinate For Point 'E' : ");
	scanf("%d", &p5.x);
	printf("Enter Y-Coordinate For Point 'E' : ");
	scanf("%d", &p5.y);

	printf("\n\n");
	printf("Co-ordinates (x, y) Of Point 'A' Are : (%d, %d)\n\n", p1.x, p1.y);
	printf("Co-ordinates (x, y) Of Point 'B' Are : (%d, %d)\n\n", p2.x, p2.y);
	printf("Co-ordinates (x, y) Of Point 'C' Are : (%d, %d)\n\n", p3.x, p3.y);
	printf("Co-ordinates (x, y) Of Point 'D' Are : (%d, %d)\n\n", p4.x, p4.y);
	printf("Co-ordinates (x, y) Of Point 'E' Are : (%d, %d)\n\n", p5.x, p5.y);

	return(0);
}


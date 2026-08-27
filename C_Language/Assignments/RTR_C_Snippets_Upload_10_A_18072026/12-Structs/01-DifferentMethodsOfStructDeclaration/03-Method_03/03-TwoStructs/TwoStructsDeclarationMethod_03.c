#include <stdio.h>
#include <string.h>

int main(void)
{
	//variable declaraions
	typedef struct {
		int x;
		int y;
	} Point;

	typedef struct {
		int quad;
		char axisLoc[10];
	} PointProps;

	Point pt;
	PointProps props;

	//code
	printf("\n\n");
	printf("Enter X-Coordinate For A Point : ");
	scanf("%d", &pt.x);
	printf("Enter Y-Coordinate For A Point : ");
	scanf("%d", &pt.y);

	printf("\n\n");
	printf("Point Co-ordinates (x, y) Are : (%d, %d) !!!\n\n", pt.x, pt.y);

	if (pt.x == 0 && pt.y == 0)
		printf("The Point Is The Origin (%d, %d) !!!\n", pt.x, pt.y);
	else
	{
		if (pt.x == 0)
		{
			if (pt.y < 0)
				strcpy(props.axisLoc, "Negative Y");

			if (pt.y > 0)
				strcpy(props.axisLoc, "Positive Y");

			props.quad = 0;
			printf("The Point Lies On The %s Axis !!!\n\n", props.axisLoc);
		}
		else if (pt.y == 0)
		{
			if (pt.x < 0)
				strcpy(props.axisLoc, "Negative X");

			if (pt.x > 0)
				strcpy(props.axisLoc, "Positive X");

			props.quad = 0;
			printf("The Point Lies On The %s Axis !!!\n\n", props.axisLoc);
		}
		else
		{
			props.axisLoc[0] = '\0';

			if (pt.x > 0 && pt.y > 0)
				props.quad = 1;
			else if (pt.x < 0 && pt.y > 0)
				props.quad = 2;
			else if (pt.x < 0 && pt.y < 0)
				props.quad = 3;
			else
				props.quad = 4;

			printf("The Point Lies In Quadrant Number %d !!!\n\n", props.quad);
		}
	}

	return(0);
}


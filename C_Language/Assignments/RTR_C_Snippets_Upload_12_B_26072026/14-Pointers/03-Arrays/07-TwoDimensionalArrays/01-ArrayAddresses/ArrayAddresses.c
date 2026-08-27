#include <stdio.h>
#include <stdlib.h>

#define NUM_ROWS 3
#define NUM_COLUMNS 2

int main(void)
{
	//variable declaraions
	int arr2D[NUM_ROWS][NUM_COLUMNS];
	int r, c;

	//code
	for (r = 0; r < NUM_ROWS; r++)
	{
		for (c = 0; c < NUM_COLUMNS; c++)
			arr2D[r][c] = (r + 1) * (c + 2);
	}

	printf("\n\n");
	printf("2D Integer Array Elements Along With Addresses : \n\n");
	for (r = 0; r < NUM_ROWS; r++)
	{
		for (c = 0; c < NUM_COLUMNS; c++)
		{
			printf("arr2D[%d][%d] = %d \t \t At Address : %p\n", r, c, arr2D[r][c], &arr2D[r][c]);
		}
		printf("\n\n");
	}

	return(0);
}


#include <stdio.h>

#define NUM_ROWS 3
#define NUM_COLUMNS 2

int main(void)
{
	//variable declaraions
	int arr2D[NUM_ROWS][NUM_COLUMNS];
	int r, c;
	int *pRow = NULL;

	//code
	for (r = 0; r < NUM_ROWS; r++)
	{
		pRow = arr2D[r];
		for (c = 0; c < NUM_COLUMNS; c++)
			*(pRow + c) = (r + 1) * (c + 2);
	}

	printf("\n\n");
	printf("2D Integer Array Elements Along With Addresses : \n\n");
	for (r = 0; r < NUM_ROWS; r++)
	{
		pRow = arr2D[r];
		for (c = 0; c < NUM_COLUMNS; c++)
		{
			printf("*(pRow + %d) = %d \t \t At Address (pRow + %d) : %p\n", c, *(pRow + c), c, (pRow + c));
		}
		printf("\n\n");
	}

	return(0);
}


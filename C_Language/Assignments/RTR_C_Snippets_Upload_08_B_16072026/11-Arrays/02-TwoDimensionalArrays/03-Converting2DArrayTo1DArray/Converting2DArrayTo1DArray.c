#include <stdio.h>

#define NUM_ROWS 5
#define NUM_COLUMNS 3

int main(void)
{
	//variable declaraions
	int iArr2D[NUM_ROWS][NUM_COLUMNS];
	int iArr1D[NUM_ROWS * NUM_COLUMNS];

	int i, j;
	int n;

	//code
	printf("Enter Elements Of Your Choice To Fill Up The Integer 2D Array : \n\n");
	for (i = 0; i < NUM_ROWS; i++)
	{
		printf("For ROW NUMBER %d : \n", (i + 1));
		for (j = 0; j < NUM_COLUMNS; j++)
		{
			printf("Enter Element Number %d : \n", (j + 1));
			scanf("%d", &n);
			iArr2D[i][j] = n;
		}
		printf("\n\n");
	}

	printf("\n\n");
	printf("Two-Dimensional ( 2D ) Array Of Integers : \n\n");
	for (i = 0; i < NUM_ROWS; i++)
	{
		printf("ROW %d \n", (i + 1));
		for (j = 0; j < NUM_COLUMNS; j++)
		{
			printf("iArr2D[%d][%d] = %d\n", i, j, iArr2D[i][j]);
		}
		printf("\n\n");
	}

	for (i = 0; i < NUM_ROWS; i++)
	{
		for (j = 0; j < NUM_COLUMNS; j++)
		{
			iArr1D[(i * NUM_COLUMNS) + j] = iArr2D[i][j];
		}
	}

	printf("\n\n");
	printf("One-Dimensional ( 1D ) Array Of Integers : \n\n");
	for (i = 0; i < (NUM_ROWS * NUM_COLUMNS); i++)
	{
		printf("iArr1D[%d] = %d\n", i, iArr1D[i]);
	}

	printf("\n\n");

	return(0);
}


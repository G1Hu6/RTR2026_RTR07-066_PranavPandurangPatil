#include <stdio.h>
#include <stdlib.h>

#define NUM_ROWS 3
#define NUM_COLUMNS 2

int main(void)
{
	//variable declaraions
	int *pArr[NUM_ROWS];
	int r, c;

	//code
	printf("\n\n");
	for (r = 0; r < NUM_ROWS; r++)
	{
		pArr[r] = (int *)malloc(NUM_COLUMNS * sizeof(int));
		if (pArr[r] == NULL)
		{
			printf("FAILED TO ALLOCATE MEMORY TO ROW %d OF 2D INTEGER ARRAY !!! EXITTING NOW...\n\n", r);
			exit(0);
		}
		else
		{
			printf("MEMORY ALLOCATION TO ROW %d OF 2D INTEGER ARRAY SUCCEEDED !!!\n\n", r);
		}
	}

	for (r = 0; r < NUM_ROWS; r++)
	{
		for (c = 0; c < NUM_COLUMNS; c++)
			pArr[r][c] = (r + 1) * (c + 3);
	}

	printf("\n\n");
	printf("DISPLAYING 2D ARRAY : \n\n");
	for (r = 0; r < NUM_ROWS; r++)
	{
		for (c = 0; c < NUM_COLUMNS; c++)
		{
			printf("pArr[%d][%d] = %d\n", r, c, pArr[r][c]);
		}
		printf("\n\n");
	}
	printf("\n\n");

	for (r = (NUM_ROWS - 1); r >= 0; r--)
	{
		free(pArr[r]);
		pArr[r] = NULL;
		printf("MEMORY ALLOCATED TO ROW %d OF 2D INTEGER ARRAY HAS BEEN SUCCESSFULLY FREED !!!\n\n", r);
	}

	return(0);
}


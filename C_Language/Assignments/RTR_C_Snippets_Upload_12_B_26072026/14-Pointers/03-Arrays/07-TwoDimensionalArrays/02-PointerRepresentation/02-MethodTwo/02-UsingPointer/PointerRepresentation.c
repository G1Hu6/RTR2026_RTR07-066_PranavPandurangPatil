#include <stdio.h>
#include <stdlib.h>

#define NUM_ROWS 3
#define NUM_COLUMNS 2

int main(void)
{
	//variable declaraions
	int r, c;
	int **ppArr = NULL;

	//code
	printf("\n\n");
	ppArr = (int **)malloc(NUM_ROWS * sizeof(int *));
	if (ppArr == NULL)
	{
		printf("MEMORY ALLOCATION TO THE 1D ARRAY OF BASE ADDRESSES OF %d ROWS FAILED !!! EXITTING NOW...\n\n", NUM_ROWS);
		exit(0);
	}
	else
	{
		printf("MEMORY ALLOCATION TO THE 1D ARRAY OF BASE ADDRESSES OF %d ROWS HAS SUCCEEDED !!!\n\n", NUM_ROWS);
	}

	for (r = 0; r < NUM_ROWS; r++)
	{
		ppArr[r] = (int *)malloc(NUM_COLUMNS * sizeof(int));
		if (ppArr[r] == NULL)
		{
			printf("MEMORY ALLOCATION TO THE COLUMNS OF ROW %d FAILED !!! EXITTING NOW...\n\n", r);
			exit(0);
		}
		else
		{
			printf("MEMORY ALLOCATION TO THE COLUMNS OF ROW %d HAS SUCCEEDED !!!\n\n", r);
		}
	}

	for (r = 0; r < NUM_ROWS; r++)
	{
		for (c = 0; c < NUM_COLUMNS; c++)
			*(*(ppArr + r) + c) = (r + 1) * (c + 3);
	}

	printf("\n\n");
	printf("2D Integer Array Elements Along With Addresses : \n\n");
	for (r = 0; r < NUM_ROWS; r++)
	{
		for (c = 0; c < NUM_COLUMNS; c++)
		{
			printf("ppArr[%d][%d] = %d \t \t At Address &ppArr[%d][%d] : %p\n", r, c, ppArr[r][c], r, c, &ppArr[r][c]);
		}
		printf("\n\n");
	}

	for (r = (NUM_ROWS - 1); r >= 0; r--)
	{
		if (*(ppArr + r))
		{
			free(*(ppArr + r));
			*(ppArr + r) = NULL;
			printf("MEMORY ALLOCATED TO ROW %d HAS BEEN SUCCESSFULLY FREED !!!\n\n", r);
		}
	}

	if (ppArr)
	{
		free(ppArr);
		ppArr = NULL;
		printf("MEMORY ALLOCATED TO ppArr HAS BEEN SUCCESSFULLY FREED !!!\n\n");
	}

	return(0);
}


#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	//variable declaraions
	int **ppArr = NULL;
	int r, c;
	int nRows, nCols;

	//code
	printf("\n\n");
	printf("Enter Number Of Rows : ");
	scanf("%d", &nRows);

	printf("\n\n");
	printf("Enter Number Of Columns : ");
	scanf("%d", &nCols);

	printf("\n\n");
	printf("MEMORY ALLOCATION TO 2D INTEGER ARRAY \n\n");
	ppArr = (int **)malloc(nRows * sizeof(int *));
	if (ppArr == NULL)
	{
		printf("FAILED TO ALLOCATE MEMORY TO %d ROWS OF 2D INTEGER ARRAY !!! EXITTING NOW...\n\n", nRows);
		exit(0);
	}
	else
	{
		printf("MEMORY ALLOCATION TO %d ROWS OF 2D INTEGER ARRAY SUCCEEDED !!!\n\n", nRows);
	}

	for (r = 0; r < nRows; r++)
	{
		ppArr[r] = (int *)malloc(nCols * sizeof(int));
		if (ppArr[r] == NULL)
		{
			printf("FAILED TO ALLOCATE MEMORY TO COLUMNS OF ROW %d OF 2D INTEGER ARRAY !!! EXITTING NOW...\n\n", r);
			exit(0);
		}
		else
		{
			printf("MEMORY ALLOCATION TO COLUMNS OF ROW %d OF 2D INTEGER ARRAY SUCCEEDED !!!\n\n", r);
		}
	}

	for (r = 0; r < nRows; r++)
	{
		for (c = 0; c < nCols; c++)
			ppArr[r][c] = (r + 1) + (c + 1);
	}

	for (r = 0; r < nRows; r++)
	{
		printf("Base Address Of Row %d : ppArr[%d] = %p \t At Address : %p\n", r, r, ppArr[r], &ppArr[r]);
	}

	printf("\n\n");

	for (r = 0; r < nRows; r++)
	{
		for (c = 0; c < nCols; c++)
		{
			printf("ppArr[%d][%d] = %d \t At Address : %p\n", r, c, ppArr[r][c], &ppArr[r][c]);
		}
		printf("\n");
	}

	for (r = (nRows - 1); r >= 0; r--)
	{
		if (ppArr[r])
		{
			free(ppArr[r]);
			ppArr[r] = NULL;
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


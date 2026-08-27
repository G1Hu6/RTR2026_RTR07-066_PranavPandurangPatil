#include <stdio.h>

#define ROWS 3
#define COLS 2
#define DEPTH 2

int main(void)
{
	//variable declaraions
	int iArr3D[ROWS][COLS][DEPTH] = {
		{ { 1, 2 }, { 3, 4 } },
		{ { 5, 6 }, { 7, 8 } },
		{ { 9, 10 }, { 11, 12 } }
	};

	int i, j, k;
	int iArr1D[ROWS * COLS * DEPTH];

	//code
	printf("\n\n");
	printf("Elements In The 3D Array : \n\n");
	for (i = 0; i < ROWS; i++)
	{
		printf("ROW %d \n", (i + 1));
		for (j = 0; j < COLS; j++)
		{
			printf("COLUMN %d \n", (j + 1));
			for (k = 0; k < DEPTH; k++)
			{
				printf("iArr3D[%d][%d][%d] = %d\n", i, j, k, iArr3D[i][j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			for (k = 0; k < DEPTH; k++)
			{
				iArr1D[(i * COLS * DEPTH) + (j * DEPTH) + k] = iArr3D[i][j][k];
			}
		}
	}

	printf("\n\n");
	printf("Elements In The 1D Array : \n\n");
	for (i = 0; i < (ROWS * COLS * DEPTH); i++)
	{
		printf("iArr1D[%d] = %d\n", i, iArr1D[i]);
	}

	return(0);
}


#include <stdio.h>

int main(void)
{
	//variable declaraions
	int iArr[3][5];
	int sz_int;
	int sz_arr;
	int cnt, rows, cols;
	int i, j;

	//code
	printf("\n\n");

	sz_int = sizeof(int);

	sz_arr = sizeof(iArr);
	printf("Size Of Two Dimensional ( 2D ) Integer Array Is = %d\n\n", sz_arr);

	rows = sz_arr / sizeof(iArr[0]);
	printf("Number Of Rows In Two Dimensional ( 2D ) Integer Array Is = %d\n\n", rows);

	cols = sizeof(iArr[0]) / sz_int;
	printf("Number of Columns In Two Dimensional ( 2D ) Integer Array Is = %d\n\n", cols);

	cnt = rows * cols;
	printf("Number of Elements In Two Dimensional ( 2D ) Integer Array Is = %d\n\n", cnt);

	printf("\n\n");
	printf("Elements In The 2D Array : \n\n");

	iArr[0][0] = 10;
	iArr[0][1] = 20;
	iArr[0][2] = 30;
	iArr[0][3] = 40;
	iArr[0][4] = 50;

	iArr[1][0] = 15;
	iArr[1][1] = 25;
	iArr[1][2] = 35;
	iArr[1][3] = 45;
	iArr[1][4] = 55;

	iArr[2][0] = 12;
	iArr[2][1] = 24;
	iArr[2][2] = 36;
	iArr[2][3] = 48;
	iArr[2][4] = 60;

	for (i = 0; i < rows; i++)
	{
		printf("ROW %d \n", (i + 1));
		for (j = 0; j < cols; j++)
		{
			printf("iArr[%d][%d] = %d\n", i, j, iArr[i][j]);
		}
		printf("\n\n");
	}

	return(0);
}


#include <stdio.h>

int main(void)
{
	//variable declaraions
	int iArr[5][3] = { {5, 10, 15}, {20, 25, 30}, {35, 40, 45}, {50, 55, 60}, {65, 70, 75} };
	int int_size;
	int iArr_size;
	int iArr_num_elements, iArr_num_rows, iArr_num_columns;
	int i, j;

	//code
	printf("\n\n");

	int_size = sizeof(int);

	iArr_size = sizeof(iArr);
	printf("Size Of Two Dimensional ( 2D ) Integer Array Is = %d\n\n", iArr_size);

	iArr_num_rows = iArr_size / sizeof(iArr[0]);
	printf("Number Of Rows In Two Dimensional ( 2D ) Integer Array Is = %d\n\n", iArr_num_rows);

	iArr_num_columns = sizeof(iArr[0]) / int_size;
	printf("Number of Columns In Two Dimensional ( 2D ) Integer Array Is = %d\n\n", iArr_num_columns);

	iArr_num_elements = iArr_num_rows * iArr_num_columns;
	printf("Number of Elements In Two Dimensional ( 2D ) Integer Array Is = %d\n\n", iArr_num_elements);

	printf("\n\n");
	printf("Elements In The 2D Array : \n\n");

	for (i = 0; i < iArr_num_rows; i++)
	{
		printf("ROW %d \n", (i + 1));
		for (j = 0; j < iArr_num_columns; j++)
		{
			printf("iArr[%d][%d] = %d\n", i, j, iArr[i][j]);
		}
		printf("\n\n");
	}

	return(0);
}


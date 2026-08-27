#include <stdio.h>

int main(void)
{
	//variable declaraions
	int iArr[5][3] = { {5, 10, 15}, {20, 25, 30}, {35, 40, 45}, {50, 55, 60}, {65, 70, 75} };
	int int_size;
	int iArr_size;
	int iArr_num_elements, iArr_num_rows, iArr_num_columns;

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

	printf("ROW 1 \n");
	printf("iArr[0][0] = %d\n", iArr[0][0]);
	printf("iArr[0][1] = %d\n", iArr[0][1]);
	printf("iArr[0][2] = %d\n", iArr[0][2]);

	printf("\n\n");

	printf("ROW 2 \n");
	printf("iArr[1][0] = %d\n", iArr[1][0]);
	printf("iArr[1][1] = %d\n", iArr[1][1]);
	printf("iArr[1][2] = %d\n", iArr[1][2]);

	printf("\n\n");

	printf("ROW 3 \n");
	printf("iArr[2][0] = %d\n", iArr[2][0]);
	printf("iArr[2][1] = %d\n", iArr[2][1]);
	printf("iArr[2][2] = %d\n", iArr[2][2]);

	printf("\n\n");

	printf("ROW 4 \n");
	printf("iArr[3][0] = %d\n", iArr[3][0]);
	printf("iArr[3][1] = %d\n", iArr[3][1]);
	printf("iArr[3][2] = %d\n", iArr[3][2]);

	printf("\n\n");

	printf("ROW 5 \n");
	printf("iArr[4][0] = %d\n", iArr[4][0]);
	printf("iArr[4][1] = %d\n", iArr[4][1]);
	printf("iArr[4][2] = %d\n", iArr[4][2]);

	printf("\n\n");

	return(0);
}


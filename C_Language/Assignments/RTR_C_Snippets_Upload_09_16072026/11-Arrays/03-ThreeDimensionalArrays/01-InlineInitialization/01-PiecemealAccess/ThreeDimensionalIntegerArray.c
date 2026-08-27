#include <stdio.h>

int main(void)
{
	//variable declaraions
	int iArr3D[3][2][2] = {
		{ { 1, 2 }, { 3, 4 } },
		{ { 5, 6 }, { 7, 8 } },
		{ { 9, 10 }, { 11, 12 } }
	};

	int sz_int;
	int sz_arr;
	int cnt, width, height, depth;

	//code
	printf("\n\n");

	sz_int = sizeof(int);

	sz_arr = sizeof(iArr3D);
	printf("Size Of Three Dimensional ( 3D ) Integer Array Is = %d\n\n", sz_arr);

	width = sz_arr / sizeof(iArr3D[0]);
	printf("Number of Rows (Width) In Three Dimensional ( 3D ) Integer Array Is = %d\n\n", width);

	height = sizeof(iArr3D[0]) / sizeof(iArr3D[0][0]);
	printf("Number of Columns (Height) In Three Dimensional ( 3D ) Integer Array Is = %d\n\n", height);

	depth = sizeof(iArr3D[0][0]) / sz_int;
	printf("Depth In Three Dimensional ( 3D ) Integer Array Is = %d\n\n", depth);

	cnt = width * height * depth;
	printf("Number of Elements In Three Dimensional ( 3D ) Integer Array Is = %d\n\n", cnt);

	printf("\n\n");
	printf("Elements In Integer 3D Array : \n\n");

	printf("ROW 1 \n");
	printf("COLUMN 1 \n");
	printf("iArr3D[0][0][0] = %d\n", iArr3D[0][0][0]);
	printf("iArr3D[0][0][1] = %d\n", iArr3D[0][0][1]);
	printf("\n");
	printf("COLUMN 2 \n");
	printf("iArr3D[0][1][0] = %d\n", iArr3D[0][1][0]);
	printf("iArr3D[0][1][1] = %d\n", iArr3D[0][1][1]);
	printf("\n\n");

	printf("ROW 2 \n");
	printf("COLUMN 1 \n");
	printf("iArr3D[1][0][0] = %d\n", iArr3D[1][0][0]);
	printf("iArr3D[1][0][1] = %d\n", iArr3D[1][0][1]);
	printf("\n");
	printf("COLUMN 2 \n");
	printf("iArr3D[1][1][0] = %d\n", iArr3D[1][1][0]);
	printf("iArr3D[1][1][1] = %d\n", iArr3D[1][1][1]);
	printf("\n\n");

	printf("ROW 3 \n");
	printf("COLUMN 1 \n");
	printf("iArr3D[2][0][0] = %d\n", iArr3D[2][0][0]);
	printf("iArr3D[2][0][1] = %d\n", iArr3D[2][0][1]);
	printf("\n");
	printf("COLUMN 2 \n");
	printf("iArr3D[2][1][0] = %d\n", iArr3D[2][1][0]);
	printf("iArr3D[2][1][1] = %d\n", iArr3D[2][1][1]);
	printf("\n\n");

	return(0);
}


#include <stdio.h>

int main(void)
{
	//variable declaraions
	int iArr1[5];
	int iArr2[3][2];
	int iArr3[4][3][2];

	int rows2D;
	int cols2D;

	int rows3D;
	int cols3D;
	int depth3D;

	//code
	printf("\n\n");
	printf("Size of 1-D integer array iArr1 = %lu\n", sizeof(iArr1));
	printf("Number of elements in 1-D integer array iArr1 = %lu\n", (sizeof(iArr1) / sizeof(int)));

	printf("\n\n");
	printf("Size of 2-D integer array iArr2 = %lu\n", sizeof(iArr2));
	printf("Number rows in 2-D integer array iArr2 = %lu\n", (sizeof(iArr2) / sizeof(iArr2[0])));
	rows2D = (sizeof(iArr2) / sizeof(iArr2[0]));

	printf("Number of elements (columns) in each row in 2-D integer array iArr2 = %lu\n", (sizeof(iArr2[0]) / sizeof(iArr2[0][0])));
	cols2D = (sizeof(iArr2[0]) / sizeof(iArr2[0][0]));

	printf("Number of elements in total in 2-D Array iArr2 = %d\n", (rows2D * cols2D));

	printf("\n\n");
	printf("Size of 3-D integer array iArr3 = %lu\n", sizeof(iArr3));

	printf("Number rows in 3-D integer array iArr3 = %lu\n", (sizeof(iArr3) / sizeof(iArr3[0])));
	rows3D = (sizeof(iArr3) / sizeof(iArr3[0]));

	printf("Number of elements (columns) in one row in 3-D integer array iArr3 = %lu\n", (sizeof(iArr3[0]) / sizeof(iArr3[0][0])));
	cols3D = (sizeof(iArr3[0]) / sizeof(iArr3[0][0]));

	printf("Number of elements (depth) in one column in one row in 3-D integer array iArr3 = %lu\n", (sizeof(iArr3[0][0]) / sizeof(int)));
	depth3D = (sizeof(iArr3[0][0]) / sizeof(int));

	printf("Number of elements in total in 3-D Array iArr3 = %d\n", (rows3D * cols3D * depth3D));

	printf("\n\n");

	return(0);
}


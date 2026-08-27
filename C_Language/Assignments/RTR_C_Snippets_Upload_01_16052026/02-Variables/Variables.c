#include<stdio.h>

int main(void)
{
	// variable declarations
	int iNum = 5;
	float fNum = 3.9f;
	double dNum = 8.041997;
	char cNum = 'A';

	// code 
	printf("\n\n");

	printf("iNum = %d\n", iNum);
	printf("fNum = %f\n", fNum);
	printf("dNum = %lf\n", dNum);
	printf("cNum = %c\n", cNum);

	printf("\n\n");

	iNum = 11;
	fNum = 2.34f;
	dNum = 34.34342;
	cNum = 'S';
	
	printf("iNum = %d\n", iNum);
	printf("fNum = %f\n", fNum);
	printf("dNum = %lf\n", dNum);
	printf("cNum = %c\n", cNum);

	printf("\n\n");

	return (0);
}



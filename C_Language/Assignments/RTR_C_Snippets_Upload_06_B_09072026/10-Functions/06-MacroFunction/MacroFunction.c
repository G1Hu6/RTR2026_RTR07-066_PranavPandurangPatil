#include <stdio.h>

#define MAX(a, b) ((a > b) ? a : b)

int main(int argc, char *argv[], char *envp[])
{
	// variable declarations
	int i1;
	int i2;
	int iRes;

	float f1;
	float f2;
	float fRes;

	// code
	// ****** COMPARING INTEGER VALUES ******
	printf("\n\n");
	printf("Enter An Integer Number : \n\n");
	scanf("%d", &i1);

	printf("\n\n");
	printf("Enter Another Integer Number : \n\n");
	scanf("%d", &i2);

	iRes = MAX(i1, i2);
	printf("\n\n");
	printf("Result Of Macro Function MAX() = %d\n", iRes);

	printf("\n\n");

	// ****** COMPARING FLOATING-POINT VALUES ******
	printf("\n\n");
	printf("Enter A Floating Point Number : \n\n");
	scanf("%f", &f1);

	printf("\n\n");
	printf("Enter Another Floating Point Number : \n\n");
	scanf("%f", &f2);

	fRes = MAX(f1, f2);
	printf("\n\n");
	printf("Result Of Macro Function MAX() = %f\n", fRes);

	printf("\n\n");

	return(0);
}


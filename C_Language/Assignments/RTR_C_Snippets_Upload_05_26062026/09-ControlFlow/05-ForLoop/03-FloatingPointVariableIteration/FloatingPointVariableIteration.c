#include<stdio.h>

int main(void)
{
	// variable declarations
	float f;
	float fNum = 1.6f;

	// code
	printf("\n\n");

	printf("Printing Numbers %f to %f : \n\n", fNum, (fNum * 10.0f));

	for(f = fNum; f <= (fNum * 10.0f); f = f + fNum)
	{
		printf("\t%f\n", f);
	}

	printf("\n\n");

	return(0);
}

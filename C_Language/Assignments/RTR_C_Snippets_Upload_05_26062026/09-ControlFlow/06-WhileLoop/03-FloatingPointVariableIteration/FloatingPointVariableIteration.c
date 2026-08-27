#include<stdio.h>

int main(void)
{
	// variable declarations
	float f;
	float fNum = 1.4f;

	// code
	printf("\n\n");
	printf("Printing Numbers %f to %f : \n\n", fNum, (fNum * 10.0f));

	f = fNum;
	while(f <= (fNum * 10.0f))
	{
		printf("\t%f\n", f);
		f += fNum;
	}

	printf("\n\n");

	return(0);
}

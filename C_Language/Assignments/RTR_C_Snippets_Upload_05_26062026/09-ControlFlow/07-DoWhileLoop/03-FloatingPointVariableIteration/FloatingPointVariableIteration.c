#include<stdio.h>

int main(void)
{
	// variable declarations 
	float f;
	float fNum = 1.3f;

	// code
	printf("\n\n");

	printf("Printing Numbers %f to %f : \n\n ", fNum, (fNum * 10.0f));
	
	f = fNum;
	do
	{
		printf("\t%f\n", f);
		f += fNum;
	}while(f <= (fNum * 10.0f));

	printf("\n\n");

	return(0);
}

#include<stdio.h>

int main(void)
{
	// variable declarations
	int i;

	// code
	printf("\n\n");
	printf("Printing Digits 1 to 10 : \n\n");

	i = 0;
	do
	{
		printf("\t%d\n", ++i);
	}while(i < 10);

	printf("\n\n");

	return(0);
}

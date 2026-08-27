#include<stdio.h>

int main(void)
{
	// variable declarations
	int i, j;

	// code
	printf("\n\n");
	
	printf("Printing Digints 10 to 1 and 100 to 10 : \n\n");

	i = 10;
	j = 100;
	while(i >= 1, j >= 10)
	{
		printf("\t %d \t %d\n", i, j);
		i--;
		j -= 10;
	}

	printf("\n\n");

	return(0);
}	

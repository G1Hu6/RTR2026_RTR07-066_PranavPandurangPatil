#include<stdio.h>
int main(void)
{
	// variable declarations
	int ip;

	// code
	printf("\n\n");

	for( ip = 0; ip <= 50; ip++)
	{
		// if remainder is not 0, the number is odd number...
		if(ip % 2 != 0)
		{
			continue;
		}
		else
		{
			printf("\t%d\n", ip);
		}
	}

	printf("\n\n");

	return(0);
}

#include<stdio.h>

int main(void)
{
	// variable declarations
	int n;

	// code
	printf("\n\n");

	printf("Enter Value For 'num' : ");
	scanf("%d", &n);

	if(n < 0)
	{
		printf("Num = %d Is Less Than 0 (NEGATIVE).\n\n", n);
	}

	if((n > 0) && (n <= 100))
	{
		printf("Num = %d Is Between 0 and 100.\n\n", n);
	}

	if((n > 100) && (n <= 200))
	{
		printf("Num = %d Is Between 100 and 200.\n\n", n);
	}

	if((n > 200) && (n <= 300))
	{
		printf("Num = %d Is Between 200 and 300.\n\n", n);
	}

	if((n > 300) && (n <= 400))
	{
		printf("Num = %d Is Between 300 and 400.\n\n", n);
	}

	if((n > 400) && (n <= 500))
	{
		printf("Num = %d Is Between 400 and 500.\n\n", n);
	}

	if(n > 500)
	{
		printf("Num = %d Is Between 0 and 100.\n\n", n);
	}

	return(0);

}

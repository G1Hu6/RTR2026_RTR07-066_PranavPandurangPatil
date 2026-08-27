#include<stdio.h>
int main(void)
{
	// variable declarations
	int p, q;

	// code
	printf("\n\n");

	p = 1;
	do 
	{
	
		printf("p = %d\n", p);
		printf("=======\n\n");
		q = 1;
		do
		{
			printf("q = %d\n", q);
			q++;
		}while(q < 4);
		printf("\n");
		p++;
	}while(p < 3);

	return(0);
}

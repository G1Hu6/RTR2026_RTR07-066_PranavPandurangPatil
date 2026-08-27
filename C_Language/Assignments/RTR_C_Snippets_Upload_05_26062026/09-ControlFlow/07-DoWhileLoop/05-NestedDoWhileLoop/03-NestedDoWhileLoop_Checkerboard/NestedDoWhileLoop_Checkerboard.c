#include<stdio.h>
int main(void)
{
	// variable declarations
	int p, q, a;

	// code
	printf("\n\n");

	p = 0;
	do 
	{
	
		q = 0;
		do
		{
			a = ((p & 0x8) == 0) ^ ((q & 0x8) == 0);

			if(a == 0) printf("  ");
			if(a == 1) printf("* ");
			q++;
		}while(q < 64);
		printf("\n");
		p++;
	}while(p < 64);

	return(0);
}


#include<stdio.h>

int main(void)
{
	// variable declarations
	int i, j, c;

	// code
	printf("\n\n");
	for(i = 0; i < 64; i++)
	{
		for(j = 0; j < 64; j++)
		{

			/*if((i == 0 && j == 0) || (i == 63 || j == 63)){
				printf("* ");
				continue;
			}*/

			c = (((((i & 0x8) == 0) && j != 0)) || j == 63) ^ (((((j & 0x8) == 0) && i != 0) || i == 63));
			if(c == 0)
			{
				printf("  ");
			}

			if(c == 1)
			{
				printf("* ");
			}
		}
		printf("\n");
	}
	return(0);
}

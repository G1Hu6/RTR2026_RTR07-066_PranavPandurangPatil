#include<stdio.h>

int main(void)
{
	// variable declarations
	int ip, jp, kp;

	// code
	printf("\n\n");

	ip = 1;
	do
	{
		printf("ip = %d \n", ip);
		printf("========\n\n");

		jp = 1;
		do
		{
			printf("\tjp = %d \n", jp);
                	printf("========\n\n");

			kp = 1;
			do
			{
				printf("\t\tkp = %d \n", kp);
				kp++;
			}while(kp <= 2);
			printf("\n\n");
			jp++;
		}while(jp <= 4);
		printf("\n\n");
		ip++;
	}while(ip <= 6);
	
	return(0);
}

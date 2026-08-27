#include<stdio.h>

int main(void)
{
	// variable declarations
	char op, ch = '\0';

	// code
	printf("\n\n");
	printf("Once The Infinite Loop Begins, Enter 'Q' or 'q' To Quit The Infinite Do-While Loop : \n\n");

	do(op == 'Y' || op == 'y')
	{
		do // Infinite Loop
		{
			printf("\n");
			printf("In Loop...\n");
			ch = getch();
		}while(ch == 'Q' || ch == 'q');
		printf("\n\n");
		printf("EXISTING USER CONTROLLED INFINITE LOOP ...");
		printf("\n\n");
		printf("Enter 'Y' or 'y' : ");
        	op = getch();
	}while(op == 'Y' || op == 'y');
	
	return(0);
}


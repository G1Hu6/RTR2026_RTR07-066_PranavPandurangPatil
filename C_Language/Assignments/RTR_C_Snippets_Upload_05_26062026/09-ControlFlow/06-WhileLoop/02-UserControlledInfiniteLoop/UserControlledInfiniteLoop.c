#include<stdio.h>

int main(void)
{
	// variable declarations
	char op, ch = '\0';

	// code
	printf("\n\n");
	printf("Once The Infinite Loop Begins, Enter 'Q' or 'q' To Quit The Infinite While Loop : \n\n");
	printf("Enter 'Y' or 'y' : ");
	printf("\n\n");
	op = getch();

	if(op == 'Y' || op == 'y')
	{
		while(1) // Infinite Loop
		{
			printf("In Loop...\n");
			ch = getch();
			if(ch == 'Q' || ch == 'q')
				break;
		}
		printf("\n\n");
		printf("EXISTING USER CONTROLLED INFINITE LOOP ...");
		printf("\n\n");
	}
	else
		printf("You Must Press 'Y' or 'y' To Initiate\n\n");

	return(0);
}

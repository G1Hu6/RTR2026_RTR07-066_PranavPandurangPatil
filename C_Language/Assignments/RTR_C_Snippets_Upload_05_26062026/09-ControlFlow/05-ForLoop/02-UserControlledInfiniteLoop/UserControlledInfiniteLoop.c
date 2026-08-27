#include<stdio.h>

int main(void)
{
	// variable declarations
	char op, ch = '\0';

	// code
	printf("\n\n");
	printf("Once The Infinite Loop Begins, Enter 'Q' or 'q' To Quit The Infinite For Loop : \n\n");

	printf("\n\n");
	op = getch();
	if(op == 'Y' || op == 'y')
	{
		for( ; ; ) // Infinite Loop
		{
			printf("In Loop...\n");
			ch = getch();
			if(ch == 'Q' || ch == 'q')
			{
				break; // User Controlled Exiting From Infinite Loop
			}
		}
	}
	printf("\n\n");

	printf("EXITING FROM CONTROLLED INFINITE LOOP...");

	printf("\n\n");
	return(0);
}

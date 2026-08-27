#include<stdio.h>

int main(void)
{
	// variable declarations
	int myAge;

	// code
	printf("\n\n");
	printf("Enter Age : ");
	scanf("%d", &myAge);

	if(myAge >= 18)
	{
		printf("You Are Eligible For Voting !!!\n\n");
	}
	printf("You Are Not Eligible For Voting !!!\n\n");
	return(0);
}

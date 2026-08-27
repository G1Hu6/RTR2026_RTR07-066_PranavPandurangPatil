#include<stdio.h>

int main(void)
{
	// variables declarations
	int a, b, p;	
	//  code
	a = 9;
	b = 20;
	p = 20;

	// *** FIRST if-else PAIR
	printf("\n\n");

	if(a < b)
	{
		printf("Entering First if-else-block...\n\n");
		printf("A Is Less Than B !!!\n\n");
	}
	else
	{
		printf("Entering First if-else-block...\n\n");
                printf("A Is Not Less Than B !!!\n\n");
	}
	printf("First if-else Pair Done !!!\n\n");

	// *** SECOND if-else PAIR
        printf("\n\n");

        if(b != p)
        {
                printf("Entering Second if-else-block...\n\n");
                printf("B Is Not Equal to P !!!\n\n");
        }
        else
        {
                printf("Entering Second if-else-block...\n\n");
                printf("A Is Equal to P !!!\n\n");
        }
        printf("Second if-else Pair Done !!!\n\n");

	return (0);
}

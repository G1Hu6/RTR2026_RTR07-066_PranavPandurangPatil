#include<stdio.h>

int main(void)
{
	// variables declarations
	int a;

	// code
	printf("\n\n");

	a = 5;
	if(a)
	{
		printf("if-block 1 : 'A' Exists And has Value = %d !!!\n\n", a);
	}

	a = -8;
	if(a) // Non Zero Value
        {
                printf("if-block 2 : 'A' Exists And has Value = %d !!!\n\n", a);
        }

	a = 0;
	if(a) // Zero Value
        {
                printf("if-block 1 : 'A' Exists And has Value = %d !!!\n\n", a);
        }

	printf("All Three if-statements Are Done !!!\n\n");
	return(0);
}

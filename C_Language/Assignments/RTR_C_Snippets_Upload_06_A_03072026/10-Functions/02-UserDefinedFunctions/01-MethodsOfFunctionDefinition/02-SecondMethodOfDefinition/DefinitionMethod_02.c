#include<stdio.h> 

// Entry-Point Function => main() => Valid Return type (int) and 3 Parameters (int argc, char * argv[], char* envp[])

int main(int argc, char* argv[], char *envp[])
{
	// function proptotype/ declaration/ signature
	int myAdd(void);

	int total;

	total = myAdd();
        printf("\n\n");
        printf("Sum = %d", total);
	return(0);
}

/*
 * USER DEFINED FUNCTION : METHOD OF DEFINATION 2
 * RETURN VALUE, NO PARAMETERS
 */

int myAdd(void) // function defination
{
	// variable declarations : local variables 
	int p, q;

	//code
	printf("\n\n");
	printf("Enter Value of P : ");
	scanf("%d", &p);

	printf("\n\n");
        printf("Enter Value of Q : ");
        scanf("%d", &q);

	return(p + q);
}


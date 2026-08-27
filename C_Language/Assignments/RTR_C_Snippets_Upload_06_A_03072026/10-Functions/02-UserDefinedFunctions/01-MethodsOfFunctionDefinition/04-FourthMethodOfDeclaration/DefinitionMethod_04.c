#include<stdio.h> 

// Entry-Point Function => main() => Valid Return type (int) and 3 Parameters (int argc, char * argv[], char* envp[])

int main(int argc, char* argv[], char *envp[])
{
	// function proptotype/ declaration/ signature
	int myAdd(int, int);

	// variable declarations : local variables 
	int p, q, sum;

	//code
	printf("\n\n");
	printf("Enter Value of P : ");
	scanf("%d", &p);

	printf("\n\n");
        printf("Enter Value of Q : ");
        scanf("%d", &q);

	sum = myAdd(p, q); // function call
	printf("\n\n");
        printf("Sum = %d", sum);
	return(0);
}


/*
 * USER DEFINED FUNCTION : METHOD OF DEFINATION 2
 * RETURN VALUE, VALID PARAMETERS
 */

int myAdd(int p, int q) // function defination
{
	return (p + q);
}


#include<stdio.h> 

// Entry-Point Function => main() => Valid Return type (int) and 3 Parameters (int argc, char * argv[], char* envp[])

int main(int argc, char* argv[], char *envp[])
{
	// function proptotype/ declaration/ signature
	void myAdd(int, int);

	// variable declarations : local variables 
	int p, q;

	//code
	printf("\n\n");
	printf("Enter Value of P : ");
	scanf("%d", &p);

	printf("\n\n");
        printf("Enter Value of Q : ");
        scanf("%d", &q);

	myAdd(p, q); // function call
	return(0);
}

/*
 * USER DEFINED FUNCTION : METHOD OF DEFINATION 3
 * NO RETURN VALUE, VALID PARAMETERS
 */

void myAdd(int p, int q) // function defination
{
	int total = p + q;
	printf("\n\n");
	printf("Sum of %d and %d = %d", p, q, total);
}

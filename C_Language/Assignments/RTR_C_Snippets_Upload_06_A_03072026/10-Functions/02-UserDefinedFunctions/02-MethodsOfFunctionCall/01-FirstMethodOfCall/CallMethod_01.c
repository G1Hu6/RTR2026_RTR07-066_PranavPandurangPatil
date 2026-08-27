#include <stdio.h> //'stdio.h' contains declaration of 'printf()'

// ****** USER DEFINED FUNCTIONS : METHOD OF CALLING FUNCTION 1 ******
// ****** CALLING ALL FUNCTIONS IN main() DIRECTLY ******

// Entry-Point Function => main() => Valid Return Type (int) and 3 Parameters
// (int argc, char *argv[], char *envp[])
int main(int argc, char *argv[], char *envp[])
{
	//function prototypes OR declarations
	void Add(void);
	int Sub(void);
	void Mult(int, int);
	int Div(int, int);

	//variable declarations
	int result_sub;
	int a_mult, b_mult;
	int a_div, b_div, result_div;

	//code

	// *** ADDITION ***
	Add(); //function call

	// *** SUBTRACTION ***
	result_sub = Sub(); //function call
	printf("\n\n");
	printf("Subtraction Yields Result = %d\n", result_sub);

	// *** MULTIPLICATION ***
	printf("\n\n");
	printf("Enter Integer Value For 'A' For Multiplication : ");
	scanf("%d", &a_mult);

	printf("\n\n");
	printf("Enter Integer Value For 'B' For Multiplication : ");
	scanf("%d", &b_mult);

	Mult(a_mult, b_mult); //function call

	// *** DIVISION ***
	printf("\n\n");
	printf("Enter Integer Value For 'A' For Division : ");
	scanf("%d", &a_div);

	printf("\n\n");
	printf("Enter Integer Value For 'B' For Division : ");
	scanf("%d", &b_div);

	result_div = Div(a_div, b_div); //function call
	printf("\n\n");
	printf("Division Of %d and %d Gives = %d (Quotient)\n", a_div, b_div, result_div);

	printf("\n\n");

	return(0);
}

// *** Function Definition Of Add() ******
void Add(void) //function definition
{
	//variable declarations : local variables to Add()
	int a, b, sum;

	//code
	printf("\n\n");
	printf("Enter Integer Value For 'A' For Addition : ");
	scanf("%d", &a);

	printf("\n\n");
	printf("Enter Integer Value For 'B' For Addition : ");
	scanf("%d", &b);

	sum = a + b;

	printf("\n\n");
	printf("Sum Of %d And %d = %d\n\n", a, b, sum);
}

// *** Function Definition Of Sub() ******
int Sub(void) //function definition
{
	//variable declarations : local variables to Sub()
	int a, b, sub;

	//code
	printf("\n\n");
	printf("Enter Integer Value For 'A' For Subtraction : ");
	scanf("%d", &a);

	printf("\n\n");
	printf("Enter Integer Value For 'B' For Subtraction : ");
	scanf("%d", &b);

	sub = a - b;
	return(sub);
}

// *** Function Definition Of Mult() ******
void Mult(int a, int b) //function definition
{
	//variable declarations : local variables to Mult()
	int mult;

	//code
	mult = a * b;

	printf("\n\n");
	printf("Multiplication Of %d And %d = %d\n\n", a, b, mult);
}

// *** Function Definition Of Div() ******
int Div(int a, int b) //function definition
{
	//variable declarations : local variables to Div()
	int quotient;

	//code
	if (a > b)
		quotient = a / b;
	else
		quotient = b / a;

	return(quotient);
}


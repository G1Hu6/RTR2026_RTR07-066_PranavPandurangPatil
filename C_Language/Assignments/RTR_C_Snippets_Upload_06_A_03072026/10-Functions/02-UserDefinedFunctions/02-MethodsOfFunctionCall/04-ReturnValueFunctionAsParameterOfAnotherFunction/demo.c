#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	//function prototypes OR declarations
	int Add(int, int);

	//variable declarations
	int res;
	int a, b;
	int c, d;

	//code
	a = 15;
	b = 25;
	c = 35;
	d = 45;

	res = Add(Add(a, b), Add(c, d)); // return value of Add() is sent as parameter to another call to Add()

	printf("\n\n");
	printf("%d + %d + %d + %d = %d\n", a, b, c, d, res);
	printf("\n\n");

	return(0);
}

// *** Function Definition Of Add() ******
int Add(int a, int b) //function definition
{
	// variable declaration
	int sum;

	// code
	sum = a + b;
	return(sum);
}

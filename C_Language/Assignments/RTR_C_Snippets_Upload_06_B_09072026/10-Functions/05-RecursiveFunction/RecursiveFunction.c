#include<stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	// variable declarations
	unsigned int num;
	// function prototype
	void Rec(unsigned int);
	// code
	printf("\n\n");
	printf("Enter Any Number : \n\n");
	scanf("%u", &num);
	printf("\n\n");
	printf("Output Of Recursive Function : \n\n");
	Rec(num);
	printf("\n\n");
	return(0);
}

void Rec(unsigned int n)
{
	// code
	printf("n = %d\n", n);
	if(n > 0)
	{
		Rec(n - 1);
	}
}

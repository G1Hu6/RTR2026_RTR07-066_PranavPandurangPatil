#include<stdio.h> // 'stdio.h' contains declaration of 'printf()'
#include<ctype.h> // 'ctype.h' contains declaration of 'atoi()'
#include<stdlib.h> // 'stdlib.h' contains declaration of 'exit()'
		   
int main(int argc, char* argv[], char *envp[])
{
	// variables declarations
	int p;
	int n;
	int s = 0;

	// code
	if(argc == 1)
	{
		printf("\n\n");
		printf("No Numbers are given for Addition !!! \n\n");
		printf("Usage : CommandLineArgumentsApplication <first number> <second number> ...\n\n");
		exit(0);
	}

	printf("\n\n");
	printf("Sum Of All Integers Command Line Arguments Is : \n\n");
	for(p = 0; p < argc; p++)
	{
		n = atoi(argv[p]);
		s += n;
	}
	printf("Sum = %d \n\n", s);
	return(0);
}


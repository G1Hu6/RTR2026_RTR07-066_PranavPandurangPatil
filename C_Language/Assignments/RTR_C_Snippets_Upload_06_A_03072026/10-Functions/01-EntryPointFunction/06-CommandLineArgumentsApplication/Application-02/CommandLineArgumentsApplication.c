#include<stdio.h> // 'stdio.h' contains declaration of 'printf()'
#include<stdlib.h> // 'stdlib.h' contains declaration of 'exit()'
		   
int main(int argc, char* argv[], char *envp[])
{
	// variables declarations
	int p;

	// code
	if(argc != 4)
	{
		printf("\n\n");
		printf("Invalid Usage !!! \n\n");
		printf("Usage : CommandLineArgumentsApplication <first name> <middle name> <last name> ...\n\n");
		exit(0);
	}

	printf("\n\n");
	printf("Your Full Name Is : \n\n");
	for(p = 0; p < argc; p++)
	{
		printf("%s " , argv[p]);
	}

	return(0);
}



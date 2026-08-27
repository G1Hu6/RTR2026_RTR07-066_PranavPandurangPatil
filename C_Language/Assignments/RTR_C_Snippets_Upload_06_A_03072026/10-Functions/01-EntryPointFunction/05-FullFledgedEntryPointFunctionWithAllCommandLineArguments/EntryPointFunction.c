#include<stdio.h> // 'stdio.h' contains declaration of 'printf()'

// Every-Point Function => main() => Valid Return type (int) and 3 Parameters (int argc, char* argv[], char *envp[])

int main(int argc, char* argv[], char* envp[])
{
        // variable declarations
        int i;

        // code
        printf("\n\n");
        printf("Hello World !!! \n"); // Library Functions
        printf("Number of Command Line Arguments = %d\n\n", argc);

        printf("Command Line Arguments Passed To This Program Are : \n\n");
        for(i = 0; i < argc; i++)
        {
                printf("Command Line Arguments Number %d = %s\n", (i + 1), argv[i]);
        }
        printf("\n\n");

	printf("First 20 Environmental Variables Passed To This Program Are : \n\n");
	for(i = 0; i < 20; i++)
	{
		printf("Environment Variable Number %d = %s\n", (i + 1), envp[i]);
	}
	printf("\n\n");
        return(0);

}

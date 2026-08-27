#include <stdio.h>
#include <ctype.h>
#include <conio.h>

int main(void)
{
	//variable declaraions
	char cInput, cLoop;
	unsigned int asciiVal = 0;

	//code
	printf("\n\n");
	printf("Enter The First Character Of First Name : ");
	cInput = getch();

	cInput = toupper(cInput);

	for (cLoop = 'A'; cLoop <= 'Z'; cLoop++)
	{
		if (cInput == cLoop)
		{
			asciiVal = (unsigned int)cInput;
			goto print_output;
		}
	}

	printf("\n\n");
	printf("Goto statement not executed, so printing \"Hello, world !!!\".\n");

print_output:
	printf("\n\n");

	if (asciiVal == 0)
	{
		printf("You must have a strange name! Could not find the character '%c' in the entire English Alphabet!\n", cInput);
	}
	else
	{
		printf("Character '%c' found. It has ASCII value %u.\n", cInput, asciiVal);
	}

	printf("\n\n");
	return(0);
}


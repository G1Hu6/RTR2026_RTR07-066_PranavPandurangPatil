#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
	// funciton prototype
	int MyStrlen(char[]);

	//variable declarations
	char chArr[MAX_STRING_LENGTH]; // A Character Array Is A String
	int strLen = 0;

	//code

	// STRING INPUT
	printf("\n\n");
	printf("Enter A String : \n\n");
	gets_s(chArr, MAX_STRING_LENGTH);

	// STRING OUTPUT
	printf("\n\n");
	printf("String Entered By You Is : \n\n");
	printf("%s\n", chArr);

	// STRING LENGTH
	printf("\n\n");
	strLen = MyStrlen(chArr);
	printf("Length Of String Is = %d Characters !!!\n\n", strLen);

	return(0);
}

int MyStrlen(char str[])
{
	//variable declarations
	int j;
	int string_length = 0;

	//code
	// DETERMINING EXACT LENGTH OF THE STRING, BY DETECTING THE FIRST OCCURENCE OF NULL-TERMINATING CHARACTR
	for (j = 0; j < MAX_STRING_LENGTH; j++)
	{
		if (str[j] == '\0')
			break;
		else
			string_length++;
	}
	return(string_length);
}


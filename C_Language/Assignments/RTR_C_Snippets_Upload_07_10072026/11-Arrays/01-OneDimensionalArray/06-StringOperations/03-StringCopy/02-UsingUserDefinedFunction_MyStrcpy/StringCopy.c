#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
	//function prototype
	void MyStrcpy(char[], char[]);

	//variable declarations
	char strOrig[MAX_STRING_LENGTH], strCopy[MAX_STRING_LENGTH]; // A Character Array Is A String

	//code

	// STRING INPUT
	printf("\n\n");
	printf("Enter A String : \n\n");
	gets_s(strOrig, MAX_STRING_LENGTH);

	// STRING COPY
	MyStrcpy(strCopy, strOrig);

	// STRING OUTPUT
	printf("\n\n");
	printf("The Original String Entered By You (i.e : 'strOrig[]') Is : \n\n");
	printf("%s\n", strOrig);

	printf("\n\n");
	printf("The Copied String (i.e : 'strCopy[]') Is : \n\n");
	printf("%s\n", strCopy);

	return(0);
}

void MyStrcpy(char str_destination[], char str_source[])
{
	//function prototype
	int MyStrlen(char[]);

	//variable declarations
	int strLen = 0;
	int j;

	//code
	strLen = MyStrlen(str_source);
	for (j = 0; j < strLen; j++)
		str_destination[j] = str_source[j];

	str_destination[j] = '\0';
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

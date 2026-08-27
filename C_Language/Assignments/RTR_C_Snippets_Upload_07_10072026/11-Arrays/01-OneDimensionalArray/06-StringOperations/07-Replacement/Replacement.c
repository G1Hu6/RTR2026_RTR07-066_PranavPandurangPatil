#include <stdio.h>

#define MAX_STRING_LENGTH 588

int main(void)
{
	//function prototype
	int MyStrlen(char[]);
	void MyStrcpy(char[], char[]);

	//variable declarations
	char strOrig[MAX_STRING_LENGTH], strVowels[MAX_STRING_LENGTH]; // A Character Array Is A String
	int strLen;
	int i;

	//code

	// STRING INPUT
	printf("\n\n");
	printf("Enter A String : \n\n");
	gets_s(strOrig, MAX_STRING_LENGTH);

	// STRING OUTPUT
	MyStrcpy(strVowels, strOrig);

	strLen = MyStrlen(strVowels);

	for (i = 0; i < strLen; i++)
	{
		switch (strVowels[i])
		{
		case 'A':
		case 'a':
		case 'E':
		case 'e':
		case 'I':
		case 'i':
		case 'O':
		case 'o':
		case 'U':
		case 'u':
			strVowels[i] = '*';
			break;
		default:
			break;
		}
	}

	// STRING OUTPUT
	printf("\n\n");
	printf("String Entered By You Is : \n\n");
	printf("%s\n", strOrig);

	printf("\n\n");
	printf("String After Replacement Of Vowels By * Is : \n\n");
	printf("%s\n", strVowels);

	return(0);
}

int MyStrlen(char str[])
{
	//variable declarations
	int j;
	int string_length = 0;

	//code
	// DETERMINNG EXACT LENGTH OF THE STRNG, BY DETECTNG THE FIRST OCCURENCE OF NULL-TERMINATING CHARACTER ( \0 )
	for (j = 0; j < MAX_STRING_LENGTH; j++)
	{
		if (str[j] == '\0')
			break;
		else
			string_length++;
	}
	return(string_length);
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


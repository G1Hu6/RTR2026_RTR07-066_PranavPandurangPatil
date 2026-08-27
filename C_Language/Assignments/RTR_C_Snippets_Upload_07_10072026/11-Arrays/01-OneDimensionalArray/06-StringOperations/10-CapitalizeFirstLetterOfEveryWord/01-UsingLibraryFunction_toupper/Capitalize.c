#include <stdio.h>
#include <ctype.h> //for toupper()

#define MAX_STRING_LENGTH 512

int main(void)
{
	//function prototype
	int MyStrlen(char[]);

	//variable declarations
	char chArr[MAX_STRING_LENGTH], strCapitalized[MAX_STRING_LENGTH]; // A Character Array Is A String
	int strLen;
	int i, j;

	//code

	printf("\n\n");
	printf("Enter A String : \n\n");
	gets_s(chArr, MAX_STRING_LENGTH);

	strLen = MyStrlen(chArr);
	j = 0;
	for (i = 0; i < strLen; i++)
	{
		if (i == 0)
			strCapitalized[j] = toupper(chArr[i]);
		else if (chArr[i] == ' ')
		{
			strCapitalized[j] = chArr[i];
			strCapitalized[j + 1] = toupper(chArr[i + 1]);

			j++;
			i++;
		}
		else
			strCapitalized[j] = chArr[i];

		j++;
	}

	strCapitalized[j] = '\0';

	// STRING OUTPUT
	printf("\n\n");
	printf("String Entered By You Is : \n\n");
	printf("%s\n", chArr);

	printf("\n\n");
	printf("String After Capitalizing First Letter Of Every Word : \n\n");
	printf("%s\n", strCapitalized);

	return(0);
}

int MyStrlen(char str[])
{
	//variable declarations
	int j;
	int string_length = 0;

	//code
	// DETERMINING EXACT LENGTH OF THE STRING, BY DETECTING THE FIRST OCCURENCE OF NULL-TERMINATING CHARACTER ( \0 )
	for (j = 0; j < MAX_STRING_LENGTH; j++)
	{
		if (str[j] == '\0')
			break;
		else
			string_length++;
	}
	return(string_length);
}


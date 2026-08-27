#include <stdio.h>

#define MAX_STRING_LENGTH 588

int main(void)
{
	//function prototype
	void MyStrcat(char[], char[]);

	//variable declarations
	char str1[MAX_STRING_LENGTH], str2[MAX_STRING_LENGTH]; // A Character Array Is A String

	//code

	// STRING INPUT
	printf("\n\n");
	printf("Enter First String : \n\n");
	gets_s(str1, MAX_STRING_LENGTH);

	printf("\n\n");
	printf("Enter Second String : \n\n");
	gets_s(str2, MAX_STRING_LENGTH);

	// STRING CONCAT
	printf("\n\n");
	printf("BEFORE CONCATENATION");
	printf("\n\n");
	printf("The Original First String Entered By You (i.e : 'str1[]') Is : \n\n");
	printf("%s\n", str1);

	printf("\n\n");
	printf("The Original Second String Entered By You (i.e : 'str2[]') Is : \n\n");
	printf("%s\n", str2);

	MyStrcat(str1, str2);

	printf("\n\n");
	printf("AFTER CONCATENATION");
	printf("\n\n");
	printf("'str1[]' Is : \n\n");
	printf("%s\n", str1);

	printf("\n\n");
	printf("'str2[]' Is : \n\n");
	printf("%s\n", str2);

	return(0);
}

void MyStrcat(char str_destination[], char str_source[])
{
	//function prototype
	int MyStrlen(char[]);

	//variable declarations
	int strLen_dest = 0;
	int strLen_src = 0;
	int i, j;

	//code
	strLen_dest = MyStrlen(str_destination);
	strLen_src = MyStrlen(str_source);

	for (i = strLen_dest, j = 0; j < strLen_src; i++, j++)
	{
		str_destination[i] = str_source[j];
	}
	str_destination[i] = '\0';
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


#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
	//function prototype
	int MyStrlen(char[]);

	//variable declarations
	char chArr[MAX_STRING_LENGTH]; // A Character Array Is A String
	int strLen;
	int cnt_A = 0, cnt_E = 0, cnt_I = 0, cnt_O = 0, cnt_U = 0; // Initial countz = 0
	int i;

	//code

	// STRING INPUT
	printf("\n\n");
	printf("Enter A String : \n\n");
	gets_s(chArr, MAX_STRING_LENGTH);

	// STRING OUTPUT
	printf("\n\n");
	printf("String Entered By You Is : \n\n");
	printf("%s\n", chArr);

	strLen = MyStrlen(chArr);

	for (i = 0; i < strLen; i++)
	{
		switch (chArr[i])
		{
		case 'A':
		case 'a':
			cnt_A++;
			break;
		case 'E':
		case 'e':
			cnt_E++;
			break;
		case 'I':
		case 'i':
			cnt_I++;
			break;
		case 'O':
		case 'o':
			cnt_O++;
			break;
		case 'U':
		case 'u':
			cnt_U++;
			break;
		default:
			break;
		}
	}

	printf("\n\n");
	printf("In The String Entered By You, The Vowels And The Number Of Their Occurences Are As Follows : \n\n");
	printf("'A' Has Occured = %d Times !!!\n", cnt_A);
	printf("'E' Has Occured = %d Times !!!\n", cnt_E);
	printf("'I' Has Occured = %d Times !!!\n", cnt_I);
	printf("'O' Has Occured = %d Times !!!\n", cnt_O);
	printf("'U' Has Occured = %d Times !!!\n", cnt_U);

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


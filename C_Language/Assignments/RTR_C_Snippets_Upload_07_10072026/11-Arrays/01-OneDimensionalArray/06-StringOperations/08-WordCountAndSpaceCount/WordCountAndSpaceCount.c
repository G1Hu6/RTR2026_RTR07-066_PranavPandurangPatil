#include <stdio.h>

#define MAX_STRING_LENGTH 588

int main(void)
{
	//function prototype
	int MyStrlen(char[]);

	//variable declarations
	char chArr[MAX_STRING_LENGTH]; // A Character Array Is A String
	int strLen;
	int i;
	int word_cnt = 0, space_cnt = 0;

	//code

	// STRING INPUT
	printf("\n\n");
	printf("Enter A String : \n\n");
	gets_s(chArr, MAX_STRING_LENGTH);

	strLen = MyStrlen(chArr);

	for (i = 0; i < strLen; i++)
	{
		switch (chArr[i])
		{
		case 32: // 32 IS THE ASCII VALUE FOR SPACE (' ') CHARACTER
			space_cnt++;
			break;
		default:
			break;
		}
	}

	word_cnt = space_cnt + 1;

	// STRING OUTPUT
	printf("\n\n");
	printf("String Entered By You Is : \n\n");
	printf("%s\n", chArr);

	printf("\n\n");
	printf("Number Of Spaces In The Input String = %d\n\n", space_cnt);
	printf("Number Of Words In The Input String = %d\n\n", word_cnt);

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


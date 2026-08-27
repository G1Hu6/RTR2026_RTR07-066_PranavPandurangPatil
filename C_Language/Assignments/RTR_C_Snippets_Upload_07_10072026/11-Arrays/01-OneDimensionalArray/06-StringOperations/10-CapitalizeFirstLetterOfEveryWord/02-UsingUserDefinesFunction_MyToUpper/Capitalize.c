#include <stdio.h>

#define MAX_STRING_LENGTH 512

#define SPACE ' '
#define FULLSTOP '.'
#define COMMA ','
#define EXCLAMATION '!'
#define QUESTION_MARK '?'

int main(void)
{
	//function prototype
	int MyStrlen(char[]);
	char MyToUpper(char);

	//variable declarations
	char chArr[MAX_STRING_LENGTH], strCapitalized[MAX_STRING_LENGTH]; // A Character Array Is A String
	int strLen;
	int i, j;

	//code

	// STRING INPUT
	printf("\n\n");
	printf("Enter A String : \n\n");
	gets_s(chArr, MAX_STRING_LENGTH);

	strLen = MyStrlen(chArr);
	j = 0;
	for (i = 0; i < strLen; i++)
	{
		if (i == 0) //First Letter Of Any Sentence Must Be A CAPITAL LETTER
			strCapitalized[j] = MyToUpper(chArr[i]);
		else if (chArr[i] == SPACE) //First Letter Of Every Word In The Sentence Must Be A CAPITAL LETTER. Words Are Separated By Spaces.
		{
			strCapitalized[j] = chArr[i];
			strCapitalized[j + 1] = MyToUpper(chArr[i + 1]);

			//SINCE, ALREADY TWO CHARACTERS (AT INDICES 'i' AND i + 1 HAVE BEEN CONSIDERED IN THIS else-if BLOCK...WE ARE EXTRA-INCREMENTING 'i' AND 'j' BY 1
			j++;
			i++;
		}
		else if ((chArr[i] == FULLSTOP || chArr[i] == COMMA || chArr[i] == EXCLAMATION || chArr[i] == QUESTION_MARK) && (chArr[i] != SPACE)) //First Letter Of Every Word After Punctuation Mark, In The Sentence Must Be A CAPITAL LETTER. Words Are Separated By Punctuations.
		{
			strCapitalized[j] = chArr[i];
			strCapitalized[j + 1] = SPACE;
			strCapitalized[j + 2] = MyToUpper(chArr[i + 1]);

			j = j + 2;
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

char MyToUpper(char ch)
{
	//variable declarations
	int num;
	char c;

	//code

	if (ch >= 97 && ch <= 122)
	{
		num = (int)ch - 32;
		c = (char)num;
	}
	else
		c = ch;

	return(c);
}


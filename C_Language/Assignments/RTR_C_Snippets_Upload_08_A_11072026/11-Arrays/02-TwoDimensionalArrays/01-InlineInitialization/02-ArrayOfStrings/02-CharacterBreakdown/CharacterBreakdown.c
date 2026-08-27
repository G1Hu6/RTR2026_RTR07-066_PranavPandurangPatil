#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
	//function prototype
	int MyStrlen(char[]);

	//variable declaraions
	char strArr[8][10] = { "Hello!", "Welcome", "To", "RTR-07", "Batch", "(2026-27)", "Of", "AMC." };
	int strLens[8];
	int sz;
	int rows;
	int i, j;

	//code
	sz = sizeof(strArr);
	rows = sz / sizeof(strArr[0]);

	for (i = 0; i < rows; i++)
		strLens[i] = MyStrlen(strArr[i]);

	printf("\n\n");
	printf("The Entire String Array : \n\n");
	for (i = 0; i < rows; i++)
		printf("%s ", strArr[i]);

	printf("\n\n");
	printf("Strings In The 2D Array : \n\n");

	for (i = 0; i < rows; i++)
	{
		printf("String Number %d => %s\n", (i + 1), strArr[i]);
		for (j = 0; j < strLens[i]; j++)
		{
			printf("Character %d = %c\n", (j + 1), strArr[i][j]);
		}
		printf("\n\n");
	}
	return(0);
}

int MyStrlen(char str[])
{
	//variable declaraions
	int j;
	int len = 0;

	//code
	for (j = 0; j < MAX_STRING_LENGTH; j++)
	{
		if (str[j] == '\0')
			break;
		else
			len++;
	}
	return(len);
}


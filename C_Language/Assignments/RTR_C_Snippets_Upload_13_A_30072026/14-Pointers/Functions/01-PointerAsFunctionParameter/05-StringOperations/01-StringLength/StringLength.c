#include<stdio.h>
#include<stdlib.h>
#define MAX_STRING_LENGTH 512

int main(void)
{
	int strLen(char*);

	char *pStr = NULL;
	int len = 0;

	printf("\n\n");
	pStr = (char*)malloc(MAX_STRING_LENGTH * sizeof(char));
	if (pStr == NULL)
	{
		printf("Memory allocation failed ! Exiting now..\n\n");
		exit(0);
	}

	printf("Enter a word or sentence : \n\n");
	gets_s(pStr, MAX_STRING_LENGTH);

	printf("\n\n");
	printf("You entered : \n\n");
	printf("%s\n", pStr);

	printf("\n\n");
	len = strLen(pStr);
	printf("Length of the string = %d characters\n\n", len);

	if (pStr)
	{
		free(pStr);
		pStr = NULL;
	}

	return (0);
}

int strLen(char *str)
{
	int i;
	int len = 0;

	for (i = 0; i < MAX_STRING_LENGTH; i++)
	{
		if (*(str + i) == '\0')
			break;
		else
			len++;
	}
	return len;
}


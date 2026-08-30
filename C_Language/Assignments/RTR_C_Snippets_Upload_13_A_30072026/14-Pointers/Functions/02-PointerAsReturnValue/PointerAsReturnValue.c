#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
	char* replaceVowels(char *);

	char buf[MAX_STRING_LENGTH];
	char *pResult = NULL;

	printf("\n\n");
	printf("Enter a string : ");
	gets_s(buf, MAX_STRING_LENGTH);

	pResult = replaceVowels(buf);
	if (pResult == NULL)
	{
		printf("replaceVowels() failed ! Exiting now...\n\n");
		exit(0);
	}

	printf("\n\n");
	printf("String after replacing vowels with '#' : \n\n");
	printf("%s\n\n", pResult);

	if (pResult)
	{
		free(pResult);
		pResult = NULL;
	}

	return(0);
}

char* replaceVowels(char *s)
{
	void strCopy(char *, char *);
	int strLen(char *);

	char *pOut = NULL;
	int i;

	pOut = (char *)malloc((strLen(s) + 1) * sizeof(char));
	if (pOut == NULL)
	{
		printf("Memory allocation for output string failed !\n\n");
		return(NULL);
	}

	strCopy(pOut, s);
	for (i = 0; i < strLen(pOut); i++)
	{
		switch (pOut[i])
		{
		case 'A': case 'a':
		case 'E': case 'e':
		case 'I': case 'i':
		case 'O': case 'o':
		case 'U': case 'u':
			pOut[i] = '#';
			break;
		default:
			break;
		}
	}

	return(pOut);
}

void strCopy(char *dst, char *src)
{
	int strLen(char *);

	int len = 0;
	int i;

	len = strLen(src);
	for (i = 0; i < len; i++)
		*(dst + i) = *(src + i);

	*(dst + i) = '\0';
}

int strLen(char *str)
{
	int i;
	int len = 0;

	for (i = 0; i < MAX_STRING_LENGTH; i++)
	{
		if (str[i] == '\0')
			break;
		else
			len++;
	}
	return(len);
}


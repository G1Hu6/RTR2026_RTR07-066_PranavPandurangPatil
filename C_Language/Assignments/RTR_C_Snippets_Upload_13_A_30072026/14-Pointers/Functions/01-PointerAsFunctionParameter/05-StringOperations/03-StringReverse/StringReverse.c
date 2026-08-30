#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
	//function prototype
	void strRev(char *, char *);
	int strLen(char *);

	//variable declarations
	char *pSrc = NULL, *pRev = NULL;
	int srcLen;

	//code
	printf("\n\n");
	pSrc = (char *)malloc(MAX_STRING_LENGTH * sizeof(char));
	if (pSrc == NULL)
	{
		printf("Memory allocation for source string failed ! Exiting now...\n\n");
		exit(0);
	}

	printf("Type a string to reverse : \n\n");
	gets_s(pSrc, MAX_STRING_LENGTH);

	srcLen = strLen(pSrc);
	pRev = (char *)malloc((srcLen + 1) * sizeof(char));
	if (pRev == NULL)
	{
		printf("Memory allocation for reversed string failed ! Exiting now...\n\n");
		exit(0);
	}

	strRev(pRev, pSrc);

	printf("Original String (pSrc) : \n\n");
	printf("%s\n", pSrc);

	printf("\n\n");
	printf("Reversed String (pRev) : \n\n");
	printf("%s\n", pRev);

	if (pRev)
	{
		free(pRev);
		pRev = NULL;
		printf("\n\n");
		printf("Memory for 'pRev' successfully freed !!!\n\n");
	}

	if (pSrc)
	{
		free(pSrc);
		pSrc = NULL;
		printf("\n\n");
		printf("Memory for 'pSrc' successfully freed !!!\n\n");
	}

	return(0);
}

void strRev(char *dst, char *src)
{
	//function prototype
	int strLen(char *);

	//variable declarations
	int len = 0;
	int i, j, last;

	//code
	len = strLen(src);
	last = len - 1;

	for (i = 0, j = last; i < len, j >= 0; i++, j--)
	{
		*(dst + i) = *(src + j);
	}

	*(dst + i) = '\0';
}

int strLen(char *str)
{
	//variable declarations
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


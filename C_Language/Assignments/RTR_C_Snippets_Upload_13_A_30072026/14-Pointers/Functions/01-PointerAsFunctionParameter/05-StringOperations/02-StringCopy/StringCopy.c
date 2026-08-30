#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
	//function prototype
	void strCopy(char *, char *);
	int strLen(char *);

	//variable declarations
	char *pSrc = NULL, *pDst = NULL;

	//code
	printf("\n\n");
	pSrc = (char *)malloc(MAX_STRING_LENGTH * sizeof(char));
	if (pSrc == NULL)
	{
		printf("Memory allocation for source string failed ! Exiting now...\n\n");
		exit(0);
	}

	printf("Type a string to copy : \n\n");
	gets_s(pSrc, MAX_STRING_LENGTH);

	int srcLen = strLen(pSrc);
	pDst = (char *)malloc((srcLen + 1) * sizeof(char));
	if (pDst == NULL)
	{
		printf("Memory allocation for destination string failed ! Exiting now...\n\n");
		exit(0);
	}

	strCopy(pDst, pSrc);

	printf("\n\n");
	printf("Source String (pSrc) : \n\n");
	printf("%s\n", pSrc);

	printf("\n\n");
	printf("Copied String (pDst) : \n\n");
	printf("%s\n", pDst);

	if (pDst)
	{
		free(pDst);
		pDst = NULL;
		printf("\n\n");
		printf("Memory for 'pDst' successfully freed !!!\n\n");
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

void strCopy(char *dst, char *src)
{
	//function prototype
	int strLen(char *);

	//variable declarations
	int len = 0;
	int i;

	//code
	len = strLen(src);
	for (i = 0; i < len; i++)
		*(dst + i) = *(src + i);

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


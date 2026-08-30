#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
	//function prototype
	void strConcat(char *, char *);
	int strLen(char *);

	//variable declarations
	char *pStr1 = NULL, *pStr2 = NULL;

	//code
	printf("\n\n");
	pStr1 = (char *)malloc(MAX_STRING_LENGTH * sizeof(char));
	if (pStr1 == NULL)
	{
		printf("Memory allocation for first string failed ! Exiting now...\n\n");
		exit(0);
	}

	printf("Enter first string : \n\n");
	gets_s(pStr1, MAX_STRING_LENGTH);

	printf("\n\n");
	pStr2 = (char *)malloc(MAX_STRING_LENGTH * sizeof(char));
	if (pStr2 == NULL)
	{
		printf("Memory allocation for second string failed ! Exiting now...\n\n");
		exit(0);
	}

	printf("Enter second string : \n\n");
	gets_s(pStr2, MAX_STRING_LENGTH);

	printf("\n\n");
	printf("****** BEFORE CONCATENATION ******");
	printf("\n\n");
	printf("pStr1 : \n\n");
	printf("%s\n", pStr1);

	printf("\n\n");
	printf("pStr2 : \n\n");
	printf("%s\n", pStr2);

	strConcat(pStr1, pStr2);

	printf("\n\n");
	printf("****** AFTER CONCATENATION ******");
	printf("\n\n");
	printf("pStr1 : \n\n");
	printf("%s\n", pStr1);

	printf("\n\n");
	printf("pStr2 : \n\n");
	printf("%s\n", pStr2);

	if (pStr2)
	{
		free(pStr2);
		pStr2 = NULL;
		printf("\n\n");
		printf("Memory for 'pStr2' successfully freed !!!\n\n");
	}

	if (pStr1)
	{
		free(pStr1);
		pStr1 = NULL;
		printf("\n\n");
		printf("Memory for 'pStr1' successfully freed !!!\n\n");
	}

	return(0);
}

void strConcat(char *dst, char *src)
{
	//function prototype
	int strLen(char *);

	//variable declarations
	int srcLen = 0, dstLen = 0;
	int i, j;

	//code
	srcLen = strLen(src);
	dstLen = strLen(dst);

	for (i = dstLen, j = 0; j < srcLen; i++, j++)
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


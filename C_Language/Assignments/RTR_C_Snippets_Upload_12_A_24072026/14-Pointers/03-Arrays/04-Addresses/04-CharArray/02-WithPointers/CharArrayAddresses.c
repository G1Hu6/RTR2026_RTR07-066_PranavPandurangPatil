#include <stdio.h>

int main(void)
{
	//variable declaraions
	char cArr[5];
	char *p_cArr = NULL;
	int i;

	//code
	for (i = 0; i < 5; i++)
		cArr[i] = (char)(i + 65);

	p_cArr = cArr;

	printf("\n\n");
	printf("Elements Of The Character Array : \n\n");
	for (i = 0; i < 5; i++)
		printf("cArr[%d] = %c\n", i, *(p_cArr + i));

	printf("\n\n");
	printf("Elements Of The Character Array : \n\n");
	for (i = 0; i < 5; i++)
		printf("cArr[%d] = %c \t \t Address = %p\n", i, *(p_cArr + i), (p_cArr + i));

	printf("\n\n");

	return(0);
}


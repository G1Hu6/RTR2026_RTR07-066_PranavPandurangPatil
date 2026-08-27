#include <stdio.h>

int main(void)
{
	//variable declaraions
	char cArr[5];
	int i;

	//code
	for (i = 0; i < 5; i++)
		cArr[i] = (char)(i + 65);

	printf("\n\n");
	printf("Elements Of The Character Array : \n\n");
	for (i = 0; i < 5; i++)
		printf("cArr[%d] = %c\n", i, cArr[i]);

	printf("\n\n");
	printf("Elements Of The Character Array : \n\n");
	for (i = 0; i < 5; i++)
		printf("cArr[%d] = %c \t \t Address = %p\n", i, cArr[i], &cArr[i]);

	printf("\n\n");

	return(0);
}


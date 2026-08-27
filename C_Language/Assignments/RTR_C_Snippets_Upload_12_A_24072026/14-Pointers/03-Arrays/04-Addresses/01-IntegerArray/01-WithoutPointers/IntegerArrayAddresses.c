#include <stdio.h>

int main(void)
{
	//variable declaraions
	int iArr[5];
	int i;

	//code
	for (i = 0; i < 5; i++)
		iArr[i] = (i + 1) * 5;

	printf("\n\n");
	printf("Elements Of The Integer Array : \n\n");
	for (i = 0; i < 5; i++)
		printf("iArr[%d] = %d\n", i, iArr[i]);

	printf("\n\n");
	printf("Elements Of The Integer Array : \n\n");
	for (i = 0; i < 5; i++)
		printf("iArr[%d] = %d \t \t Address = %p\n", i, iArr[i], &iArr[i]);

	printf("\n\n");

	return(0);
}


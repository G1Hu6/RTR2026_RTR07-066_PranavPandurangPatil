#include <stdio.h>

int main(void)
{
	//variable declaraions
	float fArr[5];
	int i;

	//code
	for (i = 0; i < 5; i++)
		fArr[i] = (float)(i + 1) * 2.5f;

	printf("\n\n");
	printf("Elements Of The 'float' Array : \n\n");
	for (i = 0; i < 5; i++)
		printf("fArr[%d] = %f\n", i, fArr[i]);

	printf("\n\n");
	printf("Elements Of The 'float' Array : \n\n");
	for (i = 0; i < 5; i++)
		printf("fArr[%d] = %f \t \t Address = %p\n", i, fArr[i], &fArr[i]);

	printf("\n\n");

	return(0);
}


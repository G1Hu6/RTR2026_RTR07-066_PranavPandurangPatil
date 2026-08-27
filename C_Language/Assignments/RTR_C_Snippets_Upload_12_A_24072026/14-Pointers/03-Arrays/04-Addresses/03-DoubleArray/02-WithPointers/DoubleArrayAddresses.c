#include <stdio.h>

int main(void)
{
	//variable declaraions
	double dArr[5];
	double *p_dArr = NULL;
	int i;

	//code
	for (i = 0; i < 5; i++)
		dArr[i] = (double)(i + 1) * 1.5;

	p_dArr = dArr;

	printf("\n\n");
	printf("Elements Of The 'double' Array : \n\n");
	for (i = 0; i < 5; i++)
		printf("dArr[%d] = %lf\n", i, *(p_dArr + i));

	printf("\n\n");
	printf("Elements Of The 'double' Array : \n\n");
	for (i = 0; i < 5; i++)
		printf("dArr[%d] = %lf \t \t Address = %p\n", i, *(p_dArr + i), (p_dArr + i));

	printf("\n\n");

	return(0);
}


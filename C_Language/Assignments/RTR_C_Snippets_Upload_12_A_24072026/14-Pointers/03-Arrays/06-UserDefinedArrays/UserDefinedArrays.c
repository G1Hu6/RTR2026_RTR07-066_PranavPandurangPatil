#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define INT_SIZE sizeof(int)
#define FLOAT_SIZE sizeof(float)
#define DOUBLE_SIZE sizeof(double)
#define CHAR_SIZE sizeof(char)

int main(void)
{
	//variable declaraions
	int *p_iArr = NULL;
	unsigned int iLen = 0;

	float *p_fArr = NULL;
	unsigned int fLen = 0;

	double *p_dArr = NULL;
	unsigned int dLen = 0;

	char *p_cArr = NULL;
	unsigned int cLen = 0;

	int i;

	//code
	printf("\n\n");
	printf("Enter The Number Of Elements You Want In The Integer Array : ");
	scanf("%u", &iLen);

	p_iArr = (int *)malloc(INT_SIZE * iLen);
	if (p_iArr == NULL)
	{
		printf("\n\n");
		printf("MEMORY ALLOCATION FOR INTEGER ARRAY FAILED !!! EXITTING NOW...\n\n");
		exit(0);
	}
	else
	{
		printf("\n\n");
		printf("MEMORY ALLOCATION FOR INTEGER ARRAY SUCCEEDED !!!\n\n");
	}

	printf("\n\n");
	printf("Enter The %d Integer Elements To Fill Up The Integer Array : \n\n", iLen);
	for (i = 0; i < iLen; i++)
		scanf("%d", (p_iArr + i));

	printf("\n\n");
	printf("Enter The Number Of Elements You Want In The 'float' Array : ");
	scanf("%u", &fLen);

	p_fArr = (float *)malloc(FLOAT_SIZE * fLen);
	if (p_fArr == NULL)
	{
		printf("\n\n");
		printf("MEMORY ALLOCATION FOR FLOATING-POINT ARRAY FAILED !!! EXITTING NOW...\n\n");
		exit(0);
	}
	else
	{
		printf("\n\n");
		printf("MEMORY ALLOCATION FOR FLOATING-POINT ARRAY SUCCEEDED !!!\n\n");
	}

	printf("\n\n");
	printf("Enter The %d Floating-Point Elements To Fill Up The 'float' Array : \n\n", fLen);
	for (i = 0; i < fLen; i++)
		scanf("%f", (p_fArr + i));

	printf("\n\n");
	printf("Enter The Number Of Elements You Want In The 'double' Array : ");
	scanf("%u", &dLen);

	p_dArr = (double *)malloc(DOUBLE_SIZE * dLen);
	if (p_dArr == NULL)
	{
		printf("\n\n");
		printf("MEMORY ALLOCATION FOR 'DOUBLE' ARRAY FAILED !!! EXITTING NOW...\n\n");
		exit(0);
	}
	else
	{
		printf("\n\n");
		printf("MEMORY ALLOCATION FOR 'DOUBLE' ARRAY SUCCEEDED !!!\n\n");
	}

	printf("\n\n");
	printf("Enter The %d Double Elements To Fill Up The 'double' Array : \n\n", dLen);
	for (i = 0; i < dLen; i++)
		scanf("%lf", (p_dArr + i));

	printf("\n\n");
	printf("Enter The Number Of Elements You Want In The Character Array : ");
	scanf("%u", &cLen);

	p_cArr = (char *)malloc(CHAR_SIZE * cLen);
	if (p_cArr == NULL)
	{
		printf("\n\n");
		printf("MEMORY ALLOCATION FOR CHARACTER ARRAY FAILED !!! EXITTING NOW...\n\n");
		exit(0);
	}
	else
	{
		printf("\n\n");
		printf("MEMORY ALLOCATION FOR CHARACTER ARRAY SUCCEEDED !!!\n\n");
	}

	printf("\n\n");
	printf("Enter The %d Character Elements To Fill Up The Character Array : \n\n", cLen);
	for (i = 0; i < cLen; i++)
	{
		*(p_cArr + i) = getch();
		printf("%c\n", *(p_cArr + i));
	}

	printf("\n\n");
	printf("The Integer Array Entered By You And Consisting Of %d Elements Is As Follows : \n\n", iLen);
	for (i = 0; i < iLen; i++)
		printf("%d \t \t At Address : %p\n", *(p_iArr + i), (p_iArr + i));

	printf("\n\n");
	printf("The Float Array Entered By You And Consisting Of %d Elements Is As Follows : \n\n", fLen);
	for (i = 0; i < fLen; i++)
		printf("%f \t \t At Address : %p\n", *(p_fArr + i), (p_fArr + i));

	printf("\n\n");
	printf("The Double Array Entered By You And Consisting Of %d Elements Is As Follows : \n\n", dLen);
	for (i = 0; i < dLen; i++)
		printf("%lf \t \t At Address : %p\n", *(p_dArr + i), (p_dArr + i));

	printf("\n\n");
	printf("The Character Array Entered By You And Consisting Of %d Elements Is As Follows : \n\n", cLen);
	for (i = 0; i < cLen; i++)
		printf("%c \t \t At Address : %p\n", *(p_cArr + i), (p_cArr + i));

	if (p_cArr)
	{
		free(p_cArr);
		p_cArr = NULL;
		printf("\n\n");
		printf("MEMORY OCCUPIED BY CHARACTER ARRAY HAS BEEN SUCCESSFULLY FREED !!!\n\n");
	}

	if (p_dArr)
	{
		free(p_dArr);
		p_dArr = NULL;
		printf("\n\n");
		printf("MEMORY OCCUPIED BY 'DOUBLE' ARRAY HAS BEEN SUCCESSFULLY FREED !!!\n\n");
	}

	if (p_fArr)
	{
		free(p_fArr);
		p_fArr = NULL;
		printf("\n\n");
		printf("MEMORY OCCUPIED BY FLOATING-POINT ARRAY HAS BEEN SUCCESSFULLY FREED !!!\n\n");
	}

	if (p_iArr)
	{
		free(p_iArr);
		p_iArr = NULL;
		printf("\n\n");
		printf("MEMORY OCCUPIED BY INTEGER ARRAY HAS BEEN SUCCESSFULLY FREED !!!\n\n");
	}

	return(0);
}


#include <stdio.h>
#include<stdlib.h>
int main(void)
{
	void mathOps(int, int, int *, int *, int *, int *, int *);

	int num1;
	int num2;
	int *pSum = NULL;
	int *pDiff = NULL;
	int *pProd = NULL;
	int *pQuot = NULL;
	int *pRem = NULL;

	printf("\n\n");
	printf("Enter First Number :");
	scanf("%d", &num1);
	printf("\n\n");
	printf("Enter Second Number :");
	scanf("%d", &num2);

	pSum = (int*)malloc(1 * sizeof(int));
	if (pSum == NULL)
	{
		printf("Could Not Allocate Memory for 'pSum' . exitting now.....\n\n");
		exit(0);
	}
	pDiff = (int*)malloc(1 * sizeof(int));
	if (pDiff == NULL)
	{
		printf("Could Not Allocate Memory for 'pDiff' . exitting now.....\n\n");
		exit(0);
	}
	pProd = (int*)malloc(1 * sizeof(int));
	if (pProd == NULL)
	{
		printf("Could Not Allocate Memory for 'pProd' . exitting now.....\n\n");
		exit(0);
	}
	pQuot = (int*)malloc(1 * sizeof(int));
	if (pQuot == NULL)
	{
		printf("Could Not Allocate Memory for 'pQuot' . exitting now.....\n\n");
		exit(0);
	}
	pRem = (int*)malloc(1 * sizeof(int));
	if (pRem == NULL)
	{
		printf("Could Not Allocate Memory for 'pRem' . exitting now.....\n\n");
		exit(0);
	}

	mathOps(num1, num2, pSum, pDiff, pProd, pQuot, pRem);
	printf("\n\n");
	printf("********* RESULT ******\n\n");
	printf("Sum        = %d\n\n", *pSum);
	printf("Difference = %d\n\n", *pDiff);
	printf("Product    = %d\n\n", *pProd);
	printf("Quotient   = %d\n\n", *pQuot);
	printf("Remainder  = %d\n\n", *pRem);

	if (pRem)
	{
		free(pRem);
		pRem = NULL;
		printf("Memory allocated for 'pRem' successfully freed !!!\n\n");
	}
	if (pQuot)
	{
		free(pQuot);
		pQuot = NULL;
		printf("Memory allocated for 'pQuot' successfully freed !!!\n\n");
	}
	if (pProd)
	{
		free(pProd);
		pProd = NULL;
		printf("Memory allocated for 'pProd' successfully freed !!!\n\n");
	}
	if (pDiff)
	{
		free(pDiff);
		pDiff = NULL;
		printf("Memory allocated for 'pDiff' successfully freed !!!\n\n");
	}
	if (pSum)
	{
		free(pSum);
		pSum = NULL;
		printf("Memory allocated for 'pSum' successfully freed !!!\n\n");
	}

	return (0);
}

void mathOps(int x, int y, int *pSum, int *pDiff, int *pProd, int *pQuot, int *pRem)
{

	*pSum  = x + y;
	*pDiff = x - y;
	*pProd = x * y;
	*pQuot = x / y;
	*pRem  = x % y;
}


#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	//function declarations
	void multiplyArr(int *, int, int);

	//variable declaration
	int *pArr = NULL;
	int count;
	int i, factor;

	//code
	printf("\n\n");
	printf("How many elements in the array : ");
	scanf("%d", &count);

	pArr = (int *)malloc(count * sizeof(int));
	if (pArr == NULL)
	{
		printf("Memory allocation for 'pArr' failed ! Exiting now...\n\n");
		exit(0);
	}

	printf("\n\n");
	printf("Enter %d integer values : \n\n", count);
	for (i = 0; i < count; i++)
		scanf("%d", &pArr[i]);

	printf("\n\n");
	printf("Array before multiplication : \n\n");
	for (i = 0; i < count; i++)
		printf("pArr[%d] = %d\n", i, pArr[i]);

	printf("\n\n");
	printf("Enter the multiplication factor : ");
	scanf("%d", &factor);

	multiplyArr(pArr, count, factor);

	printf("\n\n");
	printf("Array after multiplication by %d : \n\n", factor);
	for (i = 0; i < count; i++)
		printf("pArr[%d] = %d\n", i, pArr[i]);

	if (pArr)
	{
		free(pArr);
		pArr = NULL;
		printf("\n\n");
		printf("Memory for 'pArr' successfully freed !!!\n\n");
	}

	return(0);
}

void multiplyArr(int *arr, int size, int factor)
{
	//variable declarations
	int i;

	//code
	for (i = 0; i < size; i++)
		arr[i] = arr[i] * factor;
}


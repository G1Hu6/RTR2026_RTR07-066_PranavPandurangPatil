#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	//variable declaraions
	int *p_iArr = NULL;
	unsigned int arrLen = 0;
	int i;

	//code
	printf("\n\n");
	printf("Enter The Number Of Elements You Want In Your Integer Array : ");
	scanf("%d", &arrLen);

	p_iArr = (int *)malloc(sizeof(int) * arrLen);
	if (p_iArr == NULL)
	{
		printf("\n\n");
		printf("MEMORY ALLOCATION FOR INTEGER ARRAY HAS FAILED !!! EXITTING NOW...\n\n");
		exit(0);
	}
	else
	{
		printf("\n\n");
		printf("MEMORY ALLOCATION FOR INTEGER ARRAY HAS SUCCEEDED !!!\n");
		printf("MEMORY ADDRESSES FROM %p TO %p HAVE BEEN ALLOCATED TO INTEGER ARRAY !!!\n\n", p_iArr, (p_iArr + (arrLen - 1)));
	}

	printf("\n\n");
	printf("Enter %d Elements For The Integer Array : \n\n", arrLen);
	for (i = 0; i < arrLen; i++)
		scanf("%d", (p_iArr + i));

	printf("\n\n");
	printf("The Integer Array Entered By You, Consisting Of %d Elements : \n\n", arrLen);
	for (i = 0; i < arrLen; i++)
	{
		printf("p_iArr[%d] = %d \t \t At Address &p_iArr[%d] : %p\n", i, p_iArr[i], i, &p_iArr[i]);
	}

	printf("\n\n");
	for (i = 0; i < arrLen; i++)
	{
		printf("*(p_iArr + %d) = %d \t \t At Address (p_iArr + %d) : %p\n", i, *(p_iArr + i), i, (p_iArr + i));
	}

	if (p_iArr)
	{
		free(p_iArr);
		p_iArr = NULL;
		printf("\n\n");
		printf("MEMORY ALLOCATED FOR INTEGER ARRAY HAS BEEN SUCCESSFULLY FREED !!!\n\n");
	}

	return(0);
}


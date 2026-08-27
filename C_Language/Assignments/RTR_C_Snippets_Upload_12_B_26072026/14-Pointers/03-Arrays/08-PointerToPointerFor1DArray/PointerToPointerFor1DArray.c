#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	//function prototype
	void MyAlloc(int **pp, unsigned int numElem);

	//variable declaraions
	int *pArr = NULL;
	unsigned int nElem;
	int i;

	//code
	printf("\n\n");
	printf("How Many Elements You Want In Integer Array ?\n\n");
	scanf("%u", &nElem);

	printf("\n\n");
	MyAlloc(&pArr, nElem);

	printf("Enter %u Elements To Fill Up Your Integer Array : \n\n", nElem);
	for (i = 0; i < nElem; i++)
		scanf("%d", &pArr[i]);

	printf("\n\n");
	printf("The %u Elements Entered By You In The Integer Array : \n\n", nElem);
	for (i = 0; i < nElem; i++)
		printf("%u\n", pArr[i]);

	printf("\n\n");
	if (pArr)
	{
		free(pArr);
		pArr = NULL;
		printf("Memory Allocated Has Now Been Successfully Freed !!!\n\n");
	}

	return(0);
}

void MyAlloc(int **pp, unsigned int numElem)
{
	//code
	*pp = (int *)malloc(numElem * sizeof(int));
	if (*pp == NULL)
	{
		printf("Could Not Allocate Memory !!! Exitting Now ...\n\n");
		exit(0);
	}
	printf("MyAlloc() Has Successfully Allocated %lu Bytes For Integer Array !!!\n\n", (numElem * sizeof(int)));
}


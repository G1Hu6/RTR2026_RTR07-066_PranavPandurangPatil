#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int *p_i;
	int i;
	float *p_f;
	float f;
	double *p_d;
	double d;
} MyData;

int main(void)
{
	//variable declaraions
	MyData *pDataObj = NULL;

	//code
	printf("\n\n");
	pDataObj = (MyData *)malloc(sizeof(MyData));
	if (pDataObj == NULL)
	{
		printf("FAILED TO ALLOCATE MEMORY TO 'MyData' !!! EXITTING NOW ...\n\n");
		exit(0);
	}
	else
	{
		printf("SUCCESSFULLY ALLOCATED MEMORY TO 'MyData' !!!\n\n");
	}

	pDataObj->i = 18;
	pDataObj->p_i = &(pDataObj->i);

	pDataObj->f = 25.5f;
	pDataObj->p_f = &(pDataObj->f);

	pDataObj->d = 6.28318;
	pDataObj->p_d = &(pDataObj->d);

	printf("\n\n");
	printf("i = %d\n", *(pDataObj->p_i));
	printf("Address Of 'i' = %p\n", pDataObj->p_i);

	printf("\n\n");
	printf("f = %f\n", *(pDataObj->p_f));
	printf("Address Of 'f' = %p\n", pDataObj->p_f);

	printf("\n\n");
	printf("d = %lf\n", *(pDataObj->p_d));
	printf("Address Of 'd' = %p\n", pDataObj->p_d);

	if (pDataObj)
	{
		free(pDataObj);
		pDataObj = NULL;
		printf("MEMORY ALLOCATED TO 'MyData' HAS BEEN SUCCESSFULLY FREED !!!\n\n");
	}

	return(0);
}


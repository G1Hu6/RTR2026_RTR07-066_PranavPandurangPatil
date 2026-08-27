#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int i;
	float f;
	double d;
} MyData;

int main(void)
{
	//function prototype
	void ModifyDataMembers(MyData *);

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

	pDataObj->i = 50;
	pDataObj->f = 20.5f;
	pDataObj->d = 4.5678;

	printf("\n\n");
	printf("DATA MEMBERS OF 'MyData' ARE : \n\n");
	printf("i = %d\n", pDataObj->i);
	printf("f = %f\n", pDataObj->f);
	printf("d = %lf\n", pDataObj->d);

	ModifyDataMembers(pDataObj);

	printf("\n\n");
	printf("DATA MEMBERS OF 'MyData' ARE : \n\n");
	printf("i = %d\n", pDataObj->i);
	printf("f = %f\n", pDataObj->f);
	printf("d = %lf\n", pDataObj->d);

	if (pDataObj)
	{
		free(pDataObj);
		pDataObj = NULL;
		printf("MEMORY ALLOCATED TO 'MyData' HAS BEEN SUCCESSFULLY FREED !!!\n\n");
	}

	return(0);
}

void ModifyDataMembers(MyData *pParamData)
{
	//code
	pParamData->i = 15;
	pParamData->f = 8.4f;
	pParamData->d = 2.71828;
}


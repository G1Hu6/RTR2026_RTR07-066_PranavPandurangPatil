#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int i;
	float f;
	double d;
} MyData;

int main(void)
{
	//variable declaraions
	int sz_i;
	int sz_f;
	int sz_d;
	int sz_struct;
	int sz_ptr;

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

	pDataObj->i = 42;
	pDataObj->f = 15.75f;
	pDataObj->d = 3.14159;

	printf("\n\n");
	printf("DATA MEMBERS OF 'MyData' ARE : \n\n");
	printf("i = %d\n", pDataObj->i);
	printf("f = %f\n", pDataObj->f);
	printf("d = %lf\n", pDataObj->d);

	sz_i = sizeof(pDataObj->i);
	sz_f = sizeof(pDataObj->f);
	sz_d = sizeof(pDataObj->d);

	printf("\n\n");
	printf("SIZES (in bytes) OF DATA MEMBERS OF 'MyData' ARE : \n\n");
	printf("Size of 'i' = %d bytes\n", sz_i);
	printf("Size of 'f' = %d bytes\n", sz_f);
	printf("Size of 'd' = %d bytes\n", sz_d);

	sz_struct = sizeof(MyData);
	sz_ptr = sizeof(MyData *);

	printf("\n\n");
	printf("Size of 'MyData' : %d bytes\n\n", sz_struct);
	printf("Size of pointer to 'MyData' : %d bytes\n\n", sz_ptr);

	if (pDataObj)
	{
		free(pDataObj);
		pDataObj = NULL;
		printf("MEMORY ALLOCATED TO 'MyData' HAS BEEN SUCCESSFULLY FREED !!!\n\n");
	}

	return(0);
}


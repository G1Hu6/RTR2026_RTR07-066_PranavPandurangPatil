#include <stdio.h>

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
	MyData dObj;

	//code
	dObj.i = 18;
	dObj.p_i = &dObj.i;

	dObj.f = 25.5f;
	dObj.p_f = &dObj.f;

	dObj.d = 6.28318;
	dObj.p_d = &dObj.d;

	printf("\n\n");
	printf("i = %d\n", *(dObj.p_i));
	printf("Address Of 'i' = %p\n", dObj.p_i);

	printf("\n\n");
	printf("f = %f\n", *(dObj.p_f));
	printf("Address Of 'f' = %p\n", dObj.p_f);

	printf("\n\n");
	printf("d = %lf\n", *(dObj.p_d));
	printf("Address Of 'd' = %p\n", dObj.p_d);

	return(0);
}


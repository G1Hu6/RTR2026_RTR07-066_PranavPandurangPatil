#include <stdio.h>

typedef struct
{
	int i;
	float f;
	double d;
} MyData;

MyData d;

int main(void)
{
	//variable declaraions
	int sz_i;
	int sz_f;
	int sz_d;
	int sz_struct;

	//code
	d.i = 25;
	d.f = 8.50f;
	d.d = 3.1415;

	printf("\n\n");
	printf("DATA MEMBERS OF 'MyData' ARE : \n\n");
	printf("i = %d\n", d.i);
	printf("f = %f\n", d.f);
	printf("d = %lf\n", d.d);

	sz_i = sizeof(d.i);
	sz_f = sizeof(d.f);
	sz_d = sizeof(d.d);

	printf("\n\n");
	printf("SIZES (in bytes) OF DATA MEMBERS OF 'MyData' ARE : \n\n");
	printf("Size of 'i' = %d bytes\n", sz_i);
	printf("Size of 'f' = %d bytes\n", sz_f);
	printf("Size of 'd' = %d bytes\n", sz_d);

	sz_struct = sizeof(MyData);

	printf("\n\n");
	printf("Size of 'MyData' : %d bytes\n\n", sz_struct);

	return(0);
}


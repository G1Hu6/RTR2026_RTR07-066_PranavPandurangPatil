#include <stdio.h>

int main(void)
{
	//variable declaraions
	typedef struct {
		int i;
		float f;
		double d;
		char c;
	} MyData;

	MyData d = { 10, 4.5f, 2.71828, 'P' };

	//code
	printf("\n\n");
	printf("DATA MEMBERS OF 'MyData' ARE : \n\n");
	printf("i = %d\n", d.i);
	printf("f = %f\n", d.f);
	printf("d = %lf\n", d.d);
	printf("c = %c\n\n", d.c);

	return(0);
}


#include <stdio.h>

typedef struct {
	int i;
	float f;
	double d;
	char c;
} MyData;

MyData d = { 15, 6.2f, 8.1234, 'P' };

int main(void)
{
	//code
	printf("\n\n");
	printf("DATA MEMBERS OF 'MyData' ARE : \n\n");
	printf("i = %d\n", d.i);
	printf("f = %f\n", d.f);
	printf("d = %lf\n", d.d);
	printf("c = %c\n\n", d.c);

	return(0);
}


#include <stdio.h>

typedef struct {
	int i;
	float f;
	double d;
	char c;
} MyData;

int main(void)
{
	//variable declaraions
	MyData d = { 24, 7.5f, 9.8765, 'R' };

	//code
	printf("\n\n");
	printf("DATA MEMBERS OF 'MyData' ARE : \n\n");
	printf("i = %d\n", d.i);
	printf("f = %f\n", d.f);
	printf("d = %lf\n", d.d);
	printf("c = %c\n\n", d.c);

	return(0);
}


#include <stdio.h>

typedef union {
	int i;
	float f;
	double d;
	char c;
} MyUnion;

int main(void)
{
	//variable declaraions
	MyUnion un1, un2;

	//code
	printf("\n\n");
	printf("Members Of Union un1 Are : \n\n");

	un1.i = 12;
	un1.f = 3.5f;
	un1.d = 9.87654;
	un1.c = 'R';

	printf("un1.i = %d\n", un1.i);
	printf("un1.f = %f\n", un1.f);
	printf("un1.d = %lf\n", un1.d);
	printf("un1.c = %c\n\n", un1.c);

	printf("Addresses Of Members Of Union un1 Are : \n\n");
	printf("un1.i = %p\n", &un1.i);
	printf("un1.f = %p\n", &un1.f);
	printf("un1.d = %p\n", &un1.d);
	printf("un1.c = %p\n\n", &un1.c);

	printf("MyUnion un1 = %p\n\n", &un1);

	printf("\n\n");
	printf("Members Of Union un2 Are : \n\n");

	un2.i = 8;
	printf("un2.i = %d\n\n", un2.i);

	un2.f = 6.4f;
	printf("un2.f = %f\n\n", un2.f);

	un2.d = 7.12345;
	printf("un2.d = %lf\n\n", un2.d);

	un2.c = 'P';
	printf("un2.c = %c\n\n", un2.c);

	printf("Addresses Of Members Of Union un2 Are : \n\n");
	printf("un2.i = %p\n", &un2.i);
	printf("un2.f = %p\n", &un2.f);
	printf("un2.d = %p\n", &un2.d);
	printf("un2.c = %p\n\n", &un2.c);

	printf("MyUnion un2 = %p\n\n", &un2);

	return(0);
}


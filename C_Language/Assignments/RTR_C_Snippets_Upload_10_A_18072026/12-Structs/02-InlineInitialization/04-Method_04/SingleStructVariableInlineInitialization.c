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
	MyData d1 = { 33, 4.9f, 5.23765, 'X' };
	MyData d2 = { 'D', 6.2f, 42.199523, 68 };
	MyData d3 = { 6, 'F' };
	MyData d4 = { 9 };

	//code
	printf("\n\n");
	printf("DATA MEMBERS OF 'MyData d1' ARE : \n\n");
	printf("i = %d\n", d1.i);
	printf("f = %f\n", d1.f);
	printf("d = %lf\n", d1.d);
	printf("c = %c\n\n", d1.c);

	printf("\n\n");
	printf("DATA MEMBERS OF 'MyData d2' ARE : \n\n");
	printf("i = %d\n", d2.i);
	printf("f = %f\n", d2.f);
	printf("d = %lf\n", d2.d);
	printf("c = %c\n\n", d2.c);

	printf("\n\n");
	printf("DATA MEMBERS OF 'MyData d3' ARE : \n\n");
	printf("i = %d\n", d3.i);
	printf("f = %f\n", d3.f);
	printf("d = %lf\n", d3.d);
	printf("c = %c\n\n", d3.c);

	printf("\n\n");
	printf("DATA MEMBERS OF 'MyData d4' ARE : \n\n");
	printf("i = %d\n", d4.i);
	printf("f = %f\n", d4.f);
	printf("d = %lf\n", d4.d);
	printf("c = %c\n\n", d4.c);

	return(0);
}


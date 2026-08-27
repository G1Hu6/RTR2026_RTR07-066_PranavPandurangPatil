#include <stdio.h>

typedef struct {
	int i;
	float f;
	double d;
	char c;
} MyStruct;

typedef union {
	int i;
	float f;
	double d;
	char c;
} MyUnion;

int main(void)
{
	//variable declaraions
	MyStruct st;
	MyUnion un;

	//code
	printf("\n\n");
	printf("Members Of Struct Are : \n\n");

	st.i = 15;
	st.f = 9.25f;
	st.d = 3.14159;
	st.c = 'K';

	printf("st.i = %d\n", st.i);
	printf("st.f = %f\n", st.f);
	printf("st.d = %lf\n", st.d);
	printf("st.c = %c\n\n", st.c);

	printf("Addresses Of Members Of Struct Are : \n\n");
	printf("st.i = %p\n", &st.i);
	printf("st.f = %p\n", &st.f);
	printf("st.d = %p\n", &st.d);
	printf("st.c = %p\n\n", &st.c);

	printf("MyStruct st = %p\n\n", &st);

	printf("\n\n");
	printf("Members Of Union Are : \n\n");

	un.i = 7;
	printf("un.i = %d\n\n", un.i);

	un.f = 5.8f;
	printf("un.f = %f\n\n", un.f);

	un.d = 4.9876;
	printf("un.d = %lf\n\n", un.d);

	un.c = 'M';
	printf("un.c = %c\n\n", un.c);

	printf("Addresses Of Members Of Union Are : \n\n");
	printf("un.i = %p\n", &un.i);
	printf("un.f = %p\n", &un.f);
	printf("un.d = %p\n", &un.d);
	printf("un.c = %p\n\n", &un.c);

	printf("MyUnion un = %p\n\n", &un);

	return(0);
}


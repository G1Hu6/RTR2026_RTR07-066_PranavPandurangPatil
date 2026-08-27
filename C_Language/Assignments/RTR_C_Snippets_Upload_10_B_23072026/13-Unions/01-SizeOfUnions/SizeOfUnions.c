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
	printf("Size Of MyStruct = %lu\n", sizeof(st));

	printf("\n\n");
	printf("Size Of MyUnion = %lu\n", sizeof(un));

	return(0);
}


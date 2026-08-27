#include <stdio.h>

int main(void)
{
	//variable declaraions
	float n;
	float* p = NULL;

	//code
	n = 7.5f;

	printf("\n\n");

	printf("BEFORE p = &n \n\n");
	printf("Value Of 'n' = %f\n", n);
	printf("Address Of 'n' = %p\n", &n);
	printf("Value At Address Of 'n' = %f\n", *(&n));

	p = &n;

	printf("\n\n");

	printf("AFTER p = &n \n\n");
	printf("Value Of 'n' = %f\n", n);
	printf("Address Of 'n' = %p\n", p);
	printf("Value At Address Of 'n' = %f\n", *p);

	return(0);
}


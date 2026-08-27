#include <stdio.h>

int main(void)
{
	//variable declaraions
	double n;
	double* p = NULL;

	//code
	n = 3.141592;

	printf("\n\n");

	printf("BEFORE p = &n \n\n");
	printf("Value Of 'n' = %lf\n", n);
	printf("Address Of 'n' = %p\n", &n);
	printf("Value At Address Of 'n' = %lf\n", *(&n));

	p = &n;

	printf("\n\n");

	printf("AFTER p = &n \n\n");
	printf("Value Of 'n' = %lf\n", n);
	printf("Address Of 'n' = %p\n", p);
	printf("Value At Address Of 'n' = %lf\n", *p);

	return(0);
}


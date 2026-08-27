#include <stdio.h>

int main(void)
{
	//variable declaraions
	int n;
	int *p = NULL;

	//code
	n = 25;

	printf("\n\n");

	printf("BEFORE p = &n \n\n");
	printf("Value Of 'n' = %d\n", n);
	printf("Address Of 'n' = %p\n", &n);
	printf("Value At Address Of 'n' = %d\n", *(&n));

	p = &n;

	printf("\n\n");

	printf("AFTER p = &n \n\n");
	printf("Value Of 'n' = %d\n", n);
	printf("Address Of 'n' = %p\n", p);
	printf("Value At Address Of 'n' = %d\n", *p);

	return(0);
}


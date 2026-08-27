#include <stdio.h>

int main(void)
{
	//variable declaraions
	int n;
	int *p = NULL;
	int **pp = NULL;

	//code
	n = 20;

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

	pp = &p;

	printf("\n\n");

	printf("AFTER pp = &p \n\n");
	printf("Value Of 'n' = %d\n", n);
	printf("Address Of 'n' (p) = %p\n", p);
	printf("Address Of 'p' (pp) = %p\n", pp);
	printf("Value At Address Of 'p' (*pp) = %p\n", *pp);
	printf("Value At Address Of 'n' (*p) (*pp) = %d\n\n", **pp);

	return(0);
}


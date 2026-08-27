#include <stdio.h>

int main(void)
{
	//variable declaraions
	int n;
	int *p1 = NULL;
	int *p2 = NULL;

	//code
	n = 15;
	p1 = &n;

	printf("\n\n");
	printf("BEFORE p2 = p1 \n\n");
	printf("n = %d\n", n);
	printf("&n = %p\n", &n);
	printf("*(&n) = %d\n", *(&n));
	printf("p1 = %p\n", p1);
	printf("*p1 = %d\n\n", *p1);

	p2 = p1;

	printf("\n\n");
	printf("AFTER p2 = p1 \n\n");
	printf("n = %d\n", n);
	printf("&n = %p\n", &n);
	printf("*(&n) = %d\n", *(&n));
	printf("p1 = %p\n", p1);
	printf("*p1 = %d\n", *p1);
	printf("p2 = %p\n", p2);
	printf("*p2 = %d\n\n", *p2);

	return(0);
}


#include <stdio.h>

int main(void)
{
	//variable declaraions
	int n = 12;
	int* const p = &n;

	//code
	printf("\n");
	printf("Current Value Of 'n' = %d\n", n);
	printf("Current 'p' (Address of 'n') = %p\n", p);

	n++;
	printf("\n\n");
	printf("After n++, value of 'n' = %d\n", n);

	// p++;

	(*p)++;

	printf("\n\n");
	printf("After (*p)++, value of 'p' = %p\n", p);
	printf("Value at this 'p' = %d\n\n", *p);

	return(0);
}


#include <stdio.h>

int main(void)
{
	//variable declaraions
	int n = 12;
	const int* p = NULL;

	//code
	p = &n;
	printf("\n");
	printf("Current Value Of 'n' = %d\n", n);
	printf("Current 'p' (Address of 'n') = %p\n", p);

	n++;
	printf("\n\n");
	printf("After n++, value of 'n' = %d\n", n);

	// (*p)++;

	p++;
	printf("\n\n");
	printf("After p++, value of 'p' = %p\n", p);
	printf("Value at this new 'p' = %d\n\n", *p);

	return(0);
}


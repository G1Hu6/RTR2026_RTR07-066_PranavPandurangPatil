#include <stdio.h>

int main(void)
{
	//variable declaraions
	int n = 12;
	const int* const p = &n;

	//code
	printf("\n");
	printf("Current Value Of 'n' = %d\n", n);
	printf("Current 'p' (Address of 'n') = %p\n", p);

	n++;
	printf("\n\n");
	printf("After n++, value of 'n' = %d\n", n);

	// p++;
	// (*p)++;

	return(0);
}


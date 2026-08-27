#include <stdio.h>

int main(void)
{
	//variable declaraions
	int n;
	int *p = NULL;
	int res;

	//code
	n = 12;
	p = &n;

	printf("\n\n");
	printf("n = %d\n", n);
	printf("&n = %p\n", &n);
	printf("*(&n) = %d\n", *(&n));
	printf("p = %p\n", p);
	printf("*p = %d\n", *p);

	printf("\n\n");
	printf("Answer Of (p + 10) = %p\n", (p + 10));
	printf("Answer Of *(p + 10) = %d\n", *(p + 10));
	printf("Answer Of (*p + 10) = %d\n\n", (*p + 10));

	++*p;
	printf("Answer Of ++*p : %d\n", *p);

	*p++;
	printf("Answer Of *p++ : %d\n", *p);

	p = &n;
	(*p)++;
	printf("Answer Of (*p)++ : %d\n\n", *p);

	return(0);
}


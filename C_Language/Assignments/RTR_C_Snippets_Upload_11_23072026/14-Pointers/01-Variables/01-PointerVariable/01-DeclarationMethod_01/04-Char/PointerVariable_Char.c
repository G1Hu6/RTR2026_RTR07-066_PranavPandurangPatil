#include <stdio.h>

int main(void)
{
	//variable declaraions
	char c;
	char *p = NULL;

	//code
	c = 'P';

	printf("\n\n");

	printf("BEFORE p = &c \n\n");
	printf("Value Of 'c' = %c\n", c);
	printf("Address Of 'c' = %p\n", &c);
	printf("Value At Address Of 'c' = %c\n", *(&c));

	p = &c;

	printf("\n\n");

	printf("AFTER p = &c \n\n");
	printf("Value Of 'c' = %c\n", c);
	printf("Address Of 'c' = %p\n", p);
	printf("Value At Address Of 'c' = %c\n", *p);

	return(0);
}


#include<stdio.h>

int main(void)
{
	// variable declarations
	int a, b;
	int m, n;
	char ch_res1, ch_res2;
	int i_res1, i_res2;

	// code
	printf("\n\n");

	a = 7;
	b = 5;
	ch_res1 = (a > b) ? 'A' : 'B';
	i_res1 = (a > b) ? a : b;
	printf("Ternary Operator Answer 1 ----- %c and %d.\n\n", ch_res1, i_res1);

	m = 20;
	n = 20;
	ch_res2 = (m != n) ? 'M' : 'N';
	i_res2 = (m != n) ? m : n;
	printf("Ternary Operator Answer 2 ----- %c and %d.\n\n", ch_res2, i_res2);

	printf("\n\n");
	return(0);
}

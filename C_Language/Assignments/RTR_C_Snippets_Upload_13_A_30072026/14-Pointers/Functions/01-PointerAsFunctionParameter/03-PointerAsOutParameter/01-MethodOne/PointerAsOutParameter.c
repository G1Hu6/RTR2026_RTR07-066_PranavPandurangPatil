#include <stdio.h>

int main(void)
{
	//function declarations
	void PerformMathOps(int, int, int *, int *, int *, int *, int *);

	//variable declaraions
	int num1;
	int num2;
	int sum_ans;
	int diff_ans;
	int prod_ans;
	int quot_ans;
	int rem_ans;

	//code
	printf("\n\n");
	printf("Enter Value For 'num1' : ");
	scanf("%d", &num1);

	printf("\n\n");
	printf("Enter Value For 'num2' : ");
	scanf("%d", &num2);

	PerformMathOps(num1, num2, &sum_ans, &diff_ans, &prod_ans, &quot_ans, &rem_ans);

	printf("\n\n");
	printf("RESULTS : \n\n");
	printf("Sum = %d\n\n", sum_ans);
	printf("Difference = %d\n\n", diff_ans);
	printf("Product = %d\n\n", prod_ans);
	printf("Quotient = %d\n\n", quot_ans);
	printf("Remainder = %d\n\n", rem_ans);

	return(0);
}

void PerformMathOps(int val1, int val2, int *s_ptr, int *d_ptr, int *p_ptr, int *q_ptr, int *r_ptr)
{
	//code
	*s_ptr = val1 + val2;
	*d_ptr = val1 - val2;
	*p_ptr = val1 * val2;
	*q_ptr = val1 / val2;
	*r_ptr = val1 % val2;
}


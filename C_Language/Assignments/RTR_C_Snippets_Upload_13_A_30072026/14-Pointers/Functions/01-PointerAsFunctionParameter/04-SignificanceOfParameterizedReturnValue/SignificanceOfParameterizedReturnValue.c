#include <stdio.h>

enum {
	NEGATIVE = -1,
	ZERO,
	POSITIVE
};

int main(void)
{
	//function declarations
	int SubtractAndCheck(int, int, int *);

	//variable declaraions
	int num1;
	int num2;
	int ans;
	int status;

	//code
	printf("\n\n");
	printf("Enter Value For 'num1' : ");
	scanf("%d", &num1);

	printf("\n\n");
	printf("Enter Value For 'num2' : ");
	scanf("%d", &num2);

	status = SubtractAndCheck(num1, num2, &ans);

	printf("\n\n");
	printf("Difference Of %d And %d = %d\n\n", num1, num2, ans);

	if (status == POSITIVE)
		printf("The Difference Of %d And %d Is Positive !!!\n\n", num1, num2);
	else if (status == NEGATIVE)
		printf("The Difference Of %d And %d Is Negative !!!\n\n", num1, num2);
	else
		printf("The Difference Of %d And %d Is Zero !!!\n\n", num1, num2);

	return(0);
}

int SubtractAndCheck(int val1, int val2, int *d_out)
{
	//code
	*d_out = val1 - val2;

	if (*d_out > 0)
		return(POSITIVE);
	else if (*d_out < 0)
		return(NEGATIVE);
	else
		return(ZERO);
}


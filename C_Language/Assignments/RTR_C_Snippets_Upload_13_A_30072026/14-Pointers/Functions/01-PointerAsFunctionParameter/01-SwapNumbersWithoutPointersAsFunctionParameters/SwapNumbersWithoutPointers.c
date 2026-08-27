#include <stdio.h>

int main(void)
{
	//function declarations
	void SwapValues(int, int);

	//variable declaraions
	int num1;
	int num2;

	//code
	printf("\n\n");
	printf("Enter Value For 'num1' : ");
	scanf("%d", &num1);

	printf("\n\n");
	printf("Enter Value For 'num2' : ");
	scanf("%d", &num2);

	printf("\n\n");
	printf("BEFORE SWAPPING \n\n");
	printf("Value Of 'num1' = %d\n", num1);
	printf("Value Of 'num2' = %d\n", num2);

	SwapValues(num1, num2);

	printf("\n\n");
	printf("AFTER SWAPPING \n\n");
	printf("Value Of 'num1' = %d\n", num1);
	printf("Value Of 'num2' = %d\n", num2);

	return(0);
}

void SwapValues(int val1, int val2)
{
	//variable declaraions
	int t;

	//code
	printf("\n\n");
	printf("BEFORE SWAPPING \n\n");
	printf("Value Of 'val1' = %d\n", val1);
	printf("Value Of 'val2' = %d\n", val2);

	t = val1;
	val1 = val2;
	val2 = t;

	printf("\n\n");
	printf("AFTER SWAPPING \n\n");
	printf("Value Of 'val1' = %d\n", val1);
	printf("Value Of 'val2' = %d\n", val2);
}


#include <stdio.h>

int main(void)
{
	//function declarations
	void SwapValues(int *, int *);

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

	SwapValues(&num1, &num2);

	printf("\n\n");
	printf("AFTER SWAPPING \n\n");
	printf("Value Of 'num1' = %d\n", num1);
	printf("Value Of 'num2' = %d\n", num2);

	return(0);
}

void SwapValues(int *p1, int *p2)
{
	//variable declaraions
	int t;

	//code
	printf("\n\n");
	printf("BEFORE SWAPPING \n\n");
	printf("Value Of '*p1' = %d\n", *p1);
	printf("Value Of '*p2' = %d\n", *p2);

	t = *p1;
	*p1 = *p2;
	*p2 = t;

	printf("\n\n");
	printf("AFTER SWAPPING \n\n");
	printf("Value Of '*p1' = %d\n", *p1);
	printf("Value Of '*p2' = %d\n", *p2);
}


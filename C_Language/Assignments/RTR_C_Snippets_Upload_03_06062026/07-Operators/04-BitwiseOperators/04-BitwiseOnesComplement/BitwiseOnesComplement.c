#include<stdio.h>

int main(void)
{
	// function prototypes
	void PrintBinaryFormOfNumbers(unsigned int);

	// variable declarations
	unsigned int a;
	unsigned int result;

	// code
	printf("\n\n");
	printf("Enter An Integer = ");
	scanf("%u", &a);

	printf("\n\n\n\n");
	result = ~a;
	printf("Bitwise COMPLEMENT-ing Of \nA = %d (Decimal) gives result %d (Decimal). \n\n", a, result);

	PrintBinaryFormOfNumbers(a);
	PrintBinaryFormOfNumbers(result);

	return(0);
}

void PrintBinaryFormOfNumbers(unsigned int decimal_number)
{
	// variable declarations
	unsigned int quo, rem;
	unsigned int num;
	unsigned int binary_array[8];
	int i;

	// code
	for(i = 0; i < 8; i++)
	{
		binary_array[i] = 0;
	}

	printf("The Binary Form Of The Decimal Integer %d Is\t=\t", decimal_number);
	num = decimal_number;
	i = 7;
	while(num != 0)
	{
		quo = num / 2;
		rem = num % 2;
		binary_array[i] = rem;
		num = quo;
		i--;
	}

	for(i = 0; i < 8; i++)
	{
		printf("%u", binary_array[i]);
	}

	printf("\n\n");
}

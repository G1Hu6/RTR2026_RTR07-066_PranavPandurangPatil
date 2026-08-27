#include <stdio.h>

int main(void)
{
	//function declarations
	int SumInts(int, int);
	int SubInts(int, int);
	float SumFloats(float, float);

	//variable declaraions
	typedef int (*SumIntsFnPtr)(int, int);
	SumIntsFnPtr pSubInts = NULL;
	SumIntsFnPtr pSumInts = NULL;

	typedef float (*SumFloatsFnPtr)(float, float);
	SumFloatsFnPtr pSumFloats = NULL;

	int ansInt = 0;
	float ansFloat = 0.0f;

	//code
	pSumInts = SumInts;
	ansInt = pSumInts(15, 45);
	printf("\n\n");
	printf("Sum Of Integers = %d\n\n", ansInt);

	pSubInts = SubInts;
	ansInt = pSubInts(45, 15);
	printf("\n\n");
	printf("Subtraction Of Integers = %d\n\n", ansInt);

	pSumFloats = SumFloats;
	ansFloat = pSumFloats(22.5f, 9.4f);
	printf("\n\n");
	printf("Sum Of Floating-Point Numbers = %f\n\n", ansFloat);

	return(0);
}

int SumInts(int a, int b)
{
	//variable declaraions
	int c;

	//code
	c = a + b;
	return(c);
}

int SubInts(int a, int b)
{
	//variable declaraions
	int c;

	//code
	if (a > b)
		c = a - b;
	else
		c = b - a;

	return(c);
}

float SumFloats(float f1, float f2)
{
	//variable declaraions
	float ans;

	//code
	ans = f1 + f2;
	return(ans);
}


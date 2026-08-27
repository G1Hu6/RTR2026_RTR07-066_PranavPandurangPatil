#include <stdio.h>
#include <stdarg.h>

#define NUM_TO_BE_FOUND 5
#define NUM_ELEMENTS 8

int main(void)
{
	//function prototypes
	void SearchNumber(int, int, ...);

	//code
	printf("\n\n");
	SearchNumber(NUM_TO_BE_FOUND, NUM_ELEMENTS, 5, 8, 5, 2, 5, 6, 5, 1);

	return(0);
}

void SearchNumber(int targetNum, int num, ...)
{
	//function prototypes
	int va_SearchNumber(int, int, va_list);

	//variable declaraions
	int matchCount = 0;
	va_list argList;

	//code
	va_start(argList, num);
	matchCount = va_SearchNumber(targetNum, num, argList);

	if (matchCount == 0)
		printf("Number %d Could Not Be Found !!!\n\n", targetNum);
	else
		printf("Number %d Found %d Times !!!\n\n", targetNum, matchCount);

	va_end(argList);
}

int va_SearchNumber(int targetNum, int num, va_list argList)
{
	//variable declaraions
	int cnt = 0;
	int val;

	//code
	while (num)
	{
		val = va_arg(argList, int);
		if (val == targetNum)
			cnt++;
		num--;
	}

	return(cnt);
}


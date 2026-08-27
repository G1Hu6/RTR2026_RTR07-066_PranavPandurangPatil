#include <stdio.h>
#include <stdarg.h>

int main(void)
{
	//function prototypes
	int FindSumTotal(int, ...);

	//variable declaraions
	int ans;

	//code
	printf("\n\n");

	ans = FindSumTotal(5, 12, 24, 36, 48, 60);
	printf("Answer = %d\n\n", ans);

	ans = FindSumTotal(8, 2, 2, 2, 2, 2, 2, 2, 2);
	printf("Answer = %d\n\n", ans);

	ans = FindSumTotal(0);
	printf("Answer = %d\n\n", ans);

	return(0);
}

int FindSumTotal(int num, ...)
{
	//variable declaraions
	int total = 0;
	int num_val;
	va_list argList;

	//code
	va_start(argList, num);

	while (num)
	{
		num_val = va_arg(argList, int);
		total = total + num_val;
		num--;
	}

	va_end(argList);
	return(total);
}


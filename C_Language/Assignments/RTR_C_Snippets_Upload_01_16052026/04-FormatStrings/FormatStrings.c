#include<stdio.h>
#define D_PI 3.14159265358979323846


int main(void)
{
	// code
	printf("\n\n");
	printf("******************************************************************************************************************************************************");
	printf("\n\n");

	printf("Hello RTR !!! \n\n");

	int a = 18;
	printf("Integer Decimal Value Of 'b' = %d\n", a);
	printf("Integer Octal Value Of 'b' = %o\n", a);
	printf("Integer Hexadecimal Value Of 'b' ( Hexadecimal Letters In lower Case )= %x\n", a);
	printf("Integer Hexadecimal Value Of 'b' ( Hexadecimal Letters In UPPER Case )= %X\n\n", a);
	

	char ch = 'P';
	printf("Character ch = %c\n", ch);
	char str[] = "AstroMediComp's RTR Batch";
	printf("String str = %s\n\n", str);

	long num = 23231134L;
	printf("Long Integer = %ld\n\n", num);

	unsigned int d = 2;
	printf("Unsigned Integer 'd' = %u\n\n", d);

	float f_num = 5656.1212f;
	printf("Floating Point Number With Just %%f 'f_num' = %f\n", f_num);
	printf("Floating Point Number With Just %%4.1f 'f_num' = %4.1f\n", f_num);
	printf("Floating Point Number With Just %%5.4f 'f_num' = %5.4f\n\n", f_num);

	printf("Double Precision Floating Point Number Without Exponential = %g\n", D_PI);
	printf("Double Precision Floating Point Number Without Exponential (lower case) = %e\n", D_PI);
	printf("Double Precision Floating Point Number Without Exponential (UPPER CASE)= %E\n\n", D_PI);
	printf("Double Hexadecimal Value of 'D_PI' (Hexadecimal letters in lower case)= %a\n", D_PI);
	printf("Double Hexadecimal Value of 'D_PI' (Hexadecimal letters in UPPER CASE)= %A\n", D_PI);
	
	printf("******************************************************************************************************************************************************");
	printf("\n\n");
	return(0);
}

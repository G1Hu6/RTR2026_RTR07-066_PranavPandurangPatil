#include<stdio.h>

int main(void)
{
	// variable declarations
	int i, j;
	char ch1, ch2;

	int a, res_int;
	float f, res_float;

	int i_exp;
	float f_exp;

	// code
	printf("\n\n");

	// INTERCONVERSION AND IMPLICIT TYPE-CASTING BETWEEN char AND int TYPES....
	i = 80;
	ch1 = i;
	printf("I = %d\n", i);
	printf("Char 1 (after ch1 = i) = %c\n\n", ch1);

	ch2 = 'W';
	j = ch2;
	printf("Character 2 = %c\n", ch2);
	printf("J (after j = ch2) = %d\n\n", j);

	// IMPLICIT CONVERSION OF int TO float....
	a = 5;
	f = 3.4f;
	res_float = a + f;
	printf("Integer a = %d And Floating-Point Number %f Added Gives Floating-Point Sum = %f\n\n", a, f, res_float);
	
	res_int = a + f;
	printf("Integer a = %d And Floating-Point Number %f Added Gives Floating-Point Sum = %f\n\n", a, f, res_int);

	// EXPLICIT TYPE-CASTING USING CAST OPERATOR....
	f_exp = 40.344343f;
	i_exp = (int)f_exp;
	printf("Floating Point Number Which Will Be Type Casted Explicitly = %f\n", f_exp);
	printf("Resultant Integer After Explicit Type Casting Of %f = %d\n\n", f_exp, i_exp);

	return(0);

}

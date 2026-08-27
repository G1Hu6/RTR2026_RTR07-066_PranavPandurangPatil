#include<stdio.h>

int main(void)
{
	// variable declarations
	int p;
	int q;
	int ans;

	// code
	printf("\n\n");
	printf("Enter A Number : ");
	scanf("%d", &p);
	
	printf("\n\n");
	printf("Enter Another Number : ");
	scanf("%d", &q);

	printf("\n\n");
	
	/*
	 * The Following Are The 5 Arithmatic Operators +, -, *, / and %
	 * Also, The Resltants Of The Arithmatic Operators In All The Below
	 * Five Cases Have Been Asiggned To The Variable 'ans' Using the Assignment Operator (=)
	 */

	ans = p + q;
	printf("%d + %d = %d\n", p, q, ans);
	
	ans = p - q;
	printf("%d - %d = %d\n", p, q, ans);
	
	ans = p * q;
	printf("%d * %d = %d\n", p, q, ans);
	
	ans = p / q;
	printf("%d / %d = %d\n", p, q, ans);
	
	ans = p % q;
	printf("%d % %d = %d\n\n", p, q, ans);

	return (0);
}

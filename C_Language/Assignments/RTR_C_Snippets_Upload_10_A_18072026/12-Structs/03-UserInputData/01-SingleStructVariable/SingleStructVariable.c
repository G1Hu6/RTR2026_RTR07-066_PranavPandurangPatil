#include <stdio.h>
#include <conio.h>

typedef struct {
	int i;
	float f;
	double d;
	char c;
} MyData;

int main(void)
{
	//variable declaraions
	MyData d;

	//code
	printf("\n\n");
	printf("Enter Integer Value For Data Member 'i' Of 'MyData' : \n");
	scanf("%d", &d.i);

	printf("Enter Floating-Point Value For Data Member 'f' Of 'MyData' : \n");
	scanf("%f", &d.f);

	printf("Enter 'Double' Value For Data Member 'd' Of 'MyData' : \n");
	scanf("%lf", &d.d);

	printf("Enter Character Value For Data Member 'c' Of 'MyData' : \n");
	d.c = getch();

	printf("\n\n");
	printf("DATA MEMBERS OF 'MyData' ARE : \n\n");
	printf("i = %d\n", d.i);
	printf("f = %f\n", d.f);
	printf("d = %lf\n", d.d);
	printf("c = %c\n\n", d.c);

	return(0);
}


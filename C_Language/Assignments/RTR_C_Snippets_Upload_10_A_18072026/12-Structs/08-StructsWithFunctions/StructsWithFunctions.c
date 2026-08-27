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
	//function prototype
	MyData AddStructMembers(MyData, MyData, MyData);

	//variable declaraions
	MyData d1, d2, d3, ans;

	//code
	printf("\n\n");
	printf("DATA 1 \n");
	printf("Enter Integer Value For 'i' Of 'MyData d1' : ");
	scanf("%d", &d1.i);

	printf("\n\n");
	printf("Enter Floating-Point Value For 'f' Of 'MyData d1' : ");
	scanf("%f", &d1.f);

	printf("\n\n");
	printf("Enter 'Double' Value For 'd' Of 'MyData d1' : ");
	scanf("%lf", &d1.d);

	printf("\n\n");
	printf("Enter Character Value For 'c' Of 'MyData d1' : ");
	d1.c = getch();
	printf("%c", d1.c);

	printf("\n\n");
	printf("DATA 2 \n");
	printf("Enter Integer Value For 'i' Of 'MyData d2' : ");
	scanf("%d", &d2.i);

	printf("\n\n");
	printf("Enter Floating-Point Value For 'f' Of 'MyData d2' : ");
	scanf("%f", &d2.f);

	printf("\n\n");
	printf("Enter 'Double' Value For 'd' Of 'MyData d2' : ");
	scanf("%lf", &d2.d);

	printf("\n\n");
	printf("Enter Character Value For 'c' Of 'MyData d2' : ");
	d2.c = getch();
	printf("%c", d2.c);

	printf("\n\n");
	printf("DATA 3 \n");
	printf("Enter Integer Value For 'i' Of 'MyData d3' : ");
	scanf("%d", &d3.i);

	printf("\n\n");
	printf("Enter Floating-Point Value For 'f' Of 'MyData d3' : ");
	scanf("%f", &d3.f);

	printf("\n\n");
	printf("Enter 'Double' Value For 'd' Of 'MyData d3' : ");
	scanf("%lf", &d3.d);

	printf("\n\n");
	printf("Enter Character Value For 'c' Of 'MyData d3' : ");
	d3.c = getch();
	printf("%c", d3.c);

	ans = AddStructMembers(d1, d2, d3);

	printf("\n\n");
	printf("ANSWER \n");
	printf("ans.i = %d\n", ans.i);
	printf("ans.f = %f\n", ans.f);
	printf("ans.d = %lf\n\n", ans.d);

	ans.c = d1.c;
	printf("ans.c (from d1) = %c\n\n", ans.c);

	ans.c = d2.c;
	printf("ans.c (from d2) = %c\n\n", ans.c);

	ans.c = d3.c;
	printf("ans.c (from d3) = %c\n\n", ans.c);

	return(0);
}

MyData AddStructMembers(MyData m1, MyData m2, MyData m3)
{
	//variable declaraions
	MyData res;

	//code
	res.i = m1.i + m2.i + m3.i;
	res.f = m1.f + m2.f + m3.f;
	res.d = m1.d + m2.d + m3.d;

	return(res);
}


#include <stdio.h>

#define MAX_NAME_LENGTH 100

typedef struct {
	char name[MAX_NAME_LENGTH];
	unsigned int age;
	char gender;
	double salary;
} Employee;

typedef struct {
	int i;
	float f;
	double d;
	char c;
} MyData;

int main(void)
{
	//Typedefs
	typedef Employee MY_EMPLOYEE_TYPE;
	typedef MyData MY_DATA_TYPE;

	//variable declaraions
	Employee emp1 = { "Pranav", 25, 'M', 50000.00 };
	MY_EMPLOYEE_TYPE emp2 = { "Raj", 28, 'M', 60000.00 };

	MyData d1 = { 30, 11.45f, 26.122017, 'X' };
	MY_DATA_TYPE d2;

	//code
	d2.i = 9;
	d2.f = 1.5f;
	d2.d = 8.041997;
	d2.c = 'P';

	printf("\n\n");
	printf("struct Employee : \n\n");
	printf("emp1.name = %s\n", emp1.name);
	printf("emp1.age = %d\n", emp1.age);
	printf("emp1.gender = %c\n", emp1.gender);
	printf("emp1.salary = %lf\n", emp1.salary);

	printf("\n\n");
	printf("MY_EMPLOYEE_TYPE : \n\n");
	printf("emp2.name = %s\n", emp2.name);
	printf("emp2.age = %d\n", emp2.age);
	printf("emp2.gender = %c\n", emp2.gender);
	printf("emp2.salary = %lf\n", emp2.salary);

	printf("\n\n");
	printf("struct MyData : \n\n");
	printf("d1.i = %d\n", d1.i);
	printf("d1.f = %f\n", d1.f);
	printf("d1.d = %lf\n", d1.d);
	printf("d1.c = %c\n", d1.c);

	printf("\n\n");
	printf("MY_DATA_TYPE : \n\n");
	printf("d2.i = %d\n", d2.i);
	printf("d2.f = %f\n", d2.f);
	printf("d2.d = %lf\n", d2.d);
	printf("d2.c = %c\n", d2.c);

	printf("\n\n");

	return(0);
}


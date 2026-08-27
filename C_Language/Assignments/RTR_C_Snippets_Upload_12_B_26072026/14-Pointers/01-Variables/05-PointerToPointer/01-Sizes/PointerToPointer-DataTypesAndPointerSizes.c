#include <stdio.h>

typedef struct {
	char name[80];
	int age;
	float salary;
	char sex;
	char mStatus;
} Employee;

int main(void)
{
	//code
	printf("\n\n");
	printf("SIZES OF DATA TYPES AND POINTERS TO THOSE RESPECTIVE DATA TYPES ARE : \n\n");

	printf("Size of (int) : %d \t \t Size of pointer to int (int*) : %d \t \t Size of pointer to pointer to int (int**) : %d\n\n", sizeof(int), sizeof(int*), sizeof(int**));
	printf("Size of (float) : %d \t \t Size of pointer to float (float*) : %d \t \t Size of pointer to pointer to float (float**) : %d\n\n", sizeof(float), sizeof(float*), sizeof(float**));
	printf("Size of (double) : %d \t \t Size of pointer to double (double*) : %d \t \t Size of pointer to pointer to double (double**) : %d\n\n", sizeof(double), sizeof(double*), sizeof(double**));
	printf("Size of (char) : %d \t \t Size of pointer to char (char*) : %d \t \t Size of pointer to pointer to char (char**) : %d\n\n", sizeof(char), sizeof(char*), sizeof(char**));
	printf("Size of (Employee) : %d \t \t Size of pointer to Employee (Employee*) : %d \t \t Size of pointer to pointer to Employee (Employee**) : %d\n\n", sizeof(Employee), sizeof(Employee*), sizeof(Employee**));

	return(0);
}


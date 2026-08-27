#include <stdio.h>
#include <string.h>

#define NAME_LEN 100
#define STATUS_LEN 10

typedef struct {
	char name[NAME_LEN];
	int age;
	float salary;
	char sex;
	char mStatus[STATUS_LEN];
} Employee;

int main(void)
{
	//variable declaraions
	Employee empRec[4];

	char emp1[] = "Pranav";
	char emp2[] = "Raj";
	char emp3[] = "Mayank";
	char emp4[] = "Tanmay";

	int i;

	//code
	strcpy(empRec[0].name, emp1);
	empRec[0].age = 25;
	empRec[0].sex = 'M';
	empRec[0].salary = 50000.0f;
	strcpy(empRec[0].mStatus, "Unmarried");

	strcpy(empRec[1].name, emp2);
	empRec[1].age = 28;
	empRec[1].sex = 'M';
	empRec[1].salary = 60000.0f;
	strcpy(empRec[1].mStatus, "Married");

	strcpy(empRec[2].name, emp3);
	empRec[2].age = 26;
	empRec[2].sex = 'M';
	empRec[2].salary = 55000.0f;
	strcpy(empRec[2].mStatus, "Unmarried");

	strcpy(empRec[3].name, emp4);
	empRec[3].age = 27;
	empRec[3].sex = 'M';
	empRec[3].salary = 58000.0f;
	strcpy(empRec[3].mStatus, "Married");

	printf("\n\n");
	printf("DISPLAYING EMPLOYEE RECORDS \n\n");
	for (i = 0; i < 4; i++)
	{
		printf("EMPLOYEE NUMBER %d \n", (i + 1));
		printf("Name : %s\n", empRec[i].name);
		printf("Age : %d years\n", empRec[i].age);

		if (empRec[i].sex == 'M' || empRec[i].sex == 'm')
			printf("Sex : Male\n");
		else
			printf("Sex : Female\n");

		printf("Salary : Rs. %f\n", empRec[i].salary);
		printf("Marital Status : %s\n", empRec[i].mStatus);

		printf("\n\n");
	}

	return(0);
}


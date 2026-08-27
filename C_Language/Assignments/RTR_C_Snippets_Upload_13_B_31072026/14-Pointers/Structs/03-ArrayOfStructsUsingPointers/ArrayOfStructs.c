#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>

#define NAME_LENGTH 100
#define MARITAL_STATUS 10

typedef struct {
	char name[NAME_LENGTH];
	int age;
	char sex;
	float salary;
	char marital_status;
} Employee;

int main(void)
{
	//function prototype
	void ReadCustomString(char[], int);

	//variable declaraions
	Employee *pEmpRecords = NULL;
	int nEmp, i;

	//code
	printf("\n\n");
	printf("Enter Number Of Employees Whose Details You Want To Record : ");
	scanf("%d", &nEmp);

	printf("\n\n");
	pEmpRecords = (Employee *)malloc(sizeof(Employee) * nEmp);
	if (pEmpRecords == NULL)
	{
		printf("FAILED TO ALLOCATE MEMORY FOR %d EMPLOYEES !!! EXITTING NOW ...\n\n", nEmp);
		exit(0);
	}
	else
	{
		printf("SUCCESSFULLY ALLOCATED MEMORY FOR %d EMPLOYEES !!!\n\n", nEmp);
	}

	for (i = 0; i < nEmp; i++)
	{
		printf("\n\n\n");
		printf("DATA ENTRY FOR EMPLOYEE NUMBER %d \n", (i + 1));

		printf("\n\n");
		printf("Enter Employee Name : ");
		ReadCustomString(pEmpRecords[i].name, NAME_LENGTH);

		printf("\n\n");
		printf("Enter Employee's Age (in years) : ");
		scanf("%d", &pEmpRecords[i].age);

		printf("\n\n");
		printf("Enter Employee's Sex (M/m For Male, F/f For Female) : ");
		pEmpRecords[i].sex = getch();
		printf("%c", pEmpRecords[i].sex);
		pEmpRecords[i].sex = toupper(pEmpRecords[i].sex);

		printf("\n\n");
		printf("Enter Employee's Salary (in Indian Rupees) : ");
		scanf("%f", &pEmpRecords[i].salary);

		printf("\n\n");
		printf("Is The Employee Married? (Y/y For Yes, N/n For No) : ");
		pEmpRecords[i].marital_status = getch();
		printf("%c", pEmpRecords[i].marital_status);
		pEmpRecords[i].marital_status = toupper(pEmpRecords[i].marital_status);
	}

	printf("\n\n\n");
	printf("DISPLAYING EMPLOYEE RECORDS \n");
	for (i = 0; i < nEmp; i++)
	{
		printf("EMPLOYEE NUMBER %d \n", (i + 1));
		printf("Name : %s\n", pEmpRecords[i].name);
		printf("Age : %d years\n", pEmpRecords[i].age);

		if (pEmpRecords[i].sex == 'M')
			printf("Sex : Male\n");
		else if (pEmpRecords[i].sex == 'F')
			printf("Sex : Female\n");
		else
			printf("Sex : Invalid Data Entered\n");

		printf("Salary : Rs. %f\n", pEmpRecords[i].salary);

		if (pEmpRecords[i].marital_status == 'Y')
			printf("Marital Status : Married\n");
		else if (pEmpRecords[i].marital_status == 'N')
			printf("Marital Status : Unmarried\n");
		else
			printf("Marital Status : Invalid Data Entered\n");

		printf("\n\n");
	}

	if (pEmpRecords)
	{
		free(pEmpRecords);
		pEmpRecords = NULL;
		printf("MEMORY ALLOCATED TO %d EMPLOYEES HAS BEEN SUCCESSFULLY FREED !!!\n\n", nEmp);
	}

	return(0);
}

void ReadCustomString(char str[], int str_size)
{
	//variable declaraions
	int i;
	char ch = '\0';

	//code
	i = 0;
	do
	{
		ch = getch();
		str[i] = ch;
		printf("%c", str[i]);
		i++;
	} while ((ch != '\r') && (i < str_size));

	if (i == str_size)
		str[i - 1] = '\0';
	else
		str[i] = '\0';
}


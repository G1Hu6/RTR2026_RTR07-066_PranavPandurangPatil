#include <stdio.h>
#include <ctype.h>
#include <conio.h>

#define NUM_EMP 5
#define NAME_LEN 100
#define STATUS_LEN 10

typedef struct {
	char name[NAME_LEN];
	int age;
	char sex;
	float salary;
	char mStatus;
} Employee;

int main(void)
{
	//function prototype
	void MyGetString(char[], int);

	//variable declaraions
	Employee empRec[NUM_EMP];
	int i;

	//code
	for (i = 0; i < NUM_EMP; i++)
	{
		printf("\n\n");
		printf("DATA ENTRY FOR EMPLOYEE NUMBER %d \n", (i + 1));

		printf("\n\n");
		printf("Enter Employee Name : ");
		MyGetString(empRec[i].name, NAME_LEN);

		printf("\n\n");
		printf("Enter Employee's Age (in years) : ");
		scanf("%d", &empRec[i].age);

		printf("\n\n");
		printf("Enter Employee's Sex (M/m For Male, F/f For Female) : ");
		empRec[i].sex = getch();
		printf("%c", empRec[i].sex);
		empRec[i].sex = toupper(empRec[i].sex);

		printf("\n\n");
		printf("Enter Employee's Salary (in Indian Rupees) : ");
		scanf("%f", &empRec[i].salary);

		printf("\n\n");
		printf("Is The Employee Married? (Y/y For Yes, N/n For No) : ");
		empRec[i].mStatus = getch();
		printf("%c", empRec[i].mStatus);
		empRec[i].mStatus = toupper(empRec[i].mStatus);
	}

	printf("\n\n");
	printf("DISPLAYING EMPLOYEE RECORDS \n\n");
	for (i = 0; i < NUM_EMP; i++)
	{
		printf("EMPLOYEE NUMBER %d \n", (i + 1));
		printf("Name : %s\n", empRec[i].name);
		printf("Age : %d years\n", empRec[i].age);

		if (empRec[i].sex == 'M')
			printf("Sex : Male\n");
		else if (empRec[i].sex == 'F')
			printf("Sex : Female\n");
		else
			printf("Sex : Invalid Data Entered\n");

		printf("Salary : Rs. %f\n", empRec[i].salary);

		if (empRec[i].mStatus == 'Y')
			printf("Marital Status : Married\n");
		else if (empRec[i].mStatus == 'N')
			printf("Marital Status : Unmarried\n");
		else
			printf("Marital Status : Invalid Data Entered\n");

		printf("\n\n");
	}

	return(0);
}

void MyGetString(char str[], int str_size)
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


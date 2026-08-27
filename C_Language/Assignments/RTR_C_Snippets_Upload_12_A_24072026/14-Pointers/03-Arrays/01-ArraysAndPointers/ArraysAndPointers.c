#include <stdio.h>

int main(void)
{
	//variable declaraions
	int iArr[] = { 10, 20, 30, 40, 50 };
	float fArr[] = { 1.5f, 2.5f, 3.5f };
	double dArr[] = { 1.11, 2.22, 3.33 };
	char cArr[] = { 'P', 'R', 'A', 'N', 'A', 'V', '\0' };

	//code
	printf("\n\n");
	printf("Integer Array Elements And The Addresses They Occupy Are As Follows : \n\n");
	printf("iArr[0] = %d \t At Address : %p\n", *(iArr + 0), (iArr + 0));
	printf("iArr[1] = %d \t At Address : %p\n", *(iArr + 1), (iArr + 1));
	printf("iArr[2] = %d \t At Address : %p\n", *(iArr + 2), (iArr + 2));
	printf("iArr[3] = %d \t At Address : %p\n", *(iArr + 3), (iArr + 3));
	printf("iArr[4] = %d \t At Address : %p\n", *(iArr + 4), (iArr + 4));

	printf("\n\n");
	printf("Float Array Elements And The Addresses They Occupy Are As Follows : \n\n");
	printf("fArr[0] = %f \t At Address : %p\n", *(fArr + 0), (fArr + 0));
	printf("fArr[1] = %f \t At Address : %p\n", *(fArr + 1), (fArr + 1));
	printf("fArr[2] = %f \t At Address : %p\n", *(fArr + 2), (fArr + 2));

	printf("\n\n");
	printf("Double Array Elements And The Addresses They Occupy Are As Follows : \n\n");
	printf("dArr[0] = %lf \t At Address : %p\n", *(dArr + 0), (dArr + 0));
	printf("dArr[1] = %lf \t At Address : %p\n", *(dArr + 1), (dArr + 1));
	printf("dArr[2] = %lf \t At Address : %p\n", *(dArr + 2), (dArr + 2));

	printf("\n\n");
	printf("Character Array Elements And The Addresses They Occupy Are As Follows : \n\n");
	printf("cArr[0] = %c \t At Address : %p\n", *(cArr + 0), (cArr + 0));
	printf("cArr[1] = %c \t At Address : %p\n", *(cArr + 1), (cArr + 1));
	printf("cArr[2] = %c \t At Address : %p\n", *(cArr + 2), (cArr + 2));
	printf("cArr[3] = %c \t At Address : %p\n", *(cArr + 3), (cArr + 3));
	printf("cArr[4] = %c \t At Address : %p\n", *(cArr + 4), (cArr + 4));
	printf("cArr[5] = %c \t At Address : %p\n", *(cArr + 5), (cArr + 5));

	return(0);
}


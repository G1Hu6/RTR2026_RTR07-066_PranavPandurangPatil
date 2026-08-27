#include <stdio.h>

int main(void)
{
	//variable declaraions
	int iArr[] = { 15, 30, 45, 60, 75 };
	int *p_iArr = NULL;

	//code
	printf("\n\n");
	printf("USING ARRAY NAME AS AN ARRAY : \n\n");
	printf("Integer Array Elements And Their Addresses : \n\n");
	printf("iArr[0] = %d \t At Address &iArr[0] : %p\n", iArr[0], &iArr[0]);
	printf("iArr[1] = %d \t At Address &iArr[1] : %p\n", iArr[1], &iArr[1]);
	printf("iArr[2] = %d \t At Address &iArr[2] : %p\n", iArr[2], &iArr[2]);
	printf("iArr[3] = %d \t At Address &iArr[3] : %p\n", iArr[3], &iArr[3]);
	printf("iArr[4] = %d \t At Address &iArr[4] : %p\n", iArr[4], &iArr[4]);

	p_iArr = iArr;

	printf("\n\n");
	printf("USING POINTER AS POINTER : \n\n");
	printf("Integer Array Elements And Their Addresses : \n\n");
	printf("*(p_iArr + 0) = %d \t At Address (p_iArr + 0) : %p\n", *(p_iArr + 0), (p_iArr + 0));
	printf("*(p_iArr + 1) = %d \t At Address (p_iArr + 1) : %p\n", *(p_iArr + 1), (p_iArr + 1));
	printf("*(p_iArr + 2) = %d \t At Address (p_iArr + 2) : %p\n", *(p_iArr + 2), (p_iArr + 2));
	printf("*(p_iArr + 3) = %d \t At Address (p_iArr + 3) : %p\n", *(p_iArr + 3), (p_iArr + 3));
	printf("*(p_iArr + 4) = %d \t At Address (p_iArr + 4) : %p\n", *(p_iArr + 4), (p_iArr + 4));

	printf("\n\n");
	printf("USING ARRAY NAME AS A POINTER : \n\n");
	printf("Integer Array Elements And Their Addresses : \n\n");
	printf("*(iArr + 0) = %d \t At Address (iArr + 0) : %p\n", *(iArr + 0), (iArr + 0));
	printf("*(iArr + 1) = %d \t At Address (iArr + 1) : %p\n", *(iArr + 1), (iArr + 1));
	printf("*(iArr + 2) = %d \t At Address (iArr + 2) : %p\n", *(iArr + 2), (iArr + 2));
	printf("*(iArr + 3) = %d \t At Address (iArr + 3) : %p\n", *(iArr + 3), (iArr + 3));
	printf("*(iArr + 4) = %d \t At Address (iArr + 4) : %p\n", *(iArr + 4), (iArr + 4));

	p_iArr = iArr;

	printf("\n\n");
	printf("USING POINTER AS ARRAY NAME : \n\n");
	printf("Integer Array Elements And Their Addresses : \n\n");
	printf("p_iArr[0] = %d \t At Address &p_iArr[0] : %p\n", p_iArr[0], &p_iArr[0]);
	printf("p_iArr[1] = %d \t At Address &p_iArr[1] : %p\n", p_iArr[1], &p_iArr[1]);
	printf("p_iArr[2] = %d \t At Address &p_iArr[2] : %p\n", p_iArr[2], &p_iArr[2]);
	printf("p_iArr[3] = %d \t At Address &p_iArr[3] : %p\n", p_iArr[3], &p_iArr[3]);
	printf("p_iArr[4] = %d \t At Address &p_iArr[4] : %p\n", p_iArr[4], &p_iArr[4]);

	printf("\n\n");

	return(0);
}


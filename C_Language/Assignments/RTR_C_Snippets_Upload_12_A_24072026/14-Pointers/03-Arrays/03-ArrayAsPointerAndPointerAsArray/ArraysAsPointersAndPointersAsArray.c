#include <stdio.h>

int main(void)
{
	//variable declaraions
	int iArr[] = { 15, 30, 45, 60, 75 };
	int *p_iArr = NULL;

	//code
	p_iArr = iArr;

	printf("\n\n");
	printf("USING POINTER AS POINTER : \n\n");
	printf("Integer Array Elements And Their Addresses : \n\n");
	printf("*(p_iArr + 0) = %d \t At Address (p_iArr + 0) : %p\n", *(p_iArr + 0), (p_iArr + 0));
	printf("*(p_iArr + 1) = %d \t At Address (p_iArr + 1) : %p\n", *(p_iArr + 1), (p_iArr + 1));
	printf("*(p_iArr + 2) = %d \t At Address (p_iArr + 2) : %p\n", *(p_iArr + 2), (p_iArr + 2));
	printf("*(p_iArr + 3) = %d \t At Address (p_iArr + 3) : %p\n", *(p_iArr + 3), (p_iArr + 3));
	printf("*(p_iArr + 4) = %d \t At Address (p_iArr + 4) : %p\n", *(p_iArr + 4), (p_iArr + 4));

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


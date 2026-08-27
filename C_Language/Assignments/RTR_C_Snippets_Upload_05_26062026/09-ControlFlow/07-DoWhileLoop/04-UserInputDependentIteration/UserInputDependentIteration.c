#include<stdio.h>

int main(void)
{
	// variable declarations
	int iNum, num, i;

	// code
	printf("\n\n");
	printf("Enter An Integer Value From Which Iteration Must Begin : ");
	scanf("%d", &iNum);

	printf("How Many Digits Do You Want to Print From %d Onward ? : ", iNum);
        scanf("%d", &num);

	printf("Printing Digits %d to %d : \n\n", iNum, (iNum + num));

	i = iNum;
	do
	{
		printf("\t%d\n", i);
		i++;
	}while(i <= (iNum + num));

	printf("\n\n");

	return(0);
}


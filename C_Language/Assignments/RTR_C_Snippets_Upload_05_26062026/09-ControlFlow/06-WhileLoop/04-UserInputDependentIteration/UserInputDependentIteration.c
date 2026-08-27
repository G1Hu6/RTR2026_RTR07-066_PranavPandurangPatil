#include<stdio.h>

int main(void)
{
	// variable declarations
	int iNum, num, i;

	// code
	printf("\n\n");
	
	printf("Enter An Integer Value From Which Iteration Must Begin : ");
	scanf("%d", &iNum);

	printf("How many Digits Do You Want from %d Onwards ? : ", iNum);
        scanf("%d", &num);

	printf("Printing Digits %d to %d : \n\n", iNum, (iNum + num));

	i = iNum;
	while(i <= (iNum + num))
	{
		printf("\t%d\n", i);
		i++;
	}

	printf("\n\n");
	
	return(0);
}	

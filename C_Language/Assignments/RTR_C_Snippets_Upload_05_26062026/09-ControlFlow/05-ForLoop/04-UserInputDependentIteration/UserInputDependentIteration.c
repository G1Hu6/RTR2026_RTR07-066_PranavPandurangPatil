#include<stdio.h>
int main(void)
{
	// variable declaration
	int iNum, num, i;

	// code
	printf("\n\n");
	printf("Enter An Integer Value From Which Iteration Must Begin : ");
	scanf("%d", &iNum);

	printf("How Many Digits Do You Want To Print From %d : ", iNum);
        scanf("%d", &num);

	printf("Printing Digits %d to %d : \n\n", iNum, (iNum + num));

	for(i = iNum; i <= (iNum + num); i++)
	{
		printf("\t%d\n", i);
	}

	printf("\n\n");

	return(0);
}

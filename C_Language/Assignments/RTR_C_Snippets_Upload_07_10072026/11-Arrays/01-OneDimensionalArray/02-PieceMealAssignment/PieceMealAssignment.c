#include <stdio.h>

int main(void)
{
	//variable declaraions
	int iArr1[6];
	int iArr2[6];

	//code

	// ****** iArr1[] ******
	iArr1[0] = 5;
	iArr1[1] = 10;
	iArr1[2] = 15;
	iArr1[3] = 20;
	iArr1[4] = 25;
	iArr1[5] = 30;

	printf("\n\n");
	printf("Piece-meal (Hard-coded) Assignment And Display Of Elements to Array 'iArr1[]': \n\n");
	printf("1st Element Of Array 'iArr1[]' Or Element At 0th Index Of Array 'iArr1[]' = %d\n", iArr1[0]);
	printf("2nd Element Of Array 'iArr1[]' Or Element At 1st Index Of Array 'iArr1[]' = %d\n", iArr1[1]);
	printf("3rd Element Of Array 'iArr1[]' Or Element At 2nd Index Of Array 'iArr1[]' = %d\n", iArr1[2]);
	printf("4th Element Of Array 'iArr1[]' Or Element At 3rd Index Of Array 'iArr1[]' = %d\n", iArr1[3]);
	printf("5th Element Of Array 'iArr1[]' Or Element At 4th Index Of Array 'iArr1[]' = %d\n", iArr1[4]);
	printf("6th Element Of Array 'iArr1[]' Or Element At 5th Index Of Array 'iArr1[]' = %d\n\n", iArr1[5]);

	// ****** iArr2[] ******
	printf("\n\n");

	printf("Enter 1st Element Of Array 'iArr2[]' : ");
	scanf("%d", &iArr2[0]);
	printf("Enter 2nd Element Of Array 'iArr2[]' : ");
	scanf("%d", &iArr2[1]);
	printf("Enter 3rd Element Of Array 'iArr2[]' : ");
	scanf("%d", &iArr2[2]);
	printf("Enter 4th Element Of Array 'iArr2[]' : ");
	scanf("%d", &iArr2[3]);
	printf("Enter 5th Element Of Array 'iArr2[]' : ");
	scanf("%d", &iArr2[4]);
	printf("Enter 6th Element Of Array 'iArr2[]' : ");
	scanf("%d", &iArr2[5]);

	printf("\n\n");
	printf("Piece-meal (User Input) Assignment And Display Of Elements to Array 'iArr2[]' : \n\n");
	printf("1st Element Of Array 'iArr2[]' Or Element At 0th Index Of Array 'iArr2[]' = %d\n", iArr2[0]);
	printf("2nd Element Of Array 'iArr2[]' Or Element At 1st Index Of Array 'iArr2[]' = %d\n", iArr2[1]);
	printf("3rd Element Of Array 'iArr2[]' Or Element At 2nd Index Of Array 'iArr2[]' = %d\n", iArr2[2]);
	printf("4th Element Of Array 'iArr2[]' Or Element At 3rd Index Of Array 'iArr2[]' = %d\n", iArr2[3]);
	printf("5th Element Of Array 'iArr2[]' Or Element At 4th Index Of Array 'iArr2[]' = %d\n", iArr2[4]);
	printf("6th Element Of Array 'iArr2[]' Or Element At 5th Index Of Array 'iArr2[]' = %d\n\n", iArr2[5]);

	return(0);
}


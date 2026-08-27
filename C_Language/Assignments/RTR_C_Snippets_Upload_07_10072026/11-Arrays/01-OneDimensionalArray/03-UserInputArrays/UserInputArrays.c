#include <stdio.h>
#include <conio.h>

// MACRO CONSTANT USED AS ARRAY SIZE IN SUBSCRIPT AND AS ARRAY LENGTH.
// HENCE, THIS PROGRAM'S ARRAYS' SIZES CAN BE SIMPLY CHANGED BY CHANGING THESE
// FOLLOWING 3 GLOBAL MACRO CONSTANT VALUES, BEFORE COMPILING, LINKING AND
// EXECUTING THE PROGRAM !!!

#define INT_COUNT 5
#define FLOAT_COUNT 3
#define CHAR_COUNT 6

int main(void)
{
	//variable declarations
	int iArr[INT_COUNT];
	float fArr[FLOAT_COUNT];
	char cArr[CHAR_COUNT];
	int i, num;

	//code

	// ********** ARRAY ELEMENTS INPUT **********
	printf("\n\n");
	printf("Enter Elements For 'Integer' Array : \n");
	for (i = 0; i < INT_COUNT; i++)
		scanf("%d", &iArr[i]);

	printf("\n\n");
	printf("Enter Elements For 'Floating-Point' Array : \n");
	for (i = 0; i < FLOAT_COUNT; i++)
		scanf("%f", &fArr[i]);

	printf("\n\n");
	printf("Enter Elements For 'Character' Array : \n");
	for (i = 0; i < CHAR_COUNT; i++)
	{
		cArr[i] = getch();
		printf("%c\n", cArr[i]);
	}

	// ********** ARRAY ELEMENTS OUTPUT **********
	printf("\n\n");
	printf("Integer Array Entered By You : \n\n");
	for (i = 0; i < INT_COUNT; i++)
		printf("%d\n", iArr[i]);

	printf("\n\n");
	printf("Floating-Point Array Entered By You : \n\n");
	for (i = 0; i < FLOAT_COUNT; i++)
		printf("%f\n", fArr[i]);

	printf("\n\n");
	printf("Character Array Entered By You : \n\n");
	for (i = 0; i < CHAR_COUNT; i++)
		printf("%c\n", cArr[i]);

	printf("\n\n");

	return(0);
}


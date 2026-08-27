#include <stdio.h>
#include <string.h>

#define INT_ARRAY_SIZE 5
#define FLOAT_ARRAY_SIZE 5
#define CHAR_ARRAY_SIZE 26

#define NUM_STRINGS 6
#define MAX_CHARACTERS_PER_STRING 20

#define ALPHABET_BEGINNING 65

typedef struct {
	int iArr[INT_ARRAY_SIZE];
	float fArr[FLOAT_ARRAY_SIZE];
} MyDataOne;

typedef struct {
	char cArr[CHAR_ARRAY_SIZE];
	char strArr[NUM_STRINGS][MAX_CHARACTERS_PER_STRING];
} MyDataTwo;

int main(void)
{
	//variable declaraions
	MyDataOne d1;
	MyDataTwo d2;
	int i;

	//code
	d1.fArr[0] = 1.1f;
	d1.fArr[1] = 2.2f;
	d1.fArr[2] = 3.3f;
	d1.fArr[3] = 4.4f;
	d1.fArr[4] = 5.5f;

	printf("\n\n");
	printf("Enter %d Integers : \n\n", INT_ARRAY_SIZE);
	for (i = 0; i < INT_ARRAY_SIZE; i++)
		scanf("%d", &d1.iArr[i]);

	for (i = 0; i < CHAR_ARRAY_SIZE; i++)
		d2.cArr[i] = (char)(i + ALPHABET_BEGINNING);

	strcpy(d2.strArr[0], "My");
	strcpy(d2.strArr[1], "Favourite");
	strcpy(d2.strArr[2], "Player");
	strcpy(d2.strArr[3], "is");
	strcpy(d2.strArr[4], "Virat");
	strcpy(d2.strArr[5], "Kohli");

	printf("\n\n");
	printf("Members Of 'MyDataOne' Alongwith Their Assigned Values Are : \n\n");

	printf("Integer Array (d1.iArr[]) : \n\n");
	for (i = 0; i < INT_ARRAY_SIZE; i++)
		printf("d1.iArr[%d] = %d\n", i, d1.iArr[i]);

	printf("\n\n");
	printf("Floating-Point Array (d1.fArr[]) : \n\n");
	for (i = 0; i < FLOAT_ARRAY_SIZE; i++)
		printf("d1.fArr[%d] = %f\n", i, d1.fArr[i]);

	printf("\n\n");
	printf("Members Of 'MyDataTwo' Alongwith Their Assigned Values Are : \n\n");

	printf("Character Array (d2.cArr[]) : \n\n");
	for (i = 0; i < CHAR_ARRAY_SIZE; i++)
		printf("d2.cArr[%d] = %c\n", i, d2.cArr[i]);

	printf("\n\n");
	printf("String Array (d2.strArr[]) : \n\n");
	for (i = 0; i < NUM_STRINGS; i++)
		printf("%s ", d2.strArr[i]);

	printf("\n\n");

	return(0);
}


#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 599

int main(void)
{
	//variable declarations
	char strOrig[MAX_STRING_LENGTH], strCopy[MAX_STRING_LENGTH]; // A Character Array Is A String

	//code

	// STRING INPUT
	printf("\n\n");
	printf("Enter A String : \n\n");
	gets_s(strOrig, MAX_STRING_LENGTH);

	// STRING COPY
	strcpy(strCopy, strOrig);

	// STRING OUTPUT
	printf("\n\n");
	printf("The Original String Entered By You (i.e : 'strOrig[]') Is : \n\n");
	printf("%s\n", strOrig);

	printf("\n\n");
	printf("The Copied String (i.e : 'strCopy[]') Is : \n\n");
	printf("%s\n", strCopy);

	return(0);
}


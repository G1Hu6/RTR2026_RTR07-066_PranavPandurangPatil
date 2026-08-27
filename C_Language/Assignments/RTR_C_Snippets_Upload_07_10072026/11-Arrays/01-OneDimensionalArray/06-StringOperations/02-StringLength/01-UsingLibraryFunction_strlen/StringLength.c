#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 520

int main(void)
{
	//variable declarations
	char chArr[MAX_STRING_LENGTH]; // A Character Array Is A String
	int strLen = 0;

	//code

	// STRING INPUT
	printf("\n\n");
	printf("Enter A String : \n\n");
	gets_s(chArr, MAX_STRING_LENGTH);

	// STRING OUTPUT
	printf("\n\n");
	printf("String Entered By You Is : \n\n");
	printf("%s\n", chArr);

	// STRING LENGTH
	printf("\n\n");
	strLen = strlen(chArr);
	printf("Length Of String Is = %d Characters !!!\n\n", strLen);

	return(0);
}


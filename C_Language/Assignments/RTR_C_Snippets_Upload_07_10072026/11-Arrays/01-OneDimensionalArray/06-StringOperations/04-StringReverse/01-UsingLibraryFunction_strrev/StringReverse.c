#include <stdio.h>
#include <string.h> // for strrev()

#define MAX_STRING_LENGTH 588

int main(void)
{
	//variable declarations
	char strOrig[MAX_STRING_LENGTH]; // A Character Array Is A String

	//code

	// STRING INPUT
	printf("\n\n");
	printf("Enter A String : \n\n");
	gets_s(strOrig, MAX_STRING_LENGTH);

	// STRING OUTPUT
	printf("\n\n");
	printf("The Original String Entered By You (i.e : 'strOrig[]') Is : \n\n");
	printf("%s\n", strOrig);

	printf("\n\n");
	printf("The Reversed String (i.e : 'strRev[]') Is : \n\n");
	printf("%s\n", strrev(strOrig));

	return(0);
}


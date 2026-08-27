#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 588

int main(void)
{
	//variable declarations
	char str1[MAX_STRING_LENGTH], str2[MAX_STRING_LENGTH]; // A Character Array Is A String

	//code

	// STRING INPUT
	printf("\n\n");
	printf("Enter First String : \n\n");
	gets_s(str1, MAX_STRING_LENGTH);

	printf("\n\n");
	printf("Enter Second String : \n\n");
	gets_s(str2, MAX_STRING_LENGTH);

	// STRING CONCAT
	printf("\n\n");
	printf("BEFORE CONCATENATION");
	printf("\n\n");
	printf("The Original First String Entered By You (i.e : 'str1[]') Is : \n\n");
	printf("%s\n", str1);

	printf("\n\n");
	printf("The Original Second String Entered By You (i.e : 'str2[]') Is : \n\n");
	printf("%s\n", str2);

	strcat(str1, str2);

	printf("\n\n");
	printf("AFTER CONCATENATION");
	printf("\n\n");
	printf("'str1[]' Is : \n\n");
	printf("%s\n", str1);

	printf("\n\n");
	printf("'str2[]' Is : \n\n");
	printf("%s\n", str2);

	return(0);
}


#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_STRING_LENGTH 1024

typedef struct {
	char c;
	int count;
} CharCount;

CharCount charCounts[] = {
	{ 'A', 0 }, { 'B', 0 }, { 'C', 0 }, { 'D', 0 }, { 'E', 0 },
	{ 'F', 0 }, { 'G', 0 }, { 'H', 0 }, { 'I', 0 }, { 'J', 0 },
	{ 'K', 0 }, { 'L', 0 }, { 'M', 0 }, { 'N', 0 }, { 'O', 0 },
	{ 'P', 0 }, { 'Q', 0 }, { 'R', 0 }, { 'S', 0 }, { 'T', 0 },
	{ 'U', 0 }, { 'V', 0 }, { 'W', 0 }, { 'X', 0 }, { 'Y', 0 },
	{ 'Z', 0 }
};

#define TOTAL_ARR_SZ sizeof(charCounts)
#define ONE_STRUCT_SZ sizeof(charCounts[0])
#define NUM_ELEMENTS (TOTAL_ARR_SZ / ONE_STRUCT_SZ)

int main(void)
{
	//variable declaraions
	char str[MAX_STRING_LENGTH];
	int i, j, strLen = 0;

	//code
	printf("\n\n");
	printf("Enter A String : \n\n");
	gets_s(str, MAX_STRING_LENGTH);

	strLen = strlen(str);

	printf("\n\n");
	printf("The String You Have Entered Is : \n\n");
	printf("%s\n\n", str);

	for (i = 0; i < strLen; i++)
	{
		for (j = 0; j < NUM_ELEMENTS; j++)
		{
			str[i] = toupper(str[i]);
			if (str[i] == charCounts[j].c)
				charCounts[j].count++;
		}
	}

	printf("\n\n");
	printf("CHARACTER COUNT IN THE ENTERED STRING : \n\n");
	for (i = 0; i < NUM_ELEMENTS; i++)
	{
		if (charCounts[i].count > 0)
		{
			printf("Character '%c' Repeated %d Times!\n", charCounts[i].c, charCounts[i].count);
		}
	}

	printf("\n\n");

	return(0);
}


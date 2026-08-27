#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
	//function prototype
	void MyStrcpy(char[], char[]);

	//variable declaraions
	char strArr[5][10];
	int sz_char;
	int sz_strArr;
	int cnt, rows, cols;
	int i;

	//code
	printf("\n\n");

	sz_char = sizeof(char);

	sz_strArr = sizeof(strArr);
	printf("Size Of Two Dimensional ( 2D ) Character Array (String Array) Is = %d\n\n", sz_strArr);

	rows = sz_strArr / sizeof(strArr[0]);
	printf("Number of Rows (Strings) In Two Dimensional ( 2D ) Character Array (String Array) Is = %d\n\n", rows);

	cols = sizeof(strArr[0]) / sz_char;
	printf("Number of Columns In Two Dimensional ( 2D ) Character Array (String Array) Is = %d\n\n", cols);

	cnt = rows * cols;
	printf("Maximum Number of Elements (Characters) In Two Dimensional ( 2D ) Character Array (String Array) Is = %d\n\n", cnt);

	MyStrcpy(strArr[0], "My");
	MyStrcpy(strArr[1], "Name");
	MyStrcpy(strArr[2], "Is");
	MyStrcpy(strArr[3], "Pranav");
	MyStrcpy(strArr[4], "Patil");

	printf("\n\n");
	printf("The Strings In the 2D Character Array Are : \n\n");

	for (i = 0; i < rows; i++)
		printf("%s ", strArr[i]);

	printf("\n\n");

	return(0);
}

void MyStrcpy(char str_destination[], char str_source[])
{
	//function prototype
	int MyStrlen(char[]);

	//variable declaraions
	int strLen = 0;
	int j;

	//code
	strLen = MyStrlen(str_source);
	for (j = 0; j < strLen; j++)
		str_destination[j] = str_source[j];

	str_destination[j] = '\0';
}

int MyStrlen(char str[])
{
	//variable declaraions
	int j;
	int len = 0;

	//code
	for (j = 0; j < MAX_STRING_LENGTH; j++)
	{
		if (str[j] == '\0')
			break;
		else
			len++;
	}
	return(len);
}


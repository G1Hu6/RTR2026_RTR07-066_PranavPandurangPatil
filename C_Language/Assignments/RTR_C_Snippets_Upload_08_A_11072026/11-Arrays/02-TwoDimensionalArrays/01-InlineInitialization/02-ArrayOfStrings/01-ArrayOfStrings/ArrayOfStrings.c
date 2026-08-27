#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
	//function prototype
	int MyStrlen(char[]);

	//variable declaraions
	char strArr[6][15] = { "Hello", "My", "Name", "is", "Pranav", "Patil." };
	int char_size;
	int strArr_size;
	int strArr_num_elements, strArr_num_rows, strArr_num_columns;
	int strActual_num_chars = 0;
	int i;

	//code
	printf("\n\n");

	char_size = sizeof(char);

	strArr_size = sizeof(strArr);
	printf("Size Of Two Dimensional ( 2D ) Character Array (String Array) Is = %d\n\n", strArr_size);

	strArr_num_rows = strArr_size / sizeof(strArr[0]);
	printf("Number of Rows (Strings) In Two Dimensional ( 2D ) Character Array (String Array) Is = %d\n\n", strArr_num_rows);

	strArr_num_columns = sizeof(strArr[0]) / char_size;
	printf("Number of Columns In Two Dimensional ( 2D ) Character Array (String Array) Is = %d\n\n", strArr_num_columns);

	strArr_num_elements = strArr_num_rows * strArr_num_columns;
	printf("Maximum Number of Elements (Characters) In Two Dimensional ( 2D ) Character Array (String Array) Is = %d\n\n", strArr_num_elements);

	for (i = 0; i < strArr_num_rows; i++)
	{
		strActual_num_chars = strActual_num_chars + MyStrlen(strArr[i]);
	}
	printf("Actual Number of Elements (Characters) In Two Dimensional ( 2D ) Character Array (String Array) Is = %d\n\n", strActual_num_chars);

	printf("\n\n");
	printf("Strings In The 2D Array : \n\n");

	for (i = 0; i < strArr_num_rows; i++)
	{
		printf("%s ", strArr[i]);
	}
	printf("\n\n");

	return(0);
}

int MyStrlen(char str[])
{
	//variable declaraions
	int j;
	int string_length = 0;

	//code
	for (j = 0; j < MAX_STRING_LENGTH; j++)
	{
		if (str[j] == '\0')
			break;
		else
			string_length++;
	}
	return(string_length);
}


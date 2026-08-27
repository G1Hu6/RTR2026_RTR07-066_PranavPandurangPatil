#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
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

	strArr[0][0] = 'M';
	strArr[0][1] = 'y';
	strArr[0][2] = '\0';

	strArr[1][0] = 'N';
	strArr[1][1] = 'a';
	strArr[1][2] = 'm';
	strArr[1][3] = 'e';
	strArr[1][4] = '\0';

	strArr[2][0] = 'I';
	strArr[2][1] = 's';
	strArr[2][2] = '\0';

	strArr[3][0] = 'P';
	strArr[3][1] = 'r';
	strArr[3][2] = 'a';
	strArr[3][3] = 'n';
	strArr[3][4] = 'a';
	strArr[3][5] = 'v';
	strArr[3][6] = '\0';

	strArr[4][0] = 'P';
	strArr[4][1] = 'a';
	strArr[4][2] = 't';
	strArr[4][3] = 'i';
	strArr[4][4] = 'l';
	strArr[4][5] = '\0';

	printf("\n\n");
	printf("The Strings In the 2D Character Array Are : \n\n");

	for (i = 0; i < rows; i++)
		printf("%s ", strArr[i]);

	printf("\n\n");

	return(0);
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


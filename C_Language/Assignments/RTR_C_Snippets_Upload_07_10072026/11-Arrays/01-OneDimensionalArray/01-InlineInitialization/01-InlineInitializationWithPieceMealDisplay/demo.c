#include<stdio.h>

int main(void)
{
	//variable declaraions
	int iArr[] = { 5, 10, 15, 20, 25, 30, 35, 40, 45, 50 };
	int int_size;
	int iArr_size;
	int iArr_count;

	float fArr[] = { 1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10.0f };
	int float_size;
	int fArr_size;
	int fArr_count;

	char cArr[] = { 'P', 'R', 'A', 'N', 'A', 'V' };
	int char_size;
	int cArr_size;
	int cArr_count;

	//code

	// ****** iArr[] ******
	printf("\n\n");
	printf("In-Line Initialization And Piece-meal Display Of Elements of Array 'iArr[]': \n\n");
	printf("iArr[0] (1st Element)  = %d\n", iArr[0]);
	printf("iArr[1] (2nd Element)  = %d\n", iArr[1]);
	printf("iArr[2] (3rd Element)  = %d\n", iArr[2]);
	printf("iArr[3] (4th Element)  = %d\n", iArr[3]);
	printf("iArr[4] (5th Element)  = %d\n", iArr[4]);
	printf("iArr[5] (6th Element)  = %d\n", iArr[5]);
	printf("iArr[6] (7th Element)  = %d\n", iArr[6]);
	printf("iArr[7] (8th Element)  = %d\n", iArr[7]);
	printf("iArr[8] (9th Element)  = %d\n", iArr[8]);
	printf("iArr[9] (10th Element) = %d\n\n", iArr[9]);

	int_size = sizeof(int);
	iArr_size = sizeof(iArr);
	iArr_count = iArr_size / int_size;
	printf("Size Of Data type 'int'                           = %d bytes\n", int_size);
	printf("Number Of Elements In 'int' Array 'iArr[]'        = %d Elements\n", iArr_count);
	printf("Size Of Array 'iArr[]' (%d Elements * %d Bytes)   = %d Bytes\n\n", iArr_count, int_size, iArr_size);

	// ****** fArr[] ******
	printf("\n\n");
	printf("In-Line Initialization And Piece-meal Display Of Elements of Array 'fArr[]': \n\n");
	printf("fArr[0] (1st Element)  = %f\n", fArr[0]);
	printf("fArr[1] (2nd Element)  = %f\n", fArr[1]);
	printf("fArr[2] (3rd Element)  = %f\n", fArr[2]);
	printf("fArr[3] (4th Element)  = %f\n", fArr[3]);
	printf("fArr[4] (5th Element)  = %f\n", fArr[4]);
	printf("fArr[5] (6th Element)  = %f\n", fArr[5]);
	printf("fArr[6] (7th Element)  = %f\n", fArr[6]);
	printf("fArr[7] (8th Element)  = %f\n", fArr[7]);
	printf("fArr[8] (9th Element)  = %f\n", fArr[8]);
	printf("fArr[9] (10th Element) = %f\n\n", fArr[9]);

	float_size = sizeof(float);
	fArr_size = sizeof(fArr);
	fArr_count = fArr_size / float_size;
	printf("Size Of Data type 'float'                         = %d bytes\n", float_size);
	printf("Number Of Elements In 'float' Array 'fArr[]'      = %d Elements\n", fArr_count);
	printf("Size Of Array 'fArr[]' (%d Elements * %d Bytes)   = %d Bytes\n\n", fArr_count, float_size, fArr_size);

	// ****** cArr[] ******
	printf("\n\n");
	printf("In-Line Initialization And Piece-meal Display Of Elements of Array 'cArr[]': \n\n");
	printf("cArr[0] (1st Element) = %c\n", cArr[0]);
	printf("cArr[1] (2nd Element) = %c\n", cArr[1]);
	printf("cArr[2] (3rd Element) = %c\n", cArr[2]);
	printf("cArr[3] (4th Element) = %c\n", cArr[3]);
	printf("cArr[4] (5th Element) = %c\n", cArr[4]);
	printf("cArr[5] (6th Element) = %c\n\n", cArr[5]);

	char_size = sizeof(char);
	cArr_size = sizeof(cArr);
	cArr_count = cArr_size / char_size;
	printf("Size Of Data type 'char'                          = %d bytes\n", char_size);
	printf("Number Of Elements In 'char' Array 'cArr[]'       = %d Elements\n", cArr_count);
	printf("Size Of Array 'cArr[]' (%d Elements * %d Bytes)   = %d Bytes\n\n", cArr_count, char_size, cArr_size);

	return(0);
}

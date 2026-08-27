#include <stdio.h>

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

	int i;

	//code

	// ****** iArr[] ******
	printf("\n\n");
	printf("In-line Initialization And Loop (for) Display Of Elements of Array 'iArr[]': \n\n");

	int_size = sizeof(int);
	iArr_size = sizeof(iArr);
	iArr_count = iArr_size / int_size;

	for (i = 0; i < iArr_count; i++)
	{
		printf("iArr[%d] (Element %d) = %d\n", i, (i + 1), iArr[i]);
	}

	printf("\n\n");
	printf("Size Of Data type 'int'                           = %d bytes\n", int_size);
	printf("Number Of Elements In 'int' Array 'iArr[]'        = %d Elements\n", iArr_count);
	printf("Size Of Array 'iArr[]' (%d Elements * %d Bytes)   = %d Bytes\n\n", iArr_count, int_size, iArr_size);

	// ****** fArr[] ******
	printf("\n\n");
	printf("In-line Initialization And Loop (while) Display Of Elements of Array 'fArr[]': \n\n");

	float_size = sizeof(float);
	fArr_size = sizeof(fArr);
	fArr_count = fArr_size / float_size;

	i = 0;
	while (i < fArr_count)
	{
		printf("fArr[%d] (Element %d) = %f\n", i, (i + 1), fArr[i]);
		i++;
	}

	printf("\n\n");
	printf("Size Of Data type 'float'                         = %d bytes\n", float_size);
	printf("Number Of Elements In 'float' Array 'fArr[]'      = %d Elements\n", fArr_count);
	printf("Size Of Array 'fArr[]' (%d Elements * %d Bytes)   = %d Bytes\n\n", fArr_count, float_size, fArr_size);

	// ****** cArr[] ******
	printf("\n\n");
	printf("In-line Initialization And Loop (do while) Display Of Elements of Array 'cArr[]': \n\n");

	char_size = sizeof(char);
	cArr_size = sizeof(cArr);
	cArr_count = cArr_size / char_size;

	i = 0;
	do
	{
		printf("cArr[%d] (Element %d) = %c\n", i, (i + 1), cArr[i]);
		i++;
	} while (i < cArr_count);

	printf("\n\n");
	printf("Size Of Data type 'char'                          = %d bytes\n", char_size);
	printf("Number Of Elements In 'char' Array 'cArr[]'       = %d Elements\n", cArr_count);
	printf("Size Of Array 'cArr[]' (%d Elements * %d Bytes)   = %d Bytes\n\n", cArr_count, char_size, cArr_size);

	return(0);
}


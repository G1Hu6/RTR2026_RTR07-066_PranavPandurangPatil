#include <stdio.h>

typedef struct {
	int n;
	int table[10];
} NumberInfo;

typedef struct {
	NumberInfo t1;
	NumberInfo t2;
	NumberInfo t3;
} MultiplicationTables;

int main(void)
{
	//variable declaraions
	MultiplicationTables tablesObj;
	int i;

	//code
	tablesObj.t1.n = 5;
	for (i = 0; i < 10; i++)
		tablesObj.t1.table[i] = tablesObj.t1.n * (i + 1);

	printf("\n\n");
	printf("Table Of %d : \n\n", tablesObj.t1.n);
	for (i = 0; i < 10; i++)
		printf("%d * %d = %d\n", tablesObj.t1.n, (i + 1), tablesObj.t1.table[i]);

	tablesObj.t2.n = 7;
	for (i = 0; i < 10; i++)
		tablesObj.t2.table[i] = tablesObj.t2.n * (i + 1);

	printf("\n\n");
	printf("Table Of %d : \n\n", tablesObj.t2.n);
	for (i = 0; i < 10; i++)
		printf("%d * %d = %d\n", tablesObj.t2.n, (i + 1), tablesObj.t2.table[i]);

	tablesObj.t3.n = 9;
	for (i = 0; i < 10; i++)
		tablesObj.t3.table[i] = tablesObj.t3.n * (i + 1);

	printf("\n\n");
	printf("Table Of %d : \n\n", tablesObj.t3.n);
	for (i = 0; i < 10; i++)
		printf("%d * %d = %d\n", tablesObj.t3.n, (i + 1), tablesObj.t3.table[i]);

	return(0);
}


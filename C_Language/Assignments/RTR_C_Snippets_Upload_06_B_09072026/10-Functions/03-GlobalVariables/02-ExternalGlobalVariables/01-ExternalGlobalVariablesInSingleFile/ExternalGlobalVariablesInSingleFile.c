#include<stdio.h>

// GLOBAL SCOPE

int main(void)
{
	// function prototype
	void ChangeCount(void);

	// variable declarations
	extern int gCount;

	// code
	printf("\n");
	printf("Value of gCount before change = %d\n", gCount);
	ChangeCount();
	printf("Value of gCount after change = %d\n", gCount);
	printf("\n");

	return(0);
}

// GLOBAL SCOPE
// gCount is a gloabl variable
// Since, it is declared before ChangeCount(), it can be accessed and used as any ordinary global variable in ChangeCount().
// Since, it is declared after main(), it must be first redeclared in main() as an external global variable.

int gCount = 0;

void ChangeCount()
{
	// code
	gCount = 5;
	printf("Value of gCount in ChangeCount() = %d\n", gCount);
}

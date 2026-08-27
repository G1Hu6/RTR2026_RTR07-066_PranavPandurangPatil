#include<stdio.h>

// GLOBAL SCOPE
// If not initialized by us, then global variables are initialized to their zero values wrt data typeby default.
// But still, for good prrgramming practice we shall explictly do.

int gCount = 0;

int main(void)
{
	// function prototype
	void ChangeCount1(void);
	void ChangeCount2(void);
	void ChangeCount3(void);

	// code
	printf("\n");
	printf("main() : value of gCount = %d \n", gCount);

	ChangeCount1();
	ChangeCount2();
	ChangeCount3();

	return(0);
}

void ChangeCount1(void)
{
	gCount = 100;
	printf("ChangeCount1() : value of gCount = %d \n", gCount);
}

void ChangeCount2(void)
{
        gCount += 1;
        printf("ChangeCount2() : value of gCount = %d \n", gCount);
}

void ChangeCount3(void)
{
        gCount += 10;
        printf("ChangeCount3() : value of gCount = %d \n", gCount);
}



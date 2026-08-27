#include<stdio.h>

// GLOBAL SCOPE
int main(void)
{
	// Local scope of main()
	// variable declarations
	int a = 5;

	// function prototypes
	void ChangeCnt(void);

	// code
	printf("\n\n");
	printf("A = %d", a);

	ChangeCnt();

	ChangeCnt();

	ChangeCnt();

	return(0);
}

void ChangeCnt()
{
	static int lCnt = 0;
	lCnt++;
	printf("lCnt = %d", lCnt);
}


#include<stdio.h>

// GLOBAL SCOPE
int gCount = 0;

int main(void)
{
	// function prototype
	void ChangeCount(void);
	void ChangeCount2(void); // function defined in File_01.c
	void ChangeCount3(void); // function defined in File_01.c
				 
	// code
	printf("\n");

	ChangeCount();
	ChangeCount2();// function defined in File_01.c
	ChangeCount3();// function defined in File_02.c
		      
	return(0);
}

void ChangeCount()
{
	// code
	gCount += 1;
	printf("gCount = %d", gCount);
}

// *** GLOBAL SCOPE ***
// gCount is a global variable declared in source code file ExternalGlobalVariablesInMultipleFiles.c
// To access it in this file, it must first be re-declared as an external variable in the global scope of this file along with the 'extern' keyword and its proper data type
// Then, it can be used as any ordinary global variable throughout this file as well

#include<stdio.h>

extern int gCount;

void ChangeCount2(void)
{
	// code
	gCount += 1;
	printf("\nChangeCount2() : Value Of gCount in File_01 = %d\n", gCount);
}


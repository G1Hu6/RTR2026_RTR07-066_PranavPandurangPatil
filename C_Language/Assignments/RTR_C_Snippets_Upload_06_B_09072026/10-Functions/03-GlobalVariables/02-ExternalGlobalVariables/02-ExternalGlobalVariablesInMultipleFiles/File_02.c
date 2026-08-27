// *** GLOBAL SCOPE ***
// gCount is a global variable declared in source code file ExternalGlobalVariablesInMultipleFiles.c
// To access it in this file, it must first be re-declared as an external variable in the global scope of this file along with the 'extern' keyword and its proper data type
// Then, it can be used as any ordinary global variable throughout this file as well
// Here, Re-declaring 'gCount' as a local variable using 'extern' keyword within ChangeCount3()

#include <stdio.h>

void ChangeCount3(void)
{
	// code
	extern int gCount;
	gCount += 1;
	printf("ChangeCount3() : Value Of gCount in File_02 = %d\n", gCount);
}


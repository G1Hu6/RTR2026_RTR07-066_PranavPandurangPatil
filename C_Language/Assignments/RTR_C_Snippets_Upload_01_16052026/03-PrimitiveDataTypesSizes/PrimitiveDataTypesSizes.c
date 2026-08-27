#include<stdio.h>

int main(void)
{
	// code
	printf("\n\n");

	printf("Size of 'int'		= %ld bytes\n", sizeof(int));
	printf("Size of 'unsigned int'	= %ld bytes\n", sizeof(unsigned int));
	printf("Size of 'signed int'	= %ld bytes\n", sizeof(signed int));
	printf("Size of 'long'		= %ld bytes\n", sizeof(long));
	printf("Size of 'long long'	= %ld bytes\n", sizeof(long long));
	printf("Size of 'char'  	= %ld bytes\n", sizeof(char));

	printf("Size of 'float'		= %ld bytes\n", sizeof(float));
	printf("Size of 'double'	= %ld bytes\n", sizeof(double));
	printf("Size of 'long double'	= %ld bytes\n", sizeof(long double));
	
	printf("\n\n");

	return (0);
}

/*
 *
 * WARANING :-
 *
 *D:\code\RTR Projects\C_Language\Assignments\RTR_C_Snippets_Upload_01_16052026\03-PrimitiveDataTypesSizes>cl.exe /c /EHsc PrimitiveDataTypesSizes.c
Microsoft (R) C/C++ Optimizing Compiler Version 19.51.36246 for x64
Copyright (C) Microsoft Corporation.  All rights reserved.

PrimitiveDataTypesSizes.c
PrimitiveDataTypesSizes.c(8): warning C4477: 'printf' : format string '%ld' requires an argument of type 'long', but variadic argument 1 has type 'size_t'
PrimitiveDataTypesSizes.c(8): note: consider using '%zu' in the format string
PrimitiveDataTypesSizes.c(9): warning C4477: 'printf' : format string '%ld' requires an argument of type 'long', but variadic argument 1 has type 'size_t'
PrimitiveDataTypesSizes.c(9): note: consider using '%zu' in the format string
PrimitiveDataTypesSizes.c(10): warning C4477: 'printf' : format string '%ld' requires an argument of type 'long', but variadic argument 1 has type 'size_t'
PrimitiveDataTypesSizes.c(10): note: consider using '%zu' in the format string
PrimitiveDataTypesSizes.c(11): warning C4477: 'printf' : format string '%ld' requires an argument of type 'long', but variadic argument 1 has type 'size_t'
PrimitiveDataTypesSizes.c(11): note: consider using '%zu' in the format string
PrimitiveDataTypesSizes.c(12): warning C4477: 'printf' : format string '%ld' requires an argument of type 'long', but variadic argument 1 has type 'size_t'
PrimitiveDataTypesSizes.c(12): note: consider using '%zu' in the format string
PrimitiveDataTypesSizes.c(13): warning C4477: 'printf' : format string '%ld' requires an argument of type 'long', but variadic argument 1 has type 'size_t'
PrimitiveDataTypesSizes.c(13): note: consider using '%zu' in the format string
PrimitiveDataTypesSizes.c(15): warning C4477: 'printf' : format string '%ld' requires an argument of type 'long', but variadic argument 1 has type 'size_t'
PrimitiveDataTypesSizes.c(15): note: consider using '%zu' in the format string
PrimitiveDataTypesSizes.c(16): warning C4477: 'printf' : format string '%ld' requires an argument of type 'long', but variadic argument 1 has type 'size_t'
PrimitiveDataTypesSizes.c(16): note: consider using '%zu' in the format string
PrimitiveDataTypesSizes.c(17): warning C4477: 'printf' : format string '%ld' requires an argument of type 'long', but variadic argument 1 has type 'size_t'
 */

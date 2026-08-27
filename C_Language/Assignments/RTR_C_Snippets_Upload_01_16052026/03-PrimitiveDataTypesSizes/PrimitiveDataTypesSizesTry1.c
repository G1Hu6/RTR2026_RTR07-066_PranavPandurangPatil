int main(void)
{
        // code
        printf("\n\n");

        printf("Size of 'int'            = %zu bytes\n", sizeof(int));
        printf("Size of 'unsigned int'   = %zu bytes\n", sizeof(unsigned int));
        printf("Size of 'signed int'     = %zu bytes\n", sizeof(signed int));
        printf("Size of 'long int'       = %zu bytes\n", sizeof(long int));
        
	printf("Size of 'long'           = %zu bytes\n", sizeof(long));
        printf("Size of 'unsigned long'  = %zu bytes\n", sizeof(unsigned long));
        printf("Size of 'signed long'    = %zu bytes\n", sizeof(signed long));
        printf("Size of 'long long'      = %zu bytes\n", sizeof(long long));
        
	printf("Size of 'char'           = %zu bytes\n", sizeof(char));
	printf("Size of 'unsigned char'  = %zu bytes\n", sizeof(unsigned char));
	printf("Size of 'signed char'    = %zu bytes\n", sizeof(signed char));
	/*
	printf("Size of 'long char'  = %zu bytes\n", sizeof(long char));
	
	ERROR :-
	rimitiveDataTypesSizesTry1.c
	PrimitiveDataTypesSizesTry1.c(19): error C2632: 'long' followed by 'char' is illegal
	*/
	
        printf("Size of 'short'          = %zu bytes\n", sizeof(short));
        printf("Size of 'unsigned short' = %zu bytes\n", sizeof(unsigned short));
        printf("Size of 'signed short'   = %zu bytes\n", sizeof(signed short));       
 	/*
	printf("Size of 'long short'     = %zu bytes\n", sizeof(long short));
 	
	ERROR :-
	PrimitiveDataTypesSizesTry1.c
	PrimitiveDataTypesSizesTry1.c(21): error C2632: 'long' followed by 'short' is illegal
	*/
	
	printf("Size of 'float'          = %zu bytes\n", sizeof(float));
	printf("Size of 'unsigned float' = %zu bytes\n", sizeof(unsigned float));
	printf("Size of 'signed float'   = %zu bytes\n", sizeof(signed float));
	printf("Size of 'long float'     = %zu bytes\n", sizeof(long float));

        printf("Size of 'double'         = %zu bytes\n", sizeof(double));
        printf("Size of 'long double'    = %zu bytes\n", sizeof(long double));
        printf("Size of 'unsigned double'= %zu bytes\n", sizeof(unsigned double));
        printf("Size of 'signed double'  = %zu bytes\n", sizeof(signed double));

        printf("\n\n");

        return (0);
}

/*
 * WARNING :- 
 * PrimitiveDataTypesSizesTry1.c(35): warning C4076: 'unsigned': cannot be used with type 'float'
PrimitiveDataTypesSizesTry1.c(36): warning C4076: 'signed': cannot be used with type 'float'
PrimitiveDataTypesSizesTry1.c(37): warning C4215: nonstandard extension used: long float
PrimitiveDataTypesSizesTry1.c(41): warning C4076: 'unsigned': cannot be used with type 'double'
PrimitiveDataTypesSizesTry1.c(42): warning C4076: 'signed': cannot be used with type 'double'
*
*
*/

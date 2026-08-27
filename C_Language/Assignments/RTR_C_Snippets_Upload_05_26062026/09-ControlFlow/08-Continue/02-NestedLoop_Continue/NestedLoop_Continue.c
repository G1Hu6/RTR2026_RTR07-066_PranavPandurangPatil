#include <stdio.h>

int main(void)
{
    //variable declarations
    int outer, inner;

    //code
    printf("\n\n");

    printf("Outer Loop Prints Odd Numbers Between 1 and 10. \n\n");
    printf("Inner Loop Prints Even Numbers Between 1 and 10 For Every Odd Number Printed By Outer Loop. \n\n");

    // condition for a number to be even => division of number by 2 leaves no remainder (remainder = 0)
    // condition for a number to be odd  => division of number by 2 leaves remainder (remainder = 1 (usually))

    for (outer = 1; outer <= 10; outer++)
    {
        if (outer % 2 != 0) //If Number (outer) Is Odd..
        {
            printf("outer = %d\n", outer);
            printf("----------\n");
            for (inner = 1; inner <= 10; inner++)
            {
                if (inner % 2 == 0) //If Number (inner) Is Even...
                {
                    printf("\tinner = %d\n", inner);
                }
                else //If Number (inner) Is Odd..
                {
                    continue;
                }
            }
            printf("\n\n");
        }
        else //If Number (outer) Is Even...
        {
            continue;
        }
    }

    printf("\n\n");

    return(0);
}

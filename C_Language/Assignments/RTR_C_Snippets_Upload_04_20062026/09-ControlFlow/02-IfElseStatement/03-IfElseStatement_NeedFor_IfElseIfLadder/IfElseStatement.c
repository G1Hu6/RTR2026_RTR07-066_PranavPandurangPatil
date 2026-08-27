#include <stdio.h>

int main(void)
{
    //variable declarations
    int value;

    //code

    printf("\n\n");

    printf("Enter Value For 'value' : ");
    scanf("%d", &value);

    if (value < 0) // 'if' - 01
    {
        printf("Num = %d Is Less Than 0 (NEGATIVE) !!!\n\n", value);
    }
    else // 'else' - 01
    {
        if ((value > 0) && (value <= 100)) // 'if' - 02
        {
            printf("Num = %d Is Between 0 And 100 !!!\n\n", value);
        }
        else // 'else' - 02
        {
            if ((value > 100) && (value <= 200)) // 'if' - 03
            {
                printf("Num = %d Is Between 100 And 200 !!!\n\n", value);
            }
            else // 'else' - 03
            {
                if ((value > 200) && (value <= 300)) // 'if' - 04
                {
                    printf("Num = %d Is Between 200 And 300 !!!\n\n", value);
                }
                else // 'else' - 04
                {
                    if ((value > 300) && (value <= 400)) // 'if' - 05
                    {
                        printf("Num = %d Is Between 300 And 400 !!!\n\n", value);
                    }
                    else // 'else' - 05
                    {
                        if ((value > 400) && (value <= 500)) // 'if' - 06
                        {
                            printf("Num = %d Is Between 400 And 500 !!!\n\n", value);
                        }
                        else // 'else' - 06
                        {
                            printf("Num = %d Is Greater Than 500 !!!\n\n", value);
                        } // closing brace of 'else' - 06

                    } // closing brace of 'else' - 05

                } // closing brace of 'else' - 04

            } // closing brace of 'else' - 03

        } // closing brace of 'else' - 02

    } // closing brace of 'else' - 01

    return(0);
}

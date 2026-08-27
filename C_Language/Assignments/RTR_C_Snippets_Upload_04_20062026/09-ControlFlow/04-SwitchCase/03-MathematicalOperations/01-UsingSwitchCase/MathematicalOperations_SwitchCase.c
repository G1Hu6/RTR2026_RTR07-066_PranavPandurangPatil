#include <stdio.h> // for printf()
#include <conio.h> // for getch()

int main(void)
{
    //variable declarations
    int num1, num2;
    int ans;

    char ch, divCh;

    //code
    printf("\n\n");

    printf("Enter Value For 'A' : ");
    scanf("%d", &num1);

    printf("Enter Value For 'B' : ");
    scanf("%d", &num2);

    printf("Enter Option In Character : \n\n");
    printf("'A' or 'a' For Addition : \n");
    printf("'S' or 's' For Subtraction : \n");
    printf("'M' or 'm' For Multiplication : \n");
    printf("'D' or 'd' For Division : \n\n");

    printf("Enter Option : ");
    ch = getch();

    printf("\n\n");

    switch (ch)
    {
        // FALL THROUGH CONSITION FOR 'A' and 'a'
        case 'A':
        case 'a':
            ans = num1 + num2;
            printf("Addition Of A = %d And B = %d Gives Result %d !!!\n\n",
                   num1, num2, ans);
            break;

        // FALL THROUGH CONSITION FOR 'S' and 's'
        case 'S':
        case 's':
            if (num1 >= num2)
            {
                ans = num1 - num2;
                printf("Subtraction Of B = %d From A = %d Gives Result %d !!!\n\n",
                       num2, num1, ans);
            }
            else
            {
                ans = num2 - num1;
                printf("Subtraction Of A = %d From B = %d Gives Result %d !!!\n\n",
                       num1, num2, ans);
            }
            break;

        // FALL THROUGH CONSITION FOR 'M' and 'm'
        case 'M':
        case 'm':
            ans = num1 * num2;
            printf("Multiplication Of A = %d And B = %d Gives Result %d !!!!\n\n",
                   num1, num2, ans);
            break;

        // FALL THROUGH CONSITION FOR 'D' and 'd'
        case 'D':
        case 'd':

            printf("Enter Option In Character : \n\n");
            printf("'Q' or 'q' or '/' For Quotient Upon Division : \n");
            printf("'R' or 'r' or '%%' For Remainder Upon Division : \n");

            printf("Enter Option : ");
            divCh = getch();

            printf("\n\n");

            switch (divCh)
            {
                // FALL THROUGH CONSITION FOR 'Q' and 'q' and '/'
                case 'Q':
                case 'q':
                case '/':

                    if (num1 >= num2)
                    {
                        ans = num1 / num2;
                        printf("Division Of A = %d By B = %d Gives Quotient = %d !!!!\n\n",
                               num1, num2, ans);
                    }
                    else
                    {
                        ans = num2 / num1;
                        printf("Division Of B = %d By A = %d Gives Quotient = %d !!!!\n\n",
                               num2, num1, ans);
                    }
                    break; // 'break' of case 'Q' or case 'q' or case '/'

                // FALL THROUGH CONSITION FOR 'R' and 'r' and '%'
                case 'R':
                case 'r':
                case '%':

                    if (num1 >= num2)
                    {
                        ans = num1 % num2;
                        printf("Division Of A = %d By B = %d Gives Remainder = %d !!!!\n\n",
                               num1, num2, ans);
                    }
                    else
                    {
                        ans = num2 % num1;
                        printf("Division Of B = %d By A = %d Gives Remainder = %d !!!!\n\n",
                               num2, num1, ans);
                    }
                    break; // 'break' of case 'R' or case 'r' or case '%'

                default: // 'default' case for switch(option_division)
                    printf("Invalid Character %c Entered !!! For Division !!! Please Try Again...\n\n",
                           divCh);
                    break; // 'break' of 'default' of switch(option_division)
            } // ending curly brace of switch(option_division)

            break; // 'break' of case 'D' or case 'd'

        default: // 'default' case for switch(option)
            printf("Invalid Character %c Entered !!! Please Try Again...\n\n",
                   ch);
            break;
    } // ending curly brace of switch(option)

    printf("Switch Case Block Complete !!!\n");

    return (0);
}

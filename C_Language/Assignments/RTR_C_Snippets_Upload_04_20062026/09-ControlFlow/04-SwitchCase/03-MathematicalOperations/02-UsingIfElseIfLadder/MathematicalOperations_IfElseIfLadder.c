#include <stdio.h>   // for printf()
#include <conio.h>   // for getch()

int main(void)
{
    // variable declarations
    int x, y;
    int ans;

    char choice, divChoice;

    // input
    printf("\n\n");

    printf("Enter Value For X : ");
    scanf("%d", &x);
    printf("Enter Value For Y : ");
    scanf("%d", &y);

    printf("Enter Option In Character : \n\n");
    printf("'A' or 'a' For Addition : \n");
    printf("'S' or 's' For Subtraction : \n");
    printf("'M' or 'm' For Multiplication : \n");
    printf("'D' or 'd' For Division : \n\n");

    printf("Enter Option : ");
    choice = getch();
    printf("\n\n");

    if (choice == 'A' || choice == 'a')
    {
        ans = x + y;
        printf("Addition Of X = %d And Y = %d Gives Result %d !!\n\n", x, y, ans);
    }
    else if (choice == 'S' || choice == 's')
    {
        if (x >= y)
        {
            ans = x - y;
            printf("Subtraction Of Y = %d From X = %d Gives Result %d !!\n\n", y, x, ans);
        }
        else
        {
            ans = y - x;
            printf("Subtraction Of X = %d From Y = %d Gives Result %d !!\n\n", x, y, ans);
        }
    }
    else if (choice == 'M' || choice == 'm')
    {
        ans = x * y;
        printf("Multiplication Of X = %d And Y = %d Gives Result %d !!\n\n", x, y, ans);
    }
    else if (choice == 'D' || choice == 'd')
    {
        printf("Enter Option In Character : \n\n");
        printf("'Q' or 'q' or '/' For Quotient Upon Division : \n");
        printf("'R' or 'r' or '%%' For Remainder Upon Division : \n");
        printf("Enter Option : ");
        divChoice = getch();
        printf("\n\n");

        if (divChoice == 'Q' || divChoice == 'q' || divChoice == '/')
        {
            if (x >= y)
            {
                ans = x / y;
                printf("Division Of X = %d By Y = %d Gives Quotient = %d !!\n\n", x, y, ans);
            }
            else
            {
                ans = y / x;
                printf("Division Of Y = %d By X = %d Gives Quotient = %d !!\n\n", y, x, ans);
            }
        }
        else if (divChoice == 'R' || divChoice == 'r' || divChoice == '%')
        {
            if (x >= y)
            {
                ans = x % y;
                printf("Division Of X = %d By Y = %d Gives Remainder = %d !!\n\n", x, y, ans);
            }
            else
            {
                ans = y % x;
                printf("Division Of Y = %d By X = %d Gives Remainder = %d !!\n\n", y, x, ans);
            }
        }
        else
        {
            printf("Invalid Character %c Entered For Division !!! Please Try Again...\n\n", divChoice);
        }
    }
    else
    {
        printf("Invalid Character %c Entered !!! Please Try Again...\n\n", choice);
    }

    printf("If - Else If - Else Ladder Complete !!!\n");
    return 0;
}


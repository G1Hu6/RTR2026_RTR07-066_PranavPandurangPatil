#include <stdio.h>
#include <conio.h>

int main(void)
{
    //variable declarations
    int row, col;

    //code
    printf("\n\n");

    for (row = 1; row <= 20; row++)
    {
        for (col = 1; col <= 20; col++)
        {
            if (col > row)
            {
                break;
            }
            else
            {
                printf("* ");
            }
        }
        printf("\n");
    }

    printf("\n\n");
    return(0);
}

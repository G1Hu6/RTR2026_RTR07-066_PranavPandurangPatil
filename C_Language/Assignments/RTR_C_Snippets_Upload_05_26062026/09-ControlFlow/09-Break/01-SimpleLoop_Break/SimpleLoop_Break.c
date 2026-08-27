#include <stdio.h>
#include <conio.h>

int main(void)
{
    //variable declarations
    int num;
    char key;

    //code
    printf("\n\n");

    printf("Printing Even Numbers From 1 to 100 For Every User Input. Exitting the Loop When User Enters Character 'Q' or 'q' : \n\n");
    printf("Enter Character 'Q' or 'q' To Exit Loop : \n\n");

    for (num = 1; num <= 100; num++)
    {
        printf("\t%d\n", num);
        key = getch();
        if (key == 'Q' || key == 'q')
        {
            break;
        }
    }

    printf("\n\n");
    printf("EXITTING LOOP...");
    printf("\n\n");

    return(0);
}

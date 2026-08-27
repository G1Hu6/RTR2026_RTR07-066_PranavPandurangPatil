#include<stdio.h>

int main(void)
{
        // variable declarations
        int n;

        // code
        printf("\n\n");
        printf("Enter Value For N : ");
        scanf("%d", &n);

        // IF - ELSE - IF LADDER BEGINS FORM HERE ...
        if(n < 0)
        {
                printf("N = %d Is Less Than 0 (Negative) !!! \n\n", n);
        }
        else if((n > 0) && (n <= 100))
        {
                printf("N = %d Is Between 0 and 100 !!! \n\n", n);
        }
        else if((n > 100) && (n <= 200))
        {
                printf("N = %d Is Between 100 and 200 !!! \n\n", n);
        }
        else if((n > 200) && (n <= 300))
        {
                printf("N = %d Is Between 200 and 300 !!! \n\n", n);
        }
        else if((n > 300) && (n <= 400))
        {
                printf("N = %d Is Between 300 and 400 !!! \n\n", n);
        }
        else if((n > 400) && (n <= 500))
        {
                printf("N = %d Is Between 400 and 500 !!! \n\n", n);
        }
        else if(n > 500)
        {
                printf("N = %d Is Greater Than 500 !!!\n\n", n);
        }
	else 
	{
		printf("Invalid Value Entered !!! \n\n");
	}

        return(0);
}

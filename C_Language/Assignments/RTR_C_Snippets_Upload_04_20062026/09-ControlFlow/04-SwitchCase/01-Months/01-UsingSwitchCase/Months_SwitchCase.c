#include<stdio.h>

int main(void)
{
	// variable declarations
	int months;

	// code
	printf("\n\n");

	printf("Enter Number Of Months (1 to 12)");
	scanf("%d", &months);

	printf("\n\n");
	
	switch(months)
	{
		case 1: // like if
			printf("Month Number %d Is JANUARY !!!", months);
			break;
		case 2: // like else if
			printf("Month Number %d Is FEBRUARY !!!", months);
                        break;
		case 3: // like if
                        printf("Month Number %d Is MARCH !!!", months);
                        break;
                case 4: // like else if
                        printf("Month Number %d Is APRIL !!!", months);
                        break;
		case 5: // like if
                        printf("Month Number %d Is MAy !!!", months);
                        break;
                case 6: // like else if
                        printf("Month Number %d Is JUNE !!!", months);
                        break;
		case 7: // like if
                        printf("Month Number %d Is JULY !!!", months);
                        break;
                case 8: // like else if
                        printf("Month Number %d Is AUGUST !!!", months);
                        break;
		case 9: // like if
                        printf("Month Number %d Is SEPTEMBER !!!", months);
                        break;
                case 10: // like else if
                        printf("Month Number %d Is OCTOBER !!!", months);
                        break;
		case 11: // like if
                        printf("Month Number %d Is NOVEMBER !!!", months);
                        break;
                case 12: // like else if
                        printf("Month Number %d Is DECEMBER !!!", months);
                        break;
		default: // like ending OPTIONL 'else' ... just like terminating 'else' is optional in if-else-ladder, so it is the 'default' case optional in switch-case
			printf("Invalid Month %d Entered\n\n", months);
			break;
	}

	printf("Switch Case Block Complete !!!\n");
	return(0);

}

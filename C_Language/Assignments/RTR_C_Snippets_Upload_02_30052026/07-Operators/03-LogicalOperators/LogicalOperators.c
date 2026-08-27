#include<stdio.h>

int main(void)
{
        // variable declarations
        int firstNumber;
        int secondNumber;
        int thirdNumber;
        int resultValue;

        // code
        printf("\n\n");
        printf("Enter First Integer : ");
        scanf("%d", &firstNumber);

        printf("\n\n");
        printf("Enter Second Integer : ");
        scanf("%d", &secondNumber);

        printf("\n\n");
        printf("Enter Third Integer : ");
        scanf("%d", &thirdNumber);

        printf("\n\n");
        printf("If Answer = 0, It Is 'FALSE'.\n");
        printf("If Answer = 1, It Is 'TRUE'.\n");

        resultValue = (firstNumber <= secondNumber) && (secondNumber != thirdNumber);
        printf("LOGICAL AND (&&) : Answer is TRUE (1) If And Only If BOTH Conditions Are True. "
               "The Answer is FALSE (0), If Any One Or Both Conditions Are False.\n\n");
        printf("firstNumber = %d Is Less Than Or Equal To secondNumber = %d "
               "AND secondNumber = %d IS NOT Equal To thirdNumber = %d "
               "\t Answer = %d\n\n",
               firstNumber, secondNumber, secondNumber, thirdNumber, resultValue);

        resultValue = (secondNumber >= firstNumber) || (firstNumber == thirdNumber);
        printf("LOGICAL OR (||) : Answer is FALSE (0) If And Only If BOTH Conditions Are False. "
               "The Answer is TRUE (1), If Any One Or Both Conditions Are True.\n");
        printf("Either secondNumber = %d Is Greater Than Or Equal To firstNumber = %d "
               "OR firstNumber = %d Is Equal To thirdNumber = %d "
               "\t Answer = %d\n\n",
               secondNumber, firstNumber, firstNumber, thirdNumber, resultValue);

        resultValue = !firstNumber;
        printf("firstNumber = %d And Using Logical NOT (!) Operator On firstNumber Gives Result = %d\n\n",
               firstNumber, resultValue);

        resultValue = !secondNumber;
        printf("secondNumber = %d And Using Logical NOT (!) Operator On secondNumber Gives Result = %d\n\n",
               secondNumber, resultValue);

        resultValue = !thirdNumber;
        printf("thirdNumber = %d And Using Logical NOT (!) Operator On thirdNumber Gives Result = %d\n\n",
               thirdNumber, resultValue);

        resultValue = (!(firstNumber <= secondNumber) && !(secondNumber != thirdNumber));
        printf("Using Logical NOT (!) On (firstNumber <= secondNumber) And Also On "
               "(secondNumber != thirdNumber) And Then AND-ing Them Afterwards Gives Result = %d\n",
               resultValue);

        printf("\n\n");

        resultValue = (!(secondNumber >= firstNumber) || (firstNumber == thirdNumber));
        printf("Using Logical NOT (!) On Entire Logical Expression "
               "(secondNumber >= firstNumber) || (firstNumber == thirdNumber) "
               "Gives Result = %d\n", resultValue);

        printf("\n\n");

        return (0);
}

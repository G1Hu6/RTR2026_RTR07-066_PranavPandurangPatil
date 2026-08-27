#include<stdio.h>

int main(void)
{
        // variable declaration
        int firstNumber;
        int secondNumber;
        int resultValue;

        // code
        printf("\n\n");
        printf("Enter One Integer : ");
        scanf("%d", &firstNumber);

        printf("\n\n");
        printf("Enter One Integer : ");
        scanf("%d", &secondNumber);

        printf("\n\n");
        printf("If Answer = 0, It Is 'FALSE'.\n");
        printf("If Answer = 1, It Is 'TRUE'.\n\n");

        resultValue = (firstNumber < secondNumber);
        printf("(firstNumber < secondNumber) A = %d Is Less Than B = %d \t Answer = %d\n",
               firstNumber, secondNumber, resultValue);

        resultValue = (firstNumber > secondNumber);
        printf("(firstNumber > secondNumber) A = %d Is Greater Than B = %d \t Answer = %d\n",
               firstNumber, secondNumber, resultValue);

        resultValue = (firstNumber <= secondNumber);
        printf("(firstNumber <= secondNumber) A = %d Is Less Than Or Equal To B = %d \t Answer = %d\n",
               firstNumber, secondNumber, resultValue);

        resultValue = (firstNumber >= secondNumber);
        printf("(firstNumber >= secondNumber) A = %d Is Greater Than Or Equal To B = %d \t Answer = %d\n",
               firstNumber, secondNumber, resultValue);

        resultValue = (firstNumber == secondNumber);
        printf("(firstNumber == secondNumber) A = %d Is Equal To B = %d \t Answer = %d\n",
               firstNumber, secondNumber, resultValue);

        resultValue = (firstNumber != secondNumber);
        printf("(firstNumber != secondNumber) A = %d Is NOT Equal To B = %d \t Answer = %d\n",
               firstNumber, secondNumber, resultValue);

        return (0);
}


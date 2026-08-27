#include <stdio.h> //for printf()
#include <conio.h> //for getch()

// ASCII Values For 'A' to 'Z' => 65 to 90
#define CHAR_ALPHABET_UPPER_CASE_BEGINNING 65
#define CHAR_ALPHABET_UPPER_CASE_ENDING 90

// ASCII Values For 'a' to 'z' => 97 to 122
#define CHAR_ALPHABET_LOWER_CASE_BEGINNING 97
#define CHAR_ALPHABET_LOWER_CASE_ENDING 122

// ASCII Values For '0' to '9' => 48 to 57
#define CHAR_DIGIT_BEGINNING 48
#define CHAR_DIGIT_ENDING 57

int main(void)
{
    //variable declarations
    char letter;
    int ascii;

    //code
    printf("\n\n");

    printf("Enter Character : ");
    letter = getch();

    printf("\n\n");

    if ((letter == 'A' || letter == 'a') ||
        (letter == 'E' || letter == 'e') ||
        (letter == 'I' || letter == 'i') ||
        (letter == 'O' || letter == 'o') ||
        (letter == 'U' || letter == 'u'))
    {
        printf("Character '%c' Entered By You, Is A VOWEL CHARACTER From The English Alphabet !!!\n\n", letter);
    }
    else
    {
        ascii = (int)letter;

        //If The Character Has ASCII Value Between 65 AND 90 OR Between 97 AND
        //122, It Is Still A Letter Of The Alphabet, But It Is A 'CONSONANT', and
        //NOT a VOWEL...
        if ((ascii >= CHAR_ALPHABET_UPPER_CASE_BEGINNING &&
             ascii <= CHAR_ALPHABET_UPPER_CASE_ENDING) ||
            (ascii >= CHAR_ALPHABET_LOWER_CASE_BEGINNING &&
             ascii <= CHAR_ALPHABET_LOWER_CASE_ENDING))
        {
            printf("Character '%c' Entered By You, Is A CONSONANT CHARACTER From The English Alphabet !!!\n\n", letter);
        }
        else if (ascii >= CHAR_DIGIT_BEGINNING &&
                 ascii <= CHAR_DIGIT_ENDING)
        {
            printf("Character '%c' Entered By You, Is A DIGIT CHARACTER !!!\n\n", letter);
        }
        else
        {
            printf("Character '%c' Entered By You, Is A SPECIAL CHARACTER !!!\n\n", letter);
        }
    }

    return(0);
}

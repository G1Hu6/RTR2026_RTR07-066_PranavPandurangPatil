#include<stdio.h> // for printf()
#include<conio.h> // for getch()

// ASCII Values For 'A' to 'Z' => 65 to 90
#define CHAR_ALPHA_UPPEAR_CASE_START 65
#define CHAR_ALPHA_UPPEAR_CASE_END 90

// ASCII Values For 'a' to 'z' => 97 to 122
#define CHAR_ALPHA_LOWER_CASE_START 97
#define CHAR_ALPHA_LOWER_CASE_END 122

// ASCII Values For '0' to '9' => 48 to 57
#define CHAR_DIGIT_START 48
#define CHAR_DIGIT_END 57

int main(void)
{
	// variable declarations
	char ch;
	int ch_val;

	// code
	printf("\n\n");

	printf("Enter Character : ");
	ch = getch();

	printf("\n\n");

	switch(ch)
	{
		// FALL THROUGH CONDITION
		case 'A':
		case 'a':

		case 'E':
		case 'e':

		case 'I':
		case 'i':

		case 'O':
		case 'o':

		case 'U':
		case 'u':
			printf("Character \%c\' Entered By You, Is A VOWEL !!! \n\n", ch);
			break;
		default:
			ch_val = (int)ch;
	

			if((ch_val >= CHAR_ALPHA_UPPEAR_CASE_START && ch_val <= CHAR_ALPHA_UPPEAR_CASE_END) || (ch_val >= CHAR_ALPHA_LOWER_CASE_START && ch_val <= CHAR_ALPHA_LOWER_CASE_END))
			{
				printf("Character \'%c\' Entered By You, Is A CONSONANT CHARATER From The English Alphabet !!!\n\n", ch);
			}

			else if(ch_val >= CHAR_DIGIT_START && ch_val <= CHAR_DIGIT_END)
			{
				printf("Character \'%c\' Entered By You, Is A DIGIT CHARATER!!!\n\n", ch);
			}

			else
			{
				printf("Character \'%c\' Entered By You, Is A SPECIAL CHARATER!!!\n\n", ch);
			}
			break;
	}

	printf("Switch Case Block Complete !!!\n");
	
	return(0);
}

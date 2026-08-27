#include<stdio.h>
#define PI 3.1415926535897932
#define RTR_STR "RTR 7"

// If First Constant Is Not Assigned A Value. It Is Assumed To Be 0 i.e.: 'SUNDAY' Will Be 0
// And The Rest Of The Constants Are Assigned Consecutive Integer Values From 0 onwards.

// Un-named enums

enum
{
	SUNDAY,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
};

enum
{
	JANUARY,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

// Named enums
enum Numbers
{
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE = 5,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN
};

enum boolean
{
	TRUE = 1,
	FALSE = 0
};

int main(void)
{
	// local constant declarations
    const double epsilon = 0.000001;

    // code
    printf("\n\n");
    printf("Local Constant Epsilon = %lf\n\n", epsilon);

    // Days
    printf("Sunday Is Day Number = %d\n", SUNDAY);
    printf("Monday Is Day Number = %d\n", MONDAY);
    printf("Tuesday Is Day Number = %d\n", TUESDAY);
    printf("Wednesday Is Day Number = %d\n", WEDNESDAY);
    printf("Thursday Is Day Number = %d\n", THURSDAY);
    printf("Friday Is Day Number = %d\n", FRIDAY);
    printf("Saturday Is Day Number = %d\n\n", SATURDAY);

    // Numbers
    printf("One Is Enum Number = %d\n", ONE);
    printf("Two Is Enum Number = %d\n", TWO);
    printf("Three Is Enum Number = %d\n", THREE);
    printf("Four Is Enum Number = %d\n", FOUR);
    printf("Five Is Enum Number = %d\n", FIVE);
    printf("Six Is Enum Number = %d\n", SIX);
    printf("Seven Is Enum Number = %d\n", SEVEN);
    printf("Eight Is Enum Number = %d\n", EIGHT);
    printf("Nine Is Enum Number = %d\n", NINE);
    printf("Ten Is Enum Number = %d\n\n", TEN);

    // Months
    printf("January Is Month Number = %d\n", JANUARY);
    printf("February Is Month Number = %d\n", FEBRUARY);
    printf("March Is Month Number = %d\n", MARCH);
    printf("April Is Month Number = %d\n", APRIL);
    printf("May Is Month Number = %d\n", MAY);
    printf("June Is Month Number = %d\n", JUNE);
    printf("July Is Month Number = %d\n", JULY);
    printf("August Is Month Number = %d\n", AUGUST);
    printf("September Is Month Number = %d\n", SEPTEMBER);
    printf("October Is Month Number = %d\n", OCTOBER);
    printf("November Is Month Number = %d\n", NOVEMBER);
    printf("December Is Month Number = %d\n\n", DECEMBER);

    // Boolean values
    printf("Value Of TRUE Is = %d\n", TRUE);
    printf("Value Of FALSE Is = %d\n\n", FALSE);

    // PI Macro
    printf("PI Macro Value = %.16lf\n\n", PI);
    printf("Area Of Circle Of Radius 2 Units = %lf\n\n", PI * 2.0 * 2.0);

    // String Macro
    printf("%s\n\n", RTR_STR);

    return (0);	
}

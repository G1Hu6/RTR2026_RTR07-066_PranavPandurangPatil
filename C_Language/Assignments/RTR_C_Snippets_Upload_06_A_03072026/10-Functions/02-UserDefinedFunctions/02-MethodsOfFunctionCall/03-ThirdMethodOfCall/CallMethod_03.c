#include<stdio.h>

int main(int argc, char* argv[], char* envp[])
{
	// function prototypes
	void Country(void);

	// code
        Country();

	return(0);
}

void My(void)
{
	printf("\n\n");
	printf("My ");
}

void Name(void)
{
	void My(void);
	My();

        printf("\n\n");
        printf("Name ");
}


void FirstName(void)
{
	void Is(void);
	Is();

        printf("\n\n");
        printf("Pranav");
}

void Is(void)
{
	void Name(void);
	Name();

        printf("\n\n");
        printf("Is");
}


void MiddleName(void)
{
        void FirstName(void);
	FirstName();

	printf("\n\n");
        printf("Pandurang");
}


void LastName(void)
{
        void MiddleName(void);
	MiddleName();

	printf("\n\n");
        printf("Patil");
}


void OfRTR(void)
{
	void LastName(void);
        LastName();

        printf("\n\n");
        printf("of RTR07");
}


void Country(void)
{
        void OfRTR(void);
	OfRTR();

	printf("\n\n");
        printf("I Live in Kolhapur");
	printf("\n\n");
}


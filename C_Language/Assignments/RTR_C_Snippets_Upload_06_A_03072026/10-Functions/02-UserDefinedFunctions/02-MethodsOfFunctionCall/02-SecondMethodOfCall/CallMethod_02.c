#include<stdio.h>

int main(int argc, char* argv[], char* envp[])
{
	// function prototypes
	void DisplyInfo(void);
	void Country(void);

	// code
	DisplyInfo();
        Country();

	return(0);
}

void DisplyInfo(void) 
{
	// function prototype
	void My(void);
	void Name(void);
	void Is(void);
	void FirstName(void);
	void LastName(void);
	void MiddleName(void);
	void OfRTR(void);

	// code
	
	// function calls
	My();
	Name();
	Is();
	FirstName();
	MiddleName();
	LastName();
	OfRTR();
}

void My(void)
{
	printf("\n\n");
	printf("My ");
}

void Name(void)
{
        printf("\n\n");
        printf("Name ");
}


void FirstName(void)
{
        printf("\n\n");
        printf("Pranav");
}

void Is(void)
{
        printf("\n\n");
        printf("Is");
}


void MiddleName(void)
{
        printf("\n\n");
        printf("Pandurang");
}


void LastName(void)
{
        printf("\n\n");
        printf("Patil");
}


void OfRTR(void)
{
        printf("\n\n");
        printf("of RTR07");
}


void Country(void)
{
        printf("\n\n");
        printf("I Live in Kolhapur");
	printf("\n\n");
}

#include<stdio.h>

int main(void)
{
	int arr3D[3][3] = {
		{1, 2 ,3},
		{5, 6 ,8},
		{9, 1, 12}};

	printf("Printing Address :- ");
	printf("\n\n");
	
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++)
		{
			//for(int k = 0; k < 2; k++)
			//{
				printf("%p \n", &arr3D[i][j]);
			//}
		}
	}
}

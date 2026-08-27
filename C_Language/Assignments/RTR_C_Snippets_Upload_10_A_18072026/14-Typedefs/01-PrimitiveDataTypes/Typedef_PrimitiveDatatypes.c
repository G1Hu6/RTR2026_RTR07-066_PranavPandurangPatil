#include <stdio.h>

typedef int MY_INT;

int main(void)
{
	//function prototype
	MY_INT Add(MY_INT, MY_INT);

	//Typedefs
	typedef int MY_INT;
	typedef float PPP_FLOAT;
	typedef char CHARACTER;
	typedef double MY_DOUBLE;

	typedef unsigned int UINT;
	typedef UINT HANDLE;
	typedef HANDLE HWND;
	typedef HANDLE HINSTANCE;

	//variable declaraions
	MY_INT a = 10, i;
	MY_INT iArr[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };

	PPP_FLOAT f_ppp = 30.9f;
	const PPP_FLOAT f_ppp_pi = 3.14f;

	CHARACTER ch = '*';
	CHARACTER str1[] = "Hello";
	CHARACTER strArr[3][10] = { "RTR", "Batch", "2026-2027" };

	MY_DOUBLE d = 8.041997;

	UINT u_val = 3456;
	HANDLE h_val = 987;
	HWND w_val = 9876;
	HINSTANCE inst_val = 14466;

	MY_INT x, y, ret;

	//code
	printf("\n\n");
	printf("Type MY_INT variable a = %d\n", a);

	printf("\n\n");
	for (i = 0; i < (sizeof(iArr) / sizeof(int)); i++)
	{
		printf("Type MY_INT array variable iArr[%d] = %d\n", i, iArr[i]);
	}
	printf("\n\n");

	printf("\n\n");
	printf("Type PPP_FLOAT variable f = %f\n", f_ppp);
	printf("Type PPP_FLOAT constant f_ppp_pi = %f\n", f_ppp_pi);

	printf("\n\n");
	printf("Type MY_DOUBLE variable d = %lf\n", d);

	printf("\n\n");
	printf("Type CHARACTER variable ch = %c\n", ch);

	printf("\n\n");
	printf("Type CHARACTER array variable str1 = %s\n", str1);

	printf("\n\n");
	for (i = 0; i < (sizeof(strArr) / sizeof(strArr[0])); i++)
	{
		printf("%s\t", strArr[i]);
	}
	printf("\n\n");

	printf("\n\n");
	printf("Type UINT variable u_val = %u\n", u_val);
	printf("Type HANDLE variable h_val = %u\n", h_val);
	printf("Type HWND variable w_val = %u\n", w_val);
	printf("Type HINSTANCE variable inst_val = %u\n", inst_val);
	printf("\n\n");

	x = 90;
	y = 30;

	ret = Add(x, y);
	printf("ret = %d\n\n", ret);

	return(0);
}

MY_INT Add(MY_INT a, MY_INT b)
{
	//variable declaraions
	MY_INT c;

	//code
	c = a + b;
	return(c);
}


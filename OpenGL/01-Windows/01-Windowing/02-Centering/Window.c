/*
 * ------------------------------------------------------------- Holy Code ---------------------------------------------------------
 * Centering the Window
 * Shri Ganeshay Namah
 */

// header files
#include<windows.h>

// MACROS
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // declaration

// entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) // declarator
{
	// variable declarations (local variables)
	WNDCLASSEX wndclass; // WNDCLASSEX --> struct
	HWND hwnd = NULL;
	MSG msg; // MSG --> struct
	TCHAR szAppName[] = TEXT("RTR07-PPP"); // TEXT --> Macro
	
	// code
	// we have to initialize 12 members of WNDCLASSEX struct
	// 1.WNDCLASSEX struct initializatioon
	wndclass.cbSize = sizeof(WNDCLASSEX);	// 1st member
	wndclass.style = CS_HREDRAW | CS_VREDRAW; // 2nd
	wndclass.cbClsExtra = 0; // 3rd
	wndclass.cbWndExtra = 0; // 4th
	wndclass.lpfnWndProc = WndProc; // 5th (function pointer)
	wndclass.hInstance = hInstance; // 6th
	wndclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH); // 7th // GETStockObject is first WIN32 API out of 3lack APIs.
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // 8th // 2nd WIN32
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW); // 9th // 3rd WIN32 API
	wndclass.lpszClassName = szAppName; // 10th
	wndclass.lpszMenuName = NULL; // 11th
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // 12th
							    
	// 2.register above WNDCLASS
	RegisterClassEx(&wndclass); // 4th WIN32 API
	
	// Centering
	int iScreenWidth = GetSystemMetrics(SM_CXSCREEN); // System Metrix Count X Screen --> Width
	int iScreenHeight = GetSystemMetrics(SM_CYSCREEN); // System Metrix Count Y Screen --> Height

	// 3.create the Window
	hwnd = CreateWindow(
		szAppName, 
		TEXT("My First RTR07 Window Program : Pranav P Patil"), // glutCreateWindow("...")
		WS_OVERLAPPEDWINDOW,
		(iScreenWidth / 2) - (WIN_WIDTH / 2),	// Window X Coordinate
		(iScreenHeight / 2) - (WIN_HEIGHT / 2),	// Window Y Coordinate
		WIN_WIDTH,	// Window Width 
		WIN_HEIGHT,  // Window Height
		NULL,
		NULL,
		hInstance,
		NULL
	); // 5th Win32 API it has 11 parameters

	// 4.show Window	
	ShowWindow(hwnd, iCmdShow); // 6th Win32 API
	
	// 5.update Window to paint its background
	UpdateWindow(hwnd);

	// message loop
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) // declarator
{
	// code
	switch(iMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}


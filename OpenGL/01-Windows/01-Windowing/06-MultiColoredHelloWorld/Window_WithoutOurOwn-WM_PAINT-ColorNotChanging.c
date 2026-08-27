/*
 * ------------------------------------------------------------- Holy Code ---------------------------------------------------------
 * MultiColored Hello World
 * Shri Ganeshay Namah
 */

// header files
#include<windows.h>
// my header file
#include "Window.h"

// MACROS
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // declaration

// global variable declarations
int iPaintFlag = -1;

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
	wndclass.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH); // 7th // GETStockObject is first WIN32 API out of 3lack APIs.
	
	// My ICON
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYCHAKARAICON)); // 8th // 2nd WIN32
	
	wndclass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(MYCHAKARAICON)); // 9th // 3rd WIN32 API
	wndclass.lpszClassName = szAppName; // 10th
	wndclass.lpszMenuName = NULL; // 11th
	wndclass.hIconSm = LoadIcon(MAKEINTRESOURCE(MYCHAKARAICON), IDI_APPLICATION); // 12th
							    
	// 2.register above WNDCLASS
	RegisterClassEx(&wndclass); // 4th WIN32 API
	
	// Centering
	int iScreenWidth = GetSystemMetrics(SM_CXSCREEN); // System Metrix Count X Screen --> Width
	int iScreenHeight = GetSystemMetrics(SM_CYSCREEN); // System Metrix Count Y Screen --> Height

	// 3.create the Window
	hwnd = CreateWindow(
		szAppName, 
		TEXT("My RTR07 Hello World Program : Pranav P Patil"), // glutCreateWindow("...")
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
	// variable declarations
	HDC hdc; // Handle to DC(Device Context) Graphics Hardware Device
        PAINTSTRUCT ps;
        RECT rc;
        TCHAR str[] = TEXT("Hello World !!!");
	// code
	switch(iMsg)
	{
		case WM_CREATE: 
			break;
		case WM_SETFOCUS:
                        break;
		case WM_KILLFOCUS:
                        break;
		case WM_SIZE:
                        break;
		case WM_KEYDOWN: // key press message
                        switch(wParam)
			{
				case VK_ESCAPE: // virtual key code
					break;
				default:
					break;				
			}
                        break;
		case WM_CHAR: // alphabate press message
			switch(wParam)
			{
				case 'R':
				case 'r':
					iPaintFlag = 1;
					break;
				case 'G':
                                case 'g':
					iPaintFlag = 2;
                                        break;
				case 'B':
                                case 'b':
					iPaintFlag = 3;
                                        break;
				case 'C':
                                case 'c':
					iPaintFlag = 4;
                                        break;
				case 'M':
                                case 'm':
					iPaintFlag = 5;
                                        break;
				case 'Y':
                                case 'y':
					iPaintFlag = 6;
                                        break;
				case 'F':
				case 'f':
					break;
				default:
					iPaintFlag = -1;
					break;
			}
			break;
		case WM_PAINT: // 
			GetClientRect(hwnd, &rc); // Give me Client Rectangle dimentions
			// hdc = GetDC(hwnd); // SDK SDK , Give me Device Context Handle(Graphics Specialist)
			hdc = BeginPaint(hwnd, &ps); // When you handle WM_PAINT Dont create hdc by GetDC is the convention. 2nd parameter is out parameter, OS fill its all 6 members of PAINTSTRUCT in which 3 members are reserverd rest are hdc, rcPaint(which rectanngle is used for painting), fErase(background repaint is true or false) f for flag
			SetBkColor(hdc, RGB(0, 0, 0)); // Set background Color (If not given then bydefault background color is WHITE)
			if(iPaintFlag == 1)
			{
				SetTextColor(hdc, RGB(255, 0, 0)); // RED color
			}
			else if(iPaintFlag == 2)
			{
				SetTextColor(hdc, RGB(0, 255, 0)); // GREEN color
			}
			else if(iPaintFlag == 3)
			{
				SetTextColor(hdc, RGB(0, 0, 255)); // BLUE color
			}
			else if(iPaintFlag == 4)
			{
				SetTextColor(hdc, RGB(0, 255, 255)); // CYAN color
			}
			else if(iPaintFlag == 5)
			{
				SetTextColor(hdc, RGB(255, 0, 255)); // MAGENTA color
			}
			else if(iPaintFlag == 6)
			{
				SetTextColor(hdc, RGB(255, 255, 0)); // YELLOW color
			}
			else
			{
				SetTextColor(hdc, RGB(255, 255, 255)); // WHITE color
			}

			DrawText(
				 hdc, 
				 str, 
				 -1, // 3rd parameter -> how many text letters are visible.
				 &rc, // Rectangle
				 DT_SINGLELINE | DT_CENTER | DT_VCENTER // Draw Text Single Line | Hprzontical Center | Verticle Center
			);
			// ReleaseDC(hwnd, hdc);
			EndPaint(hwnd, &ps); // Release Specialist
			break;
		case WM_CLOSE:
			break;
		case WM_DESTROY:
			PostQuitMessage(18);
			break;
		default:
			break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}


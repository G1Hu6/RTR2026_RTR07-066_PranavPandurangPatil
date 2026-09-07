/*
 * ------------------------------------------------------------- Holy Code ---------------------------------------------------------
 * Full Screen
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
HWND ghwnd = NULL;
BOOL bFullScreen = FALSE;
DWORD dwStyle;
WINDOWPLACEMENT wpPrev; // previous placement

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
	// WNDCLASSEX struct initializatioon
	wndclass.cbSize = sizeof(WNDCLASSEX);	// 1st member
	wndclass.style = CS_HREDRAW | CS_VREDRAW; // 2nd
	wndclass.cbClsExtra = 0; // 3rd
	wndclass.cbWndExtra = 0; // 4th
	wndclass.lpfnWndProc = WndProc; // 5th (function pointer)
	wndclass.hInstance = hInstance; // 6th
	wndclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH); // 7th // GETStockObject is first WIN32 API out of 3lack APIs.
	
	// My ICON
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYCHAKARAICON)); // 8th // 2nd WIN32
	
	wndclass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(MYCHAKARAICON)); // 9th // 3rd WIN32 API
	wndclass.lpszClassName = szAppName; // 10th
	wndclass.lpszMenuName = NULL; // 11th
	wndclass.hIconSm = LoadIcon(MAKEINTRESOURCE(MYCHAKARAICON), IDI_APPLICATION); // 12th
							    
	// register above WNDCLASS
	RegisterClassEx(&wndclass); // 4th WIN32 API
	
	// Centering
	int iScreenWidth = GetSystemMetrics(SM_CXSCREEN); // System Metrix Count X Screen --> Width
	int iScreenHeight = GetSystemMetrics(SM_CYSCREEN); // System Metrix Count Y Screen --> Height

	// create the Window EX for exteded style
	hwnd = CreateWindowEx( // step 1: use extended style
		WS_EX_APPWINDOW, // step 1: APPWINDOW is special kind of window in the topmost window in z order (above taskbar)
		szAppName, 
		TEXT("My First RTR07 Window Program : Pranav P Patil"), // glutCreateWindow("...")
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE, // in fullscreen if child, siblings window comes between so clip child windows
		(iScreenWidth / 2) - (WIN_WIDTH / 2),	// Window X Coordinate
		(iScreenHeight / 2) - (WIN_HEIGHT / 2),	// Window Y Coordinate
		WIN_WIDTH,	// Window Width 
		WIN_HEIGHT,  // Window Height
		NULL,
		NULL,
		hInstance,
		NULL
	); // 5th Win32 API it has 11 parameters

	// Set Global window handle
	ghwnd = hwnd;

	// show Window	
	ShowWindow(hwnd, iCmdShow); // 6th Win32 API
	
	// update Window to paint its background
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
	// function declarations
	void ToggleFullScreen(void);
	// code
	switch(iMsg)
	{
		case WM_CREATE:
			// 
			memset(&wpPrev, 0, sizeof(WINDOWPLACEMENT)); // set all parameters to 0;
			wpPrev.length = sizeof(WINDOWPLACEMENT); // lenght is initialized to sizeof(WINDOWPLACEMENT)
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
				case 'F':
				case 'f':
					if(!bFullScreen)
					{
						ToggleFullScreen();
						bFullScreen = TRUE;
					}else
					{
						ToggleFullScreen();
						bFullScreen = FALSE;
					}
					break;
				default:
					break;
			}
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

void ToggleFullScreen()
{
	// variable declarations
	MONITORINFO mi;

	// code
	if(!bFullScreen) // step 2
	{
		dwStyle = GetWindowLong(
				ghwnd, // global handle
				GWL_STYLE // 
		); // step 3: Get current window style

		// OR
		// GetWindowLongPtr(...) // new way

		if(dwStyle & WS_OVERLAPPEDWINDOW) // step 4: check WS_OVERLAPPEDWINDOW is present 
		{
			memset(&mi, 0, sizeof(MONITORINFO));
			mi.cbSize = sizeof(MONITORINFO);
			// step 5 and 6: Get current window placement and monitor info
			if(GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				// MONITORINFOF_PRIMARY -> primary monitor in case you have more monitor.
				// MonitorFromWindow return HMONITOR, GetWindowPlacement and GetMonitorInfo retrun bool
				SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW); // step 8: remove WS_OVERLAPPEDWINDOW
				//step 9:
				SetWindowPos(
					ghwnd, // which window
					HWND_TOP, // how
					mi.rcMonitor.left, // x coordinate
					mi.rcMonitor.top, // y coordinate
					(mi.rcMonitor.right - mi.rcMonitor.left), // width
					(mi.rcMonitor.bottom - mi.rcMonitor.top), // height
					SWP_NOZORDER | SWP_FRAMECHANGED // z order do not adject | frame changed (NC area also)
				);
			}
		}
		ShowCursor(FALSE); // step 10: hide cursor
	}
	else // step 12: already full screen
	{
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW); 

		SetWindowPlacement(ghwnd, &wpPrev);

		SetWindowPos(
			ghwnd,
			HWND_TOP,
			0, // if we call SetWindowPlacement then no need to give coordinates
			0,
			0,
			0,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED
			// SWP_NOMOVE -> no not disturb placement given by SetWindowPlacement
			// SWP_NOSIZE -> do not change size
			// SWP_NOOWNERZORDER -> tooptip , dialog boxes are owned window
		);

		ShowCursor(TRUE);
	}
}


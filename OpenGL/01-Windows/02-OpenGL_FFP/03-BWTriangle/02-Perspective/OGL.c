/*
 * ------------------------------------------------------------- Holy Code ---------------------------------------------------------
 * Perspective Triangle
 * Shri Ganeshay Namah
 */

// header files- all this headers files are just like #include<GL/freeglut.h>
#include<windows.h>
#include<stdio.h> // no need alredy sub included in <windows.h>. but file I/O functions declared in this
#include<stdlib.h> // for exit(0)

// OpenGL related header files
#include<gl/GL.h>
#include<gl/GLU.h> // graphic lib untility

// my header file
#include "OGL.h"

// Link with OpenGL import lib
// or link.exe OGL.obj User32.lib GDI32.lib opengl32.lib /SUBSYSTEM:WINDOWS
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "GLU32.lib")

// MACROS
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// global function declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // declaration

// global variable declarations
HWND ghwnd = NULL;
HDC ghdc = NULL; // Device Context Handle
HGLRC ghrc = NULL; // Graphic Lib Rendering Context Handle
BOOL bFullScreen = FALSE;
DWORD dwStyle;
WINDOWPLACEMENT wpPrev; // previous placement
FILE* gpFile = NULL;

BOOL bActiveWindow = FALSE;
BOOL bEscapeKeyIsPressed = FALSE;

// entry point function - freeglut call WinMin internally inisde its main
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) // declarator
{

	//functions declarations (stub functions) 
	int Initialize(void); // initialize all variables
	void Uninitialize(void);
	void Render(void); // Display/Draw/Render
	void Update(void); // Animation

	// variable declarations (local variables)
	WNDCLASSEX wndclass; // WNDCLASSEX --> struct - inside glutInit(&args, argv);
	HWND hwnd = NULL;
	MSG msg; // MSG --> struct
	TCHAR szAppName[] = TEXT("RTR07-PPP"); // TEXT --> Macro
	BOOL bDone = FALSE; // game loop variable

	// code
	// we have to initialize 12 members of WNDCLASSEX struct
	// WNDCLASSEX struct initializatioon
	
	// Create Log File
	gpFile = fopen("Log.txt", "w"); // w -> write
	if(gpFile == NULL)
	{
		MessageBox(NULL, TEXT("Log file is not created!!! ERROR while creating"), TEXT("Error"), MB_OK);
		exit(0);
	}else
	{
		fprintf(gpFile, "--------------------------------------------- Log File ---------------------------------------------\n\n");
		fprintf(gpFile, "PPP: Program Started Successfully...\n");
	}

	wndclass.cbSize = sizeof(WNDCLASSEX);	// 1st member
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // CS_OWNDC -> fixed and nondiscardable window Device Context
	wndclass.cbClsExtra = 0; // 3rd
	wndclass.cbWndExtra = 0; // 4th
	wndclass.lpfnWndProc = WndProc; // 5th (function pointer)
	wndclass.hInstance = hInstance; // 6th
	wndclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH); // 7th // GETStockObject is first WIN32 API out of 3lack APIs.
	
	// My ICON
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYCHAKARAICON)); // 8th // 2nd WIN32
	
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW); // 9th // 3rd WIN32 API
	wndclass.lpszClassName = szAppName; // 10th
	wndclass.lpszMenuName = NULL; // 11th
	wndclass.hIconSm = LoadCursor(hInstance, MAKEINTRESOURCE(MYCHAKARAICON)); // 12th
							    
	// register above WNDCLASS - inside glutInit(&args, argv);
	RegisterClassEx(&wndclass); // 4th WIN32 API
	
	// Centering
	int iScreenWidth = GetSystemMetrics(SM_CXSCREEN); // System Metrix Count X Screen --> Width
	int iScreenHeight = GetSystemMetrics(SM_CYSCREEN); // System Metrix Count Y Screen --> Height

	/* glutInitWindowSize(800, 600); 
	glutInitWindowPosition(100, 100);
	glutCreateWindow("My First RTR-7 Program : Harshal Wadne");
	
	- CreateWindow(), ShowWindow(), UpdateWindow()
	*/

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

	int iResult = Initialize();
	if(iResult != 0)
	{
		fprintf(gpFile, "PPP:WinMain():Initialize() function is failed \n");
		DestroyWindow(hwnd); // WM_DESTROY message send
		fprintf(gpFile, "PPP:WinMain():DestroyWindow() function called and WM_DESTROY message is sent \n");
		hwnd = NULL;
	}
	else
	{
		fprintf(gpFile, "PPP:WinMain():Initialize() function is success \n");
	}


	// show Window	
	ShowWindow(hwnd, iCmdShow); // 6th Win32 API
	
	// update Window to paint its background
	UpdateWindow(hwnd);

	SetForegroundWindow(hwnd);

	SetFocus(hwnd); // WM_SETFOCUS message is send
	fprintf(gpFile, "PPP:WinMain():SetFocus() function is called \n");

	// Game Loop
	while(bDone == FALSE)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				bDone = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if(bActiveWindow == TRUE)
			{
				if(bEscapeKeyIsPressed == TRUE)
				{
					bDone = TRUE;
				}
		
				// Render/Draw only when window is Active
				Render(); // After escape one frame is allowed for smooth transition.

				// Update
				Update();
			}
		}
	}
	
	Uninitialize(); 

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) // declarator
{
	// function declarations
	void Resize(int, int);
	void Uninitialize(void);
	void ToggleFullScreen(void);
	

	// code
	switch(iMsg)
	{
		case WM_CREATE:
			fprintf(gpFile, "PPP:WndProc() WM_CREATE: window created successfully...\n");
			memset(&wpPrev, 0, sizeof(WINDOWPLACEMENT)); // set all parameters to 0;
			wpPrev.length = sizeof(WINDOWPLACEMENT); // lenght is initialized to sizeof(WINDOWPLACEMENT)
			break;
		case WM_SETFOCUS:
			bActiveWindow = TRUE;
			fprintf(gpFile, "PPP:WndProc() WM_SETFOCUS: message and bActiveWindow = %d \n", bActiveWindow);
			break;
		case WM_KILLFOCUS:
			bActiveWindow = FALSE;
			fprintf(gpFile, "PPP:WndProc() WM_KILLFOCUS: message and bActiveWindow = %d \n", bActiveWindow);
                        break;
		case WM_SIZE:
			Resize(LOWORD(lParam), HIWORD(lParam));
			fprintf(gpFile, "PPP:WndProc() WM_SIZE: message \n");
                        break;
		case WM_KEYDOWN: // key press message
                        switch(wParam)
			{
				case VK_ESCAPE: // virtual key code
					bEscapeKeyIsPressed = TRUE;
					fprintf(gpFile, "PPP:WndProc() WM_KEYDOWN: VK_ESCAPE key pressed\n");
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
					fprintf(gpFile, "PPP:WndProc() WM_CHAR: F/f key pressed\n");
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
			fprintf(gpFile, "PPP:WndProc() WM_CLOSE: message created\n");
			Uninitialize();
			break;
		case WM_DESTROY:
			fprintf(gpFile, "PPP:WndProc() WM_DESTROY: message created\n");
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

// stub functions
int Initialize()
{
	// function declarations
	void Resize(int, int);

	// variable declarations
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex;

	// code
	// fprintf(gpFile, "PPP:Initialize() function called... \n");
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	// or 
	// ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR)); Win32 API

	// mapping glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR); // n -> short
	pfd.nVersion = 1; // convention always 1
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER; // PFD_DRAW_TO_WINDOW -> To Draw on Window | PFD_SUPPORT_OPENGL -> OpenGL la suppored | PFD_DOUBLEBUFFER -> faster and more realistic (chota battachan)
	pfd.iPixelType = PFD_TYPE_RGBA; // R G B Alpha type 32 bit pixel
	pfd.cRedBits = 8; // c-> count
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;

	// get Specialist
	ghdc = GetDC(ghwnd);

	if(ghdc == NULL)
	{
		return (-1); // fail
	}

	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd); // 1 based indexing, if 0 then it is failed to get index
	if(iPixelFormatIndex == 0) 
	{
		return (-2); // fail
	}

	if(SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		return (-3); // fail
	}

	// WGL (Windows Graphic Library) -> Bridging API
	ghrc = wglCreateContext(ghdc);
	if(ghrc == NULL)
	{
		return (-4); // fail
	}

	if(wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		return (-5); // fail
	}

	// OpenGL
	// Choose Screen Clear Color as Blue
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // RGBA 2^16 shades
	// Worm Up resize Call
	Resize(WIN_WIDTH, WIN_HEIGHT);

	return (0); // success
}

void Resize(int width, int height)
{
	// code
	fprintf(gpFile, "PPP:Resize() function called... \n");
	if(height <= 0)
	{
		height = 1; // ignore -ve height because to avoid infinity in divide by 0
	}

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Perspective Projection
	gluPerspective(
		45.0f, // degree angle FOVy
		((GLfloat)width / (GLfloat)height), // ratio
		0.1f, // near
		100.0f // far
	);
}

void Render()
{
	// code
	// fprintf(gpFile, "PPP:Render() function called... \n");
	glClear(GL_COLOR_BUFFER_BIT); // Actual Color is given by this call, GL_COLOR_BUFFER_BIT -> every bit
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	// Draw Tringle
	glTranslatef(0.0f, 0.0f, -3.0f);
	glBegin(GL_TRIANGLES);
	
	glVertex3f(0.0f, 1.0f, 0.0f);
	
	glVertex3f(-1.0f, -1.0f, 0.0f);
	
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();

	// 2 Double Buffring
	SwapBuffers(ghdc);
}

void Update()
{
	// code
	// fprintf(gpFile, "PPP:Update() function called... \n");
}

void Uninitialize()
{
	// code
	fprintf(gpFile, "PPP:Uninitialize() function called... \n");
	// if exiting in full screen first restore and then processed
	if(bFullScreen == TRUE)
	{
		ToggleFullScreen();
	}

	// first check the current context and if it is then unmake it
	if(wglGetCurrentContext() == ghrc)
	{
		wglMakeCurrent(NULL, NULL); // unmake
	}

	// now destroy the current rendering context
	if(ghrc)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}
	
	// release the device context
	if(ghdc)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	if(ghwnd)
	{
		DestroyWindow(ghwnd);
		ghwnd = NULL;
	}

	// Close Log File
        if(gpFile)
        {
                fprintf(gpFile, "PPP: Program Terminated Successfully...\n");
                fclose(gpFile);
                gpFile = NULL;
        }
}

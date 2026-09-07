#include<GL/freeglut.h>
/*
#include<windows.h>
#include<stdio.h> // no need alredy sub included in <windows.h>. but file I/O functions declared in this
#include<stdlib.h> // for exit(0)

// OpenGL related header files
#include<gl/GL.h>
*/

bool bIsFullScreen = false;

int main(int args, char* argv[])
{
	// function declaration
	void initialize(void);
	void uninitialize(void);
	void resize(int, int);
	void display(void);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);

	// code
	glutInit(&args, argv); // internally calls WinMin(), WndClassEx initialization, RegisterClassEx(&wndclass);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); 
	/*
	* GLUT_DOUBLE -> PFD_DOUBLEBUFFER
	* GLUT_RGBA -> iPixelType, cRedBits, cGreenBits, cBlueBits, cAlphaBits
	* 
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR); // n -> short
	pfd.nVersion = 1; // convention always 1
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER; // PFD_DRAW_TO_WINDOW -> To Draw on Window | PFD_SUPPORT_OPENGL -> OpenGL la suppored | PFD_DOUBLEBUFFER -> faster and more realistic (chota battachan)
	pfd.iPixelType = PFD_TYPE_RGBA; // R G B Alpha type 32 bit pixel
	pfd.cRedBits = 8; // c-> count
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;
	*/
	glutInitWindowSize(800, 600); 
	glutInitWindowPosition(100, 100);
	glutCreateWindow("My First RTR-7 Program : Harshal Wadne");
	/*
	* Above 3 function are internally CreateWindowEx(), ShowWindow(), UpdateWindow().
	* glutInitWindowSize(800, 600); first param -> x , second param -> y
	* glutInitWindowPosition(100, 100); first param -> width , second param -> height
	* glutCreateWindow("") -> TEXT("My First RTR07 Window Program : Pranav P Patil") -> 3rd parameter of CreateWindow()
	*/

	initialize();

	glutReshapeFunc(resize);
	/*
	case WM_SIZE:
			Resize(LOWORD(lParam), HIWORD(lParam));
			fprintf(gpFile, "PPP:WndProc() WM_SIZE: message \n");
                        break;
	*/
	glutDisplayFunc(display);   
	/*
	internally Render() call
	*/
	glutKeyboardFunc(keyboard); // ESC call
	glutMouseFunc(mouse);
	/*
	case WM_RBUTTONDOWN:
		...
		break;
	*/
	glutCloseFunc(uninitialize);
	/*
	case WM_CLOSE:
			fprintf(gpFile, "PPP:WndProc() WM_CLOSE: message created\n");
			Uninitialize();
			break;
	*/
	glutMainLoop();
	/*
		GAME LOOP
	*/
	// flow should not come here
	return(0);
}

void initialize(void) 
{
	//code
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void resize(int width, int height) 
{
	// code 
	if (height <= 0) 
	{
		height = 1;
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void display(void) 
{
	// code
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();

	glutSwapBuffers(); // internally calls SwapBuffers(ghdc);
}

void keyboard(unsigned char key, int x, int y) 
{
	// code
	switch (key)
	{
	case 27: // internally VK_ESCAPE ascii code
		glutLeaveMainLoop();
		break;
	case 'F':
	case 'f':
		if (bIsFullScreen == false) {
			glutFullScreen();
			bIsFullScreen = true;
		}
		else {
			glutLeaveFullScreen();
			bIsFullScreen = false;
		}
		break;
	default:
		break;
	}
}

void mouse(int button, int state, int x, int y) {
	// code
	switch (button) 
	{
	case GLUT_RIGHT_BUTTON:
		glutLeaveMainLoop();
		break;
	default:
		break;
	}
}

void uninitialize(void) 
{
	// code
}



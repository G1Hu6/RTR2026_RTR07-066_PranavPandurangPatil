#include<GL/freeglut.h>
#include<math.h>

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
	glutInit(&args, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("My First RTR-7 Program : Pranav Patil");

	initialize();

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutCloseFunc(uninitialize);

	glutMainLoop();

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
	float x = 0.0f;
	float y = 0.0f;
	float r = 0.5f;
	
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_LINES);
	
	for(int theta = 0; theta <= 10; theta += 1)
	{
		x = cos(theta) * r;
		y = sin(theta) * r;

		glColor3f(0.0f, 0.1f, 0.0f);
        	glVertex3f(0.0f, 0.0f, 0.0f);

		glColor3f(0.0f, 0.0f, 1.0f);
        	glVertex3f(x, y, 0.0f);
	}

	glEnd();
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) 
{
	// code
	switch (key)
	{
	case 27:
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


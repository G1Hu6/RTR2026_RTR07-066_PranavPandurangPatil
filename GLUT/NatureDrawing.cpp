#include<GL/freeglut.h>
#define X_MAX 30.0f
#define Y_MAX 13.0f

bool bIsFullScreen = false;


int main(int argc, char *argv[])
{
	// function declarations
	void initialize(void);
	void uninitialize(void);
	void resize(int, int);
	void display(void);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void graphCoordinate(float, float);
	// code
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Nature Drawing Demo");
	
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

void graphCoordinate(float xPoint, float yPoint)
{
	float graphXPoint = (((xPoint / X_MAX) * 2.0f) - 1.0f);
	float graphYPoint = (1.0f - ((yPoint / Y_MAX) * 2.0f));
	glVertex3f(graphXPoint, graphYPoint, 0.0f);
}

void initialize(void)
{
	// code
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

	// House
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.5f, 0.0f);
	graphCoordinate(7.5f, 7.5f);
	//glColor3f(0.0f, 1.0f, 0.0f);
	graphCoordinate(6.5f, 9.0f);
	//glColor3f(0.0f, 0.0f, 1.0f);
	graphCoordinate(8.5f, 9.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.55f, 0.27f, 0.07f);
	graphCoordinate(7.5f, 7.5f);
	//glColor3f(0.0f, 1.0f, 0.0f);
	graphCoordinate(8.0f, 9.00f);
	//glColor3f(0.0f, 0.0f, 1.0f);
	graphCoordinate(14.5f, 9.0f);
	graphCoordinate(13.5f, 7.5f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	graphCoordinate(8.25f, 9.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);
	graphCoordinate(8.25f, 13.00f);
	//glColor3f(0.0f, 0.0f, 1.0f);
	graphCoordinate(14.25f, 12.5f);
	glColor3f(0.75f, 0.75f, 0.75f);
	graphCoordinate(14.25f, 9.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	graphCoordinate(6.75f, 9.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	graphCoordinate(6.75f, 12.5f);
	glColor3f(0.75f, 0.75f, 0.75f);
	graphCoordinate(8.25f, 13.00f);
	glColor3f(0.75f, 0.75f, 0.75f);
	graphCoordinate(8.25f, 9.0f);
	glEnd();

	// House - Door
	glBegin(GL_QUADS);
	glColor3f(0.55f, 0.27f, 0.07f);
	graphCoordinate(7.0f, 10.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);
	graphCoordinate(7.0f, 12.5f);
	//glColor3f(0.0f, 0.0f, 1.0f);
	graphCoordinate(7.75f, 12.75f);
	//glColor3f(0.75f, 0.75f, 0.75f);
	graphCoordinate(7.75f, 10.25f);
	glEnd();

	/*
	glLineWidth(5.0f);
	glColor3f(1.0f, 0.5f, 0.0f);
	glBegin(GL_LINES);
	graphCoordinate(7.25f, 10.0f);
	graphCoordinate(7.25f, 12.75f);
	glEnd();
	*/

	// House - Window
	glBegin(GL_QUADS);
	glColor3f(0.55f, 0.27f, 0.07f);
	graphCoordinate(9.75f, 10.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);
	graphCoordinate(9.75f, 11.5f);
	//glColor3f(0.0f, 0.0f, 1.0f);
	graphCoordinate(12.0f, 11.25f);
	//glColor3f(0.75f, 0.75f, 0.75f);
	graphCoordinate(12.0f, 10.0f);
	glEnd();

	glLineWidth(5.0f);
	glColor3f(1.0f, 0.5f, 0.0f);
	glBegin(GL_LINES);
	graphCoordinate(11.0f, 10.0f);
	graphCoordinate(11.0f, 11.35f);
	glEnd();

	glLineWidth(5.0f);
	glColor3f(1.0f, 0.5f, 0.0f);
	glBegin(GL_LINES);
	graphCoordinate(9.75f, 10.75f);
	graphCoordinate(12.0f, 10.65f);
	glEnd();

	// Tree
	glBegin(GL_TRIANGLES);
	//glColor3f(1.0f, 0.0f, 0.0f);
	graphCoordinate(15.0f, 7.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	graphCoordinate(12.0f, 10.0f);
	//glColor3f(0.0f, 0.0f, 1.0f);
	graphCoordinate(18.0f, 10.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	//glColor3f(1.0f, 0.0f, 0.0f);
	graphCoordinate(15.0f, 4.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	graphCoordinate(12.0f, 8.0f);
	//glColor3f(0.0f, 0.0f, 1.0f);
	graphCoordinate(18.0f, 8.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.55f, 0.27f, 0.07f);
	graphCoordinate(14.75f, 10.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);
	graphCoordinate(14.75f, 13.25f);
	//glColor3f(0.0f, 0.0f, 1.0f);
	graphCoordinate(15.25f, 13.25f);
	//glColor3f(0.0f, 0.0f, 1.0f);
	graphCoordinate(15.25f, 10.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.55f, 0.27f, 0.07f);
	graphCoordinate(16.00f, 10.00f);
	//glColor3f(0.0f, 1.0f, 0.0f);
	graphCoordinate(15.25f, 10.75f);
	//glColor3f(0.0f, 0.0f, 1.0f);
	graphCoordinate(15.25f, 11.00f);
	//glColor3f(0.0f, 0.0f, 1.0f);
	graphCoordinate(16.25f, 10.0f);
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
		if (!bIsFullScreen)
		{
			glutFullScreen();
			bIsFullScreen = true;
		}
		else 
		{
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


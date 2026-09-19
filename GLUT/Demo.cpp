#include <Gl/freeglut.h>
#include <math.h>
bool bIsFullscreen = false;

int main(int argc, char* argv[])
{
	//Function Declration
	void initialize(void);
	void uninitialize(void);
	void resize(int, int);
	void DrawCircle(void);
	void display(void);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);

	//Code
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);


	glutCreateWindow("My Frist RTR7 Program : Saeed Haroon Shaikh");

	initialize();

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutCloseFunc(uninitialize);

	glutMainLoop();

	//flow should not come here
	return(0);
}

void initialize(void)
{
	// Code
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void resize(int width, int height)
{
	// Code
	if (height <= 0)
		height = 1;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void DrawCircle(void)
{
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.0f, 0.0f);

	for (int i = 0; i <= 360; i++)
	{
		float angle = i * 3.14159f / 180.0f;
		glVertex2f(cosf(angle), sinf(angle));

	}
	glEnd();
}

void display(void)
{
	// Code
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(0.2f, 0.0f, 0.0);
	glScalef(0.6f, 0.6f, 1.0f);
	{
		glBegin(GL_QUADS);
		glColor3f(0.55f, 0.32f, 0.12f);
		glVertex3f(-0.6f, 0.39f, 0.0f);
		glVertex3f(-0.29f, 0.39f, 0.0f);
		glVertex3f(-0.24f, 0.16f, 0.0f);
		glVertex3f(-0.65f, 0.16f, 0.0f);
		glEnd();

		glLineWidth(3.0f);
		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.61f, 0.35f, 0.0f);
		glVertex3f(-0.28f, 0.35f, 0.0f);
		glEnd();

		glLineWidth(3.0f);
		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.63f, 0.29f, 0.0f);
		glVertex3f(-0.26f, 0.29f, 0.0f);
		glEnd();

		glLineWidth(3.0f);
		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.64f, 0.21f, 0.0f);
		glVertex3f(-0.25f, 0.21f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.65f, 0.0f);
		glVertex3f(-0.59f, 0.4f, 0.0f);
		glVertex3f(-0.64f, 0.18f, 0.0f);
		glVertex3f(-0.74f, 0.18f, 0.0f);
		glVertex3f(-0.67f, 0.4f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.65f, 0.0f);
		glVertex3f(-0.3f, 0.4f, 0.0f);
		glVertex3f(-0.25f, 0.18f, 0.0f);
		glVertex3f(-0.15f, 0.18f, 0.0f);
		glVertex3f(-0.22f, 0.4f, 0.0f);
		glEnd();

		glLineWidth(3.0f);
		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.75f, 0.18f, 0.0f);
		glVertex3f(-0.14f, 0.18f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.65f, 0.0f);
		glVertex3f(-0.75f, 0.18f, 0.0f);
		glVertex3f(-0.75f, 0.09f, 0.0f);
		glVertex3f(-0.14f, 0.09f, 0.0f);
		glVertex3f(-0.14f, 0.18f, 0.0f);
		glEnd();

		glLineWidth(3.0f);
		glBegin(GL_LINE_STRIP);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.75f, 0.18f, 0.0f);
		glVertex3f(-0.75f, 0.09f, 0.0f);
		glVertex3f(-0.14f, 0.09f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.65f, 0.0f);
		glVertex3f(-0.75f, 0.09f, 0.0f);
		glVertex3f(-0.75f, 0.05f, 0.0f);
		glVertex3f(-0.14f, 0.05f, 0.0f);
		glVertex3f(-0.14f, 0.09f, 0.0f);
		glEnd();

		glLineWidth(3.0f);
		glBegin(GL_LINE_STRIP);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.75f, 0.09f, 0.0f);
		glVertex3f(-0.75f, 0.05f, 0.0f);
		glVertex3f(-0.14f, 0.05f, 0.0f);
		glVertex3f(-0.14f, 0.09f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.65f, 0.0f);
		glVertex3f(-0.71f, 0.05f, 0.0f);
		glVertex3f(-0.68f, -0.31f, 0.0f);
		glVertex3f(-0.22f, -0.31f, 0.0f);
		glVertex3f(-0.18f, 0.05f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.55f, 0.32f, 0.12f);
		glVertex3f(-0.66f, 0.02f, 0.0f);
		glVertex3f(-0.63f, -0.29f, 0.0f);
		glVertex3f(-0.27f, -0.29f, 0.0f);
		glVertex3f(-0.24f, 0.02f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(1.0f, 0.65f, 0.0f);
		glVertex3f(-0.49f, 0.05f, 0.0f);
		glVertex3f(-0.49f, -0.04f, 0.0f);
		glVertex3f(-0.39f, -0.04f, 0.0f);
		glVertex3f(-0.39f, 0.05f, 0.0f);
		glEnd();

		glLineWidth(3.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_LINE_STRIP);
		glVertex3f(-0.49f, 0.05f, 0.0f);
		glVertex3f(-0.49f, -0.04f, 0.0f);
		glVertex3f(-0.39f, -0.04f, 0.0f);
		glVertex3f(-0.39f, 0.05f, 0.0f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.55f, 0.32f, 0.12f);
		glVertex3f(-0.445f, 0.01f, 0.0f);
		glVertex3f(-0.445f, -0.03f, 0.0f);
		glVertex3f(-0.435f, -0.03f, 0.0f);
		glVertex3f(-0.435f, 0.01f, 0.0f);
		glEnd();

		glPushMatrix();
		glTranslatef(-0.44f, 0.02f, 0.0);
		glScalef(0.03f, 0.03f, 1.0f);
		glColor3f(0.45f, 0.22f, 0.10f);
		DrawCircle();
		glPopMatrix();

		glLineWidth(3.0f);
		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.65f, -0.06f, 0.0f);
		glVertex3f(-0.25f, -0.06f, 0.0f);
		glEnd();

		glLineWidth(3.0f);
		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.64f, -0.15f, 0.0f);
		glVertex3f(-0.26f, -0.15f, 0.0f);
		glEnd();

		glLineWidth(3.0f);
		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-0.63f, -0.23f, 0.0f);
		glVertex3f(-0.27f, -0.23f, 0.0f);
		glEnd();
	}
	glPopMatrix();

	glutSwapBuffers();

}

void keyboard(unsigned char Key, int x, int y)
{
	//Code
	switch (Key)
	{
	case 27:
		glutLeaveMainLoop();
		break;
	case 'F':
	case 'f':
		if (bIsFullscreen == false)
		{
			glutFullScreen();
			bIsFullscreen = true;

		}
		else
		{
			glutLeaveFullScreen();
			bIsFullscreen = false;
		}
		break;
	default:
		break;

	}

}

void mouse(int button, int state, int x, int y)
{
	// Code
	switch (button)
	{
	case GLUT_RIGHT_BUTTON:
		glutMainLoop();
		break;
	default:
		break;

	}

}

void uninitialize(void)
{
	// Code

}


#include <Gl/freeglut.h>
#include <math.h>
#include <stdlib.h>

bool bIsFullscreen = false;

void DrawCircle(void);
void Balloon(void);
void DrawMayuresh(void);

// global variable declarations
float happyX = -2.5f;
float birthdayX = 2.5f;
float MayureshY = -2.0f;
float BalloonY = -2.0f;
float HappyAlpha = 1.0f;
float BirthdayAlpha = 1.0f;
float MayureshAlpha = 1.0f;
GLfloat MayureshDrawingAlpha = 0.005f;
GLboolean bShowMayureshDrawing = FALSE;


int main(int argc, char* argv[])
{
	//Function Declration
	void initialize(void);
	void uninitialize(void);
	void resize(int, int);
	void Happy(void);
	void Birthday(void);
	void Mayuresh(void);
	void display(void);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void Update(int);

	//Code
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);


	glutCreateWindow("My Frist RTR7 Program : Saeed Haroon Shaikh");

	initialize();
	glutFullScreen();
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutTimerFunc(16, Update, 0);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutCloseFunc(uninitialize);

	glutMainLoop();

	//flow should not come here
	return(0);
}

void initialize(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

void Happy(void)
{
	glPushMatrix();
	glTranslatef(happyX, -0.1f, 0.0f);
	glScalef(0.9f, 1.0f, 1.0f);

	//H letter //////////////////////////////
	glPushMatrix();
	glTranslatef(0.1f, 0.05f, 0.0f);
	glScalef(0.8f, 0.9f, 1.0f);

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, HappyAlpha);
	glVertex3f(-0.7f, 0.9f, 0.0f);
	glVertex3f(-0.7f, 0.6f, 0.0f);
	glVertex3f(-0.65f, 0.6f, 0.0f);
	glVertex3f(-0.65f, 0.9f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, HappyAlpha);
	glVertex3f(-0.65f, 0.77f, 0.0f);
	glVertex3f(-0.65f, 0.73f, 0.0f);
	glVertex3f(-0.55f, 0.73f, 0.0f);
	glVertex3f(-0.55f, 0.77f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, HappyAlpha);
	glVertex3f(-0.5f, 0.9f, 0.0f);
	glVertex3f(-0.5f, 0.6f, 0.0f);
	glVertex3f(-0.55f, 0.6f, 0.0f);
	glVertex3f(-0.55f, 0.9f, 0.0f);
	glEnd();
	glPopMatrix();

	//A letter /////////////////////////////////
	glPushMatrix();
	glTranslatef(0.15f, 0.05f, 0.0f);
	glScalef(0.9f, 0.9f, 1.0f);

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, HappyAlpha);
	glVertex3f(-0.45f, 0.6f, 0.0f);
	glVertex3f(-0.37f, 0.9f, 0.0f);
	glVertex3f(-0.33f, 0.9f, 0.0f);
	glVertex3f(-0.4f, 0.6f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, HappyAlpha);
	glVertex3f(-0.25f, 0.6f, 0.0f);
	glVertex3f(-0.33f, 0.9f, 0.0f);
	glVertex3f(-0.37f, 0.9f, 0.0f);
	glVertex3f(-0.3f, 0.6f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, HappyAlpha);
	glVertex3f(-0.41f, 0.75f, 0.0f);
	glVertex3f(-0.42f, 0.7f, 0.0f);
	glVertex3f(-0.28f, 0.7f, 0.0f);
	glVertex3f(-0.29f, 0.75f, 0.0f);
	glEnd();
	glPopMatrix();

	//1st P letter ///////////////////////////////
	glPushMatrix();
	glTranslatef(-0.35f, 0.59f, 0.0f);
	glScalef(0.8f, 0.7f, 1.0f);

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, HappyAlpha);
	glVertex3f(0.4f, 0.4f, 0.0f);
	glVertex3f(0.45f, 0.4f, 0.0f);
	glVertex3f(0.45f, 0.0f, 0.0f);
	glVertex3f(0.4f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, HappyAlpha);
	glVertex3f(0.45f, 0.4f, 0.0f);
	glVertex3f(0.5f, 0.4f, 0.0f);
	glVertex3f(0.5f, 0.35f, 0.0f);
	glVertex3f(0.45f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, HappyAlpha);
	glVertex3f(0.45f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glVertex3f(0.45f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, HappyAlpha);
	glVertex3f(0.5f, 0.35f, 0.0f);
	glVertex3f(0.55f, 0.35f, 0.0f);
	glVertex3f(0.55f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.25f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(1.0f, 0.0f, 0.0f, HappyAlpha);
	glVertex3f(0.55f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(1.0f, 0.0f, 0.0f, HappyAlpha);
	glVertex3f(0.55f, 0.35f, 0.0f);
	glVertex3f(0.5f, 0.4f, 0.0f);
	glVertex3f(0.5f, 0.35f, 0.0f);
	glEnd();
	glPopMatrix();

	//2nd P letter ///////////////////////////////
	glPushMatrix();
	glTranslatef(-0.18f, 0.59f, 0.0f);
	glScalef(0.8f, 0.7f, 1.0f);

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, HappyAlpha);
	glVertex3f(0.4f, 0.4f, 0.0f);
	glVertex3f(0.45f, 0.4f, 0.0f);
	glVertex3f(0.45f, 0.0f, 0.0f);
	glVertex3f(0.4f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, HappyAlpha);
	glVertex3f(0.45f, 0.4f, 0.0f);
	glVertex3f(0.5f, 0.4f, 0.0f);
	glVertex3f(0.5f, 0.35f, 0.0f);
	glVertex3f(0.45f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, HappyAlpha);
	glVertex3f(0.45f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glVertex3f(0.45f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, HappyAlpha);
	glVertex3f(0.5f, 0.35f, 0.0f);
	glVertex3f(0.55f, 0.35f, 0.0f);
	glVertex3f(0.55f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.25f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(1.0f, 0.0f, 0.0f, HappyAlpha);
	glVertex3f(0.55f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(1.0f, 0.0f, 0.0f, HappyAlpha);
	glVertex3f(0.55f, 0.35f, 0.0f);
	glVertex3f(0.5f, 0.4f, 0.0f);
	glVertex3f(0.5f, 0.35f, 0.0f);
	glEnd();
	glPopMatrix();

	//Y letter ///////////////////////////////
	glPushMatrix();
	glTranslatef(0.15f, 0.05f, 0.0f);
	glScalef(0.8f, 0.9f, 1.0f);

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, HappyAlpha);
	glVertex3f(0.25f, 0.6f, 0.0f);
	glVertex3f(0.25f, 0.75f, 0.0f);
	glVertex3f(0.3f, 0.75f, 0.0f);
	glVertex3f(0.3f, 0.6f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, HappyAlpha);
	glVertex3f(0.25f, 0.75f, 0.0f);
	glVertex3f(0.2f, 0.87f, 0.0f);
	glVertex3f(0.23f, 0.9f, 0.0f);
	glVertex3f(0.3f, 0.75f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, HappyAlpha);
	glVertex3f(0.3f, 0.75f, 0.0f);
	glVertex3f(0.35f, 0.87f, 0.0f);
	glVertex3f(0.32f, 0.9f, 0.0f);
	glVertex3f(0.25f, 0.75f, 0.0f);
	glEnd();
	glPopMatrix();

	glPopMatrix();
}


void Birthday(void)
{
	glPushMatrix();
	glTranslatef(birthdayX, -0.3f, 0.0f);
	glScalef(0.9f, 1.0f, 1.0f);

	//B letter //////////////////////////////
	glPushMatrix();
	glTranslatef(-0.1f, 0.01f, 0.0f);
	glScalef(0.8f, 0.97f, 1.0f);

	glBegin(GL_POLYGON);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(-0.7f, 0.5f, 0.0f);
	glVertex3f(-0.6f, 0.5f, 0.0f);
	glVertex3f(-0.55f, 0.45f, 0.0f);
	glVertex3f(-0.6f, 0.43f, 0.0f);
	glVertex3f(-0.63f, 0.46f, 0.0f);
	glVertex3f(-0.67f, 0.46f, 0.0f);
	glVertex3f(-0.7f, 0.5f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(-0.6f, 0.43f, 0.0f);
	glVertex3f(-0.55f, 0.45f, 0.0f);
	glVertex3f(-0.55f, 0.4f, 0.0f);
	glVertex3f(-0.6f, 0.4f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(-0.6f, 0.4f, 0.0f);
	glVertex3f(-0.55f, 0.4f, 0.0f);
	glVertex3f(-0.6f, 0.35f, 0.0f);
	glVertex3f(-0.63f, 0.37f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(-0.6f, 0.35f, 0.0f);
	glVertex3f(-0.55f, 0.3f, 0.0f);
	glVertex3f(-0.6f, 0.3f, 0.0f);
	glVertex3f(-0.63f, 0.33f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(-0.6f, 0.3f, 0.0f);
	glVertex3f(-0.55f, 0.3f, 0.0f);
	glVertex3f(-0.55f, 0.25f, 0.0f);
	glVertex3f(-0.6f, 0.22f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(-0.7f, 0.2f, 0.0f);
	glVertex3f(-0.6f, 0.2f, 0.0f);
	glVertex3f(-0.55f, 0.25f, 0.0f);
	glVertex3f(-0.55f, 0.3f, 0.0f);
	glVertex3f(-0.63f, 0.24f, 0.0f);
	glVertex3f(-0.67f, 0.24f, 0.0f);
	glVertex3f(-0.7f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(-0.7f, 0.2f, 0.0f);
	glVertex3f(-0.7f, 0.5f, 0.0f);
	glVertex3f(-0.67f, 0.5f, 0.0f);
	glVertex3f(-0.67f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(-0.7f, 0.37f, 0.0f);
	glVertex3f(-0.6f, 0.37f, 0.0f);
	glVertex3f(-0.6f, 0.33f, 0.0f);
	glVertex3f(-0.7f, 0.33f, 0.0f);
	glEnd();
	glPopMatrix();

	//I letter ////////////////////////////
	glPushMatrix();
	glTranslatef(-0.07f, 0.01f, 0.0f);
	glScalef(0.8f, 0.97f, 1.0f);

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(-0.5f, 0.2f, 0.0f);
	glVertex3f(-0.5f, 0.25f, 0.0f);
	glVertex3f(-0.35f, 0.25f, 0.0f);
	glVertex3f(-0.35f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(-0.5f, 0.45f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glVertex3f(-0.35f, 0.5f, 0.0f);
	glVertex3f(-0.35f, 0.45f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(-0.45f, 0.25f, 0.0f);
	glVertex3f(-0.45f, 0.45f, 0.0f);
	glVertex3f(-0.4f, 0.45f, 0.0f);
	glVertex3f(-0.4f, 0.25f, 0.0f);
	glEnd();
	glPopMatrix();

	//R Letter /////////////////////////////////
	glPushMatrix();
	glTranslatef(-0.58f, 0.2f, 0.0f);
	glScalef(0.7f, 0.75f, 1.0f);

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(0.4f, 0.4f, 0.0f);
	glVertex3f(0.45f, 0.4f, 0.0f);
	glVertex3f(0.45f, 0.0f, 0.0f);
	glVertex3f(0.4f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(0.45f, 0.2f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glVertex3f(0.55f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(0.45f, 0.4f, 0.0f);
	glVertex3f(0.5f, 0.4f, 0.0f);
	glVertex3f(0.5f, 0.35f, 0.0f);
	glVertex3f(0.45f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(0.45f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glVertex3f(0.45f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(0.5f, 0.35f, 0.0f);
	glVertex3f(0.55f, 0.35f, 0.0f);
	glVertex3f(0.55f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.25f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(0.55f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(0.55f, 0.35f, 0.0f);
	glVertex3f(0.5f, 0.4f, 0.0f);
	glVertex3f(0.5f, 0.35f, 0.0f);
	glEnd();
	glPopMatrix();

	//T Letter //////////////////////////////
	glPushMatrix();
	glTranslatef(-1.08f, 0.64f, 0.0f);
	glScalef(1.1f, 1.45f, 1.0f);

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(0.88f, -0.3f, 0.0f);
	glVertex3f(0.88f, -0.15f, 0.0f);
	glVertex3f(0.92f, -0.15f, 0.0f);
	glVertex3f(0.92f, -0.3f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(0.85f, -0.15f, 0.0f);
	glVertex3f(0.85f, -0.1f, 0.0f);
	glVertex3f(0.95f, -0.1f, 0.0f);
	glVertex3f(0.95f, -0.15f, 0.0f);
	glEnd();
	glPopMatrix();

	//H letter //////////////////////////////
	glPushMatrix();
	glTranslatef(0.58f, -0.35f, 0.0f);
	glScalef(0.8f, 0.94f, 1.0f);

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(-0.7f, 0.9f, 0.0f);
	glVertex3f(-0.7f, 0.6f, 0.0f);
	glVertex3f(-0.65f, 0.6f, 0.0f);
	glVertex3f(-0.65f, 0.9f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(-0.65f, 0.77f, 0.0f);
	glVertex3f(-0.65f, 0.73f, 0.0f);
	glVertex3f(-0.55f, 0.73f, 0.0f);
	glVertex3f(-0.55f, 0.77f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(-0.5f, 0.9f, 0.0f);
	glVertex3f(-0.5f, 0.6f, 0.0f);
	glVertex3f(-0.55f, 0.6f, 0.0f);
	glVertex3f(-0.55f, 0.9f, 0.0f);
	glEnd();
	glPopMatrix();


	//D Letter //////////////////////////////////////
	glPushMatrix();
	glTranslatef(0.24f, 0.21f, 0.0f);
	glScalef(0.8f, 0.72f, 1.0f);

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(0.0, 0.35f, 0.0f);
	glVertex3f(0.04f, 0.35f, 0.0f);
	glVertex3f(0.04f, 0.05f, 0.0f);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(0.04f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.04f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(0.04f, 0.4f, 0.0f);
	glVertex3f(0.1f, 0.4f, 0.0f);
	glVertex3f(0.1f, 0.35f, 0.0f);
	glVertex3f(0.04f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glVertex3f(0.15f, 0.3f, 0.0f);
	glVertex3f(0.15f, 0.09f, 0.0f);
	glVertex3f(0.1f, 0.09f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(0.0f, 0.05f, 0.0f);
	glVertex3f(0.04f, 0.05f, 0.0f);
	glVertex3f(0.04f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(0.0f, 0.4f, 0.0f);
	glVertex3f(0.04f, 0.4f, 0.0f);
	glVertex3f(0.04f, 0.35f, 0.0f);
	glVertex3f(0.0f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(0.1f, 0.4f, 0.0f);
	glVertex3f(0.13f, 0.35f, 0.0f);
	glVertex3f(0.1f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(0.03f, 0.35f, 0.0f);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glVertex3f(0.1f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(0.1f, 0.35f, 0.0f);
	glVertex3f(0.13f, 0.35f, 0.0f);
	glVertex3f(0.15f, 0.3f, 0.0f);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(0.1f, 0.09f, 0.0f);
	glVertex3f(0.05f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	glVertex3f(0.15f, 0.05f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(0.1f, 0.09f, 0.0f);
	glVertex3f(0.15f, 0.09f, 0.0f);
	glVertex3f(0.15f, 0.05f, 0.0f);
	glVertex3f(0.1f, 0.05f, 0.0f);
	glEnd();
	glPopMatrix();

	//A letter /////////////////////////////////
	glPushMatrix();
	glTranslatef(0.8f, -0.35f, 0.0f);
	glScalef(0.9f, 0.93f, 1.0f);

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(-0.45f, 0.6f, 0.0f);
	glVertex3f(-0.37f, 0.9f, 0.0f);
	glVertex3f(-0.33f, 0.9f, 0.0f);
	glVertex3f(-0.4f, 0.6f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(-0.25f, 0.6f, 0.0f);
	glVertex3f(-0.33f, 0.9f, 0.0f);
	glVertex3f(-0.37f, 0.9f, 0.0f);
	glVertex3f(-0.3f, 0.6f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(-0.41f, 0.75f, 0.0f);
	glVertex3f(-0.42f, 0.7f, 0.0f);
	glVertex3f(-0.28f, 0.7f, 0.0f);
	glVertex3f(-0.29f, 0.75f, 0.0f);
	glEnd();
	glPopMatrix();

	//Y letter ///////////////////////////////
	glPushMatrix();
	glTranslatef(0.43f, -0.35f, 0.0f);
	glScalef(0.8f, 0.95f, 1.0f);

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(0.25f, 0.6f, 0.0f);
	glVertex3f(0.25f, 0.75f, 0.0f);
	glVertex3f(0.3f, 0.75f, 0.0f);
	glVertex3f(0.3f, 0.6f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(0.25f, 0.75f, 0.0f);
	glVertex3f(0.2f, 0.87f, 0.0f);
	glVertex3f(0.23f, 0.9f, 0.0f);
	glVertex3f(0.3f, 0.75f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, BirthdayAlpha);
	glVertex3f(0.3f, 0.75f, 0.0f);
	glVertex3f(0.35f, 0.87f, 0.0f);
	glVertex3f(0.32f, 0.9f, 0.0f);
	glVertex3f(0.25f, 0.75f, 0.0f);
	glEnd();
	glPopMatrix();

	glPopMatrix();
}


void Mayuresh(void)
{
	glPushMatrix();
	glTranslatef(0.0f, MayureshY, 0.0f);
	glScalef(0.9f, 1.0f, 1.0f);

	//M Letter //////////////////////////////
	glPushMatrix();
	glTranslatef(-0.03f, 0.0f, 0.0f);
	glScalef(0.7f, 0.95f, 1.0f);

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(-0.9f, -0.2f, 0.0f);
	glVertex3f(-0.9f, 0.1f, 0.0f);
	glVertex3f(-0.85f, 0.1f, 0.0f);
	glVertex3f(-0.85f, -0.2f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(-0.85f, 0.1f, 0.0f);
	glVertex3f(-0.8f, -0.02f, 0.0f);
	glVertex3f(-0.8f, -0.1f, 0.0f);
	glVertex3f(-0.85f, 0.02f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(-0.8f, -0.02f, 0.0f);
	glVertex3f(-0.8f, -0.1f, 0.0f);
	glVertex3f(-0.75f, 0.02f, 0.0f);
	glVertex3f(-0.75f, 0.1f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(-0.7f, -0.2f, 0.0f);
	glVertex3f(-0.7f, 0.1f, 0.0f);
	glVertex3f(-0.75f, 0.1f, 0.0f);
	glVertex3f(-0.75f, -0.2f, 0.0f);
	glEnd();

	glPopMatrix();

	//A letter /////////////////////////////////
	glPushMatrix();
	glTranslatef(-0.08f, -0.77f, 0.0f);
	glScalef(0.9f, 0.97f, 1.0f);

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(-0.45f, 0.6f, 0.0f);
	glVertex3f(-0.37f, 0.9f, 0.0f);
	glVertex3f(-0.33f, 0.9f, 0.0f);
	glVertex3f(-0.4f, 0.6f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(-0.25f, 0.6f, 0.0f);
	glVertex3f(-0.33f, 0.9f, 0.0f);
	glVertex3f(-0.37f, 0.9f, 0.0f);
	glVertex3f(-0.3f, 0.6f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(-0.41f, 0.75f, 0.0f);
	glVertex3f(-0.42f, 0.7f, 0.0f);
	glVertex3f(-0.28f, 0.7f, 0.0f);
	glVertex3f(-0.29f, 0.75f, 0.0f);
	glEnd();
	glPopMatrix();

	//Y letter ///////////////////////////////
	glPushMatrix();
	glTranslatef(-0.47f, -0.76f, 0.0f);
	glScalef(0.8f, 0.98f, 1.0f);

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(0.25f, 0.6f, 0.0f);
	glVertex3f(0.25f, 0.75f, 0.0f);
	glVertex3f(0.3f, 0.75f, 0.0f);
	glVertex3f(0.3f, 0.6f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(0.25f, 0.75f, 0.0f);
	glVertex3f(0.2f, 0.87f, 0.0f);
	glVertex3f(0.23f, 0.9f, 0.0f);
	glVertex3f(0.3f, 0.75f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(0.3f, 0.75f, 0.0f);
	glVertex3f(0.35f, 0.87f, 0.0f);
	glVertex3f(0.32f, 0.9f, 0.0f);
	glVertex3f(0.25f, 0.75f, 0.0f);
	glEnd();

	glPopMatrix();

	//U letter ///////////////////////////////
	glPushMatrix();
	glTranslatef(-0.02f, 0.02f, 0.0f);
	glScalef(0.8f, 0.98f, 1.0f);

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(-0.15f, -0.1f, 0.0f);
	glVertex3f(-0.1f, -0.1f, 0.0f);
	glVertex3f(-0.1f, 0.1f, 0.0f);
	glVertex3f(-0.15f, 0.1f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(-0.15f, -0.1f, 0.0f);
	glVertex3f(-0.15f, -0.15f, 0.0f);
	glVertex3f(-0.1f, -0.2f, 0.0f);
	glVertex3f(-0.07f, -0.15f, 0.0f);
	glVertex3f(-0.1f, -0.1f, 0.0f);
	glVertex3f(-0.15f, -0.1f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(-0.1f, -0.15f, 0.0f);
	glVertex3f(-0.1f, -0.2f, 0.0f);
	glVertex3f(0.0f, -0.2f, 0.0f);
	glVertex3f(0.0f, -0.15f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(-0.03f, -0.15f, 0.0f);
	glVertex3f(0.0f, -0.2f, 0.0f);
	glVertex3f(0.05f, -0.15f, 0.0f);
	glVertex3f(0.05f, -0.1f, 0.0f);
	glVertex3f(0.0f, -0.1f, 0.0f);
	glVertex3f(-0.03f, -0.15f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(0.0f, -0.1f, 0.0f);
	glVertex3f(0.05f, -0.1f, 0.0f);
	glVertex3f(0.05f, 0.1f, 0.0f);
	glVertex3f(0.0f, 0.1f, 0.0f);
	glEnd();

	glPopMatrix();

	//R Letter //////////////////////////////////
	glPushMatrix();
	glTranslatef(-0.23f, -0.18f, 0.0f);
	glScalef(0.76f, 0.74f, 1.0f);

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(0.4f, 0.4f, 0.0f);
	glVertex3f(0.45f, 0.4f, 0.0f);
	glVertex3f(0.45f, 0.0f, 0.0f);
	glVertex3f(0.4f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(0.45f, 0.2f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glVertex3f(0.55f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(0.45f, 0.4f, 0.0f);
	glVertex3f(0.5f, 0.4f, 0.0f);
	glVertex3f(0.5f, 0.35f, 0.0f);
	glVertex3f(0.45f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(0.45f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glVertex3f(0.45f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(0.5f, 0.35f, 0.0f);
	glVertex3f(0.55f, 0.35f, 0.0f);
	glVertex3f(0.55f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.25f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(0.55f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.25f, 0.0f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(0.55f, 0.35f, 0.0f);
	glVertex3f(0.5f, 0.4f, 0.0f);
	glVertex3f(0.5f, 0.35f, 0.0f);
	glEnd();
	glPopMatrix();

	//E Letter /////////////////////////////
	glPushMatrix();
	glTranslatef(0.1f, -0.18f, 0.0f);
	glScalef(0.7f, 0.73f, 1.0f);

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(0.2f, 0.4f, 0.0f);
	glVertex3f(0.25f, 0.4f, 0.0f);
	glVertex3f(0.25f, 0.0f, 0.0f);
	glVertex3f(0.2f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(0.25f, 0.4f, 0.0f);
	glVertex3f(0.35f, 0.4f, 0.0f);
	glVertex3f(0.35f, 0.35f, 0.0f);
	glVertex3f(0.25f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(0.25f, 0.22f, 0.0f);
	glVertex3f(0.35f, 0.22f, 0.0f);
	glVertex3f(0.35f, 0.18f, 0.0f);
	glVertex3f(0.25f, 0.18f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(0.25f, 0.06f, 0.0f);
	glVertex3f(0.35f, 0.06f, 0.0f);
	glVertex3f(0.35f, 0.0f, 0.0f);
	glVertex3f(0.25f, 0.0f, 0.0f);
	glEnd();
	glPopMatrix();

	//S Letter /////////////////////////
	glPushMatrix();
	glTranslatef(0.84f, -0.17f, 0.0f);
	glScalef(0.7f, 0.73f, 1.0f);

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(-0.55f, 0.35f, 0.0f);
	glVertex3f(-0.55f, 0.3f, 0.0f);
	glVertex3f(-0.5f, 0.3f, 0.0f);
	glVertex3f(-0.5f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(-0.6f, 0.4f, 0.0f);
	glVertex3f(-0.55f, 0.4f, 0.0f);
	glVertex3f(-0.55f, 0.35f, 0.0f);
	glVertex3f(-0.6f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(-0.65f, 0.35f, 0.0f);
	glVertex3f(-0.6f, 0.35f, 0.0f);
	glVertex3f(-0.6f, 0.25f, 0.0f);
	glVertex3f(-0.65f, 0.25f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(-0.6f, 0.25f, 0.0f);
	glVertex3f(-0.55f, 0.25f, 0.0f);
	glVertex3f(-0.55f, 0.2f, 0.0f);
	glVertex3f(-0.6f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(-0.55f, 0.2f, 0.0f);
	glVertex3f(-0.5f, 0.2f, 0.0f);
	glVertex3f(-0.5f, 0.05f, 0.0f);
	glVertex3f(-0.55f, 0.05f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(-0.6f, 0.05f, 0.0f);
	glVertex3f(-0.55f, 0.05f, 0.0f);
	glVertex3f(-0.55f, 0.0f, 0.0f);
	glVertex3f(-0.6f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(-0.65f, 0.1f, 0.0f);
	glVertex3f(-0.6f, 0.1f, 0.0f);
	glVertex3f(-0.6f, 0.05f, 0.0f);
	glVertex3f(-0.65f, 0.05f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(-0.6f, 0.35f, 0.0f);
	glVertex3f(-0.65f, 0.35f, 0.0f);
	glVertex3f(-0.6f, 0.4f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(-0.56f, 0.4f, 0.0f);
	glVertex3f(-0.5f, 0.35f, 0.0f);
	glVertex3f(-0.56f, 0.35f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(-0.55f, 0.2f, 0.0f);
	glVertex3f(-0.5f, 0.2f, 0.0f);
	glVertex3f(-0.55f, 0.25f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(-0.65f, 0.25f, 0.0f);
	glVertex3f(-0.6f, 0.25f, 0.0f);
	glVertex3f(-0.6f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(-0.55f, 0.0f, 0.0f);
	glVertex3f(-0.5f, 0.05f, 0.0f);
	glVertex3f(-0.55f, 0.05f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(-0.65f, 0.05f, 0.0f);
	glVertex3f(-0.6f, 0.0f, 0.0f);
	glVertex3f(-0.6f, 0.05f, 0.0f);
	glEnd();
	glPopMatrix();

	//H letter //////////////////////////////
	glPushMatrix();
	glTranslatef(1.1f, -0.7f, 0.0f);
	glScalef(0.8f, 0.9f, 1.0f);

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(-0.7f, 0.9f, 0.0f);
	glVertex3f(-0.7f, 0.6f, 0.0f);
	glVertex3f(-0.65f, 0.6f, 0.0f);
	glVertex3f(-0.65f, 0.9f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(-0.65f, 0.77f, 0.0f);
	glVertex3f(-0.65f, 0.73f, 0.0f);
	glVertex3f(-0.55f, 0.73f, 0.0f);
	glVertex3f(-0.55f, 0.77f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(1.0f, 0.0f, 0.0f, MayureshAlpha);
	glVertex3f(-0.5f, 0.9f, 0.0f);
	glVertex3f(-0.5f, 0.6f, 0.0f);
	glVertex3f(-0.55f, 0.6f, 0.0f);
	glVertex3f(-0.55f, 0.9f, 0.0f);
	glEnd();
	glPopMatrix();

	glPopMatrix();

}



void display(void)
{
	// Code
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);
	Happy();
	Birthday();
	Mayuresh();

	if (MayureshY >= -0.5f && BalloonY < 2.5f)
	{
		// 1
		glPushMatrix();
		glTranslatef(0.00f, BalloonY + 0.72f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		Balloon();
		glPopMatrix();

		// 2
		glPushMatrix();
		glTranslatef(-0.12f, BalloonY + 0.64f, 0.0f);
		glColor3f(0.2f, 0.6f, 1.0f);
		Balloon();
		glPopMatrix();

		// 3
		glPushMatrix();
		glTranslatef(0.10f, BalloonY + 0.65f, 0.0f);
		glColor3f(0.0f, 0.3f, 1.0f);
		Balloon();
		glPopMatrix();

		// 4
		glPushMatrix();
		glTranslatef(0.22f, BalloonY + 0.60f, 0.0f);
		glColor3f(0.0f, 0.6f, 0.2f);
		Balloon();
		glPopMatrix();

		// 5
		glPushMatrix();
		glTranslatef(-0.28f, BalloonY + 0.54f, 0.0f);
		glColor3f(0.0f, 0.5f, 0.1f);
		Balloon();
		glPopMatrix();

		// 6
		glPushMatrix();
		glTranslatef(-0.14f, BalloonY + 0.52f, 0.0f);
		glColor3f(0.4f, 1.0f, 0.4f);
		Balloon();
		glPopMatrix();

		// 7
		glPushMatrix();
		glTranslatef(0.00f, BalloonY + 0.55f, 0.0f);
		glColor3f(0.3f, 0.7f, 1.0f);
		Balloon();
		glPopMatrix();

		// 8
		glPushMatrix();
		glTranslatef(0.14f, BalloonY + 0.51f, 0.0f);
		glColor3f(1.0f, 0.4f, 0.2f);
		Balloon();
		glPopMatrix();

		// 9
		glPushMatrix();
		glTranslatef(0.28f, BalloonY + 0.53f, 0.0f);
		glColor3f(1.0f, 0.65f, 0.0f);
		Balloon();
		glPopMatrix();


		// 10
		glPushMatrix();
		glTranslatef(-0.38f, BalloonY + 0.38f, 0.0f);
		glColor3f(0.0f, 0.9f, 0.9f);
		Balloon();
		glPopMatrix();

		// 11
		glPushMatrix();
		glTranslatef(-0.25f, BalloonY + 0.40f, 0.0f);
		glColor3f(1.0f, 0.6f, 0.3f);
		Balloon();
		glPopMatrix();

		// 12
		glPushMatrix();
		glTranslatef(-0.12f, BalloonY + 0.36f, 0.0f);
		glColor3f(1.0f, 0.75f, 0.0f);
		Balloon();
		glPopMatrix();

		// 13
		glPushMatrix();
		glTranslatef(0.02f, BalloonY + 0.40f, 0.0f);
		glColor3f(1.0f, 0.92f, 0.10f);
		Balloon();
		glPopMatrix();

		// 14
		glPushMatrix();
		glTranslatef(0.15f, BalloonY + 0.36f, 0.0f);
		glColor3f(0.7f, 0.1f, 0.9f);
		Balloon();
		glPopMatrix();

		// 15
		glPushMatrix();
		glTranslatef(0.28f, BalloonY + 0.40f, 0.0f);
		glColor3f(1.0f, 0.4f, 0.0f);
		Balloon();
		glPopMatrix();

		// 16
		glPushMatrix();
		glTranslatef(0.40f, BalloonY + 0.35f, 0.0f);
		glColor3f(0.0f, 0.1f, 0.6f);
		Balloon();
		glPopMatrix();

		// 17
		glPushMatrix();
		glTranslatef(-0.46f, BalloonY + 0.22f, 0.0f);
		glColor3f(0.7f, 0.4f, 1.0f);
		Balloon();
		glPopMatrix();

		// 18
		glPushMatrix();
		glTranslatef(-0.32f, BalloonY + 0.25f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		Balloon();
		glPopMatrix();

		// 19
		glPushMatrix();
		glTranslatef(-0.18f, BalloonY + 0.20f, 0.0f);
		glColor3f(1.0f, 0.3f, 0.6f);
		Balloon();
		glPopMatrix();

		// 20
		glPushMatrix();
		glTranslatef(-0.04f, BalloonY + 0.25f, 0.0f);
		glColor3f(0.2f, 0.6f, 1.0f);
		Balloon();
		glPopMatrix();

		// 21
		glPushMatrix();
		glTranslatef(0.10f, BalloonY + 0.20f, 0.0f);
		glColor3f(0.1f, 0.3f, 0.8f);
		Balloon();
		glPopMatrix();

		// 22
		glPushMatrix();
		glTranslatef(0.24f, BalloonY + 0.25f, 0.0f);
		glColor3f(1.0f, 0.92f, 0.10f);
		Balloon();
		glPopMatrix();

		// 23
		glPushMatrix();
		glTranslatef(0.38f, BalloonY + 0.20f, 0.0f);
		glColor3f(1.0f, 0.75f, 0.0f);
		Balloon();
		glPopMatrix();

		// 24
		glPushMatrix();
		glTranslatef(0.50f, BalloonY + 0.23f, 0.0f);
		glColor3f(0.4f, 0.8f, 1.0f);
		Balloon();
		glPopMatrix();


		// 25
		glPushMatrix();
		glTranslatef(-0.36f, BalloonY + 0.08f, 0.0f);
		glColor3f(0.0f, 0.9f, 0.9f);
		Balloon();
		glPopMatrix();

		// 26
		glPushMatrix();
		glTranslatef(-0.22f, BalloonY + 0.10f, 0.0f);
		glColor3f(0.0f, 0.1f, 0.6f);
		Balloon();
		glPopMatrix();

		// 27
		glPushMatrix();
		glTranslatef(-0.08f, BalloonY + 0.06f, 0.0f);
		glColor3f(0.6f, 0.1f, 1.0f);
		Balloon();
		glPopMatrix();

		// 28
		glPushMatrix();
		glTranslatef(0.06f, BalloonY + 0.10f, 0.0f);
		glColor3f(1.0f, 0.9f, 0.1f);
		Balloon();
		glPopMatrix();

		// 29
		glPushMatrix();
		glTranslatef(0.20f, BalloonY + 0.06f, 0.0f);
		glColor3f(0.7f, 0.1f, 0.9f);
		Balloon();
		glPopMatrix();

		// 30
		glPushMatrix();
		glTranslatef(0.34f, BalloonY + 0.09f, 0.0f);
		glColor3f(1.0f, 0.4f, 0.2f);
		Balloon();
		glPopMatrix();


		// 31
		glPushMatrix();
		glTranslatef(-0.22f, BalloonY - 0.06f, 0.0f);
		glColor3f(0.9f, 0.4f, 1.0f);
		Balloon();
		glPopMatrix();

		// 32
		glPushMatrix();
		glTranslatef(-0.10f, BalloonY - 0.03f, 0.0f);
		glColor3f(0.8f, 0.0f, 0.1f);
		Balloon();
		glPopMatrix();

		// 33
		glPushMatrix();
		glTranslatef(0.03f, BalloonY - 0.08f, 0.0f);
		glColor3f(0.0f, 0.1f, 0.6f);
		Balloon();
		glPopMatrix();

		// 34
		glPushMatrix();
		glTranslatef(0.16f, BalloonY - 0.04f, 0.0f);
		glColor3f(1.0f, 0.65f, 0.2f);
		Balloon();
		glPopMatrix();


		// 35
		glPushMatrix();
		glTranslatef(-0.10f, BalloonY - 0.17f, 0.0f);
		glColor3f(0.2f, 0.9f, 0.6f);
		Balloon();
		glPopMatrix();

		// 36
		glPushMatrix();
		glTranslatef(0.02f, BalloonY - 0.20f, 0.0f);
		glColor3f(0.0f, 0.7f, 1.0f);
		Balloon();
		glPopMatrix();

		// 37
		glPushMatrix();
		glTranslatef(0.12f, BalloonY - 0.14f, 0.0f);
		glColor3f(0.0f, 0.1f, 0.6f);
		Balloon();
		glPopMatrix();

		// 38 
		glPushMatrix();
		glTranslatef(-0.58f, BalloonY + 0.30f, 0.0f);
		glColor3f(1.0f, 0.2f, 0.5f);
		Balloon();
		glPopMatrix();

		// 39
		glPushMatrix();
		glTranslatef(-0.52f, BalloonY + 0.48f, 0.0f);
		glColor3f(0.8f, 0.3f, 1.0f);
		Balloon();
		glPopMatrix();

		// 40
		glPushMatrix();
		glTranslatef(-0.42f, BalloonY + 0.66f, 0.0f);
		glColor3f(1.0f, 0.8f, 0.0f);
		Balloon();
		glPopMatrix();

		// 41
		glPushMatrix();
		glTranslatef(-0.28f, BalloonY + 0.82f, 0.0f);
		glColor3f(0.2f, 0.8f, 0.4f);
		Balloon();
		glPopMatrix();

		// 42
		glPushMatrix();
		glTranslatef(0.58f, BalloonY + 0.30f, 0.0f);
		glColor3f(1.0f, 0.25f, 0.4f);
		Balloon();
		glPopMatrix();

		// 43
		glPushMatrix();
		glTranslatef(0.52f, BalloonY + 0.48f, 0.0f);
		glColor3f(0.3f, 0.7f, 1.0f);
		Balloon();
		glPopMatrix();

		// 44
		glPushMatrix();
		glTranslatef(0.42f, BalloonY + 0.66f, 0.0f);
		glColor3f(0.7f, 0.2f, 1.0f);
		Balloon();
		glPopMatrix();

		// 45
		glPushMatrix();
		glTranslatef(0.28f, BalloonY + 0.82f, 0.0f);
		glColor3f(1.0f, 0.7f, 0.1f);
		Balloon();
		glPopMatrix();

		// 46
		glPushMatrix();
		glTranslatef(-0.20f, BalloonY + 0.90f, 0.0f);
		glColor3f(1.0f, 0.3f, 0.6f);
		Balloon();
		glPopMatrix();

		// 47
		glPushMatrix();
		glTranslatef(-0.10f, BalloonY + 0.98f, 0.0f);
		glColor3f(0.2f, 0.8f, 1.0f);
		Balloon();
		glPopMatrix();

		// 48
		glPushMatrix();
		glTranslatef(0.00f, BalloonY + 1.04f, 0.0f);
		glColor3f(1.0f, 0.85f, 0.0f);
		Balloon();
		glPopMatrix();

		// 49
		glPushMatrix();
		glTranslatef(0.10f, BalloonY + 0.98f, 0.0f);
		glColor3f(0.5f, 0.2f, 1.0f);
		Balloon();
		glPopMatrix();

		// 50
		glPushMatrix();
		glTranslatef(0.20f, BalloonY + 0.90f, 0.0f);
		glColor3f(0.1f, 0.8f, 0.5f);
		Balloon();
		glPopMatrix();
	}

	// ONLY after balloons leave the screen
	if (BalloonY > 1.3f)
	{
		DrawMayuresh();
	}


	glutSwapBuffers();
}

void Balloon(void)
{
	glPushMatrix();
	glScalef(0.05f, 0.13f, 1.0f);
	DrawCircle();
	glPopMatrix();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, -0.23f, 0.0f);
	glVertex3f(0.0f, -0.13f, 0.0f);
	glVertex3f(0.01f, -0.13f, 0.0f);
	glVertex3f(0.01f, -0.23f, 0.0f);
	glEnd();

}

void DrawMayuresh(void)
{
	glColor4f(
		1.0f,
		1.0f,
		1.0f,
		MayureshDrawingAlpha
	);
	glBegin(GL_LINES);
	glVertex2f(-0.2500000000f, 0.7000000000f);
	glVertex2f(-0.2688889538f, 0.5990844641f);
	glVertex2f(-0.3759620782f, 0.5659891347f);
	glVertex2f(-0.2500000000f, 0.7000000000f);
	glVertex2f(-0.3759620782f, 0.5659891347f);
	glVertex2f(-0.2688889538f, 0.5990844641f);
	glVertex2f(-0.3701217259f, 0.4634585065f);
	glVertex2f(-0.3759620782f, 0.5659891347f);
	glVertex2f(-0.3701217259f, 0.4634585065f);
	glVertex2f(-0.2688889538f, 0.5990844641f);
	glVertex2f(-0.2688889538f, 0.5990844641f);
	glVertex2f(-0.1450945894f, 0.6787942362f);
	glVertex2f(-0.1450945894f, 0.6787942362f);
	glVertex2f(-0.2500000000f, 0.7000000000f);
	glVertex2f(-0.1450945894f, 0.6787942362f);
	glVertex2f(-0.0800000000f, 0.7400000000f);
	glVertex2f(-0.2500000000f, 0.7000000000f);
	glVertex2f(-0.0800000000f, 0.7400000000f);
	glVertex2f(0.0488016570f, 0.7397845381f);
	glVertex2f(-0.0800000000f, 0.7400000000f);
	glVertex2f(-0.0800000000f, 0.7400000000f);
	glVertex2f(0.0242339060f, 0.6790604743f);
	glVertex2f(0.0242339060f, 0.6790604743f);
	glVertex2f(0.0488016570f, 0.7397845381f);
	glVertex2f(-0.2688889538f, 0.5990844641f);
	glVertex2f(-0.2893330611f, 0.4716683739f);
	glVertex2f(-0.2893330611f, 0.4716683739f);
	glVertex2f(-0.3701217259f, 0.4634585065f);
	glVertex2f(-0.3701217259f, 0.4634585065f);
	glVertex2f(-0.4033500467f, 0.4295906768f);
	glVertex2f(-0.4033500467f, 0.4295906768f);
	glVertex2f(-0.3759620782f, 0.5659891347f);
	glVertex2f(-0.2688889538f, 0.5990844641f);
	glVertex2f(0.0086041809f, 0.6202976586f);
	glVertex2f(0.0086041809f, 0.6202976586f);
	glVertex2f(-0.1450945894f, 0.6787942362f);
	glVertex2f(0.0086041809f, 0.6202976586f);
	glVertex2f(0.0242339060f, 0.6790604743f);
	glVertex2f(0.0086041809f, 0.6202976586f);
	glVertex2f(0.1626628460f, 0.5904360672f);
	glVertex2f(0.1626628460f, 0.5904360672f);
	glVertex2f(0.0242339060f, 0.6790604743f);
	glVertex2f(0.0242339060f, 0.6790604743f);
	glVertex2f(0.1660562086f, 0.7030957077f);
	glVertex2f(0.1660562086f, 0.7030957077f);
	glVertex2f(0.0488016570f, 0.7397845381f);
	glVertex2f(0.1660562086f, 0.7030957077f);
	glVertex2f(0.1626628460f, 0.5904360672f);
	glVertex2f(0.1660562086f, 0.7030957077f);
	glVertex2f(0.2495329302f, 0.5565024405f);
	glVertex2f(0.2495329302f, 0.5565024405f);
	glVertex2f(0.1626628460f, 0.5904360672f);
	glVertex2f(0.2495329302f, 0.5565024405f);
	glVertex2f(0.2500000000f, 0.6500000000f);
	glVertex2f(0.2500000000f, 0.6500000000f);
	glVertex2f(0.1660562086f, 0.7030957077f);
	glVertex2f(0.0086041809f, 0.6202976586f);
	glVertex2f(0.1572334657f, 0.5062806731f);
	glVertex2f(0.1572334657f, 0.5062806731f);
	glVertex2f(0.1626628460f, 0.5904360672f);
	glVertex2f(0.1626628460f, 0.5904360672f);
	glVertex2f(0.2644637260f, 0.4703110288f);
	glVertex2f(0.1572334657f, 0.5062806731f);
	glVertex2f(0.2644637260f, 0.4703110288f);
	glVertex2f(0.1572334657f, 0.5062806731f);
	glVertex2f(-0.1000000000f, 0.5500000000f);
	glVertex2f(-0.1000000000f, 0.5500000000f);
	glVertex2f(0.0086041809f, 0.6202976586f);
	glVertex2f(-0.1000000000f, 0.5500000000f);
	glVertex2f(-0.2893330611f, 0.4716683739f);
	glVertex2f(-0.1000000000f, 0.5500000000f);
	glVertex2f(-0.2688889538f, 0.5990844641f);
	glVertex2f(-0.1000000000f, 0.5500000000f);
	glVertex2f(-0.0205579801f, 0.4736559879f);
	glVertex2f(-0.0205579801f, 0.4736559879f);
	glVertex2f(0.1572334657f, 0.5062806731f);
	glVertex2f(0.1572334657f, 0.5062806731f);
	glVertex2f(0.0864475913f, 0.4460028626f);
	glVertex2f(0.1572334657f, 0.5062806731f);
	glVertex2f(0.1886439236f, 0.4616328899f);
	glVertex2f(0.1886439236f, 0.4616328899f);
	glVertex2f(0.0864475913f, 0.4460028626f);
	glVertex2f(0.1886439236f, 0.4616328899f);
	glVertex2f(0.2644637260f, 0.4703110288f);
	glVertex2f(0.2644637260f, 0.4703110288f);
	glVertex2f(0.2391409349f, 0.4279682158f);
	glVertex2f(0.1886439236f, 0.4616328899f);
	glVertex2f(0.2391409349f, 0.4279682158f);
	glVertex2f(0.2500000000f, 0.6500000000f);
	glVertex2f(0.3449441965f, 0.5433899558f);
	glVertex2f(0.3449441965f, 0.5433899558f);
	glVertex2f(0.2495329302f, 0.5565024405f);
	glVertex2f(0.3449441965f, 0.5433899558f);
	glVertex2f(0.2644637260f, 0.4703110288f);
	glVertex2f(0.3449441965f, 0.5433899558f);
	glVertex2f(0.3100772126f, 0.4147428081f);
	glVertex2f(0.2644637260f, 0.4703110288f);
	glVertex2f(0.3100772126f, 0.4147428081f);
	glVertex2f(0.3100772126f, 0.4147428081f);
	glVertex2f(0.2391409349f, 0.4279682158f);
	glVertex2f(0.3100772126f, 0.4147428081f);
	glVertex2f(0.3000000000f, 0.3000000000f);
	glVertex2f(0.3100772126f, 0.4147428081f);
	glVertex2f(0.3305164790f, 0.3438065304f);
	glVertex2f(0.3305164790f, 0.3438065304f);
	glVertex2f(0.3822158001f, 0.4484074822f);
	glVertex2f(0.3449441965f, 0.5433899558f);
	glVertex2f(0.3822158001f, 0.4484074822f);
	glVertex2f(0.3822158001f, 0.4484074822f);
	glVertex2f(0.3100772126f, 0.4147428081f);
	glVertex2f(0.3822158001f, 0.4484074822f);
	glVertex2f(0.3677880826f, 0.3125464758f);
	glVertex2f(0.3677880826f, 0.3125464758f);
	glVertex2f(0.3293141693f, 0.2824887310f);
	glVertex2f(0.3000000000f, 0.3000000000f);
	glVertex2f(0.3293141693f, 0.2824887310f);
	glVertex2f(0.3677880826f, 0.3125464758f);
	glVertex2f(0.3605742238f, 0.2608471547f);
	glVertex2f(0.3293141693f, 0.2824887310f);
	glVertex2f(0.3605742238f, 0.2608471547f);
	glVertex2f(0.3605742238f, 0.2608471547f);
	glVertex2f(0.3233026203f, 0.2259801708f);
	glVertex2f(0.3293141693f, 0.2824887310f);
	glVertex2f(0.3233026203f, 0.2259801708f);
	glVertex2f(0.3000000000f, 0.3000000000f);
	glVertex2f(0.3233026203f, 0.2259801708f);
	glVertex2f(0.0864475913f, 0.4460028626f);
	glVertex2f(-0.1415254095f, 0.4029332549f);
	glVertex2f(-0.1415254095f, 0.4029332549f);
	glVertex2f(-0.0205579801f, 0.4736559879f);
	glVertex2f(-0.0205579801f, 0.4736559879f);
	glVertex2f(-0.2346390268f, 0.4272602360f);
	glVertex2f(-0.2346390268f, 0.4272602360f);
	glVertex2f(-0.1063422453f, 0.4235028375f);
	glVertex2f(-0.1063422453f, 0.4235028375f);
	glVertex2f(-0.0205579801f, 0.4736559879f);
	glVertex2f(-0.1415254095f, 0.4029332549f);
	glVertex2f(-0.2539328394f, 0.3433740943f);
	glVertex2f(-0.2346390268f, 0.4272602360f);
	glVertex2f(-0.2539328394f, 0.3433740943f);
	glVertex2f(-0.2346390268f, 0.4272602360f);
	glVertex2f(-0.1000000000f, 0.5500000000f);
	glVertex2f(-0.2346390268f, 0.4272602360f);
	glVertex2f(-0.2797350422f, 0.3814196473f);
	glVertex2f(-0.2893330611f, 0.4716683739f);
	glVertex2f(-0.2797350422f, 0.3814196473f);
	glVertex2f(-0.2797350422f, 0.3814196473f);
	glVertex2f(-0.3534256622f, 0.3335207442f);
	glVertex2f(-0.2893330611f, 0.4716683739f);
	glVertex2f(-0.3534256622f, 0.3335207442f);
	glVertex2f(-0.3701217259f, 0.4634585065f);
	glVertex2f(-0.3534256622f, 0.3335207442f);
	glVertex2f(-0.4033500467f, 0.4295906768f);
	glVertex2f(-0.3534256622f, 0.3335207442f);
	glVertex2f(-0.3534256622f, 0.3335207442f);
	glVertex2f(-0.3128958212f, 0.2942190802f);
	glVertex2f(-0.3128958212f, 0.2942190802f);
	glVertex2f(-0.2797350422f, 0.3814196473f);
	glVertex2f(-0.4033500467f, 0.4295906768f);
	glVertex2f(-0.3878146182f, 0.3175544432f);
	glVertex2f(-0.3878146182f, 0.3175544432f);
	glVertex2f(-0.3534256622f, 0.3335207442f);
	glVertex2f(-0.3534256622f, 0.3335207442f);
	glVertex2f(-0.3534256622f, 0.2819373102f);
	glVertex2f(-0.3878146182f, 0.3175544432f);
	glVertex2f(-0.3534256622f, 0.3052726732f);
	glVertex2f(-0.3878146182f, 0.3175544432f);
	glVertex2f(-0.2797350422f, 0.3814196473f);
	glVertex2f(-0.1594022336f, 0.3934612063f);
	glVertex2f(-0.1593736961f, 0.3543997532f);
	glVertex2f(-0.1593736961f, 0.3543997532f);
	glVertex2f(-0.0119924560f, 0.3470306912f);
	glVertex2f(-0.3878146182f, 0.3175544432f);
	glVertex2f(-0.4172908663f, 0.2819373102f);
	glVertex2f(-0.4172908663f, 0.2819373102f);
	glVertex2f(-0.3534256622f, 0.2819373102f);
	glVertex2f(-0.4172908663f, 0.2819373102f);
	glVertex2f(-0.4123781583f, 0.2168439291f);
	glVertex2f(-0.4123781583f, 0.2168439291f);
	glVertex2f(-0.3804455562f, 0.2819373102f);
	glVertex2f(-0.3804455562f, 0.2819373102f);
	glVertex2f(-0.3902709722f, 0.1677168491f);
	glVertex2f(-0.4123781583f, 0.2168439291f);
	glVertex2f(-0.3902709722f, 0.1677168491f);
	glVertex2f(-0.3902709722f, 0.1677168491f);
	glVertex2f(-0.3460566002f, 0.0780599280f);
	glVertex2f(-0.3460566002f, 0.0780599280f);
	glVertex2f(-0.3178085292f, 0.0620936270f);
	glVertex2f(-0.3178085292f, 0.0620936270f);
	glVertex2f(-0.2821913962f, 0.0719190430f);
	glVertex2f(-0.2821913962f, 0.0719190430f);
	glVertex2f(-0.3067549362f, 0.1247306541f);
	glVertex2f(-0.3067549362f, 0.1247306541f);
	glVertex2f(-0.3362311842f, 0.1210461231f);
	glVertex2f(-0.3362311842f, 0.1210461231f);
	glVertex2f(-0.3583383702f, 0.1296433621f);
	glVertex2f(-0.3583383702f, 0.1296433621f);
	glVertex2f(-0.3902709722f, 0.1677168491f);
	glVertex2f(-0.3362311842f, 0.1210461231f);
	glVertex2f(-0.3460566002f, 0.0780599280f);
	glVertex2f(-0.3804455562f, 0.2819373102f);
	glVertex2f(-0.3239494142f, 0.2107030441f);
	glVertex2f(-0.3239494142f, 0.2107030441f);
	glVertex2f(-0.3000000000f, 0.2000000000f);
	glVertex2f(-0.3239494142f, 0.2107030441f);
	glVertex2f(-0.3214930602f, 0.1738577341f);
	glVertex2f(-0.3214930602f, 0.1738577341f);
	glVertex2f(-0.3067549362f, 0.1247306541f);
	glVertex2f(-0.3239494142f, 0.2107030441f);
	glVertex2f(-0.3607947242f, 0.1836831501f);
	glVertex2f(-0.3534256622f, 0.2819373102f);
	glVertex2f(-0.3288621222f, 0.2549174162f);
	glVertex2f(-0.3288621222f, 0.2549174162f);
	glVertex2f(-0.3128958212f, 0.2942190802f);
	glVertex2f(-0.3128958212f, 0.2942190802f);
	glVertex2f(-0.2821913962f, 0.1578914331f);
	glVertex2f(-0.3128958212f, 0.2942190802f);
	glVertex2f(-0.2662250952f, 0.2942190802f);
	glVertex2f(-0.2662250952f, 0.2942190802f);
	glVertex2f(-0.2821913962f, 0.1578914331f);
	glVertex2f(-0.2662250952f, 0.2942190802f);
	glVertex2f(-0.2342924931f, 0.3040444962f);
	glVertex2f(-0.3128958212f, 0.2942190802f);
	glVertex2f(-0.2797350422f, 0.3814196473f);
	glVertex2f(-0.3128958212f, 0.2942190802f);
	glVertex2f(-0.2342924931f, 0.3040444962f);
	glVertex2f(-0.2342924931f, 0.3040444962f);
	glVertex2f(-0.2318361391f, 0.3249235052f);
	glVertex2f(0.0371346241f, 0.3408898062f);
	glVertex2f(-0.0119924560f, 0.3470306912f);
	glVertex2f(0.0864475913f, 0.4460028626f);
	glVertex2f(0.0371346241f, 0.3408898062f);
	glVertex2f(-0.3128958212f, 0.2942190802f);
	glVertex2f(-0.2318361391f, 0.3249235052f);
	glVertex2f(0.0371346241f, 0.3408898062f);
	glVertex2f(0.0223965001f, 0.2966754342f);
	glVertex2f(-0.0119924560f, 0.3470306912f);
	glVertex2f(0.0223965001f, 0.2966754342f);
	glVertex2f(0.0223965001f, 0.2966754342f);
	glVertex2f(0.0825771731f, 0.2929909032f);
	glVertex2f(0.0825771731f, 0.2929909032f);
	glVertex2f(0.1108252441f, 0.3421179832f);
	glVertex2f(0.1108252441f, 0.3421179832f);
	glVertex2f(0.0371346241f, 0.3408898062f);
	glVertex2f(-0.2318361391f, 0.3249235052f);
	glVertex2f(-0.1163875010f, 0.3286080362f);
	glVertex2f(-0.1163875010f, 0.3286080362f);
	glVertex2f(-0.0512941200f, 0.3212389742f);
	glVertex2f(-0.0512941200f, 0.3212389742f);
	glVertex2f(0.0223965001f, 0.2966754342f);
	glVertex2f(-0.2318361391f, 0.3249235052f);
	glVertex2f(-0.2342924931f, 0.3040444962f);
	glVertex2f(-0.2342924931f, 0.3040444962f);
	glVertex2f(-0.2195543691f, 0.2880781952f);
	glVertex2f(-0.2195543691f, 0.2880781952f);
	glVertex2f(-0.2000000000f, 0.2000000000f);
	glVertex2f(-0.2000000000f, 0.2000000000f);
	glVertex2f(-0.1606018731f, 0.1664886721f);
	glVertex2f(-0.1606018731f, 0.1664886721f);
	glVertex2f(-0.0512941200f, 0.1591196101f);
	glVertex2f(-0.0512941200f, 0.1591196101f);
	glVertex2f(-0.0218178720f, 0.1664886721f);
	glVertex2f(-0.0218178720f, 0.1664886721f);
	glVertex2f(0.0285373851f, 0.2635146552f);
	glVertex2f(0.0285373851f, 0.2635146552f);
	glVertex2f(0.0223965001f, 0.2966754342f);
	glVertex2f(-0.2318361391f, 0.3249235052f);
	glVertex2f(-0.1163875010f, 0.3286080362f);
	glVertex2f(-0.1802527051f, 0.3150980892f);
	glVertex2f(-0.2000000000f, 0.3000000000f);
	glVertex2f(-0.1974471831f, 0.2389511152f);
	glVertex2f(-0.2000000000f, 0.3000000000f);
	glVertex2f(-0.2000000000f, 0.3000000000f);
	glVertex2f(-0.1802527051f, 0.3150980892f);
	glVertex2f(0.2391409349f, 0.4279682158f);
	glVertex2f(0.2229519376f, 0.3352925204f);
	glVertex2f(0.2391409349f, 0.4279682158f);
	glVertex2f(0.2729446082f, 0.3937014173f);
	glVertex2f(0.3233026203f, 0.2259801708f);
	glVertex2f(0.2741727852f, -0.0140533470f);
	glVertex2f(0.2841257042f, 0.0345736052f);
	glVertex2f(0.3171589803f, 0.0412146180f);
	glVertex2f(0.3171589803f, 0.0412146180f);
	glVertex2f(0.3797960073f, 0.1812267961f);
	glVertex2f(0.3797960073f, 0.1812267961f);
	glVertex2f(0.3822523613f, 0.2352665842f);
	glVertex2f(0.3822523613f, 0.2352665842f);
	glVertex2f(0.3605742238f, 0.2608471547f);
	glVertex2f(0.3822523613f, 0.2352665842f);
	glVertex2f(0.3540042903f, 0.2303538762f);
	glVertex2f(0.3540042903f, 0.2303538762f);
	glVertex2f(0.3144063363f, 0.1825156175f);
	glVertex2f(0.3540042903f, 0.2303538762f);
	glVertex2f(0.3441788743f, 0.1419251321f);
	glVertex2f(0.3441788743f, 0.1419251321f);
	glVertex2f(0.3183871573f, 0.1099925301f);
	glVertex2f(0.3183871573f, 0.1099925301f);
	glVertex2f(0.2976169515f, 0.1004877601f);
	glVertex2f(0.3144063363f, 0.1825156175f);
	glVertex2f(0.3183871573f, 0.1099925301f);
	glVertex2f(0.2976169515f, 0.1004877601f);
	glVertex2f(0.3159308033f, 0.0891135211f);
	glVertex2f(0.3159308033f, 0.0891135211f);
	glVertex2f(0.3478690749f, 0.1098607119f);
	glVertex2f(0.2741727852f, -0.0140533470f);
	glVertex2f(0.2557501302f, -0.0644086041f);
	glVertex2f(0.2557501302f, -0.0644086041f);
	glVertex2f(0.1155952616f, -0.1821327162f);
	glVertex2f(0.1155952616f, -0.1821327162f);
	glVertex2f(-0.0795421910f, -0.1737163571f);
	glVertex2f(-0.0795421910f, -0.1737163571f);
	glVertex2f(-0.2379770241f, -0.0410732410f);
	glVertex2f(-0.2379770241f, -0.0410732410f);
	glVertex2f(-0.2821913962f, 0.0719190430f);
	glVertex2f(-0.2821913962f, 0.0719190430f);
	glVertex2f(-0.2821913962f, 0.1578914331f);
	glVertex2f(-0.1606018731f, 0.1664886721f);
	glVertex2f(-0.2735941572f, 0.1370124241f);
	glVertex2f(-0.2735941572f, 0.1370124241f);
	glVertex2f(-0.1520046341f, 0.0350737330f);
	glVertex2f(-0.1520046341f, 0.0350737330f);
	glVertex2f(-0.1606018731f, 0.1664886721f);
	glVertex2f(-0.1520046341f, 0.0350737330f);
	glVertex2f(-0.0218178720f, 0.1664886721f);
	glVertex2f(0.0285373851f, 0.2635146552f);
	glVertex2f(0.0297655621f, 0.1517505481f);
	glVertex2f(0.0285373851f, 0.2635146552f);
	glVertex2f(0.0000441886f, 0.0005853441f);
	glVertex2f(0.0592418101f, 0.2757964252f);
	glVertex2f(0.0752081111f, 0.2598301242f);
	glVertex2f(0.0752081111f, 0.2598301242f);
	glVertex2f(0.0838053501f, 0.1517505481f);
	glVertex2f(0.0752081111f, 0.2598301242f);
	glVertex2f(0.1329324301f, 0.1259588311f);
	glVertex2f(0.1329324301f, 0.1259588311f);
	glVertex2f(0.1329324301f, 0.1026234681f);
	glVertex2f(0.1329324301f, 0.1026234681f);
	glVertex2f(0.1120534211f, 0.0866571671f);
	glVertex2f(-0.0218178720f, 0.1664886721f);
	glVertex2f(-0.0439250580f, 0.1345560701f);
	glVertex2f(-0.0439250580f, 0.1345560701f);
	glVertex2f(0.0297655621f, 0.1517505481f);
	glVertex2f(0.0297655621f, 0.1517505481f);
	glVertex2f(0.0838053501f, 0.1517505481f);
	glVertex2f(0.0838053501f, 0.1517505481f);
	glVertex2f(0.1329324301f, 0.1259588311f);
	glVertex2f(-0.0218178720f, 0.1664886721f);
	glVertex2f(0.0297655621f, 0.1517505481f);
	glVertex2f(0.0297655621f, 0.1517505481f);
	glVertex2f(0.0211683231f, 0.1075361761f);
	glVertex2f(0.0874898811f, 0.1026234681f);
	glVertex2f(0.0838053501f, 0.1517505481f);
	glVertex2f(0.0211683231f, 0.1075361761f);
	glVertex2f(0.0383628011f, 0.0854289900f);
	glVertex2f(0.0383628011f, 0.0854289900f);
	glVertex2f(0.0580136331f, 0.0854289900f);
	glVertex2f(0.0580136331f, 0.0854289900f);
	glVertex2f(0.0874898811f, 0.1026234681f);
	glVertex2f(-0.0402405270f, 0.1063079991f);
	glVertex2f(-0.0193615180f, 0.0927980521f);
	glVertex2f(0.0211683231f, 0.1075361761f);
	glVertex2f(-0.0402405270f, 0.1063079991f);
	glVertex2f(0.1329324301f, 0.1259588311f);
	glVertex2f(0.1120534211f, 0.0866571671f);
	glVertex2f(0.1329324301f, 0.1259588311f);
	glVertex2f(0.1120534211f, 0.0866571671f);
	glVertex2f(-0.1520046341f, 0.0350737330f);
	glVertex2f(-0.0537504740f, -0.1295019851f);
	glVertex2f(-0.0537504740f, -0.1295019851f);
	glVertex2f(-0.1884231087f, -0.0825602400f);
	glVertex2f(-0.2379770241f, -0.0410732410f);
	glVertex2f(-0.1884231087f, -0.0825602400f);
	glVertex2f(0.1132200916f, 0.0991570171f);
	glVertex2f(0.0874898811f, 0.1026234681f);
	glVertex2f(0.1132200916f, 0.0991570171f);
	glVertex2f(0.1120534211f, 0.0866571671f);
	glVertex2f(-0.0199201035f, 0.1055015266f);
	glVertex2f(-0.0193615180f, 0.0927980521f);
	glVertex2f(0.0211683231f, 0.1075361761f);
	glVertex2f(0.0567205570f, 0.1022243566f);
	glVertex2f(0.0567205570f, 0.1022243566f);
	glVertex2f(0.0874898811f, 0.1026234681f);
	glVertex2f(-0.1520046341f, 0.0350737330f);
	glVertex2f(-0.1062044730f, 0.0179604289f);
	glVertex2f(-0.1062044730f, 0.0179604289f);
	glVertex2f(-0.0903523825f, 0.0285924563f);
	glVertex2f(-0.0903523825f, 0.0285924563f);
	glVertex2f(-0.0824473702f, -0.0162876131f);
	glVertex2f(-0.0824473702f, -0.0162876131f);
	glVertex2f(-0.0537504740f, -0.1295019851f);
	glVertex2f(0.1586237008f, 0.0125498634f);
	glVertex2f(0.1210080926f, -0.1280890096f);
	glVertex2f(-0.0903523825f, 0.0285924563f);
	glVertex2f(0.0256082513f, 0.0273293578f);
	glVertex2f(0.0256082513f, 0.0273293578f);
	glVertex2f(0.0447346558f, 0.0238518297f);
	glVertex2f(0.0447346558f, 0.0238518297f);
	glVertex2f(0.0742936446f, 0.0281987398f);
	glVertex2f(0.0742936446f, 0.0281987398f);
	glVertex2f(0.1586237008f, 0.0125498634f);
	glVertex2f(-0.0903523825f, 0.0285924563f);
	glVertex2f(-0.0074282656f, 0.0047254252f);
	glVertex2f(-0.0074282656f, 0.0047254252f);
	glVertex2f(0.1000000000f, 0.0000000000f);
	glVertex2f(0.1000000000f, 0.0000000000f);
	glVertex2f(0.1586237008f, 0.0125498634f);
	glVertex2f(-0.1802527051f, 0.3150980892f);
	glVertex2f(-0.1400000000f, 0.3200000000f);
	glVertex2f(-0.1974471831f, 0.2389511152f);
	glVertex2f(-0.1867107040f, 0.1988972156f);
	glVertex2f(-0.1867107040f, 0.1988972156f);
	glVertex2f(-0.1593943148f, 0.1762304246f);
	glVertex2f(-0.1593943148f, 0.1762304246f);
	glVertex2f(-0.0536159566f, 0.1704184269f);
	glVertex2f(-0.0536159566f, 0.1704184269f);
	glVertex2f(-0.0367611632f, 0.1750680251f);
	glVertex2f(-0.0367611632f, 0.1750680251f);
	glVertex2f(-0.0204875696f, 0.1936664177f);
	glVertex2f(-0.0204875696f, 0.1936664177f);
	glVertex2f(0.0074100193f, 0.2575983925f);
	glVertex2f(0.0074100193f, 0.2575983925f);
	glVertex2f(0.0138032168f, 0.2854959814f);
	glVertex2f(0.0138032168f, 0.2854959814f);
	glVertex2f(-0.0077011747f, 0.3011883752f);
	glVertex2f(-0.0571031552f, 0.3145559700f);
	glVertex2f(-0.0077011747f, 0.3011883752f);
	glVertex2f(-0.0571031552f, 0.3145559700f);
	glVertex2f(-0.1400000000f, 0.3200000000f);
	glVertex2f(-0.0571031552f, 0.3145559700f);
	glVertex2f(-0.0664023515f, 0.3006071755f);
	glVertex2f(-0.0664023515f, 0.3006071755f);
	glVertex2f(-0.0571031552f, 0.3145559700f);
	glVertex2f(-0.0571031552f, 0.3145559700f);
	glVertex2f(-0.0158379715f, 0.2709659872f);
	glVertex2f(-0.1652063125f, 0.2628291904f);
	glVertex2f(-0.1506763182f, 0.2849147817f);
	glVertex2f(-0.1506763182f, 0.2849147817f);
	glVertex2f(-0.1175479313f, 0.3000259757f);
	glVertex2f(-0.1175479313f, 0.3000259757f);
	glVertex2f(-0.0664023515f, 0.3006071755f);
	glVertex2f(-0.0664023515f, 0.3006071755f);
	glVertex2f(-0.0466415593f, 0.2924703787f);
	glVertex2f(-0.0466415593f, 0.2924703787f);
	glVertex2f(-0.0158379715f, 0.2709659872f);
	glVertex2f(-0.1987133592f, 0.2692308573f);
	glVertex2f(-0.1652063125f, 0.2628291904f);
	glVertex2f(-0.1652063125f, 0.2628291904f);
	glVertex2f(-0.1274283274f, 0.2337692019f);
	glVertex2f(-0.1274283274f, 0.2337692019f);
	glVertex2f(-0.1059239359f, 0.2233076060f);
	glVertex2f(-0.1059239359f, 0.2233076060f);
	glVertex2f(-0.1593943148f, 0.1762304246f);
	glVertex2f(-0.1059239359f, 0.2233076060f);
	glVertex2f(-0.0716331495f, 0.2302820033f);
	glVertex2f(-0.0716331495f, 0.2302820033f);
	glVertex2f(-0.0233935685f, 0.2512051950f);
	glVertex2f(-0.1652063125f, 0.2628291904f);
	glVertex2f(-0.1124722770f, 0.2468661661f);
	glVertex2f(-0.1124722770f, 0.2468661661f);
	glVertex2f(-0.0806245964f, 0.2471979128f);
	glVertex2f(-0.0806245964f, 0.2471979128f);
	glVertex2f(-0.0233935685f, 0.2512051950f);
	glVertex2f(-0.1349839244f, 0.2843335819f);
	glVertex2f(-0.1652063125f, 0.2628291904f);
	glVertex2f(-0.1349839244f, 0.2843335819f);
	glVertex2f(-0.1183836307f, 0.2922171167f);
	glVertex2f(-0.1183836307f, 0.2922171167f);
	glVertex2f(-0.1134178985f, 0.2936137288f);
	glVertex2f(-0.1134178985f, 0.2936137288f);
	glVertex2f(-0.0693470250f, 0.2946999828f);
	glVertex2f(-0.0693470250f, 0.2946999828f);
	glVertex2f(-0.0494840961f, 0.2841478018f);
	glVertex2f(-0.0494840961f, 0.2841478018f);
	glVertex2f(-0.0243450768f, 0.2594743198f);
	glVertex2f(-0.0243450768f, 0.2594743198f);
	glVertex2f(-0.0193793446f, 0.2528016172f);
	glVertex2f(-0.0193793446f, 0.2528016172f);
	glVertex2f(-0.0233935685f, 0.2512051950f);
	glVertex2f(-0.0700000000f, 0.2900000000f);
	glVertex2f(-0.0693470250f, 0.2946999828f);
	glVertex2f(-0.1126420028f, 0.2889583549f);
	glVertex2f(-0.1134178985f, 0.2936137288f);
	glVertex2f(-0.1126420028f, 0.2889583549f);
	glVertex2f(-0.1332808273f, 0.2799579652f);
	glVertex2f(-0.1332808273f, 0.2799579652f);
	glVertex2f(-0.1520575023f, 0.2670780973f);
	glVertex2f(-0.1520575023f, 0.2670780973f);
	glVertex2f(-0.1652063125f, 0.2628291904f);
	glVertex2f(-0.1126420028f, 0.2889583549f);
	glVertex2f(-0.0700000000f, 0.2900000000f);
	glVertex2f(-0.0700000000f, 0.2900000000f);
	glVertex2f(-0.0509568957f, 0.2793106322f);
	glVertex2f(-0.0509568957f, 0.2793106322f);
	glVertex2f(-0.0193793446f, 0.2528016172f);
	glVertex2f(-0.0326146567f, 0.2639125196f);
	glVertex2f(-0.0401907297f, 0.2495453498f);
	glVertex2f(-0.0401907297f, 0.2495453498f);
	glVertex2f(-0.0233935685f, 0.2512051950f);
	glVertex2f(-0.1126420028f, 0.2889583549f);
	glVertex2f(-0.1172826037f, 0.2821971868f);
	glVertex2f(-0.1172826037f, 0.2821971868f);
	glVertex2f(-0.1199365771f, 0.2740693933f);
	glVertex2f(-0.1199365771f, 0.2740693933f);
	glVertex2f(-0.1199365771f, 0.2629558798f);
	glVertex2f(-0.1199365771f, 0.2629558798f);
	glVertex2f(-0.1172826037f, 0.2564868196f);
	glVertex2f(-0.1172826037f, 0.2564868196f);
	glVertex2f(-0.1123064036f, 0.2520082396f);
	glVertex2f(-0.1123064036f, 0.2520082396f);
	glVertex2f(-0.1089889369f, 0.2476955328f);
	glVertex2f(-0.0806245964f, 0.2471979128f);
	glVertex2f(-0.1124722770f, 0.2468661661f);
	glVertex2f(-0.1089889369f, 0.2476955328f);
	glVertex2f(-0.0806245964f, 0.2471979128f);
	glVertex2f(-0.0806245964f, 0.2471979128f);
	glVertex2f(-0.0739896629f, 0.2511788729f);
	glVertex2f(-0.0739896629f, 0.2511788729f);
	glVertex2f(-0.0688475895f, 0.2576479330f);
	glVertex2f(-0.0688475895f, 0.2576479330f);
	glVertex2f(-0.0660277428f, 0.2632876264f);
	glVertex2f(-0.0660277428f, 0.2632876264f);
	glVertex2f(-0.0665253628f, 0.2702543066f);
	glVertex2f(-0.0665253628f, 0.2702543066f);
	glVertex2f(-0.0665253628f, 0.2770551133f);
	glVertex2f(-0.0665253628f, 0.2770551133f);
	glVertex2f(-0.0688475895f, 0.2830265535f);
	glVertex2f(-0.0688475895f, 0.2830265535f);
	glVertex2f(-0.0725035781f, 0.2899388434f);
	glVertex2f(-0.1593736961f, 0.3543997532f);
	glVertex2f(-0.1589139564f, 0.3483364162f);
	glVertex2f(-0.1589139564f, 0.3483364162f);
	glVertex2f(-0.1797923962f, 0.3359509011f);
	glVertex2f(-0.1797923962f, 0.3359509011f);
	glVertex2f(-0.0853086096f, 0.3327660543f);
	glVertex2f(-0.0853086096f, 0.3327660543f);
	glVertex2f(-0.0279813683f, 0.3260424890f);
	glVertex2f(-0.0279813683f, 0.3260424890f);
	glVertex2f(0.0051416587f, 0.3219414519f);
	glVertex2f(0.0825771731f, 0.2929909032f);
	glVertex2f(0.0718773113f, 0.2631609240f);
	glVertex2f(0.0825771731f, 0.2929909032f);
	glVertex2f(0.0880790655f, 0.2806200697f);
	glVertex2f(0.0880790655f, 0.2806200697f);
	glVertex2f(0.1295729863f, 0.2982235513f);
	glVertex2f(0.1295729863f, 0.2982235513f);
	glVertex2f(0.1471764678f, 0.3016813780f);
	glVertex2f(0.1471764678f, 0.3016813780f);
	glVertex2f(0.2072169138f, 0.3004239865f);
	glVertex2f(0.2072169138f, 0.3004239865f);
	glVertex2f(0.2650569246f, 0.2906792020f);
	glVertex2f(0.2650569246f, 0.2906792020f);
	glVertex2f(0.2807743188f, 0.2825061570f);
	glVertex2f(0.2807743188f, 0.2825061570f);
	glVertex2f(0.2914621469f, 0.2645883276f);
	glVertex2f(0.2914621469f, 0.2645883276f);
	glVertex2f(0.2800000000f, 0.2000000000f);
	glVertex2f(0.2800000000f, 0.2000000000f);
	glVertex2f(0.2678860555f, 0.1712270059f);
	glVertex2f(0.2678860555f, 0.1712270059f);
	glVertex2f(0.2402234417f, 0.1517374371f);
	glVertex2f(0.2402234417f, 0.1517374371f);
	glVertex2f(0.1987295209f, 0.1501656976f);
	glVertex2f(0.1987295209f, 0.1501656976f);
	glVertex2f(0.1400000000f, 0.1600000000f);
	glVertex2f(0.1400000000f, 0.1600000000f);
	glVertex2f(0.1207712455f, 0.1702839622f);
	glVertex2f(0.1207712455f, 0.1702839622f);
	glVertex2f(0.1113408090f, 0.1838009213f);
	glVertex2f(0.1113408090f, 0.1838009213f);
	glVertex2f(0.0981381978f, 0.2155500576f);
	glVertex2f(0.0981381978f, 0.2155500576f);
	glVertex2f(0.0912225444f, 0.2476135419f);
	glVertex2f(0.0912225444f, 0.2476135419f);
	glVertex2f(0.0880790655f, 0.2806200697f);
	glVertex2f(0.0912225444f, 0.2476135419f);
	glVertex2f(0.1352312482f, 0.2979092034f);
	glVertex2f(0.1078829823f, 0.2488709334f);
	glVertex2f(0.1264295075f, 0.2677318065f);
	glVertex2f(0.1264295075f, 0.2677318065f);
	glVertex2f(0.1471764678f, 0.2806200697f);
	glVertex2f(0.1471764678f, 0.2806200697f);
	glVertex2f(0.1547208171f, 0.2828205049f);
	glVertex2f(0.1547208171f, 0.2828205049f);
	glVertex2f(0.1955860421f, 0.2803057219f);
	glVertex2f(0.1955860421f, 0.2803057219f);
	glVertex2f(0.2172760461f, 0.2664744149f);
	glVertex2f(0.2172760461f, 0.2664744149f);
	glVertex2f(0.2361369192f, 0.2482422376f);
	glVertex2f(0.1930712590f, 0.2749618078f);
	glVertex2f(0.1955860421f, 0.2803057219f);
	glVertex2f(0.1930712590f, 0.2749618078f);
	glVertex2f(0.2125608278f, 0.2642739797f);
	glVertex2f(0.2125608278f, 0.2642739797f);
	glVertex2f(0.2361369192f, 0.2482422376f);
	glVertex2f(0.1078829823f, 0.2488709334f);
	glVertex2f(0.1185708103f, 0.2454131067f);
	glVertex2f(0.1185708103f, 0.2454131067f);
	glVertex2f(0.1400000000f, 0.2400000000f);
	glVertex2f(0.1400000000f, 0.2400000000f);
	glVertex2f(0.1968434336f, 0.2359826701f);
	glVertex2f(0.1968434336f, 0.2359826701f);
	glVertex2f(0.2361369192f, 0.2482422376f);
	glVertex2f(0.1078829823f, 0.2488709334f);
	glVertex2f(0.1144842878f, 0.2400691926f);
	glVertex2f(0.1144842878f, 0.2400691926f);
	glVertex2f(0.1600000000f, 0.2200000000f);
	glVertex2f(0.1600000000f, 0.2200000000f);
	glVertex2f(0.1814403873f, 0.2105204915f);
	glVertex2f(0.1814403873f, 0.2105204915f);
	glVertex2f(0.2166473503f, 0.2290670167f);
	glVertex2f(0.2166473503f, 0.2290670167f);
	glVertex2f(0.2361369192f, 0.2482422376f);
	glVertex2f(0.1829924446f, 0.2369615693f);
	glVertex2f(0.1814403873f, 0.2105204915f);
	glVertex2f(0.1814403873f, 0.2105204915f);
	glVertex2f(0.2298410439f, 0.1513441644f);
	glVertex2f(0.2361369192f, 0.2482422376f);
	glVertex2f(0.2800000000f, 0.2000000000f);
	glVertex2f(0.2361369192f, 0.2482422376f);
	glVertex2f(0.2914621469f, 0.2645883276f);
	glVertex2f(0.2072169138f, 0.3004239865f);
	glVertex2f(0.1955860421f, 0.2803057219f);
	glVertex2f(0.1078829823f, 0.2488709334f);
	glVertex2f(0.1081973301f, 0.2705609374f);
	glVertex2f(0.1081973301f, 0.2705609374f);
	glVertex2f(0.1267438553f, 0.2803057219f);
	glVertex2f(0.1267438553f, 0.2803057219f);
	glVertex2f(0.1515773382f, 0.2906792020f);
	glVertex2f(0.1940143026f, 0.2881644190f);
	glVertex2f(0.1515773382f, 0.2906792020f);
	glVertex2f(0.1940143026f, 0.2881644190f);
	glVertex2f(0.2081599574f, 0.2828205049f);
	glVertex2f(0.2216769165f, 0.2746474599f);
	glVertex2f(0.2081599574f, 0.2828205049f);
	glVertex2f(0.2216769165f, 0.2746474599f);
	glVertex2f(0.2337590478f, 0.2614833467f);
	glVertex2f(0.2337590478f, 0.2614833467f);
	glVertex2f(0.2361369192f, 0.2482422376f);
	glVertex2f(0.1514317458f, 0.2762535891f);
	glVertex2f(0.1547208171f, 0.2828205049f);
	glVertex2f(0.1514317458f, 0.2762535891f);
	glVertex2f(0.1452783225f, 0.2705396961f);
	glVertex2f(0.1452783225f, 0.2705396961f);
	glVertex2f(0.1430806713f, 0.2637269774f);
	glVertex2f(0.1430806713f, 0.2637269774f);
	glVertex2f(0.1430806713f, 0.2577933192f);
	glVertex2f(0.1430806713f, 0.2577933192f);
	glVertex2f(0.1430806713f, 0.2507608355f);
	glVertex2f(0.1430806713f, 0.2507608355f);
	glVertex2f(0.1472562086f, 0.2446074122f);
	glVertex2f(0.1472562086f, 0.2446074122f);
	glVertex2f(0.1505780495f, 0.2392524112f);
	glVertex2f(0.1505780495f, 0.2392524112f);
	glVertex2f(0.1829924446f, 0.2369615693f);
	glVertex2f(0.1829924446f, 0.2369615693f);
	glVertex2f(0.1890115809f, 0.2439481168f);
	glVertex2f(0.1890115809f, 0.2439481168f);
	glVertex2f(0.1947254740f, 0.2512003657f);
	glVertex2f(0.1947254740f, 0.2512003657f);
	glVertex2f(0.1949452391f, 0.2602107355f);
	glVertex2f(0.1949452391f, 0.2602107355f);
	glVertex2f(0.1931871181f, 0.2687815751f);
	glVertex2f(0.1595521198f, 0.2779702077f);
	glVertex2f(0.1514317458f, 0.2762535891f);
	glVertex2f(0.1595521198f, 0.2779702077f);
	glVertex2f(0.1701661951f, 0.2778375317f);
	glVertex2f(0.1701661951f, 0.2778375317f);
	glVertex2f(0.1806475945f, 0.2771741520f);
	glVertex2f(0.1806475945f, 0.2771741520f);
	glVertex2f(0.1875467435f, 0.2751840129f);
	glVertex2f(0.1875467435f, 0.2751840129f);
	glVertex2f(0.1911289939f, 0.2719997903f);
	glVertex2f(0.1911289939f, 0.2719997903f);
	glVertex2f(0.1931871181f, 0.2687815751f);
	glVertex2f(0.1911289939f, 0.2719997903f);
	glVertex2f(0.1930712590f, 0.2749618078f);
	glVertex2f(-0.1010185630f, 0.3912056841f);
	glVertex2f(-0.1594022336f, 0.3934612063f);
	glVertex2f(-0.1010185630f, 0.3912056841f);
	glVertex2f(0.0445940991f, 0.4345485835f);
	glVertex2f(0.1108252441f, 0.3421179832f);
	glVertex2f(0.1253397415f, 0.3458193258f);
	glVertex2f(0.2229519376f, 0.3352925204f);
	glVertex2f(0.1253397415f, 0.3458193258f);
	glVertex2f(0.2229519376f, 0.3352925204f);
	glVertex2f(0.2344357253f, 0.3309860999f);
	glVertex2f(0.2344357253f, 0.3309860999f);
	glVertex2f(0.2550108451f, 0.3151958918f);
	glVertex2f(0.2550108451f, 0.3151958918f);
	glVertex2f(0.2645806682f, 0.3008411571f);
	glVertex2f(0.2645806682f, 0.3008411571f);
	glVertex2f(0.2004628532f, 0.3094539979f);
	glVertex2f(0.2004628532f, 0.3094539979f);
	glVertex2f(0.1487858082f, 0.3089755067f);
	glVertex2f(0.1487858082f, 0.3089755067f);
	glVertex2f(0.0825771731f, 0.2929909032f);
	glVertex2f(0.1013918972f, 0.3257121624f);
	glVertex2f(0.1138559538f, 0.3185453299f);
	glVertex2f(0.1138559538f, 0.3185453299f);
	glVertex2f(0.1507825170f, 0.3198598524f);
	glVertex2f(0.1507825170f, 0.3198598524f);
	glVertex2f(0.2000000000f, 0.3200000000f);
	glVertex2f(0.2000000000f, 0.3200000000f);
	glVertex2f(0.2550108451f, 0.3151958918f);
	glVertex2f(-0.1146047170f, 0.0510472492f);
	glVertex2f(-0.1154846949f, 0.0214279988f);
	glVertex2f(-0.1146047170f, 0.0510472492f);
	glVertex2f(-0.0854933470f, 0.0647360406f);
	glVertex2f(-0.0854933470f, 0.0647360406f);
	glVertex2f(-0.0482806828f, 0.0732302357f);
	glVertex2f(-0.0482806828f, 0.0732302357f);
	glVertex2f(-0.0126859606f, 0.0780840615f);
	glVertex2f(-0.0402405270f, 0.1063079991f);
	glVertex2f(-0.0482806828f, 0.0732302357f);
	glVertex2f(-0.0402405270f, 0.1063079991f);
	glVertex2f(-0.0199201035f, 0.1055015266f);
	glVertex2f(-0.0193615180f, 0.0927980521f);
	glVertex2f(-0.0402405270f, 0.1063079991f);
	glVertex2f(-0.0193615180f, 0.0927980521f);
	glVertex2f(-0.0126859606f, 0.0780840615f);
	glVertex2f(0.1120534211f, 0.0866571671f);
	glVertex2f(0.1057031916f, 0.0862909561f);
	glVertex2f(0.1057031916f, 0.0862909561f);
	glVertex2f(0.1064925278f, 0.0744509132f);
	glVertex2f(-0.0126859606f, 0.0780840615f);
	glVertex2f(0.0383628011f, 0.0854289900f);
	glVertex2f(0.0580136331f, 0.0854289900f);
	glVertex2f(0.0800000000f, 0.0800000000f);
	glVertex2f(0.0800000000f, 0.0800000000f);
	glVertex2f(0.1064925278f, 0.0744509132f);
	glVertex2f(0.1064925278f, 0.0744509132f);
	glVertex2f(0.1400000000f, 0.0600000000f);
	glVertex2f(0.1400000000f, 0.0600000000f);
	glVertex2f(0.1688769914f, 0.0460022662f);
	glVertex2f(0.1688769914f, 0.0460022662f);
	glVertex2f(0.1873092970f, 0.0320910921f);
	glVertex2f(0.1873092970f, 0.0320910921f);
	glVertex2f(0.1876570764f, 0.0223532702f);
	glVertex2f(0.1876570764f, 0.0223532702f);
	glVertex2f(0.1831359448f, 0.0115721103f);
	glVertex2f(-0.0903523825f, 0.0285924563f);
	glVertex2f(-0.0693518646f, 0.0428722520f);
	glVertex2f(-0.0693518646f, 0.0428722520f);
	glVertex2f(-0.0220538727f, 0.0487845010f);
	glVertex2f(-0.0220538727f, 0.0487845010f);
	glVertex2f(0.0301130300f, 0.0567834261f);
	glVertex2f(0.0383628011f, 0.0854289900f);
	glVertex2f(0.0301130300f, 0.0567834261f);
	glVertex2f(0.0580136331f, 0.0854289900f);
	glVertex2f(0.0655865239f, 0.0567834261f);
	glVertex2f(0.0655865239f, 0.0567834261f);
	glVertex2f(0.1111456190f, 0.0439155900f);
	glVertex2f(0.1111456190f, 0.0439155900f);
	glVertex2f(0.1452279955f, 0.0317433127f);
	glVertex2f(0.1452279955f, 0.0317433127f);
	glVertex2f(0.1563569347f, 0.0199188148f);
	glVertex2f(0.1563569347f, 0.0199188148f);
	glVertex2f(0.1744414610f, 0.0018342885f);
	glVertex2f(0.1744414610f, 0.0018342885f);
	glVertex2f(0.1831359448f, 0.0115721103f);
	glVertex2f(-0.0766798093f, 0.0284435282f);
	glVertex2f(-0.0446595306f, 0.0366122237f);
	glVertex2f(-0.0446595306f, 0.0366122237f);
	glVertex2f(0.0158540766f, 0.0477411629f);
	glVertex2f(0.0158540766f, 0.0477411629f);
	glVertex2f(0.0280263539f, 0.0487845010f);
	glVertex2f(0.0280263539f, 0.0487845010f);
	glVertex2f(0.0468064389f, 0.0432200313f);
	glVertex2f(0.0468064389f, 0.0432200313f);
	glVertex2f(0.0687165381f, 0.0477411629f);
	glVertex2f(0.0687165381f, 0.0477411629f);
	glVertex2f(0.1000000000f, 0.0400000000f);
	glVertex2f(0.1000000000f, 0.0400000000f);
	glVertex2f(0.1476624509f, 0.0195710354f);
	glVertex2f(0.1476624509f, 0.0195710354f);
	glVertex2f(0.1563569347f, 0.0199188148f);
	glVertex2f(0.1177855893f, 0.0217109849f);
	glVertex2f(0.0742936446f, 0.0281987398f);
	glVertex2f(0.1177855893f, 0.0217109849f);
	glVertex2f(0.1476624509f, 0.0195710354f);
	glVertex2f(0.1563569347f, 0.0199188148f);
	glVertex2f(0.1586237008f, 0.0125498634f);
	glVertex2f(0.0485639782f, -0.0159701855f);
	glVertex2f(0.0145600591f, -0.0159701855f);
	glVertex2f(0.0145600591f, -0.0159701855f);
	glVertex2f(0.0017049189f, -0.0246785062f);
	glVertex2f(0.0017049189f, -0.0246785062f);
	glVertex2f(0.0095838758f, -0.0317280992f);
	glVertex2f(0.0095838758f, -0.0317280992f);
	glVertex2f(0.0270005173f, -0.0362896005f);
	glVertex2f(0.0270005173f, -0.0362896005f);
	glVertex2f(0.0448318407f, -0.0420951477f);
	glVertex2f(0.0448318407f, -0.0420951477f);
	glVertex2f(0.0655659377f, -0.0379483283f);
	glVertex2f(0.0655659377f, -0.0379483283f);
	glVertex2f(0.0842266250f, -0.0325574631f);
	glVertex2f(0.0842266250f, -0.0325574631f);
	glVertex2f(0.0896374851f, -0.0266605511f);
	glVertex2f(0.0896374851f, -0.0266605511f);
	glVertex2f(0.0799056855f, -0.0167124893f);
	glVertex2f(0.0365274210f, -0.0393913832f);
	glVertex2f(0.0489860408f, -0.0576370918f);
	glVertex2f(0.0501165932f, -0.0431660211f);
	glVertex2f(0.0489860408f, -0.0576370918f);
	glVertex2f(0.0655659377f, -0.0379483283f);
	glVertex2f(0.0489860408f, -0.0576370918f);
	glVertex2f(0.0489860408f, -0.0576370918f);
	glVertex2f(-0.0199963109f, -0.1244579950f);
	glVertex2f(0.0489860408f, -0.0576370918f);
	glVertex2f(0.0332585711f, -0.1190114729f);
	glVertex2f(0.0489860408f, -0.0576370918f);
	glVertex2f(0.0701738870f, -0.1190114729f);
	glVertex2f(0.0489860408f, -0.0576370918f);
	glVertex2f(0.1210080926f, -0.1280890096f);
	glVertex2f(-0.0199963109f, -0.1244579950f);
	glVertex2f(0.0332585711f, -0.1190114729f);
	glVertex2f(0.0332585711f, -0.1190114729f);
	glVertex2f(0.0701738870f, -0.1190114729f);
	glVertex2f(0.0701738870f, -0.1190114729f);
	glVertex2f(0.1210080926f, -0.1280890096f);
	glVertex2f(-0.0537504740f, -0.1295019851f);
	glVertex2f(0.0500000000f, -0.1500000000f);
	glVertex2f(0.0500000000f, -0.1500000000f);
	glVertex2f(0.0818974396f, -0.1475058712f);
	glVertex2f(0.0818974396f, -0.1475058712f);
	glVertex2f(0.1210080926f, -0.1280890096f);
	glVertex2f(0.0018783809f, -0.1404925961f);
	glVertex2f(-0.0537504740f, -0.1295019851f);
	glVertex2f(0.0018783809f, -0.1404925961f);
	glVertex2f(0.0500000000f, -0.1500000000f);
	glVertex2f(0.1210080926f, -0.1280890096f);
	glVertex2f(0.2557501302f, -0.0644086041f);
	glVertex2f(0.2976169515f, 0.1004877601f);
	glVertex2f(0.2280626072f, 0.0198394000f);
	glVertex2f(0.2298410439f, 0.1513441644f);
	glVertex2f(0.2280626072f, 0.0198394000f);
	glVertex2f(0.2296542544f, 0.1375321939f);
	glVertex2f(0.1671417437f, 0.1449741466f);
	glVertex2f(0.1329324301f, 0.1259588311f);
	glVertex2f(0.2280626072f, 0.0198394000f);
	glVertex2f(0.2280626072f, 0.0198394000f);
	glVertex2f(0.1876570764f, 0.0223532702f);
	glVertex2f(0.1873092970f, 0.0320910921f);
	glVertex2f(0.2280626072f, 0.0198394000f);
	glVertex2f(0.2280626072f, 0.0198394000f);
	glVertex2f(0.1210080926f, -0.1280890096f);
	glVertex2f(0.3144063363f, 0.1825156175f);
	glVertex2f(0.3441788743f, 0.1419251321f);
	glVertex2f(0.3085385228f, 0.2542191136f);
	glVertex2f(0.2978348856f, 0.2915092045f);
	glVertex2f(0.3085385228f, 0.2542191136f);
	glVertex2f(0.2981801642f, 0.2131309580f);
	glVertex2f(0.2981801642f, 0.2131309580f);
	glVertex2f(0.2816067905f, 0.1720428023f);
	glVertex2f(0.2816067905f, 0.1720428023f);
	glVertex2f(0.2671050885f, 0.1544335927f);
	glVertex2f(0.2671050885f, 0.1544335927f);
	glVertex2f(0.2439714210f, 0.1437299555f);
	glVertex2f(0.2439714210f, 0.1437299555f);
	glVertex2f(0.2296542544f, 0.1375321939f);
	glVertex2f(0.0838053501f, 0.1517505481f);
	glVertex2f(0.1089674810f, 0.1647919513f);
	glVertex2f(0.1089674810f, 0.1647919513f);
	glVertex2f(0.1431500643f, 0.1485638562f);
	glVertex2f(0.1431500643f, 0.1485638562f);
	glVertex2f(0.1671417437f, 0.1449741466f);
	glVertex2f(-0.2821913962f, 0.0719190430f);
	glVertex2f(-0.2686998329f, 0.0222310550f);
	glVertex2f(-0.2686998329f, 0.0222310550f);
	glVertex2f(-0.2589884011f, -0.0196494947f);
	glVertex2f(-0.2589884011f, -0.0196494947f);
	glVertex2f(-0.2541326852f, -0.1137289906f);
	glVertex2f(-0.2541326852f, -0.1137289906f);
	glVertex2f(-0.2572777083f, -0.2232773198f);
	glVertex2f(-0.2572777083f, -0.2232773198f);
	glVertex2f(-0.1132715958f, -0.3274245976f);
	glVertex2f(-0.2379770241f, -0.0410732410f);
	glVertex2f(-0.1132715958f, -0.3274245976f);
	glVertex2f(-0.0795421910f, -0.1737163571f);
	glVertex2f(-0.1261292844f, -0.2772796120f);
	glVertex2f(-0.0795421910f, -0.1737163571f);
	glVertex2f(0.0127337526f, -0.2772796120f);
	glVertex2f(0.0018783809f, -0.1404925961f);
	glVertex2f(-0.0004808062f, -0.2624486315f);
	glVertex2f(0.1155952616f, -0.1821327162f);
	glVertex2f(0.1143094927f, -0.2927088383f);
	glVertex2f(0.1143094927f, -0.2927088383f);
	glVertex2f(0.1155952616f, -0.1821327162f);
	glVertex2f(0.1155952616f, -0.1821327162f);
	glVertex2f(0.0127337526f, -0.2772796120f);
	glVertex2f(0.1143094927f, -0.2927088383f);
	glVertex2f(0.1773121669f, -0.2245630887f);
	glVertex2f(0.1882077306f, -0.1211413391f);
	glVertex2f(0.1773121669f, -0.2245630887f);
	glVertex2f(0.1799342579f, -0.1996739462f);
	glVertex2f(0.2207046172f, -0.2426737486f);
	glVertex2f(0.2207046172f, -0.2426737486f);
	glVertex2f(0.2256216869f, -0.3023810237f);
	glVertex2f(0.1792607440f, -0.2461859413f);
	glVertex2f(0.2256216869f, -0.3023810237f);
	glVertex2f(0.1792607440f, -0.2461859413f);
	glVertex2f(0.2000000000f, -0.4000000000f);
	glVertex2f(0.2256216869f, -0.3023810237f);
	glVertex2f(0.2000000000f, -0.4000000000f);
	glVertex2f(0.2311038669f, -0.3661643368f);
	glVertex2f(0.2256216869f, -0.3023810237f);
	glVertex2f(0.2311038669f, -0.3661643368f);
	glVertex2f(0.2303021861f, -0.4158685455f);
	glVertex2f(0.2303021861f, -0.4158685455f);
	glVertex2f(0.2267758833f, -0.4565867932f);
	glVertex2f(0.2267758833f, -0.4565867932f);
	glVertex2f(0.3381304708f, -0.4328144655f);
	glVertex2f(0.2207046172f, -0.2426737486f);
	glVertex2f(0.2643111375f, -0.3076969514f);
	glVertex2f(0.2643111375f, -0.3076969514f);
	glVertex2f(0.3381304708f, -0.4328144655f);
	glVertex2f(0.2643111375f, -0.3076969514f);
	glVertex2f(0.5000000000f, -0.4000000000f);
	glVertex2f(0.0127337526f, -0.2772796120f);
	glVertex2f(0.1143094927f, -0.2927088383f);
	glVertex2f(0.0127337526f, -0.2772796120f);
	glVertex2f(0.0129625494f, -0.3960865108f);
	glVertex2f(-0.1261292844f, -0.2772796120f);
	glVertex2f(0.0127337526f, -0.2772796120f);
	glVertex2f(0.1143094927f, -0.2927088383f);
	glVertex2f(0.0129625494f, -0.3960865108f);
	glVertex2f(-0.2548328100f, -0.1381159366f);
	glVertex2f(-0.3243016892f, -0.1575665127f);
	glVertex2f(-0.3243016892f, -0.1575665127f);
	glVertex2f(-0.3174292376f, -0.2549262434f);
	glVertex2f(-0.3174292376f, -0.2549262434f);
	glVertex2f(-0.2548328100f, -0.1381159366f);
	glVertex2f(-0.3380465923f, -0.1816200933f);
	glVertex2f(-0.3174292376f, -0.2549262434f);
	glVertex2f(-0.3380465923f, -0.1816200933f);
	glVertex2f(-0.3243016892f, -0.1575665127f);
	glVertex2f(-0.3380465923f, -0.1816200933f);
	glVertex2f(-0.3769904846f, -0.2537808348f);
	glVertex2f(-0.3769904846f, -0.2537808348f);
	glVertex2f(-0.2647404422f, -0.3889390491f);
	glVertex2f(-0.3174292376f, -0.2549262434f);
	glVertex2f(-0.3139930118f, -0.2801252325f);
	glVertex2f(-0.3139930118f, -0.2801252325f);
	glVertex2f(-0.2572777083f, -0.2232773198f);
	glVertex2f(-0.3139930118f, -0.2801252325f);
	glVertex2f(-0.2647404422f, -0.3889390491f);
	glVertex2f(-0.3139930118f, -0.2801252325f);
	glVertex2f(-0.3061547334f, -0.2681418025f);
	glVertex2f(-0.3061547334f, -0.2681418025f);
	glVertex2f(-0.2393774248f, -0.3705336756f);
	glVertex2f(-0.2393774248f, -0.3705336756f);
	glVertex2f(-0.2251347028f, -0.3964811539f);
	glVertex2f(-0.2572777083f, -0.2232773198f);
	glVertex2f(-0.2251347028f, -0.3964811539f);
	glVertex2f(-0.3769904846f, -0.2537808348f);
	glVertex2f(-0.4341118997f, -0.3121340396f);
	glVertex2f(-0.4341118997f, -0.3121340396f);
	glVertex2f(-0.3919470982f, -0.4475052444f);
	glVertex2f(-0.3919470982f, -0.4475052444f);
	glVertex2f(-0.2647404422f, -0.3889390491f);
	glVertex2f(-0.2647404422f, -0.3889390491f);
	glVertex2f(-0.2532470932f, -0.5473692479f);
	glVertex2f(-0.3919470982f, -0.4475052444f);
	glVertex2f(-0.2532470932f, -0.5473692479f);
	glVertex2f(-0.3919470982f, -0.4475052444f);
	glVertex2f(-0.3486726966f, -0.5462596479f);
	glVertex2f(-0.3486726966f, -0.5462596479f);
	glVertex2f(-0.2532470932f, -0.5473692479f);
	glVertex2f(-0.2532470932f, -0.5473692479f);
	glVertex2f(-0.1444910599f, -0.5156929714f);
	glVertex2f(-0.2647404422f, -0.3889390491f);
	glVertex2f(-0.1444910599f, -0.5156929714f);
	glVertex2f(-0.1736686513f, -0.4849371033f);
	glVertex2f(-0.1000000000f, -0.5000000000f);
	glVertex2f(-0.2251347028f, -0.3964811539f);
	glVertex2f(-0.1000000000f, -0.5000000000f);
	glVertex2f(-0.1000000000f, -0.5000000000f);
	glVertex2f(-0.0235598851f, -0.5362732475f);
	glVertex2f(-0.1132715958f, -0.3274245976f);
	glVertex2f(-0.0235598851f, -0.5362732475f);
	glVertex2f(0.0129625494f, -0.3960865108f);
	glVertex2f(-0.0235598851f, -0.5362732475f);
	glVertex2f(-0.1132715958f, -0.3274245976f);
	glVertex2f(0.0129625494f, -0.3960865108f);
	glVertex2f(0.1143094927f, -0.2927088383f);
	glVertex2f(0.0483648716f, -0.5173129638f);
	glVertex2f(-0.0235598851f, -0.5362732475f);
	glVertex2f(0.0483648716f, -0.5173129638f);
	glVertex2f(0.0483648716f, -0.5173129638f);
	glVertex2f(0.1704938494f, -0.3808158710f);
	glVertex2f(0.1704938494f, -0.3808158710f);
	glVertex2f(0.1792607440f, -0.2461859413f);
	glVertex2f(0.1704938494f, -0.3808158710f);
	glVertex2f(0.1762410954f, -0.4512196347f);
	glVertex2f(0.1762410954f, -0.4512196347f);
	glVertex2f(0.1589993574f, -0.4900135453f);
	glVertex2f(0.0483648716f, -0.5173129638f);
	glVertex2f(0.1589993574f, -0.4900135453f);
	glVertex2f(0.2267758833f, -0.4565867932f);
	glVertex2f(0.1000000000f, -0.6000000000f);
	glVertex2f(0.1589993574f, -0.4900135453f);
	glVertex2f(0.1000000000f, -0.6000000000f);
	glVertex2f(0.1000000000f, -0.6000000000f);
	glVertex2f(0.2337135555f, -0.5130025293f);
	glVertex2f(0.2337135555f, -0.5130025293f);
	glVertex2f(0.2267758833f, -0.4565867932f);
	glVertex2f(0.2267758833f, -0.4565867932f);
	glVertex2f(0.3381304708f, -0.4328144655f);
	glVertex2f(0.3381304708f, -0.4328144655f);
	glVertex2f(0.5000000000f, -0.4000000000f);
	glVertex2f(-0.4346378459f, -0.3248127187f);
	glVertex2f(-0.4341118997f, -0.3121340396f);
	glVertex2f(-0.4346378459f, -0.3248127187f);
	glVertex2f(-0.4887619993f, -0.4276486101f);
	glVertex2f(-0.4887619993f, -0.4276486101f);
	glVertex2f(-0.3395529383f, -0.7645339427f);
	glVertex2f(-0.3486726966f, -0.5462596479f);
	glVertex2f(-0.3395529383f, -0.7645339427f);
	glVertex2f(-0.7179837788f, -0.4881695114f);
	glVertex2f(-0.4887619993f, -0.4276486101f);
	glVertex2f(-0.7179837788f, -0.4881695114f);
	glVertex2f(-0.4346378459f, -0.3248127187f);
	glVertex2f(-0.7179837788f, -0.4881695114f);
	glVertex2f(-0.5483965142f, -0.5604011241f);
	glVertex2f(-0.4887619993f, -0.4276486101f);
	glVertex2f(-0.5483965142f, -0.5604011241f);
	glVertex2f(-0.5483965142f, -0.5604011241f);
	glVertex2f(-0.3395529383f, -0.7645339427f);
	glVertex2f(-0.5483965142f, -0.5604011241f);
	glVertex2f(-0.6677357004f, -0.6389137466f);
	glVertex2f(-0.7179837788f, -0.4881695114f);
	glVertex2f(-0.6677357004f, -0.6389137466f);
	glVertex2f(-0.7179837788f, -0.4881695114f);
	glVertex2f(-0.8704770590f, -0.7788737948f);
	glVertex2f(-0.8704770590f, -0.7788737948f);
	glVertex2f(-0.8685383251f, -0.8254034095f);
	glVertex2f(-0.8685383251f, -0.8254034095f);
	glVertex2f(-0.6677357004f, -0.6389137466f);
	glVertex2f(-0.6677357004f, -0.6389137466f);
	glVertex2f(-0.6727261969f, -0.8816266938f);
	glVertex2f(-0.8685383251f, -0.8254034095f);
	glVertex2f(-0.8704770590f, -0.8855041617f);
	glVertex2f(-0.8704770590f, -0.8855041617f);
	glVertex2f(-0.6727261969f, -0.8816266938f);
	glVertex2f(-0.6727261969f, -0.8816266938f);
	glVertex2f(-0.2423272617f, -0.8835654277f);
	glVertex2f(-0.3395529383f, -0.7645339427f);
	glVertex2f(-0.2423272617f, -0.8835654277f);
	glVertex2f(-0.6677357004f, -0.6389137466f);
	glVertex2f(-0.2423272617f, -0.8835654277f);
	glVertex2f(-0.2423272617f, -0.8835654277f);
	glVertex2f(-0.0930447481f, -0.8796879598f);
	glVertex2f(-0.1124320876f, -0.7148955747f);
	glVertex2f(-0.0930447481f, -0.8796879598f);
	glVertex2f(-0.1124320876f, -0.7148955747f);
	glVertex2f(-0.0213115923f, -0.8816266938f);
	glVertex2f(-0.0930447481f, -0.8796879598f);
	glVertex2f(-0.0213115923f, -0.8816266938f);
	glVertex2f(-0.0213115923f, -0.8816266938f);
	glVertex2f(0.0116468847f, -0.8796879598f);
	glVertex2f(0.0116468847f, -0.8796879598f);
	glVertex2f(0.0542990315f, -0.7052019050f);
	glVertex2f(0.5000000000f, -0.4000000000f);
	glVertex2f(0.4614331594f, -0.5074510429f);
	glVertex2f(0.3381304708f, -0.4328144655f);
	glVertex2f(0.4614331594f, -0.5074510429f);
	glVertex2f(0.4614331594f, -0.5074510429f);
	glVertex2f(0.2753147009f, -0.8040773361f);
	glVertex2f(0.2337135555f, -0.5130025293f);
	glVertex2f(0.2753147009f, -0.8040773361f);
	glVertex2f(0.2753147009f, -0.8040773361f);
	glVertex2f(0.2769805716f, -0.8829403852f);
	glVertex2f(0.0116468847f, -0.8796879598f);
	glVertex2f(0.2769805716f, -0.8829403852f);
	glVertex2f(0.5000000000f, -0.4000000000f);
	glVertex2f(0.5506149207f, -0.5908166024f);
	glVertex2f(0.4614331594f, -0.5074510429f);
	glVertex2f(0.5506149207f, -0.5908166024f);
	glVertex2f(0.5506149207f, -0.5908166024f);
	glVertex2f(0.2265996840f, -0.8823228229f);
	glVertex2f(-0.2532470932f, -0.5473692479f);
	glVertex2f(-0.2551190991f, -0.5725284237f);
	glVertex2f(-0.3486726966f, -0.5462596479f);
	glVertex2f(-0.2551190991f, -0.5725284237f);
	glVertex2f(-0.2551190991f, -0.5725284237f);
	glVertex2f(-0.1444910599f, -0.5156929714f);
	glVertex2f(-0.2169559293f, -0.5529219928f);
	glVertex2f(-0.1993386406f, -0.5908013326f);
	glVertex2f(-0.1993386406f, -0.5908013326f);
	glVertex2f(-0.1124320876f, -0.7148955747f);
	glVertex2f(-0.1676014831f, -0.5417529983f);
	glVertex2f(-0.1124320876f, -0.7148955747f);
	glVertex2f(-0.1676014831f, -0.5417529983f);
	glVertex2f(-0.1458174278f, -0.5685755434f);
	glVertex2f(-0.1458174278f, -0.5685755434f);
	glVertex2f(-0.0049530530f, -0.6697790748f);
	glVertex2f(-0.1458174278f, -0.5685755434f);
	glVertex2f(0.0000000000f, -0.6000000000f);
	glVertex2f(0.0000000000f, -0.6000000000f);
	glVertex2f(0.0542990315f, -0.7052019050f);
	glVertex2f(-0.1676014831f, -0.5417529983f);
	glVertex2f(-0.1566778245f, -0.5333317097f);
	glVertex2f(-0.1566778245f, -0.5333317097f);
	glVertex2f(-0.1335871126f, -0.5564224215f);
	glVertex2f(-0.1566778245f, -0.5333317097f);
	glVertex2f(-0.1444910599f, -0.5156929714f);
	glVertex2f(-0.1335871126f, -0.5564224215f);
	glVertex2f(-0.0043432671f, -0.5856065157f);
	glVertex2f(-0.1444910599f, -0.5156929714f);
	glVertex2f(-0.0963854102f, -0.5320488923f);
	glVertex2f(-0.0963854102f, -0.5320488923f);
	glVertex2f(-0.0043432671f, -0.5856065157f);
	glVertex2f(-0.0043432671f, -0.5856065157f);
	glVertex2f(0.0165574226f, -0.6015933427f);
	glVertex2f(0.0165574226f, -0.6015933427f);
	glVertex2f(0.0590889695f, -0.6824866771f);
	glVertex2f(0.0590889695f, -0.6824866771f);
	glVertex2f(0.0542990315f, -0.7052019050f);
	glVertex2f(0.0590889695f, -0.6824866771f);
	glVertex2f(0.0685290329f, -0.6776086286f);
	glVertex2f(0.0685290329f, -0.6776086286f);
	glVertex2f(0.1000000000f, -0.6000000000f);
	glVertex2f(0.1000000000f, -0.6000000000f);
	glVertex2f(0.0849351142f, -0.6371505942f);
	glVertex2f(0.1000000000f, -0.6000000000f);
	glVertex2f(0.0932118385f, -0.6451968638f);
	glVertex2f(0.0932118385f, -0.6451968638f);
	glVertex2f(0.0809950963f, -0.6756140585f);
	glVertex2f(0.0809950963f, -0.6756140585f);
	glVertex2f(0.0685290329f, -0.6776086286f);
	glVertex2f(0.0809950963f, -0.6756140585f);
	glVertex2f(0.0867294855f, -0.6845896241f);
	glVertex2f(0.0867294855f, -0.6845896241f);
	glVertex2f(0.0917800435f, -0.7262803155f);
	glVertex2f(0.0917800435f, -0.7262803155f);
	glVertex2f(0.0746410087f, -0.7292796466f);
	glVertex2f(0.0685290329f, -0.6776086286f);
	glVertex2f(0.0746410087f, -0.7292796466f);
	glVertex2f(0.0542990315f, -0.7052019050f);
	glVertex2f(0.0575019738f, -0.7309935501f);
	glVertex2f(0.0575019738f, -0.7309935501f);
	glVertex2f(0.0746410087f, -0.7292796466f);
	glVertex2f(0.0932118385f, -0.6451968638f);
	glVertex2f(0.1309541441f, -0.5939097071f);
	glVertex2f(0.1309541441f, -0.5939097071f);
	glVertex2f(0.2461981356f, -0.5188265005f);
	glVertex2f(0.1479788247f, -0.5860521622f);
	glVertex2f(0.0899202987f, -0.6978039115f);
	glVertex2f(0.0899202987f, -0.6978039115f);
	glVertex2f(0.1868461156f, -0.8801455183f);
	glVertex2f(0.2511280532f, -0.5384730455f);
	glVertex2f(0.2461981356f, -0.5188265005f);
	glVertex2f(0.2511280532f, -0.5384730455f);
	glVertex2f(0.2265996840f, -0.8823228229f);
	glVertex2f(0.0575019738f, -0.7309935501f);
	glVertex2f(0.0760883440f, -0.8841955572f);
	glVertex2f(0.0917800435f, -0.7262803155f);
	glVertex2f(0.0976586734f, -0.7820203127f);
	glVertex2f(0.0976586734f, -0.7820203127f);
	glVertex2f(0.0642505722f, -0.7866202705f);
	glVertex2f(0.0866938787f, -0.7835300541f);
	glVertex2f(0.0999155606f, -0.8807699456f);
	glVertex2f(0.0866938787f, -0.7835300541f);
	glVertex2f(0.0976586734f, -0.7820203127f);
	glVertex2f(0.5506149207f, -0.5908166024f);
	glVertex2f(0.5637897576f, -0.8887510055f);
	glVertex2f(0.5637897576f, -0.8887510055f);
	glVertex2f(0.2769805716f, -0.8829403852f);
	glVertex2f(0.5000000000f, -0.4000000000f);
	glVertex2f(0.6952441676f, -0.5213284019f);
	glVertex2f(0.6952441676f, -0.5213284019f);
	glVertex2f(0.8505648033f, -0.8875782958f);
	glVertex2f(0.5506149207f, -0.5908166024f);
	glVertex2f(0.6799038579f, -0.7533505860f);
	glVertex2f(0.6952441676f, -0.5213284019f);
	glVertex2f(0.6799038579f, -0.7533505860f);
	glVertex2f(0.6799038579f, -0.7533505860f);
	glVertex2f(0.8505648033f, -0.8875782958f);
	glVertex2f(0.6799038579f, -0.7533505860f);
	glVertex2f(0.6779863192f, -0.8779906023f);
	glVertex2f(0.5637897576f, -0.8887510055f);
	glVertex2f(0.8505648033f, -0.8875782958f);
	glVertex2f(0.3540042903f, 0.2303538762f);
	glVertex2f(0.3797960073f, 0.1812267961f);
	glVertex2f(-0.2681193721f, 0.2780448690f);
	glVertex2f(-0.1867107040f, 0.1988972156f);
	glVertex2f(-0.0205579801f, 0.4736559879f);
	glVertex2f(0.0864475913f, 0.4460028626f);
	glVertex2f(0.2391409349f, 0.4279682158f);
	glVertex2f(0.3100772126f, 0.4147428081f);
	glVertex2f(-0.3067549362f, 0.1247306541f);
	glVertex2f(-0.2735941572f, 0.1370124241f);
	glVertex2f(0.2976169515f, 0.1004877601f);
	glVertex2f(0.3159308033f, 0.0891135211f);
	glVertex2f(0.2976169515f, 0.1004877601f);
	glVertex2f(0.2841257042f, 0.0345736052f);
	glVertex2f(0.2841257042f, 0.0345736052f);
	glVertex2f(0.2741727852f, -0.0140533470f);
	glVertex2f(0.2841257042f, 0.0345736052f);
	glVertex2f(0.3171589803f, 0.0412146180f);
	glVertex2f(0.3171589803f, 0.0412146180f);
	glVertex2f(0.3478690749f, 0.1098607119f);
	glVertex2f(0.3478690749f, 0.1098607119f);
	glVertex2f(0.3797960073f, 0.1812267961f);
	glVertex2f(0.3605742238f, 0.2608471547f);
	glVertex2f(0.3822523613f, 0.2352665842f);
	glVertex2f(-0.3804455562f, 0.2819373102f);
	glVertex2f(-0.3534256622f, 0.2819373102f);
	glVertex2f(0.5506149207f, -0.5908166024f);
	glVertex2f(0.6952441676f, -0.5213284019f);
	glEnd();
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

void Update(int value)
{
	if (happyX < 0.0f)
	{
		happyX += 0.009f;
	}

	else if (birthdayX > 0.0f)
	{
		birthdayX -= 0.006f;
	}

	else if (MayureshY < -0.5f)
	{
		MayureshY += 0.009f;
	}

	// BALLOONS MOVE UPWARD
	else if (BalloonY < 2.5f)
	{
		BalloonY += 0.005f;

		// MAYURESH word fades FIRST
		if (BalloonY > -0.5f && BalloonY < 0.2f)
		{
			MayureshAlpha -= 0.01f;

			if (MayureshAlpha < 0.05f)
				MayureshAlpha = 0.05f;
		}

		// BIRTHDAY fades SECOND
		if (BalloonY > 0.2f && BalloonY < 0.7f)
		{
			BirthdayAlpha -= 0.01f;

			if (BirthdayAlpha < 0.05f)
				BirthdayAlpha = 0.05f;
		}

		// HAPPY fades LAST
		if (BalloonY > 0.7f && BalloonY < 1.2f)
		{
			HappyAlpha -= 0.01f;

			if (HappyAlpha < 0.05f)
				HappyAlpha = 0.05f;
		}
	}

	// ONLY AFTER BALLOONS COMPLETELY LEAVE
	else
	{
		bShowMayureshDrawing = TRUE;

		// Slowly fade in complete Mayuresh drawing
		if (MayureshDrawingAlpha < 1.0f)
		{
			MayureshDrawingAlpha += 0.005f;

			if (MayureshDrawingAlpha > 1.0f)
				MayureshDrawingAlpha = 1.0f;
		}
	}

	glutPostRedisplay();

	glutTimerFunc(16, Update, 0);
}

void uninitialize(void)
{
	// Code

}

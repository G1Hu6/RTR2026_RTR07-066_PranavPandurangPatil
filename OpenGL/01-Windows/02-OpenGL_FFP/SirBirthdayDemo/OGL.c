#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "OGL.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "GLU32.lib")
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "GDI32.lib")

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define PI 3.14159265358979323846f

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void glPerspective(GLfloat, GLfloat, GLfloat, GLfloat);

HWND ghwnd = NULL;
HDC ghdc = NULL;
HGLRC ghrc = NULL;
BOOL bFullScreen = FALSE;
DWORD dwStyle;
WINDOWPLACEMENT wpPrev;
FILE* gpFile = NULL;
BOOL bActiveWindow = FALSE;
BOOL bEscapeKeyIsPressed = FALSE;
float gTime = 0.0f;

void drawCircleXY(float cx, float cy, float cz, float r, int segments)
{
	int i;
	float angle;
	glBegin(GL_POLYGON);
	for (i = 0; i < segments; i++)
	{
		angle = 2.0f * PI * ((float)i / (float)segments);
		glVertex3f(cx + cosf(angle) * r, cy + sinf(angle) * r, cz);
	}
	glEnd();
}

void drawDiscXZ(float cx, float cy, float cz, float r, int segments)
{
	int i;
	float angle;
	glBegin(GL_POLYGON);
	for (i = 0; i < segments; i++)
	{
		angle = 2.0f * PI * ((float)i / (float)segments);
		glVertex3f(cx + cosf(angle) * r, cy, cz + sinf(angle) * r);
	}
	glEnd();
}

void drawCylinderY(float cx, float cy, float cz, float r, float h, int segments)
{
	int i;
	float halfH = h * 0.5f;
	float angle;
	float x, z;
	glBegin(GL_QUAD_STRIP);
	for (i = 0; i <= segments; i++)
	{
		angle = 2.0f * PI * ((float)i / (float)segments);
		x = cosf(angle) * r;
		z = sinf(angle) * r;
		glVertex3f(cx + x, cy - halfH, cz + z);
		glVertex3f(cx + x, cy + halfH, cz + z);
	}
	glEnd();
}

void drawBox3D(float cx, float cy, float cz, float w, float h, float d)
{
	float hw = w * 0.5f;
	float hh = h * 0.5f;
	float hd = d * 0.5f;

	glBegin(GL_QUADS);
	glVertex3f(cx - hw, cy - hh, cz + hd);
	glVertex3f(cx + hw, cy - hh, cz + hd);
	glVertex3f(cx + hw, cy + hh, cz + hd);
	glVertex3f(cx - hw, cy + hh, cz + hd);

	glVertex3f(cx - hw, cy - hh, cz - hd);
	glVertex3f(cx - hw, cy + hh, cz - hd);
	glVertex3f(cx + hw, cy + hh, cz - hd);
	glVertex3f(cx + hw, cy - hh, cz - hd);

	glVertex3f(cx - hw, cy + hh, cz - hd);
	glVertex3f(cx - hw, cy + hh, cz + hd);
	glVertex3f(cx + hw, cy + hh, cz + hd);
	glVertex3f(cx + hw, cy + hh, cz - hd);

	glVertex3f(cx - hw, cy - hh, cz - hd);
	glVertex3f(cx + hw, cy - hh, cz - hd);
	glVertex3f(cx + hw, cy - hh, cz + hd);
	glVertex3f(cx - hw, cy - hh, cz + hd);

	glVertex3f(cx + hw, cy - hh, cz - hd);
	glVertex3f(cx + hw, cy + hh, cz - hd);
	glVertex3f(cx + hw, cy + hh, cz + hd);
	glVertex3f(cx + hw, cy - hh, cz + hd);

	glVertex3f(cx - hw, cy - hh, cz - hd);
	glVertex3f(cx - hw, cy - hh, cz + hd);
	glVertex3f(cx - hw, cy + hh, cz + hd);
	glVertex3f(cx - hw, cy + hh, cz - hd);
	glEnd();
}

void drawTrapezoidXY(float cx, float cy, float cz, float topW, float bottomW, float h)
{
	float htop = topW * 0.5f;
	float hbot = bottomW * 0.5f;
	float hh = h * 0.5f;

	glBegin(GL_QUADS);
	glVertex3f(cx - hbot, cy - hh, cz);
	glVertex3f(cx + hbot, cy - hh, cz);
	glVertex3f(cx + htop, cy + hh, cz);
	glVertex3f(cx - htop, cy + hh, cz);
	glEnd();
}

void drawElephantPillar(float x, float y, float z, float scale, float rotY)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(scale, scale, scale);
	glRotatef(rotY, 0.0f, 1.0f, 0.0f);

	glColor3f(0.72f, 0.56f, 0.35f);
	drawBox3D(0.0f, 0.15f, 0.0f, 1.80f, 0.30f, 1.80f);
	glColor3f(0.78f, 0.62f, 0.38f);
	drawBox3D(0.0f, 0.35f, 0.0f, 1.60f, 0.20f, 1.60f);
	glColor3f(0.74f, 0.58f, 0.36f);
	drawBox3D(0.0f, 0.70f, 0.0f, 1.45f, 0.50f, 1.45f);
	glColor3f(0.80f, 0.64f, 0.38f);
	drawBox3D(0.0f, 1.00f, 0.0f, 1.60f, 0.15f, 1.60f);
	glColor3f(0.74f, 0.58f, 0.36f);
	drawBox3D(0.0f, 1.10f, 0.0f, 1.50f, 0.08f, 1.50f);

	glColor3f(0.82f, 0.66f, 0.38f);
	drawCylinderY(0.0f, 3.45f, 0.0f, 0.38f, 4.62f, 24);
	drawDiscXZ(0.0f, 1.14f, 0.0f, 0.38f, 24);
	drawDiscXZ(0.0f, 5.76f, 0.0f, 0.38f, 24);

	glColor3f(0.80f, 0.62f, 0.32f);
	drawBox3D(-0.32f, 1.45f,  0.35f, 0.22f, 0.62f, 0.22f);
	drawBox3D( 0.32f, 1.45f,  0.35f, 0.22f, 0.62f, 0.22f);
	drawBox3D(-0.32f, 1.45f, -0.35f, 0.22f, 0.62f, 0.22f);
	drawBox3D( 0.32f, 1.45f, -0.35f, 0.22f, 0.62f, 0.22f);

	glColor3f(0.74f, 0.56f, 0.30f);
	drawBox3D(-0.32f, 1.18f,  0.35f, 0.24f, 0.10f, 0.24f);
	drawBox3D( 0.32f, 1.18f,  0.35f, 0.24f, 0.10f, 0.24f);
	drawBox3D(-0.32f, 1.18f, -0.35f, 0.24f, 0.10f, 0.24f);
	drawBox3D( 0.32f, 1.18f, -0.35f, 0.24f, 0.10f, 0.24f);

	glColor3f(0.96f, 0.95f, 0.90f);
	drawBox3D(-0.38f, 1.18f, 0.47f, 0.05f, 0.06f, 0.04f);
	drawBox3D(-0.32f, 1.18f, 0.47f, 0.05f, 0.06f, 0.04f);
	drawBox3D(-0.26f, 1.18f, 0.47f, 0.05f, 0.06f, 0.04f);
	drawBox3D( 0.26f, 1.18f, 0.47f, 0.05f, 0.06f, 0.04f);
	drawBox3D( 0.32f, 1.18f, 0.47f, 0.05f, 0.06f, 0.04f);
	drawBox3D( 0.38f, 1.18f, 0.47f, 0.05f, 0.06f, 0.04f);

	glColor3f(0.85f, 0.68f, 0.34f);
	drawBox3D(0.0f, 1.95f, 0.0f, 0.90f, 0.85f, 1.25f);
	drawBox3D(0.0f, 1.92f, -0.58f, 0.82f, 0.78f, 0.20f);
	drawCircleXY(-0.45f, 1.95f, 0.0f, 0.38f, 16);
	drawCircleXY( 0.45f, 1.95f, 0.0f, 0.38f, 16);

	glColor3f(0.75f, 0.58f, 0.28f);
	drawBox3D(0.0f, 1.62f, -0.68f, 0.04f, 0.50f, 0.04f);
	drawTrapezoidXY(0.0f, 1.34f, -0.68f, 0.08f, 0.02f, 0.10f);

	glColor3f(0.76f, 0.14f, 0.18f);
	drawBox3D(0.0f, 2.15f, 0.0f, 0.96f, 0.52f, 0.78f);
	glColor3f(0.95f, 0.82f, 0.22f);
	drawBox3D(0.0f, 1.90f, 0.0f, 0.98f, 0.08f, 0.80f);
	drawBox3D(-0.49f, 1.82f,  0.35f, 0.06f, 0.10f, 0.06f);
	drawBox3D( 0.49f, 1.82f,  0.35f, 0.06f, 0.10f, 0.06f);
	drawBox3D(-0.49f, 1.82f, -0.35f, 0.06f, 0.10f, 0.06f);
	drawBox3D( 0.49f, 1.82f, -0.35f, 0.06f, 0.10f, 0.06f);

	glColor3f(0.85f, 0.68f, 0.34f);
	drawBox3D(0.0f, 1.95f, 0.55f, 0.82f, 0.75f, 0.25f);
	glColor3f(0.95f, 0.80f, 0.20f);
	drawTrapezoidXY(0.0f, 1.78f, 0.69f, 0.60f, 0.35f, 0.14f);
	drawCircleXY(0.0f, 1.66f, 0.70f, 0.08f, 12);

	glColor3f(0.86f, 0.69f, 0.35f);
	drawBox3D(0.0f, 2.22f, 0.78f, 0.68f, 0.62f, 0.48f);
	drawCircleXY(-0.18f, 2.50f, 0.88f, 0.22f, 18);
	drawCircleXY( 0.18f, 2.50f, 0.88f, 0.22f, 18);

	glColor3f(0.96f, 0.84f, 0.22f);
	glBegin(GL_POLYGON);
	glVertex3f(-0.18f, 2.54f, 0.96f);
	glVertex3f( 0.18f, 2.54f, 0.96f);
	glVertex3f( 0.14f, 2.30f, 0.98f);
	glVertex3f( 0.00f, 2.15f, 1.00f);
	glVertex3f(-0.14f, 2.30f, 0.98f);
	glEnd();
	glColor3f(0.85f, 0.12f, 0.18f);
	drawCircleXY(0.0f, 2.36f, 1.01f, 0.06f, 12);

	glColor3f(0.20f, 0.15f, 0.10f);
	drawCircleXY(-0.35f, 2.28f, 0.88f, 0.05f, 10);
	drawCircleXY( 0.35f, 2.28f, 0.88f, 0.05f, 10);

	glColor3f(0.84f, 0.66f, 0.32f);
	glBegin(GL_POLYGON);
	glVertex3f(-0.32f, 2.45f, 0.70f);
	glVertex3f(-0.62f, 2.40f, 0.65f);
	glVertex3f(-0.68f, 2.05f, 0.60f);
	glVertex3f(-0.50f, 1.75f, 0.65f);
	glVertex3f(-0.32f, 1.95f, 0.72f);
	glEnd();
	glColor3f(0.76f, 0.52f, 0.30f);
	glBegin(GL_POLYGON);
	glVertex3f(-0.36f, 2.35f, 0.71f);
	glVertex3f(-0.56f, 2.30f, 0.66f);
	glVertex3f(-0.60f, 2.08f, 0.62f);
	glVertex3f(-0.46f, 1.88f, 0.66f);
	glVertex3f(-0.36f, 2.02f, 0.73f);
	glEnd();

	glColor3f(0.84f, 0.66f, 0.32f);
	glBegin(GL_POLYGON);
	glVertex3f(0.32f, 2.45f, 0.70f);
	glVertex3f(0.62f, 2.40f, 0.65f);
	glVertex3f(0.68f, 2.05f, 0.60f);
	glVertex3f(0.50f, 1.75f, 0.65f);
	glVertex3f(0.32f, 1.95f, 0.72f);
	glEnd();
	glColor3f(0.76f, 0.52f, 0.30f);
	glBegin(GL_POLYGON);
	glVertex3f(0.36f, 2.35f, 0.71f);
	glVertex3f(0.56f, 2.30f, 0.66f);
	glVertex3f(0.60f, 2.08f, 0.62f);
	glVertex3f(0.46f, 1.88f, 0.66f);
	glVertex3f(0.36f, 2.02f, 0.73f);
	glEnd();

	glColor3f(0.96f, 0.95f, 0.88f);
	drawBox3D(-0.18f, 1.95f, 0.96f, 0.08f, 0.10f, 0.15f);
	drawBox3D(-0.20f, 1.90f, 1.10f, 0.07f, 0.08f, 0.18f);
	drawBox3D(-0.21f, 1.98f, 1.25f, 0.05f, 0.07f, 0.15f);
	glColor3f(0.95f, 0.82f, 0.22f);
	drawBox3D(-0.18f, 1.95f, 0.98f, 0.09f, 0.11f, 0.04f);

	glColor3f(0.96f, 0.95f, 0.88f);
	drawBox3D( 0.18f, 1.95f, 0.96f, 0.08f, 0.10f, 0.15f);
	drawBox3D( 0.20f, 1.90f, 1.10f, 0.07f, 0.08f, 0.18f);
	drawBox3D( 0.21f, 1.98f, 1.25f, 0.05f, 0.07f, 0.15f);
	glColor3f(0.95f, 0.82f, 0.22f);
	drawBox3D( 0.18f, 1.95f, 0.98f, 0.09f, 0.11f, 0.04f);

	glColor3f(0.85f, 0.68f, 0.34f);
	drawBox3D(0.0f, 1.98f, 0.95f, 0.26f, 0.25f, 0.22f);
	drawBox3D(0.0f, 1.75f, 1.00f, 0.22f, 0.26f, 0.20f);
	drawBox3D(0.0f, 1.50f, 1.05f, 0.19f, 0.26f, 0.18f);
	drawBox3D(0.0f, 1.28f, 1.12f, 0.16f, 0.22f, 0.16f);
	drawBox3D(0.0f, 1.18f, 1.24f, 0.14f, 0.14f, 0.18f);
	drawBox3D(0.0f, 1.30f, 1.30f, 0.12f, 0.14f, 0.12f);

	glColor3f(0.78f, 0.60f, 0.28f);
	drawBox3D(0.0f, 1.86f, 1.00f, 0.24f, 0.03f, 0.21f);
	drawBox3D(0.0f, 1.62f, 1.05f, 0.21f, 0.03f, 0.19f);
	drawBox3D(0.0f, 1.38f, 1.10f, 0.18f, 0.03f, 0.17f);

	glColor3f(0.76f, 0.60f, 0.36f);
	drawCylinderY(0.0f, 2.50f, 0.0f, 0.44f, 0.20f, 24);
	drawDiscXZ(0.0f, 2.40f, 0.0f, 0.44f, 24);
	drawDiscXZ(0.0f, 2.60f, 0.0f, 0.44f, 24);

	glColor3f(0.85f, 0.68f, 0.34f);
	drawBox3D(0.0f, 3.05f, 0.35f, 0.38f, 0.60f, 0.45f);
	drawCircleXY(0.0f, 3.45f, 0.48f, 0.18f, 16);
	glColor3f(0.78f, 0.60f, 0.28f);
	drawCircleXY(0.0f, 3.45f, 0.44f, 0.26f, 16);

	glColor3f(0.92f, 0.78f, 0.26f);
	glBegin(GL_POLYGON);
	glVertex3f(-0.16f, 3.10f, 0.35f);
	glVertex3f(-0.55f, 3.65f, 0.30f);
	glVertex3f(-0.48f, 3.85f, 0.28f);
	glVertex3f(-0.16f, 3.40f, 0.32f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f( 0.16f, 3.10f, 0.35f);
	glVertex3f( 0.55f, 3.65f, 0.30f);
	glVertex3f( 0.48f, 3.85f, 0.28f);
	glVertex3f( 0.16f, 3.40f, 0.32f);
	glEnd();

	glColor3f(0.92f, 0.78f, 0.25f);
	drawCylinderY(0.0f, 3.90f, 0.0f, 0.43f, 0.14f, 24);
	drawDiscXZ(0.0f, 3.83f, 0.0f, 0.43f, 24);
	drawDiscXZ(0.0f, 3.97f, 0.0f, 0.43f, 24);

	drawCylinderY(0.0f, 4.80f, 0.0f, 0.43f, 0.14f, 24);
	drawDiscXZ(0.0f, 4.73f, 0.0f, 0.43f, 24);
	drawDiscXZ(0.0f, 4.87f, 0.0f, 0.43f, 24);

	glColor3f(0.78f, 0.62f, 0.38f);
	drawBox3D(0.0f, 5.85f, 0.0f, 1.10f, 0.20f, 1.10f);
	drawBox3D(0.0f, 6.05f, 0.0f, 1.35f, 0.20f, 1.35f);
	glColor3f(0.72f, 0.56f, 0.35f);
	drawBox3D(0.0f, 6.25f, 0.0f, 1.60f, 0.20f, 1.60f);

	glPopMatrix();
}

void drawSoldier(float x, float y, float z, float scale, float rBody, float gBody, float bBody, float rTurban, float gTurban, float bTurban, int hasSpear, float rotY)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(scale, scale, scale);
	glRotatef(rotY, 0.0f, 1.0f, 0.0f);

	glColor3f(0.85f, 0.62f, 0.45f);
	drawCircleXY(0.0f, 1.55f, 0.0f, 0.20f, 24);

	glColor3f(rTurban, gTurban, bTurban);
	glBegin(GL_POLYGON);
	glVertex3f(-0.22f, 1.58f, 0.01f);
	glVertex3f( 0.22f, 1.58f, 0.01f);
	glVertex3f( 0.20f, 1.76f, 0.01f);
	glVertex3f( 0.00f, 1.84f, 0.01f);
	glVertex3f(-0.20f, 1.76f, 0.01f);
	glEnd();

	glColor3f(0.95f, 0.82f, 0.20f);
	drawCircleXY(0.0f, 1.73f, 0.02f, 0.05f, 12);

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glVertex3f( 0.00f, 1.95f, 0.02f);
	glVertex3f(-0.04f, 1.75f, 0.02f);
	glVertex3f( 0.04f, 1.75f, 0.02f);
	glEnd();

	glColor3f(0.80f, 0.58f, 0.40f);
	drawTrapezoidXY(0.0f, 1.33f, 0.0f, 0.12f, 0.14f, 0.10f);

	glColor3f(rBody, gBody, bBody);
	drawTrapezoidXY(0.0f, 1.05f, 0.0f, 0.55f, 0.40f, 0.46f);

	glColor3f(0.92f, 0.78f, 0.22f);
	drawCircleXY(-0.26f, 1.24f, 0.01f, 0.08f, 12);
	drawCircleXY( 0.26f, 1.24f, 0.01f, 0.08f, 12);

	glColor3f(0.95f, 0.80f, 0.20f);
	drawTrapezoidXY(0.0f, 0.78f, 0.0f, 0.41f, 0.38f, 0.08f);

	glColor3f(rTurban, gTurban, bTurban);
	drawTrapezoidXY(0.0f, 0.66f, 0.01f, 0.12f, 0.18f, 0.18f);

	glColor3f(0.90f, 0.85f, 0.75f);
	drawTrapezoidXY(0.0f, 0.42f, 0.0f, 0.38f, 0.28f, 0.60f);

	glColor3f(0.80f, 0.58f, 0.40f);
	drawTrapezoidXY(-0.08f, 0.06f, 0.0f, 0.07f, 0.06f, 0.14f);
	drawTrapezoidXY( 0.08f, 0.06f, 0.0f, 0.07f, 0.06f, 0.14f);

	if (hasSpear != 0)
	{
		glColor3f(0.48f, 0.30f, 0.15f);
		drawBox3D(0.32f, 1.10f, 0.05f, 0.04f, 2.10f, 0.04f);

		glColor3f(0.88f, 0.92f, 0.98f);
		glBegin(GL_TRIANGLES);
		glVertex3f(0.32f, 2.38f, 0.06f);
		glVertex3f(0.26f, 2.14f, 0.06f);
		glVertex3f(0.38f, 2.14f, 0.06f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex3f(0.24f, 2.26f, 0.06f);
		glVertex3f(0.22f, 2.14f, 0.06f);
		glVertex3f(0.26f, 2.14f, 0.06f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex3f(0.40f, 2.26f, 0.06f);
		glVertex3f(0.38f, 2.14f, 0.06f);
		glVertex3f(0.42f, 2.14f, 0.06f);
		glEnd();

		glColor3f(0.95f, 0.80f, 0.20f);
		drawBox3D(0.32f, 2.13f, 0.05f, 0.08f, 0.04f, 0.06f);
	}
	else
	{
		glColor3f(0.95f, 0.82f, 0.20f);
		drawCircleXY(0.0f, 0.92f, 0.12f, 0.14f, 16);
		glColor3f(0.20f, 0.75f, 0.30f);
		drawCircleXY(0.0f, 0.96f, 0.13f, 0.08f, 12);
	}

	glPopMatrix();
}

void glPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar)
{
	gluPerspective(fovy, aspect, zNear, zFar);
}

void Resize(int width, int height)
{
	if (height <= 0)
	{
		height = 1;
	}

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glPerspective(
		45.0f,
		((GLfloat)width / (GLfloat)height),
		0.1f,
		100.0f
	);
}

int Initialize(void)
{
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex;

	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 32;

	ghdc = GetDC(ghwnd);
	if (ghdc == NULL)
	{
		return (-1);
	}

	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);
	if (iPixelFormatIndex == 0)
	{
		return (-2);
	}

	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		return (-3);
	}

	ghrc = wglCreateContext(ghdc);
	if (ghrc == NULL)
	{
		return (-4);
	}

	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		return (-5);
	}

	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Resize(WIN_WIDTH, WIN_HEIGHT);

	return (0);
}

void Render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
		0.0f, 2.1f, 8.2f,
		0.0f, 1.4f, 0.0f,
		0.0f, 1.0f, 0.0f
	);

	drawElephantPillar(-3.3f, -0.70f,  3.4f, 1.0f,  45.0f);
	drawElephantPillar( 3.3f, -0.70f,  3.4f, 1.0f, -45.0f);
	drawElephantPillar(-2.8f, -0.70f, -0.6f, 0.95f,  30.0f);
	drawElephantPillar( 2.8f, -0.70f, -0.6f, 0.95f, -30.0f);

	drawSoldier(-1.50f, -0.70f,  0.2f, 0.92f, 0.92f, 0.45f, 0.15f, 0.18f, 0.25f, 0.70f, 1,  30.0f);
	drawSoldier(-1.55f, -0.70f,  1.4f, 0.95f, 0.18f, 0.60f, 0.25f, 0.85f, 0.15f, 0.15f, 1,  35.0f);
	drawSoldier(-1.60f, -0.70f,  2.6f, 0.98f, 0.20f, 0.30f, 0.80f, 0.92f, 0.75f, 0.20f, 1,  40.0f);
	drawSoldier(-1.65f, -0.70f,  3.8f, 1.02f, 0.80f, 0.15f, 0.20f, 0.90f, 0.45f, 0.15f, 1,  45.0f);
	drawSoldier(-1.70f, -0.70f,  5.0f, 1.05f, 0.85f, 0.50f, 0.15f, 0.20f, 0.55f, 0.25f, 1,  50.0f);

	drawSoldier(-2.25f, -0.70f,  0.8f, 0.90f, 0.75f, 0.20f, 0.65f, 0.90f, 0.75f, 0.20f, 0,  35.0f);
	drawSoldier(-2.30f, -0.70f,  2.0f, 0.95f, 0.90f, 0.75f, 0.20f, 0.18f, 0.25f, 0.70f, 0,  40.0f);
	drawSoldier(-2.35f, -0.70f,  3.2f, 1.00f, 0.20f, 0.55f, 0.25f, 0.80f, 0.15f, 0.20f, 0,  45.0f);
	drawSoldier(-2.40f, -0.70f,  4.4f, 1.04f, 0.18f, 0.25f, 0.70f, 0.90f, 0.45f, 0.15f, 0,  50.0f);

	drawSoldier( 1.50f, -0.70f,  0.2f, 0.92f, 0.20f, 0.30f, 0.80f, 0.85f, 0.15f, 0.15f, 1, -30.0f);
	drawSoldier( 1.55f, -0.70f,  1.4f, 0.95f, 0.92f, 0.45f, 0.15f, 0.18f, 0.60f, 0.25f, 1, -35.0f);
	drawSoldier( 1.60f, -0.70f,  2.6f, 0.98f, 0.18f, 0.60f, 0.25f, 0.92f, 0.75f, 0.20f, 1, -40.0f);
	drawSoldier( 1.65f, -0.70f,  3.8f, 1.02f, 0.80f, 0.15f, 0.20f, 0.20f, 0.30f, 0.80f, 1, -45.0f);
	drawSoldier( 1.70f, -0.70f,  5.0f, 1.05f, 0.90f, 0.75f, 0.20f, 0.85f, 0.50f, 0.15f, 1, -50.0f);

	drawSoldier( 2.25f, -0.70f,  0.8f, 0.90f, 0.80f, 0.15f, 0.20f, 0.18f, 0.60f, 0.25f, 0, -35.0f);
	drawSoldier( 2.30f, -0.70f,  2.0f, 0.95f, 0.20f, 0.55f, 0.25f, 0.90f, 0.75f, 0.20f, 0, -40.0f);
	drawSoldier( 2.35f, -0.70f,  3.2f, 1.00f, 0.90f, 0.45f, 0.15f, 0.20f, 0.30f, 0.80f, 0, -45.0f);
	drawSoldier( 2.40f, -0.70f,  4.4f, 1.04f, 0.75f, 0.20f, 0.65f, 0.85f, 0.15f, 0.15f, 0, -50.0f);

	drawSoldier(-1.20f, -0.45f, -1.2f, 0.88f, 0.85f, 0.15f, 0.15f, 0.92f, 0.75f, 0.20f, 1,  20.0f);
	drawSoldier( 1.20f, -0.45f, -1.2f, 0.88f, 0.85f, 0.15f, 0.15f, 0.92f, 0.75f, 0.20f, 1, -20.0f);

	drawSoldier( 0.00f, -0.70f,  1.0f, 0.94f, 0.88f, 0.60f, 0.15f, 0.75f, 0.15f, 0.20f, 0, 180.0f);

	SwapBuffers(ghdc);
}

void Update(void)
{
}

void ToggleFullScreen(void)
{
	MONITORINFO mi;

	if (!bFullScreen)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);

		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			memset(&mi, 0, sizeof(MONITORINFO));
			mi.cbSize = sizeof(MONITORINFO);

			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(
					ghwnd,
					HWND_TOP,
					mi.rcMonitor.left,
					mi.rcMonitor.top,
					(mi.rcMonitor.right - mi.rcMonitor.left),
					(mi.rcMonitor.bottom - mi.rcMonitor.top),
					SWP_NOZORDER | SWP_FRAMECHANGED
				);
			}
		}
		ShowCursor(FALSE);
	}
	else
	{
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(
			ghwnd,
			HWND_TOP,
			0,
			0,
			0,
			0,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED
		);
		ShowCursor(TRUE);
	}
}

void Uninitialize(void)
{
	if (bFullScreen == TRUE)
	{
		ToggleFullScreen();
	}

	if (wglGetCurrentContext() == ghrc)
	{
		wglMakeCurrent(NULL, NULL);
	}

	if (ghrc)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}

	if (ghdc)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	if (ghwnd)
	{
		DestroyWindow(ghwnd);
		ghwnd = NULL;
	}

	if (gpFile)
	{
		fclose(gpFile);
		gpFile = NULL;
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_CREATE:
		memset(&wpPrev, 0, sizeof(WINDOWPLACEMENT));
		wpPrev.length = sizeof(WINDOWPLACEMENT);
		break;
	case WM_SETFOCUS:
		bActiveWindow = TRUE;
		break;
	case WM_KILLFOCUS:
		bActiveWindow = FALSE;
		break;
	case WM_SIZE:
		Resize(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			bEscapeKeyIsPressed = TRUE;
			break;
		default:
			break;
		}
		break;
	case WM_CHAR:
		switch (wParam)
		{
		case 'F':
		case 'f':
			if (!bFullScreen)
			{
				ToggleFullScreen();
				bFullScreen = TRUE;
			}
			else
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
		Uninitialize();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd = NULL;
	MSG msg;
	TCHAR szAppName[] = TEXT("RTR07-PPP");
	BOOL bDone = FALSE;
	int iScreenWidth;
	int iScreenHeight;
	int iResult;

	gpFile = fopen("Log.txt", "w");
	if (gpFile == NULL)
	{
		MessageBox(NULL, TEXT("Log file is not created"), TEXT("Error"), MB_OK);
		exit(0);
	}

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYCHAKARAICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadCursor(hInstance, MAKEINTRESOURCE(MYCHAKARAICON));

	RegisterClassEx(&wndclass);

	iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	iScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	hwnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		szAppName,
		TEXT("Sir Birthday Demo : Pranav P Patil"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		(iScreenWidth / 2) - (WIN_WIDTH / 2),
		(iScreenHeight / 2) - (WIN_HEIGHT / 2),
		WIN_WIDTH,
		WIN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ghwnd = hwnd;

	iResult = Initialize();
	if (iResult != 0)
	{
		DestroyWindow(hwnd);
		hwnd = NULL;
	}

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	while (bDone == FALSE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
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
			if (bActiveWindow == TRUE)
			{
				if (bEscapeKeyIsPressed == TRUE)
				{
					bDone = TRUE;
				}

				Render();
				Update();
			}
		}
	}

	Uninitialize();

	return ((int)msg.wParam);
}

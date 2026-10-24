#pragma once

// header files
#include <windows.h>
#include <gl/GL.h>
#include <math.h>


// variable declarations
// Global Color Arrays
static float shadowDarkColorArr[3] = { 0.45f, 0.0f, 0.0f };
static float bodyLightColorArr[3]  = { 1.0f,  0.0f, 0.0f };


// Color Setter Helper
static inline void setLetterColor(float r, float g, float b)
{
	// code
	bodyLightColorArr[0] = r;
	bodyLightColorArr[1] = g;
	bodyLightColorArr[2] = b;
	shadowDarkColorArr[0] = r * 0.45f;
	shadowDarkColorArr[1] = g * 0.45f;
	shadowDarkColorArr[2] = b * 0.45f;
}


// -------------------------------------------------------------
// Letter A
// --------------------------------------------------------------------------------------------------------------------
static inline void drawA(float xPoint, float yPoint)
{
	float height  = 0.50f;
	float slant   = 0.18f;
	float width   = 0.055f;
	float zDepth  = 0.035f;
	float dH      = 0.15f;
	float dW      = 0.055f;
	float t = 1.0f - ((dH + 0.5f * dW) / height);
	float leftCrossX  = xPoint - (slant * t) + (0.5f * width);
	float rightCrossX = xPoint + (slant * t) + (0.5f * width);
	
	// ----------------------------- Body A -----------------------------
	glBegin(GL_QUADS);
	
	// Left Leg ('/')
	//------ Front Face -------
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	glVertex3f(xPoint - slant,         yPoint,          zDepth);
	glVertex3f(xPoint,                 yPoint + height, zDepth);
	glVertex3f(xPoint + width,         yPoint + height, zDepth);
	glVertex3f(xPoint - slant + width, yPoint,          zDepth);
	
	//------ Left Face -------
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	glVertex3f(xPoint - slant,         yPoint,          -zDepth);
	glVertex3f(xPoint,                 yPoint + height, -zDepth);
	glVertex3f(xPoint,                 yPoint + height,  zDepth);
	glVertex3f(xPoint - slant,         yPoint,           zDepth);

	//------ Top Face -------
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	glVertex3f(xPoint,                 yPoint + height,  zDepth);
	glVertex3f(xPoint,                 yPoint + height, -zDepth);
	glVertex3f(xPoint + width,         yPoint + height, -zDepth);
	glVertex3f(xPoint + width,         yPoint + height,  zDepth);

	//------ Right Face -----
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	glVertex3f(xPoint - slant + width, yPoint,           zDepth);
	glVertex3f(xPoint + width,         yPoint + height,  zDepth);
	glVertex3f(xPoint + width,         yPoint + height, -zDepth);
	glVertex3f(xPoint - slant + width, yPoint,          -zDepth);

	//------ Bottom Face -----
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	glVertex3f(xPoint - slant,         yPoint,           zDepth);
	glVertex3f(xPoint - slant,         yPoint,          -zDepth);
	glVertex3f(xPoint - slant + width, yPoint,          -zDepth);
	glVertex3f(xPoint - slant + width, yPoint,           zDepth);

	//------ Back Face -----
	glColor3f(1.0f, 0.60f, 0.20f);
	glVertex3f(xPoint - slant,         yPoint,          -zDepth);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(xPoint,                 yPoint + height, -zDepth);
	glVertex3f(xPoint + width,         yPoint + height, -zDepth);
	glColor3f(0.075f, 0.533f, 0.031f);
	glVertex3f(xPoint - slant + width, yPoint,          -zDepth);

	// Right Leg ('\')
	//------ Front Face -------
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	glVertex3f(xPoint,                 yPoint + height, zDepth);
	glVertex3f(xPoint + slant,         yPoint,          zDepth);
	glVertex3f(xPoint + slant + width, yPoint,          zDepth);
	glVertex3f(xPoint + width,         yPoint + height, zDepth);

	//------ Right Face -------
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	glVertex3f(xPoint + slant + width, yPoint,           zDepth);
	glVertex3f(xPoint + width,         yPoint + height,  zDepth);
	glVertex3f(xPoint + width,         yPoint + height, -zDepth);
	glVertex3f(xPoint + slant + width, yPoint,          -zDepth);

	//------ Left Face -------
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	glVertex3f(xPoint + slant, yPoint,          -zDepth);
	glVertex3f(xPoint,         yPoint + height, -zDepth);
	glVertex3f(xPoint,         yPoint + height,  zDepth);
	glVertex3f(xPoint + slant, yPoint,           zDepth);

	//------ Top Face -------
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	glVertex3f(xPoint,                 yPoint + height,  zDepth);
	glVertex3f(xPoint,                 yPoint + height, -zDepth);
	glVertex3f(xPoint + width,         yPoint + height, -zDepth);
	glVertex3f(xPoint + width,         yPoint + height,  zDepth);

	//------ Bottom Face -------
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	glVertex3f(xPoint + slant,         yPoint,  zDepth);
	glVertex3f(xPoint + slant,         yPoint, -zDepth);
	glVertex3f(xPoint + slant + width, yPoint, -zDepth);
	glVertex3f(xPoint + slant + width, yPoint,  zDepth);

	//------ Back Face -------
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	glVertex3f(xPoint,                 yPoint + height, -zDepth);
	glVertex3f(xPoint + width,         yPoint + height, -zDepth);
	glVertex3f(xPoint + slant + width, yPoint,          -zDepth);
	glVertex3f(xPoint + slant,         yPoint,          -zDepth);

	// Crossbar ('-')
	//------ Front Face -------
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	glVertex3f(leftCrossX,  yPoint + dH,      zDepth);
	glVertex3f(leftCrossX,  yPoint + dH + dW, zDepth);
	glVertex3f(rightCrossX, yPoint + dH + dW, zDepth);
	glVertex3f(rightCrossX, yPoint + dH,      zDepth);

	//------ Back Face -------
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	glVertex3f(leftCrossX,  yPoint + dH,      -zDepth);
	glVertex3f(rightCrossX, yPoint + dH,      -zDepth);
	glVertex3f(rightCrossX, yPoint + dH + dW, -zDepth);
	glVertex3f(leftCrossX,  yPoint + dH + dW, -zDepth);

	//------ Top Face -------
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	glVertex3f(leftCrossX,  yPoint + dH + dW,  zDepth);
	glVertex3f(leftCrossX,  yPoint + dH + dW, -zDepth);
	glVertex3f(rightCrossX, yPoint + dH + dW, -zDepth);
	glVertex3f(rightCrossX, yPoint + dH + dW,  zDepth);

	//------ Bottom Face -------
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	glVertex3f(leftCrossX,  yPoint + dH,  zDepth);
	glVertex3f(rightCrossX, yPoint + dH,  zDepth);
	glVertex3f(rightCrossX, yPoint + dH, -zDepth);
	glVertex3f(leftCrossX,  yPoint + dH, -zDepth);
	glEnd();
}



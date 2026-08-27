#include<GL/freeglut.h>
#include<math.h>
#define X_MAX 30.0f
#define Y_MAX 13.0f
#define PI 3.14f

float shadowDarkColorArr[] = { 0.45f, 0.0f, 0.0f };
float bodyLightColorArr[] = { 1.0f, 0.0f, 0.0f };
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
	void graphCoordinate(float, float);
	void drawA(float, float);
	void drawS(float, float);
	void drawT(float, float);
	void drawI(float, float);
	void drawC(float, float);
	void drawP(float, float);
	void drawB(float, float);
	void drawG(float, float);
	void drawH(float, float);
	void drawK(float, float);
	void drawL(float, float);
	void drawN(float, float);
	void drawU(float, float);
	void drawV(float, float);
	void drawY(float, float);
	void drawW(float, float);
	void drawF(float, float);
	void drawJ(float, float);
	void drawColon(float, float);
	void drawDash(float, float);
	void drawDot(float, float);
	void drawCircle(void);
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

void graphCoordinate(float xPoint, float yPoint)
{
	float graphXPoint = (((xPoint / X_MAX) * 2.0f) - 1.0f);
	float graphYPoint = (1.0f - ((yPoint / Y_MAX) * 2.0f));
	glVertex3f(graphXPoint, graphYPoint, 0.0f);
}

void drawCircle()
{
	float circle_center_x = 2.5f;
	float circle_center_y = 5.0f;

	float current_x_position = 0.0f;
	float current_y_position = 0.0f;

	float radius = 0.7f; // size of circle

	/*
	Circle has 0 to 360 degrees, means we need 0 to 360 points
	Each 1 degree = 1 point, so total 360 points are required to make circle

	But to make a circle that appears smooth to the human eye we might not need all 360 points

	Minimum 36 points also gives us smooth circle
	*/

	float number_of_points_to_draw_circle = 36.0f; // Ideal value is 360
	float distance_between_two_circle_points = 360 / number_of_points_to_draw_circle; // 360 / 36 = 10 (each point has distance of 10 between each other)


	// Start drawing circle using any one of the 3 methods from below

	// Method 1 - Draw circle using points
	//glPointSize(2.5f);
	//glBegin(GL_POINTS);

	// Method 2 - Draw Hollow circle
	glBegin(GL_LINE_LOOP);
	glLineWidth(12.0f);
	// Method 3 - Draw Filled Circle
	//glBegin(GL_TRIANGLE_FAN);

	for (float angle = 0.0f; angle < 360.0f; angle = angle + distance_between_two_circle_points)
	{
		/*
		Humans understand angles in Degrees - (0 to 360 degree)
		Computer understands angles in Radiance - ( 0 to 6.28 or 0 to 2PI radiance)

		so we should convert degrees into radiance

		radiance = degree * 3.14 / 180
		*/

		// degree to radians
		float angle_in_radians = angle * PI / 180.0f;

		// calculate x-y position of points using sin-cos formula
		current_x_position = radius * cos(angle_in_radians); // 0.5 * cos(angle_in_radians)
		current_y_position = radius * sin(angle_in_radians); // 0.5 * sin(angle_in_radians)

		// specify the position of circle on a monitor window
		current_x_position = current_x_position + circle_center_x; // current_x_position + 0.0f
		current_y_position = current_y_position + circle_center_y; // current_y_position + 0.0f

		// set color of circle and draw the circle
		glColor3f(1.0f, 1.0f, 0.0f); // Red, Green, Blue
		graphCoordinate(current_x_position, current_y_position); // x, y, z
	}
	glEnd();
}

void drawS(float xPoint, float yPoint)
{
	float width = 0.40f;
	float height = 1.73f;
	float slant = 0.74f;

	float dShadow = 0.25;
	float dW = 0.7f * width;
	float dH = 0.6f * height;
	
	//----------------------------- Shadow S -----------------------------
	//------- '|'
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + (height / 2.0f) + (width / 2.0f) + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + (height / 2.0f) + (width / 2.0f) + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '_' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + width + dShadow);

	graphCoordinate(xPoint - dShadow + (height / 2.0f) + (width / 2.0f), yPoint + width + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '_' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + (height / 2.0f) - (width / 2.0f) + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + (height / 2.0f) + (width / 2.0f) + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + (height / 2.0f) + (width / 2.0f) + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + (height / 2.0f) - (width / 2.0f) + dShadow);
	glEnd();

	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width - dShadow, yPoint + (height / 2.0f) - (width / 2.0f) + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width - dShadow, yPoint + (2 * (height / 2.0f)) + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + (2 * (height / 2.0f)) + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + (height / 2.0f) - (width / 2.0f) + dShadow);
	glEnd();

	// ------ '_' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + height - width + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + height - width + dShadow);
	glEnd();
	
	//----------------------------- S -----------------------------
	//------- '|'
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint, yPoint + (height/2.0f) + (width / 2.0f));

	graphCoordinate(xPoint + width, yPoint + (height / 2.0f) + (width / 2.0f));

	graphCoordinate(xPoint + width, yPoint);
	glEnd();

	// ------ '-' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint, yPoint + width);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + width);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint);
	glEnd();

	// ------ '_' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint + (height / 2.0f) - (width / 2.0f));

	graphCoordinate(xPoint, yPoint + (height / 2.0f) + (width / 2.0f));

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + (height / 2.0f) + (width / 2.0f));

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + (height / 2.0f) - (width / 2.0f));
	glEnd();

	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width, yPoint + (height / 2.0f) - (width / 2.0f));

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width, yPoint + (2 * (height / 2.0f)));

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + (2*(height / 2.0f)));

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + (height / 2.0f) - (width / 2.0f));
	glEnd();

	// ------ '_' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint , yPoint + height - width);

	graphCoordinate(xPoint , yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + height - width);
	glEnd();
}

void drawT(float xPoint, float yPoint)
{
	float width = 0.40f;
	float height = 1.73f;

	float dShadow = 0.25;


	//----------------------------- Shadow T -----------------------------
	//------- '_'
	
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + width + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + width + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint + (height / 4.0f) - (width / 4.0f) - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint + (height / 4.0f) - (width / 4.0f) - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 4.0f) - (width / 4.0f) + width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 4.0f) - (width / 4.0f) + width - dShadow, yPoint + dShadow);
	glEnd();

	//----------------------------- T -----------------------------
	//------- '_'
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint, yPoint + width);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + width);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint);
	glEnd();

	// ------ '|' xPoint + (height / 2.0f)
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint + (height / 4.0f) - (width / 4.0f) , yPoint);

	graphCoordinate(xPoint + (height / 4.0f) - (width / 4.0f) , yPoint + height);

	graphCoordinate(xPoint + (height / 4.0f) - (width / 4.0f) + width, yPoint + height);

	graphCoordinate(xPoint + (height / 4.0f) - (width / 4.0f) + width, yPoint);
	glEnd();
	
}

void drawI(float xPoint, float yPoint)
{
	float width = 0.40f;
	float height = 1.73f;

	float dShadow = 0.25;

	//----------------------------- Shadow I -----------------------------
	//------- '-' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + width + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + width + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint + (height / 4.0f) - (width / 4.0f) - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint + (height / 4.0f) - (width / 4.0f) - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 4.0f) - (width / 4.0f) + width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 4.0f) - (width / 4.0f) + width - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '_' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + height - width + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + height - width + dShadow);
	glEnd();

	//----------------------------- I -----------------------------
	//------- '-' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint, yPoint + width);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + width);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint);
	glEnd();

	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint + (height / 4.0f) - (width / 4.0f), yPoint);

	graphCoordinate(xPoint + (height / 4.0f) - (width / 4.0f), yPoint + height);

	graphCoordinate(xPoint + (height / 4.0f) - (width / 4.0f) + width, yPoint + height);

	graphCoordinate(xPoint + (height / 4.0f) - (width / 4.0f) + width, yPoint);
	glEnd();

	// ------ '_' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint + height - width);

	graphCoordinate(xPoint, yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + height - width);
	glEnd();
}

void drawA(float xPoint, float yPoint)
{
	float width = 0.50f;
	float height = 1.73f;
	float slant = 0.74f;

	float dShadow = 0.25;
	float dW = 0.7f * width;
	float dH = 0.6f * height;
	//----------------------------- Shadow A -----------------------------
	//------- '/'
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint - slant - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint - slant + width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '\' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint + slant - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + slant + width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '-'
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dH + dShadow);

	graphCoordinate(xPoint - (slant / 2.0f) - dShadow, yPoint + dH + dW + dShadow);

	graphCoordinate(xPoint - (slant / 2.0f) + (2.0f * width) - dShadow, yPoint + dH + dW + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + dH + dShadow);
	glEnd();

	//----------------------------- A -----------------------------
	//------- '/'
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint - slant, yPoint + height);

	graphCoordinate(xPoint - slant + width, yPoint + height);

	graphCoordinate(xPoint + width, yPoint);
	glEnd();

	// ------ '\' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint + slant, yPoint + height);

	graphCoordinate(xPoint + slant + width, yPoint + height);

	graphCoordinate(xPoint + width, yPoint);
	glEnd();

	// ------ '-'
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint + dH);

	graphCoordinate(xPoint - slant / 2.0f, yPoint + dH + dW);

	graphCoordinate(xPoint - slant / 2.0f + (2.0f * width), yPoint + dH + dW);

	graphCoordinate(xPoint + width, yPoint + dH);
	glEnd();
}

void drawR(float xPoint, float yPoint)
{
	float width = 0.40f;
	float height = 1.73f;
	float slant = 0.74f;

	float dShadow = 0.25;
	float dH = 0.4 * height;

	//----------------------------- Shadow R -----------------------------
	//------- '|'
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '-' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + width + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + width + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '_' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + (height / 2.0f) - (width / 2.0f) + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + (height / 2.0f) + (width / 2.0f) + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + (height / 2.0f) + (width / 2.0f) + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + (height / 2.0f) - (width / 2.0f) + dShadow);
	glEnd();

	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width - dShadow, yPoint + (height / 2.0f) + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + (height / 2.0f) + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '\' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dH + dShadow);

	graphCoordinate(xPoint + slant - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + slant + width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + dH + dShadow);
	glEnd();
	//----------------------------- R -----------------------------
	//------- '|'
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint, yPoint + height);

	graphCoordinate(xPoint + width, yPoint + height);

	graphCoordinate(xPoint + width, yPoint);
	glEnd();

	// ------ '-' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint, yPoint + width);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + width);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint);
	glEnd();

	// ------ '_' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint + (height / 2.0f) - (width / 2.0f));

	graphCoordinate(xPoint, yPoint + (height / 2.0f) + (width / 2.0f));

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + (height / 2.0f) + (width / 2.0f));

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + (height / 2.0f) - (width / 2.0f));
	glEnd();

	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width, yPoint);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width, yPoint + (height / 2.0f));

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + (height / 2.0f));

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint);
	glEnd();

	// ------ '\' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint + dH);

	graphCoordinate(xPoint + slant, yPoint + height);

	graphCoordinate(xPoint + slant + width, yPoint + height);

	graphCoordinate(xPoint + width, yPoint + dH);
	glEnd();
}

void drawP(float xPoint, float yPoint)
{
	float width = 0.40f;
	float height = 1.73f;
	float slant = 0.74f;

	float dShadow = 0.25;
	float dH = 0.4 * height;

	//----------------------------- Shadow P -----------------------------
	//------- '|'
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '-' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + width + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + width + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '_' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + (height / 2.0f) - (width / 2.0f) + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + (height / 2.0f) + (width / 2.0f) + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + (height / 2.0f) + (width / 2.0f) + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + (height / 2.0f) - (width / 2.0f) + dShadow);
	glEnd();

	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width - dShadow, yPoint + (height / 2.0f) + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + (height / 2.0f) + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + dShadow);
	glEnd();

	//----------------------------- P -----------------------------
	//------- '|'
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint, yPoint + height);

	graphCoordinate(xPoint + width, yPoint + height);

	graphCoordinate(xPoint + width, yPoint);
	glEnd();

	// ------ '-' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint, yPoint + width);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + width);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint);
	glEnd();

	// ------ '_' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint + (height / 2.0f) - (width / 2.0f));

	graphCoordinate(xPoint, yPoint + (height / 2.0f) + (width / 2.0f));

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + (height / 2.0f) + (width / 2.0f));

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + (height / 2.0f) - (width / 2.0f));
	glEnd();

	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width, yPoint);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width, yPoint + (height / 2.0f));

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + (height / 2.0f));

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint);
	glEnd();
}

void drawO(float xPoint, float yPoint)
{
	float width = 0.40f;
	float height = 1.73f;
	float slant = 0.74f;

	float dShadow = 0.25;
	float dW = 0.7f * width;
	float dH = 0.6f * height;

	//----------------------------- Shadow O -----------------------------
	// ------ '-' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + width + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + width + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + dShadow);
	glEnd();

	//------- '|'
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '_' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint- dShadow, yPoint + height - width + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + height - width + dShadow);
	glEnd();

	//------- '|'
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + dShadow);
	glEnd();

	//----------------------------- O -----------------------------
	
	// ------ '-' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint, yPoint + width);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + width);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint);
	glEnd();
	
	//------- '|'
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint, yPoint + height);

	graphCoordinate(xPoint + width, yPoint + height);

	graphCoordinate(xPoint + width, yPoint);
	glEnd();

	// ------ '_' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint + height - width);

	graphCoordinate(xPoint, yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + height - width);
	glEnd();

	//------- '|'
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width, yPoint);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width, yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint);
	glEnd();
	
}

void drawM(float xPoint, float yPoint)
{
	float width = 0.40f;
	float height = 1.73f;
	float slant = 0.74f;

	float dShadow = 0.25;
	float dW = 0.7f * width;
	float dH = 0.6f * height;

	//----------------------------- Shadow M -----------------------------
	// ------ '-' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow );

	graphCoordinate(xPoint - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + dShadow);
	glEnd();

	//------- '|'
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint + slant - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + slant + width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '_' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint + 2 * slant - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint + slant - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + slant + width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (2 * slant) + width - dShadow, yPoint + dShadow);
	glEnd();

	//------- '|'
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint + 2 * slant - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint + 2 * slant - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (2 * slant) + width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (2 * slant) + width - dShadow, yPoint + dShadow);
	glEnd();

	//----------------------------- M -----------------------------

	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint, yPoint + height);

	graphCoordinate(xPoint + width, yPoint + height);

	graphCoordinate(xPoint + width, yPoint);
	glEnd();

	//------- '\'
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint + slant, yPoint + height);

	graphCoordinate(xPoint + slant + width, yPoint + height);

	graphCoordinate(xPoint + width, yPoint);
	glEnd();

	// ------ '/' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint + 2*slant, yPoint);

	graphCoordinate(xPoint + slant, yPoint + height);

	graphCoordinate(xPoint + slant + width, yPoint + height);

	graphCoordinate(xPoint + (2 * slant) + width, yPoint);
	glEnd();

	//------- '|'
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint + 2 * slant, yPoint);

	graphCoordinate(xPoint + 2 * slant, yPoint + height);

	graphCoordinate(xPoint + (2 * slant) + width, yPoint + height);

	graphCoordinate(xPoint + (2 * slant) + width, yPoint);
	glEnd();

}

void drawE(float xPoint, float yPoint)
{
	float width = 0.40f;
	float height = 1.73f;
	float slant = 0.74f;

	float dShadow = 0.25;
	float dW = 0.7f * width;
	float dH = 0.6f * height;

	//----------------------------- Shadow E -----------------------------

	// ------ '|'
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '-'
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + width + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + width + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '_'
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + (height / 2.0f) - (width / 2.0f) + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + (height / 2.0f) + (width / 2.0f) + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) - dShadow, yPoint + (height / 2.0f) + (width / 2.0f) + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) - dShadow, yPoint + (height / 2.0f) - (width / 2.0f) + dShadow);
	glEnd();

	// ------ '_'
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + height - width + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + height - width + dShadow);
	glEnd();

	//----------------------------- E -----------------------------

	// ------ '|'
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint, yPoint + height);

	graphCoordinate(xPoint + width, yPoint + height);

	graphCoordinate(xPoint + width, yPoint);
	glEnd();

	// ------ '-'
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint, yPoint + width);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + width);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint);
	glEnd();

	// ------ '_'
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint + (height / 2.0f) - (width / 2.0f));

	graphCoordinate(xPoint, yPoint + (height / 2.0f) + (width / 2.0f));

	graphCoordinate(xPoint + (height / 2.0f), yPoint + (height / 2.0f) + (width / 2.0f));

	graphCoordinate(xPoint + (height / 2.0f), yPoint + (height / 2.0f) - (width / 2.0f));
	glEnd();

	// ------ '_'
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint + height - width);

	graphCoordinate(xPoint, yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + height - width);
	glEnd();
}

void drawC(float xPoint, float yPoint)
{
	float width = 0.40f;
	float height = 1.73f;
	float slant = 0.74f;

	float dShadow = 0.25;
	float dW = 0.7f * width;
	float dH = 0.6f * height;

	//----------------------------- Shadow C -----------------------------

	// ------ '|'
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '-'
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + width + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + width + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '_'
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + height - width + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + height - width + dShadow);
	glEnd();

	//----------------------------- C -----------------------------

	// ------ '|'
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint, yPoint + height);

	graphCoordinate(xPoint + width, yPoint + height);

	graphCoordinate(xPoint + width, yPoint);
	glEnd();

	// ------ '-'
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint, yPoint + width);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + width);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint);
	glEnd();

	// ------ '_'
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint + height - width);

	graphCoordinate(xPoint, yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + height - width);
	glEnd();
}

void drawD(float xPoint, float yPoint)
{
	float width = 0.40f;
	float height = 1.73f;
	float slant = 0.74f;

	float dShadow = 0.25;
	float dW = 0.7f * width;
	float dH = 0.6f * height;

	float cut = 0.22f;   // cut amount for D

	//----------------------------- Shadow D -----------------------------

	// ------ '-'
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + width + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - cut - dShadow, yPoint + width + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - cut - dShadow, yPoint + dShadow);
	glEnd();

	//------- '|'
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '_'
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + height - width + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - cut - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - cut - dShadow, yPoint + height - width + dShadow);
	glEnd();

	//------- '|'
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width - dShadow, yPoint + cut + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width - dShadow, yPoint + height - cut + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + height - cut + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + cut + dShadow);
	glEnd();

	//----------------------------- D -----------------------------

	// ------ '-'
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint, yPoint + width);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - cut, yPoint + width);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - cut, yPoint);
	glEnd();

	//------- '|'
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint, yPoint + height);

	graphCoordinate(xPoint + width, yPoint + height);

	graphCoordinate(xPoint + width, yPoint);
	glEnd();

	// ------ '_'
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint + height - width);

	graphCoordinate(xPoint, yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - cut, yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - cut, yPoint + height - width);
	glEnd();

	//------- '|'
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width, yPoint + cut);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width, yPoint + height - cut);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + height - cut);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + cut);
	glEnd();
}

void drawB(float xPoint, float yPoint)
{
	float width = 0.40f;
	float height = 1.73f;

	float dShadow = 0.25;

	//----------------------------- Shadow B -----------------------------
	//------- '|'
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '-' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + width + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + width + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '_' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + (height / 2.0f) - (width / 2.0f) + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + (height / 2.0f) + (width / 2.0f) + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + (height / 2.0f) + (width / 2.0f) + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + (height / 2.0f) - (width / 2.0f) + dShadow);
	glEnd();

	// ------ '_' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + height - width + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + height - width + dShadow);
	glEnd();

	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width - dShadow, yPoint + (height / 2.0f) + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + (height / 2.0f) + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width - dShadow, yPoint + (height / 2.0f) + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + (height / 2.0f) + dShadow);
	glEnd();

	//----------------------------- B -----------------------------
	//------- '|'
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint, yPoint + height);

	graphCoordinate(xPoint + width, yPoint + height);

	graphCoordinate(xPoint + width, yPoint);
	glEnd();

	// ------ '-' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint, yPoint + width);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + width);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint);
	glEnd();

	// ------ '_' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint + (height / 2.0f) - (width / 2.0f));

	graphCoordinate(xPoint, yPoint + (height / 2.0f) + (width / 2.0f));

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + (height / 2.0f) + (width / 2.0f));

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + (height / 2.0f) - (width / 2.0f));
	glEnd();

	// ------ '_' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint + height - width);

	graphCoordinate(xPoint, yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + height - width);
	glEnd();

	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width, yPoint);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width, yPoint + (height / 2.0f));

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + (height / 2.0f));

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint);
	glEnd();

	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width, yPoint + (height / 2.0f));

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width, yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + (height / 2.0f));
	glEnd();
}

void drawG(float xPoint, float yPoint)
{
	float width = 0.40f;
	float height = 1.73f;

	float dShadow = 0.25;

	//----------------------------- Shadow G -----------------------------
	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '-' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + width + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + width + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '_' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + height - width + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + height - width + dShadow);
	glEnd();

	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width - dShadow, yPoint + (height / 2.0f) + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + (height / 2.0f) + dShadow);
	glEnd();

	// ------ '-' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint + (height / 4.0f) - dShadow, yPoint + (height / 2.0f) - (width / 2.0f) + dShadow);

	graphCoordinate(xPoint + (height / 4.0f) - dShadow, yPoint + (height / 2.0f) + (width / 2.0f) + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + (height / 2.0f) + (width / 2.0f) + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + (height / 2.0f) - (width / 2.0f) + dShadow);
	glEnd();

	//----------------------------- G -----------------------------
	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint, yPoint + height);

	graphCoordinate(xPoint + width, yPoint + height);

	graphCoordinate(xPoint + width, yPoint);
	glEnd();

	// ------ '-' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint, yPoint + width);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + width);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint);
	glEnd();

	// ------ '_' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint + height - width);

	graphCoordinate(xPoint, yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + height - width);
	glEnd();

	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width, yPoint + (height / 2.0f));

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width, yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + (height / 2.0f));
	glEnd();

	// ------ '-' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint + (height / 4.0f), yPoint + (height / 2.0f) - (width / 2.0f));

	graphCoordinate(xPoint + (height / 4.0f), yPoint + (height / 2.0f) + (width / 2.0f));

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + (height / 2.0f) + (width / 2.0f));

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + (height / 2.0f) - (width / 2.0f));
	glEnd();
}

void drawH(float xPoint, float yPoint)
{
	float width = 0.40f;
	float height = 1.73f;

	float dShadow = 0.25;

	//----------------------------- Shadow H -----------------------------
	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '_' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + (height / 2.0f) - (width / 2.0f) + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + (height / 2.0f) + (width / 2.0f) + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + (height / 2.0f) + (width / 2.0f) + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + (height / 2.0f) - (width / 2.0f) + dShadow);
	glEnd();

	//----------------------------- H -----------------------------
	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint, yPoint + height);

	graphCoordinate(xPoint + width, yPoint + height);

	graphCoordinate(xPoint + width, yPoint);
	glEnd();

	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width, yPoint);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width, yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint);
	glEnd();

	// ------ '_' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint + (height / 2.0f) - (width / 2.0f));

	graphCoordinate(xPoint, yPoint + (height / 2.0f) + (width / 2.0f));

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + (height / 2.0f) + (width / 2.0f));

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + (height / 2.0f) - (width / 2.0f));
	glEnd();
}

void drawK(float xPoint, float yPoint)
{
	float width = 0.40f;
	float height = 1.73f;
	float slant = 0.74f;

	float dShadow = 0.25;

	//----------------------------- Shadow K -----------------------------
	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '/' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + (height / 2.0f) + dShadow);

	graphCoordinate(xPoint + slant - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint + slant + width - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + (height / 2.0f) + dShadow);
	glEnd();

	// ------ '\' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + (height / 2.0f) - (width / 2.0f) + dShadow);

	graphCoordinate(xPoint + slant - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + slant + width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + (height / 2.0f) - (width / 2.0f) + dShadow);
	glEnd();

	//----------------------------- K -----------------------------
	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint, yPoint + height);

	graphCoordinate(xPoint + width, yPoint + height);

	graphCoordinate(xPoint + width, yPoint);
	glEnd();

	// ------ '/' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint + (height / 2.0f));

	graphCoordinate(xPoint + slant, yPoint);

	graphCoordinate(xPoint + slant + width, yPoint);

	graphCoordinate(xPoint + width, yPoint + (height / 2.0f));
	glEnd();

	// ------ '\' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint + (height / 2.0f) - (width / 2.0f));

	graphCoordinate(xPoint + slant, yPoint + height);

	graphCoordinate(xPoint + slant + width, yPoint + height);

	graphCoordinate(xPoint + width, yPoint + (height / 2.0f) - (width / 2.0f));
	glEnd();
}

void drawL(float xPoint, float yPoint)
{
	float width = 0.40f;
	float height = 1.73f;

	float dShadow = 0.25;

	//----------------------------- Shadow L -----------------------------
	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '_' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + height - width + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + height - width + dShadow);
	glEnd();

	//----------------------------- L -----------------------------
	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint, yPoint + height);

	graphCoordinate(xPoint + width, yPoint + height);

	graphCoordinate(xPoint + width, yPoint);
	glEnd();

	// ------ '_' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint + height - width);

	graphCoordinate(xPoint, yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + height - width);
	glEnd();
}

void drawN(float xPoint, float yPoint)
{
	float width = 0.40f;
	float height = 1.73f;
	float slant = 0.74f;

	float dShadow = 0.25;

	//----------------------------- Shadow N -----------------------------
	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '\' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint + slant - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + slant + width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint + slant - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint + slant - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + slant + width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + slant + width - dShadow, yPoint + dShadow);
	glEnd();

	//----------------------------- N -----------------------------
	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint, yPoint + height);

	graphCoordinate(xPoint + width, yPoint + height);

	graphCoordinate(xPoint + width, yPoint);
	glEnd();

	// ------ '\' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint + slant, yPoint + height);

	graphCoordinate(xPoint + slant + width, yPoint + height);

	graphCoordinate(xPoint + width, yPoint);
	glEnd();

	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint + slant, yPoint);

	graphCoordinate(xPoint + slant, yPoint + height);

	graphCoordinate(xPoint + slant + width, yPoint + height);

	graphCoordinate(xPoint + slant + width, yPoint);
	glEnd();
}

void drawU(float xPoint, float yPoint)
{
	float width = 0.40f;
	float height = 1.73f;

	float dShadow = 0.25;

	//----------------------------- Shadow U -----------------------------
	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '_' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + height - width + dShadow);

	graphCoordinate(xPoint - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + height - width + dShadow);
	glEnd();

	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + dShadow);
	glEnd();

	//----------------------------- U -----------------------------
	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint, yPoint + height);

	graphCoordinate(xPoint + width, yPoint + height);

	graphCoordinate(xPoint + width, yPoint);
	glEnd();

	// ------ '_' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint + height - width);

	graphCoordinate(xPoint, yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + height - width);
	glEnd();

	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width, yPoint);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width, yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + height);

	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint);
	glEnd();
}

void drawV(float xPoint, float yPoint)
{
	float width = 0.40f;
	float height = 1.73f;
	float slant = 0.50f;

	float dShadow = 0.25;

	//----------------------------- Shadow V -----------------------------
	// ------ '\' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint + slant - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + slant + width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '/' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint + (2.0f * slant) - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint + slant - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + slant + width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + (2.0f * slant) + width - dShadow, yPoint + dShadow);
	glEnd();

	//----------------------------- V -----------------------------
	// ------ '\' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint + slant, yPoint + height);

	graphCoordinate(xPoint + slant + width, yPoint + height);

	graphCoordinate(xPoint + width, yPoint);
	glEnd();

	// ------ '/' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint + (2.0f * slant), yPoint);

	graphCoordinate(xPoint + slant, yPoint + height);

	graphCoordinate(xPoint + slant + width, yPoint + height);

	graphCoordinate(xPoint + (2.0f * slant) + width, yPoint);
	glEnd();
}

void drawY(float xPoint, float yPoint)
{
	float width = 0.40f;
	float height = 1.73f;
	float slant = 0.40f;

	float dShadow = 0.25;

	//----------------------------- Shadow Y -----------------------------
	// ------ '\' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint + slant - dShadow, yPoint + (height / 2.0f) + dShadow);

	graphCoordinate(xPoint + slant + width - dShadow, yPoint + (height / 2.0f) + dShadow);

	graphCoordinate(xPoint + width - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '/' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint + (2.0f * slant) - dShadow, yPoint + dShadow);

	graphCoordinate(xPoint + slant - dShadow, yPoint + (height / 2.0f) + dShadow);

	graphCoordinate(xPoint + slant + width - dShadow, yPoint + (height / 2.0f) + dShadow);

	graphCoordinate(xPoint + (2.0f * slant) + width - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint + slant - dShadow, yPoint + (height / 2.0f) + dShadow);

	graphCoordinate(xPoint + slant - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + slant + width - dShadow, yPoint + height + dShadow);

	graphCoordinate(xPoint + slant + width - dShadow, yPoint + (height / 2.0f) + dShadow);
	glEnd();

	//----------------------------- Y -----------------------------
	// ------ '\' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);

	graphCoordinate(xPoint + slant, yPoint + (height / 2.0f));

	graphCoordinate(xPoint + slant + width, yPoint + (height / 2.0f));

	graphCoordinate(xPoint + width, yPoint);
	glEnd();

	// ------ '/' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint + (2.0f * slant), yPoint);

	graphCoordinate(xPoint + slant, yPoint + (height / 2.0f));

	graphCoordinate(xPoint + slant + width, yPoint + (height / 2.0f));

	graphCoordinate(xPoint + (2.0f * slant) + width, yPoint);
	glEnd();

	// ------ '|' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint + slant, yPoint + (height / 2.0f));

	graphCoordinate(xPoint + slant, yPoint + height);

	graphCoordinate(xPoint + slant + width, yPoint + height);

	graphCoordinate(xPoint + slant + width, yPoint + (height / 2.0f));
	glEnd();
}

void drawW(float xPoint, float yPoint)
{
	float width = 0.40f;
	float height = 1.73f;
	float slant = 0.74f;
	float dShadow = 0.25;

	//----------------------------- Shadow W -----------------------------
	// ------ '/' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + height + dShadow);
	graphCoordinate(xPoint + slant - dShadow, yPoint + dShadow);
	graphCoordinate(xPoint + slant + width - dShadow, yPoint + dShadow);
	graphCoordinate(xPoint + width - dShadow, yPoint + height + dShadow);
	glEnd();

	//------- '\' 
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint + slant - dShadow, yPoint + dShadow);
	graphCoordinate(xPoint + 2 * slant - dShadow, yPoint + height + dShadow);
	graphCoordinate(xPoint + 2 * slant + width - dShadow, yPoint + height + dShadow);
	graphCoordinate(xPoint + slant + width - dShadow, yPoint + dShadow);
	glEnd();

	//----------------------------- W -----------------------------
	// ------ '|' left
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);
	graphCoordinate(xPoint, yPoint + height);
	graphCoordinate(xPoint + width, yPoint + height);
	graphCoordinate(xPoint + width, yPoint);
	glEnd();

	//------- '/'
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint + height);
	graphCoordinate(xPoint + slant, yPoint);
	graphCoordinate(xPoint + slant + width, yPoint);
	graphCoordinate(xPoint + width, yPoint + height);
	glEnd();

	// ------ '\' 
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint + slant, yPoint);
	graphCoordinate(xPoint + 2 * slant, yPoint + height);
	graphCoordinate(xPoint + 2 * slant + width, yPoint + height);
	graphCoordinate(xPoint + slant + width, yPoint);
	glEnd();

	//------- '|' right
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint + 2 * slant, yPoint);
	graphCoordinate(xPoint + 2 * slant, yPoint + height);
	graphCoordinate(xPoint + (2 * slant) + width, yPoint + height);
	graphCoordinate(xPoint + (2 * slant) + width, yPoint);
	glEnd();
}

void drawF(float xPoint, float yPoint)
{
	float width = 0.40f;
	float height = 1.73f;
	float dShadow = 0.25;

	//----------------------------- Shadow F -----------------------------
	// ------ '|'
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);
	graphCoordinate(xPoint - dShadow, yPoint + height + dShadow);
	graphCoordinate(xPoint + width - dShadow, yPoint + height + dShadow);
	graphCoordinate(xPoint + width - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '-' (Top)
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + dShadow);
	graphCoordinate(xPoint - dShadow, yPoint + width + dShadow);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + width + dShadow);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '_' (Middle)
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + (height / 2.0f) - (width / 2.0f) + dShadow);
	graphCoordinate(xPoint - dShadow, yPoint + (height / 2.0f) + (width / 2.0f) + dShadow);
	graphCoordinate(xPoint + (height / 2.0f) - dShadow, yPoint + (height / 2.0f) + (width / 2.0f) + dShadow);
	graphCoordinate(xPoint + (height / 2.0f) - dShadow, yPoint + (height / 2.0f) - (width / 2.0f) + dShadow);
	glEnd();

	//----------------------------- F -----------------------------
	// ------ '|'
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);
	graphCoordinate(xPoint, yPoint + height);
	graphCoordinate(xPoint + width, yPoint + height);
	graphCoordinate(xPoint + width, yPoint);
	glEnd();

	// ------ '-' (Top)
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint);
	graphCoordinate(xPoint, yPoint + width);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + width);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint);
	glEnd();

	// ------ '_' (Middle)
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint + (height / 2.0f) - (width / 2.0f));
	graphCoordinate(xPoint, yPoint + (height / 2.0f) + (width / 2.0f));
	graphCoordinate(xPoint + (height / 2.0f), yPoint + (height / 2.0f) + (width / 2.0f));
	graphCoordinate(xPoint + (height / 2.0f), yPoint + (height / 2.0f) - (width / 2.0f));
	glEnd();
}

void drawJ(float xPoint, float yPoint)
{
	float width = 0.40f;
	float height = 1.73f;
	float dShadow = 0.25;

	//----------------------------- Shadow J -----------------------------
	// ------ '|' Right
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width - dShadow, yPoint + dShadow);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width - dShadow, yPoint + height + dShadow);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + height + dShadow);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + dShadow);
	glEnd();

	// ------ '_' Bottom
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + height - width + dShadow);
	graphCoordinate(xPoint - dShadow, yPoint + height + dShadow);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + height + dShadow);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + height - width + dShadow);
	glEnd();

	// ------ '|' Left hook
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + (height * 0.6f) + dShadow);
	graphCoordinate(xPoint - dShadow, yPoint + height + dShadow);
	graphCoordinate(xPoint + width - dShadow, yPoint + height + dShadow);
	graphCoordinate(xPoint + width - dShadow, yPoint + (height * 0.6f) + dShadow);
	glEnd();

	//----------------------------- J -----------------------------
	// ------ '|' Right
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width, yPoint);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - width, yPoint + height);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + height);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint);
	glEnd();

	// ------ '_' Bottom
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint + height - width);
	graphCoordinate(xPoint, yPoint + height);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + height);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + height - width);
	glEnd();

	// ------ '|' Left hook
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint + (height * 0.6f));
	graphCoordinate(xPoint, yPoint + height);
	graphCoordinate(xPoint + width, yPoint + height);
	graphCoordinate(xPoint + width, yPoint + (height * 0.6f));
	glEnd();
}

void drawColon(float xPoint, float yPoint)
{
	float width = 0.40f;
	float height = 1.73f;
	float dShadow = 0.25;

	//----------------------------- Shadow : -----------------------------
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	// Top dot
	graphCoordinate(xPoint - dShadow, yPoint + (height * 0.2f) + dShadow);
	graphCoordinate(xPoint - dShadow, yPoint + (height * 0.2f) + width + dShadow);
	graphCoordinate(xPoint + width - dShadow, yPoint + (height * 0.2f) + width + dShadow);
	graphCoordinate(xPoint + width - dShadow, yPoint + (height * 0.2f) + dShadow);

	// Bottom dot
	graphCoordinate(xPoint - dShadow, yPoint + (height * 0.7f) + dShadow);
	graphCoordinate(xPoint - dShadow, yPoint + (height * 0.7f) + width + dShadow);
	graphCoordinate(xPoint + width - dShadow, yPoint + (height * 0.7f) + width + dShadow);
	graphCoordinate(xPoint + width - dShadow, yPoint + (height * 0.7f) + dShadow);
	glEnd();

	//----------------------------- : -----------------------------
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	// Top dot
	graphCoordinate(xPoint, yPoint + (height * 0.2f));
	graphCoordinate(xPoint, yPoint + (height * 0.2f) + width);
	graphCoordinate(xPoint + width, yPoint + (height * 0.2f) + width);
	graphCoordinate(xPoint + width, yPoint + (height * 0.2f));

	// Bottom dot
	graphCoordinate(xPoint, yPoint + (height * 0.7f));
	graphCoordinate(xPoint, yPoint + (height * 0.7f) + width);
	graphCoordinate(xPoint + width, yPoint + (height * 0.7f) + width);
	graphCoordinate(xPoint + width, yPoint + (height * 0.7f));
	glEnd();
}

void drawDash(float xPoint, float yPoint)
{
	float width = 0.40f;
	float height = 1.73f;
	float dShadow = 0.25;

	//----------------------------- Shadow - -----------------------------
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + (height / 2.0f) - (width / 2.0f) + dShadow);
	graphCoordinate(xPoint - dShadow, yPoint + (height / 2.0f) + (width / 2.0f) + dShadow);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + (height / 2.0f) + (width / 2.0f) + dShadow);
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f) - dShadow, yPoint + (height / 2.0f) - (width / 2.0f) + dShadow);
	glEnd();

	//----------------------------- - -----------------------------
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint + (height / 2.0f) - (width / 2.0f));
	graphCoordinate(xPoint, yPoint + (height / 2.0f) + (width / 2.0f));
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + (height / 2.0f) + (width / 2.0f));
	graphCoordinate(xPoint + (height / 2.0f) + (width / 2.0f), yPoint + (height / 2.0f) - (width / 2.0f));
	glEnd();
}

void drawDot(float xPoint, float yPoint)
{
	float width = 0.40f;
	float height = 1.73f;
	float dShadow = 0.25;

	//----------------------------- Shadow . -----------------------------
	glBegin(GL_QUADS);
	glColor3f(shadowDarkColorArr[0], shadowDarkColorArr[1], shadowDarkColorArr[2]);
	graphCoordinate(xPoint - dShadow, yPoint + height - width + dShadow);
	graphCoordinate(xPoint - dShadow, yPoint + height + dShadow);
	graphCoordinate(xPoint + width - dShadow, yPoint + height + dShadow);
	graphCoordinate(xPoint + width - dShadow, yPoint + height - width + dShadow);
	glEnd();

	//----------------------------- . -----------------------------
	glBegin(GL_QUADS);
	glColor3f(bodyLightColorArr[0], bodyLightColorArr[1], bodyLightColorArr[2]);
	graphCoordinate(xPoint, yPoint + height - width);
	graphCoordinate(xPoint, yPoint + height);
	graphCoordinate(xPoint + width, yPoint + height);
	graphCoordinate(xPoint + width, yPoint + height - width);
	glEnd();
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


void setLetterColor(float r, float g, float b)
{
	bodyLightColorArr[0] = r;
	bodyLightColorArr[1] = g;
	bodyLightColorArr[2] = b;

	shadowDarkColorArr[0] = r * 0.45f;
	shadowDarkColorArr[1] = g * 0.45f;
	shadowDarkColorArr[2] = b * 0.45f;
}

void display(void) 
{
	// code
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(-0.3f, 0.3f, 0.0f);
	glScalef(0.7f, 0.7f, 1.0f);

	// ----------------------------- TECHNOLOGIES USED -----------------------------
	setLetterColor(1.0f, 0.84f, 0.0f);
	float yT = 1.0f;
	drawT(6.8f, yT); drawE(8.6f, yT); drawC(10.4f, yT); drawH(12.2f, yT); drawN(14.0f, yT); drawO(15.8f, yT); drawL(17.6f, yT); drawO(19.4f, yT); drawG(21.2f, yT); drawI(23.0f, yT); drawE(24.2f, yT); drawS(26.0f, yT);
	drawU(28.8f, yT); drawS(30.6f, yT); drawE(32.4f, yT); drawD(34.2f, yT);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5f, 0.5f, 0.0f);
	glScalef(0.5f, 0.5f, 1.0f);

	// FREEGLUT
	setLetterColor(0.0f, 1.0f, 1.0f);
	float yF = 5.0f;
	drawF(22.8f, yF); drawR(24.6f, yF); drawE(26.4f, yF); drawE(28.2f, yF); drawG(30.0f, yF); drawL(31.8f, yF); drawU(33.6f, yF); drawT(35.4f, yF);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3f, 0.3f, 0.0f);
	glScalef(0.7f, 0.7f, 1.0f);

	// ----------------------------- SPECIAL THANKS -----------------------------
	setLetterColor(1.0f, 0.84f, 0.0f);
	float yS = 6.5f;
	drawS(11.0f, yS); drawP(12.8f, yS); drawE(14.6f, yS); drawC(16.4f, yS); drawI(18.2f, yS); drawA(20.0f, yS); drawL(21.8f, yS);
	drawT(24.6f, yS); drawH(26.4f, yS); drawA(28.2f, yS); drawN(30.0f, yS); drawK(31.8f, yS); drawS(33.6f, yS);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5f, 0.5f, 0.0f);
	glScalef(0.5f, 0.5f, 1.0f);

	setLetterColor(1.0f, 0.4f, 0.6f);
	float yR = 13.0f;
	drawD(10.2f, yR); drawR(12.0f, yR); drawDot(13.8f, yR);
	drawR(16.6f, yR); drawA(18.4f, yR); drawM(20.2f, yR); drawA(23.2f, yR);
	drawG(26.0f, yR); drawO(27.8f, yR); drawK(29.6f, yR); drawH(31.4f, yR); drawA(33.2f, yR); drawL(35.0f, yR); drawE(36.8f, yR);
	drawM(39.6f, yR); drawA(42.6f, yR); drawD(44.4f, yR); drawA(46.2f, yR); drawM(48.0f, yR);

	setLetterColor(0.7f, 0.3f, 1.0f);
	float yP = 16.0f;
	drawP(11.1f, yP); drawR(12.9f, yP); drawA(14.7f, yP); drawD(16.5f, yP); drawN(18.3f, yP); drawY(20.1f, yP); drawA(21.9f, yP);
	drawG(24.7f, yP); drawO(26.5f, yP); drawK(28.3f, yP); drawH(30.1f, yP); drawA(31.9f, yP); drawL(33.7f, yP); drawE(35.5f, yP);
	drawM(38.3f, yP); drawA(41.3f, yP); drawD(43.1f, yP); drawA(44.9f, yP); drawM(46.7f, yP);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3f, 0.3f, 0.0f);
	glScalef(0.7f, 0.7f, 1.0f);

	// ----------------------------- GUIDED BY -----------------------------
	setLetterColor(1.0f, 0.84f, 0.0f);
	float yG = 14.5f;
	drawG(14.0f, yG); drawU(15.8f, yG); drawI(17.6f, yG); drawD(18.8f, yG); drawE(20.6f, yG); drawD(22.4f, yG);
	drawB(25.2f, yG); drawY(27.0f, yG);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5f, 0.5f, 0.0f);
	glScalef(0.5f, 0.5f, 1.0f);

	setLetterColor(1.0f, 0.5f, 0.0f);
	float yV = 24.0f;
	drawD(9.3f, yV); drawR(11.1f, yV); drawDot(12.9f, yV);
	drawV(15.7f, yV); drawI(17.5f, yV); drawJ(18.7f, yV); drawA(20.5f, yV); drawY(22.3f, yV);
	drawD(25.1f, yV);
	drawG(27.9f, yV); drawO(29.7f, yV); drawK(31.5f, yV); drawH(33.3f, yV); drawA(35.1f, yV); drawL(36.9f, yV); drawE(38.7f, yV);
	drawS(41.5f, yV); drawI(43.3f, yV); drawR(44.5f, yV);

	glPopMatrix();

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


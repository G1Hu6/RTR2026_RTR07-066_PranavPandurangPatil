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
	glScalef(0.8f, 0.8f, 1.0f);

	float titleY = 8.5f;

	// THE CALL
	setLetterColor(1.0f, 0.5f, 0.1f);
	drawT(3.6f, titleY); drawH(5.4f, titleY); drawE(7.2f, titleY);
	drawC(10.0f, titleY); drawA(11.8f, titleY); drawL(13.6f, titleY); drawL(15.4f, titleY);

	// FOR
	setLetterColor(1.0f, 1.0f, 1.0f); // White
	drawF(18.2f, titleY);
	
	setLetterColor(0.0f, 0.0f, 1.0f); // Blue
	drawO(20.0f, titleY);
	
	setLetterColor(1.0f, 1.0f, 1.0f); // White
	drawR(21.8f, titleY);

	// FREEDOM
	setLetterColor(0.1f, 0.6f, 0.1f);
	drawF(24.6f, titleY); drawR(26.4f, titleY); drawE(28.2f, titleY); drawE(30.0f, titleY); drawD(31.8f, titleY); drawO(33.6f, titleY); drawM(35.4f, titleY);

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


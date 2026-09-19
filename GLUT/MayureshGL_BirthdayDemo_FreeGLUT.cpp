#include <GL/freeglut.h>
#include <math.h>
#include <stdlib.h>

bool bIsFullscreen = false;
const float PI = 3.14159265358979323846f;

// Coordinate mapping constants for Group Members & Credit Screens
#define X_MAX 30.0f
#define Y_MAX 13.0f

float shadowDarkColorArr[] = { 0.45f, 0.0f, 0.0f };
float bodyLightColorArr[] = { 1.0f, 0.0f, 0.0f };

// ============================================================
// MASTER NARRATIVE ANIMATION STATE MACHINE
// ============================================================
enum MasterSceneState {
    // Scene 1: Sheep Island & Going Merry Sailing
    MSTATE_SHEEP_TRANSIT,        // Ship sailing across open sea
    MSTATE_SHEEP_SAIL,           // Ship approaching Sheep Island
    MSTATE_SHEEP_DOCK_PAUSE,     // Ship docked at island, pausing
    MSTATE_FADE_TO_LUFFY_WALK,   // Fade out to black

    // Scene 2: Luffy Walking on Beach & Spotting Chest
    MSTATE_LUFFY_WALK,           // Luffy walking side-profile on beach
    MSTATE_LUFFY_SPOT,           // Luffy stops near chest, '!' pops up
    MSTATE_FADE_TO_REAR,         // Fade out to black

    // Scene 3: Rear-View Observation of Open Glowing Chest
    MSTATE_REAR_VIEW,            // Luffy from behind watching open glowing chest
    MSTATE_FADE_TO_BIRTHDAY,     // Fade out to black before Birthday Scene

    // Scene 4: Birthday Celebration & Tribute (Mayuresh)
    MSTATE_BIRTHDAY,             // Happy Birthday Mayuresh + Balloons + Portrait Drawing
    MSTATE_FADE_TO_GROUP_MEMBERS,// Fade out to black before Group Members Screen

    // Scene 5: Group Members & Group Leader Screen
    MSTATE_GROUP_MEMBERS,        // Group Members List & Leader Display
    MSTATE_FADE_TO_CREDITS,      // Fade out to black before Credits Screen

    // Scene 6: Credits Screen (Technologies & Special Thanks)
    MSTATE_CREDIT_SCREEN,        // Technologies Used & Guided By Credits
    MSTATE_FADE_TO_SHEEP         // Fade out to black back to Scene 1
};

MasterSceneState g_masterState = MSTATE_SHEEP_TRANSIT;

// Animation & State Control Variables
float g_fadeAlpha    = 0.0f;
float g_stateTimer   = 0.0f;
float g_sparkleAngle = 0.0f;
bool  g_isAnimating  = true;

// Window Dimensions for Resizing & Perspective Projection
int g_winWidth  = 1140;
int g_winHeight = 760;

// Scene 1 Variables (Going Merry / Sheep Island)
float shipX = 1.15f;
float waterMove = 0.0f;
float flagWave = 0.0f;
float dockPauseTimer = 0.0f;

const float TRANSIT_SPEED    = 0.005f;
const float TRANSIT_EXIT_X   = -0.15f;
const float APPROACH_START_X = 0.55f;
const float SHIP_STOP_X      = 0.30f;

// Scene 2 & 3 Variables (Luffy Walking & Rear View)
float g_translateX = -1.8f;
float g_walkSpeed  = 0.005f;
float g_walkPhase  = 0.0f;

// Scene 4 Variables (Birthday Animation & Mayuresh Drawing)
float happyX = -2.5f;
float birthdayX = 2.5f;
float MayureshY = -2.0f;
float BalloonY = -2.0f;
float HappyAlpha = 1.0f;
float BirthdayAlpha = 1.0f;
float MayureshAlpha = 1.0f;
GLfloat MayureshDrawingAlpha = 0.005f;
GLboolean bShowMayureshDrawing = FALSE;
float g_birthdayHoldTimer = 0.0f;

// ============================================================
// MATHEMATICAL PRIMITIVE DRAWING UTILITIES
// ============================================================

void circle(float x, float y, float r) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 40; i++) {
        float angle = i * 2.0f * PI / 40.0f;
        glVertex2f(x + r * 0.67f * cosf(angle), y + r * sinf(angle));
    }
    glEnd();
}

void DrawCircle(void) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    for (int i = 0; i <= 360; i++) {
        float angle = (float)i * PI / 180.0f;
        glVertex2f(cosf(angle), sinf(angle));
    }
    glEnd();
}

void drawCircle(float cx, float cy, float r, int segments = 32) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++) {
        float a = 2.0f * PI * ((float)i / (float)segments);
        glVertex2f(cx + cosf(a) * r, cy + sinf(a) * r);
    }
    glEnd();
}

void drawEllipse(float cx, float cy, float rx, float ry, int segments = 32) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < segments; i++) {
        float a = 2.0f * PI * ((float)i / (float)segments);
        glVertex2f(cx + cosf(a) * rx, cy + sinf(a) * ry);
    }
    glEnd();
}

void drawCapsule(float x1, float y1, float x2, float y2, float r) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float len = sqrtf(dx * dx + dy * dy);
    if (len < 0.0001f) {
        drawCircle(x1, y1, r);
        return;
    }
    float nx = -dy / len * r;
    float ny =  dx / len * r;

    glBegin(GL_QUADS);
    glVertex2f(x1 + nx, y1 + ny);
    glVertex2f(x2 + nx, y2 + ny);
    glVertex2f(x2 - nx, y2 - ny);
    glVertex2f(x1 - nx, y1 - ny);
    glEnd();

    drawCircle(x1, y1, r, 20);
    drawCircle(x2, y2, r, 20);
}

void drawPerpendicularCuff(float cx, float cy, float vx, float vy, float hl, float hw) {
    float len = sqrtf(vx * vx + vy * vy);
    if (len < 0.0001f) return;

    float ux = vx / len;
    float uy = vy / len;

    float nx = -uy;
    float ny =  ux;

    float c1x = cx - ux * hl - nx * hw, c1y = cy - uy * hl - ny * hw;
    float c2x = cx + ux * hl - nx * hw, c2y = cy + uy * hl - ny * hw;
    float c3x = cx + ux * hl + nx * hw, c3y = cy + uy * hl + ny * hw;
    float c4x = cx - ux * hl + nx * hw, c4y = cy - uy * hl + ny * hw;

    glBegin(GL_QUADS);
    glVertex2f(c1x, c1y);
    glVertex2f(c2x, c2y);
    glVertex2f(c3x, c3y);
    glVertex2f(c4x, c4y);
    glEnd();

    drawCircle(cx - nx * hw, cy - ny * hw, hl, 16);
    drawCircle(cx + nx * hw, cy + ny * hw, hl, 16);
}

void drawQuadPx(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glVertex2f(x4, y4);
    glEnd();
}

void drawTrianglePx(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

void drawLinePx(float x1, float y1, float x2, float y2, float width) {
    glLineWidth(width);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
    glLineWidth(1.0f);
}

void drawFlatFootAndSandal(
    float heelX, float heelY,
    float toeX, float toeY,
    float soleThickPx,
    float ankleX, float ankleY,
    const float* skinColor,
    const float* soleColor,
    const float* strapColor,
    bool isFrontFoot
) {
    float dx = toeX - heelX;
    float dy = toeY - heelY;
    float len = sqrtf(dx * dx + dy * dy);
    if (len < 0.001f) return;

    float ux = dx / len;
    float uy = dy / len;

    float nx = -uy;
    float ny =  ux;

    float fx = -nx;
    float fy = -ny;

    glColor3fv(soleColor);
    float p1x = heelX - ux * 2.0f,                    p1y = heelY - uy * 2.0f;
    float p2x = toeX  + ux * 2.0f,                    p2y = toeY  + uy * 2.0f;
    float p3x = toeX  + ux * 2.0f + nx * soleThickPx, p3y = toeY  + uy * 2.0f + ny * soleThickPx;
    float p4x = heelX - ux * 2.0f + nx * soleThickPx, p4y = heelY - uy * 2.0f + ny * soleThickPx;
    drawQuadPx(p1x, p1y, p2x, p2y, p3x, p3y, p4x, p4y);

    float halfThick = soleThickPx * 0.5f;
    drawCircle(heelX + nx * halfThick, heelY + ny * halfThick, halfThick, 16);
    drawCircle(toeX  + nx * halfThick, toeY  + ny * halfThick, halfThick, 16);

    glColor3fv(skinColor);
    float instepH = isFrontFoot ? 8.0f : 7.5f;
    float instepX = toeX - ux * 7.0f + fx * instepH;
    float instepY = toeY - uy * 7.0f + fy * instepH;

    drawTrianglePx(heelX, heelY, toeX, toeY, instepX, instepY);
    drawTrianglePx(heelX, heelY, instepX, instepY, ankleX, ankleY);
    drawCircle(toeX, toeY, 3.5f, 16);
    drawCircle(ankleX, ankleY, 4.8f, 16);

    glColor3fv(strapColor);
    if (isFrontFoot) {
        float s1x = heelX + ux * 13.0f, s1y = heelY + uy * 13.0f;
        float s2x = heelX + ux * 17.0f + fx * 6.5f, s2y = heelY + uy * 17.0f + fy * 6.5f;
        float s3x = heelX + ux * 22.0f, s3y = heelY + uy * 22.0f;
        drawLinePx(s1x, s1y, s2x, s2y, 4.5f);
        drawLinePx(s2x, s2y, s3x, s3y, 4.5f);
        drawCircle(s2x, s2y, 2.5f, 12);
    } else {
        float s1x = heelX + ux * 12.0f, s1y = heelY + uy * 12.0f;
        float s2x = heelX + ux * 16.0f + fx * 6.0f, s2y = heelY + uy * 16.0f + fy * 6.0f;
        float s3x = heelX + ux * 20.0f, s3y = heelY + uy * 20.0f;
        drawLinePx(s1x, s1y, s2x, s2y, 4.5f);
        drawLinePx(s2x, s2y, s3x, s3y, 4.5f);
        drawCircle(s2x, s2y, 2.5f, 12);
    }
}

// ============================================================
// SCENE 1: SHEEP ISLAND & GOING MERRY RENDERING
// ============================================================

void drawFlag() {
    glColor3ub(92, 53, 23);
    glRectf(0.52f, 0.83f, 0.53f, 0.98f);

    float wave1 = 0.015f * sinf(flagWave);
    float wave2 = 0.025f * sinf(flagWave + 0.8f);

    glColor3ub(20, 20, 20);
    glBegin(GL_QUADS);
    glVertex2f(0.53f, 0.97f);
    glVertex2f(0.63f + wave1, 0.96f + wave1);
    glVertex2f(0.63f + wave2, 0.86f + wave2);
    glVertex2f(0.53f, 0.85f);
    glEnd();

    glColor3ub(255, 255, 255);
    circle(0.58f + wave2, 0.91f, 0.02f);
    glRectf(0.57f + wave2, 0.88f, 0.59f + wave2, 0.90f);

    glColor3ub(20, 20, 20);
    circle(0.57f + wave2, 0.92f, 0.01f);
    circle(0.58f + wave2, 0.92f, 0.01f);

    glRectf(0.56f + wave2, 0.93f, 0.60f + wave2, 0.94f);
    glRectf(0.57f + wave2, 0.94f, 0.59f + wave2, 0.95f);
}

void drawMast() {
    glColor3ub(20, 20, 20);
    glRectf(0.51f, 0.35f, 0.53f, 0.83f);

    glBegin(GL_QUADS);
    glVertex2f(0.49f, 0.79f);
    glVertex2f(0.56f, 0.79f);
    glVertex2f(0.55f, 0.85f);
    glVertex2f(0.49f, 0.85f);
    glEnd();

    glColor3ub(123, 74, 36);
    glBegin(GL_QUADS);
    glVertex2f(0.36f, 0.82f);
    glVertex2f(0.73f, 0.83f);
    glVertex2f(0.73f, 0.82f);
    glVertex2f(0.36f, 0.81f);
    glEnd();
}

void drawSail() {
    glColor3ub(241, 238, 230);
    glBegin(GL_QUADS);
    glVertex2f(0.38f, 0.81f);
    glVertex2f(0.68f, 0.82f);
    glVertex2f(0.65f, 0.37f);
    glVertex2f(0.42f, 0.39f);
    glEnd();

    glColor3ub(20, 20, 20);
    glLineWidth(8);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.38f, 0.81f);
    glVertex2f(0.68f, 0.82f);
    glVertex2f(0.65f, 0.37f);
    glVertex2f(0.42f, 0.39f);
    glEnd();
    glLineWidth(1.0f);
}

void drawStripedSail() {
    glColor3ub(255, 255, 255);
    glBegin(GL_QUADS);
    glVertex2f(0.66f, 0.62f);
    glVertex2f(0.78f, 0.65f);
    glVertex2f(0.72f, 0.36f);
    glVertex2f(0.66f, 0.37f);
    glEnd();

    glColor3ub(226, 58, 50);
    glBegin(GL_QUADS);
    glVertex2f(0.68f, 0.63f);
    glVertex2f(0.70f, 0.63f);
    glVertex2f(0.68f, 0.36f);
    glVertex2f(0.67f, 0.37f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(0.71f, 0.63f);
    glVertex2f(0.73f, 0.64f);
    glVertex2f(0.71f, 0.36f);
    glVertex2f(0.69f, 0.36f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(0.75f, 0.64f);
    glVertex2f(0.77f, 0.65f);
    glVertex2f(0.72f, 0.36f);
    glVertex2f(0.71f, 0.36f);
    glEnd();

    glColor3ub(20, 20, 20);
    glLineWidth(7);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.66f, 0.62f);
    glVertex2f(0.78f, 0.65f);
    glVertex2f(0.72f, 0.36f);
    glVertex2f(0.66f, 0.37f);
    glEnd();
    glLineWidth(1.0f);
}

void drawBones() {
    glColor3ub(255, 255, 255);
    glLineWidth(30);
    glBegin(GL_LINES);
    glVertex2f(0.42f, 0.70f);
    glVertex2f(0.64f, 0.49f);
    glVertex2f(0.42f, 0.49f);
    glVertex2f(0.64f, 0.70f);
    glEnd();
    glLineWidth(1.0f);

    circle(0.41f, 0.72f, 0.02f);
    circle(0.40f, 0.69f, 0.02f);
    circle(0.64f, 0.48f, 0.02f);
    circle(0.66f, 0.50f, 0.02f);
    circle(0.41f, 0.48f, 0.02f);
    circle(0.40f, 0.50f, 0.02f);
    circle(0.64f, 0.72f, 0.02f);
    circle(0.66f, 0.69f, 0.02f);
}

void drawSkull() {
    glColor3ub(255, 255, 255);
    circle(0.53f, 0.60f, 0.09f);

    glBegin(GL_QUADS);
    glVertex2f(0.49f, 0.57f);
    glVertex2f(0.56f, 0.57f);
    glVertex2f(0.56f, 0.50f);
    glVertex2f(0.50f, 0.50f);
    glEnd();

    glColor3ub(20, 20, 20);
    circle(0.50f, 0.61f, 0.03f);
    circle(0.55f, 0.61f, 0.03f);

    glBegin(GL_TRIANGLES);
    glVertex2f(0.53f, 0.58f);
    glVertex2f(0.52f, 0.56f);
    glVertex2f(0.53f, 0.56f);
    glEnd();

    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(0.49f, 0.54f); glVertex2f(0.56f, 0.54f);
    glVertex2f(0.51f, 0.54f); glVertex2f(0.51f, 0.50f);
    glVertex2f(0.52f, 0.54f); glVertex2f(0.52f, 0.50f);
    glVertex2f(0.53f, 0.54f); glVertex2f(0.53f, 0.50f);
    glVertex2f(0.55f, 0.54f); glVertex2f(0.55f, 0.50f);
    glEnd();
    glLineWidth(1.0f);
}

void drawStrawHat() {
    glColor3ub(246, 195, 36);
    glRectf(0.48f, 0.67f, 0.57f, 0.71f);
    glColor3ub(226, 58, 50);
    glRectf(0.48f, 0.67f, 0.57f, 0.69f);

    glColor3ub(246, 195, 36);
    glBegin(GL_QUADS);
    glVertex2f(0.44f, 0.67f);
    glVertex2f(0.61f, 0.67f);
    glVertex2f(0.61f, 0.65f);
    glVertex2f(0.45f, 0.65f);
    glEnd();
}

void drawHull() {
    glColor3ub(123, 74, 36);
    glBegin(GL_POLYGON);
    glVertex2f(0.32f, 0.32f); glVertex2f(0.75f, 0.34f);
    glVertex2f(0.74f, 0.23f); glVertex2f(0.70f, 0.13f);
    glVertex2f(0.64f, 0.08f); glVertex2f(0.55f, 0.05f);
    glVertex2f(0.46f, 0.06f); glVertex2f(0.40f, 0.09f);
    glVertex2f(0.35f, 0.16f); glVertex2f(0.33f, 0.25f);
    glEnd();

    glColor3ub(20, 20, 20);
    glLineWidth(9);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.32f, 0.32f); glVertex2f(0.75f, 0.34f);
    glVertex2f(0.74f, 0.23f); glVertex2f(0.70f, 0.13f);
    glVertex2f(0.64f, 0.08f); glVertex2f(0.55f, 0.05f);
    glVertex2f(0.46f, 0.06f); glVertex2f(0.40f, 0.09f);
    glVertex2f(0.35f, 0.16f); glVertex2f(0.33f, 0.25f);
    glEnd();

    glColor3ub(92, 53, 23);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2f(0.34f, 0.27f); glVertex2f(0.75f, 0.29f);
    glVertex2f(0.35f, 0.21f); glVertex2f(0.73f, 0.23f);
    glEnd();
    glLineWidth(1.0f);

    glColor3ub(20, 20, 20);
    circle(0.44f, 0.25f, 0.04f);
    glColor3ub(140, 140, 140);
    circle(0.44f, 0.25f, 0.03f);
    glColor3ub(60, 60, 60);
    circle(0.44f, 0.25f, 0.02f);
}

void drawDeck() {
    glColor3ub(255, 255, 255);
    glBegin(GL_QUADS);
    glVertex2f(0.33f, 0.34f); glVertex2f(0.75f, 0.35f);
    glVertex2f(0.75f, 0.32f); glVertex2f(0.33f, 0.30f);
    glEnd();

    glColor3ub(20, 20, 20);
    glLineWidth(4);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.33f, 0.34f); glVertex2f(0.75f, 0.35f);
    glVertex2f(0.75f, 0.32f); glVertex2f(0.33f, 0.30f);
    glEnd();
    glLineWidth(1.0f);
}

void drawRailing() {
    glColor3ub(255, 255, 255);
    glLineWidth(12);
    glBegin(GL_LINES);
    glVertex2f(0.37f, 0.36f); glVertex2f(0.52f, 0.37f);
    glVertex2f(0.37f, 0.31f); glVertex2f(0.52f, 0.31f);
    glEnd();

    for (int i = 0; i <= 6; i++) {
        glBegin(GL_LINES);
        glVertex2f(0.37f + (float)i * 0.03f, 0.36f);
        glVertex2f(0.37f + (float)i * 0.03f, 0.31f);
        glEnd();
    }

    glBegin(GL_LINES);
    glVertex2f(0.66f, 0.36f); glVertex2f(0.75f, 0.35f);
    glVertex2f(0.66f, 0.30f); glVertex2f(0.75f, 0.30f);
    glEnd();

    for (int i = 0; i <= 4; i++) {
        glBegin(GL_LINES);
        glVertex2f(0.66f + (float)i * 0.02f, 0.36f);
        glVertex2f(0.66f + (float)i * 0.02f, 0.30f);
        glEnd();
    }
    glLineWidth(1.0f);
}

void drawSheep() {
    glColor3ub(255, 255, 255);
    glBegin(GL_QUADS);
    glVertex2f(0.26f, 0.44f); glVertex2f(0.30f, 0.46f);
    glVertex2f(0.41f, 0.28f); glVertex2f(0.36f, 0.25f);
    glEnd();

    glColor3ub(107, 67, 39);
    circle(0.33f, 0.54f, 0.05f);
    circle(0.35f, 0.57f, 0.03f);
    circle(0.34f, 0.60f, 0.02f);
    circle(0.32f, 0.59f, 0.02f);
    circle(0.32f, 0.56f, 0.01f);

    glColor3ub(74, 44, 23);
    circle(0.33f, 0.57f, 0.01f);

    glColor3ub(255, 255, 255);
    circle(0.25f, 0.47f, 0.11f);

    glColor3ub(20, 20, 20);
    glLineWidth(7);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 40; i++) {
        float angle = (float)i * 2.0f * PI / 40.0f;
        glVertex2f(0.25f + 0.07f * cosf(angle), 0.47f + 0.11f * sinf(angle));
    }
    glEnd();
    glLineWidth(1.0f);

    circle(0.28f, 0.51f, 0.02f);
    glColor3ub(255, 255, 255);
    circle(0.28f, 0.52f, 0.01f);

    glColor3ub(20, 20, 20);
    glLineWidth(5);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.18f, 0.49f); glVertex2f(0.20f, 0.50f); glVertex2f(0.21f, 0.49f);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(0.19f, 0.45f); glVertex2f(0.21f, 0.43f); glVertex2f(0.23f, 0.45f);
    glEnd();
    glLineWidth(1.0f);
}

void drawShip() {
    glPushMatrix();
    glTranslatef(shipX, 0.10f, 0.0f);
    glScalef(0.62f, 0.62f, 1.0f);

    drawFlag();
    drawMast();
    drawStripedSail();
    drawSail();
    drawBones();
    drawSkull();
    drawStrawHat();
    drawHull();
    drawDeck();
    drawRailing();
    drawSheep();

    glPopMatrix();
}

void drawSky() {
    glColor3ub(135, 206, 235);
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 0.45f); glVertex2f(1.0f, 0.45f);
    glVertex2f(1.0f, 1.0f);  glVertex2f(0.0f, 1.0f);
    glEnd();
}

void drawSun() {
    glColor3ub(255, 210, 50);
    circle(0.82f, 0.86f, 0.07f);
}

void drawCloud(float x, float y) {
    glColor3ub(255, 255, 255);
    circle(x, y, 0.05f);
    circle(x + 0.06f, y + 0.02f, 0.06f);
    circle(x + 0.12f, y, 0.05f);
    glRectf(x - 0.01f, y - 0.04f, x + 0.13f, y + 0.02f);
}

void drawSea() {
    glColor3ub(35, 150, 210);
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 0.0f);  glVertex2f(1.0f, 0.0f);
    glVertex2f(1.0f, 0.55f); glVertex2f(0.0f, 0.55f);
    glEnd();

    glColor3ub(80, 190, 225);
    glLineWidth(4);
    for (float y = 0.08f; y < 0.55f; y += 0.09f) {
        glBegin(GL_LINE_STRIP);
        for (float x = 0.0f; x <= 1.0f; x += 0.01f) {
            float wave = 0.012f * sinf(18.0f * x + waterMove * 3.0f + y * 20.0f);
            glVertex2f(x, y + wave);
        }
        glEnd();
    }

    glColor3ub(220, 245, 250);
    glLineWidth(3);
    for (float y = 0.12f; y < 0.55f; y += 0.13f) {
        glBegin(GL_LINE_STRIP);
        for (float x = 0.0f; x <= 1.0f; x += 0.015f) {
            float wave = 0.008f * sinf(22.0f * x + waterMove * 4.0f);
            if (fmodf(x + waterMove * 0.02f, 0.18f) < 0.09f)
                glVertex2f(x, y + wave);
        }
        glEnd();
    }
    glLineWidth(1.0f);
}

void drawIsland(float x, float y, float size) {
    glColor3ub(238, 205, 120);
    circle(x, y, size);
    glColor3ub(80, 150, 60);
    circle(x, y + size * 0.12f, size * 0.82f);
}

void drawTree(float x, float y, float size) {
    glColor3ub(120, 70, 30);
    glBegin(GL_QUADS);
    glVertex2f(x - 0.018f * size, y);
    glVertex2f(x + 0.018f * size, y);
    glVertex2f(x + 0.035f * size, y + 0.30f * size);
    glVertex2f(x + 0.005f * size, y + 0.32f * size);
    glEnd();

    glColor3ub(30, 130, 40);
    glBegin(GL_TRIANGLES);
    glVertex2f(x + 0.02f * size, y + 0.30f * size);
    glVertex2f(x - 0.25f * size, y + 0.42f * size);
    glVertex2f(x - 0.04f * size, y + 0.27f * size);

    glVertex2f(x + 0.02f * size, y + 0.30f * size);
    glVertex2f(x + 0.28f * size, y + 0.42f * size);
    glVertex2f(x + 0.07f * size, y + 0.27f * size);

    glVertex2f(x + 0.02f * size, y + 0.30f * size);
    glVertex2f(x - 0.13f * size, y + 0.55f * size);
    glVertex2f(x, y + 0.34f * size);

    glVertex2f(x + 0.02f * size, y + 0.30f * size);
    glVertex2f(x + 0.18f * size, y + 0.55f * size);
    glVertex2f(x + 0.04f * size, y + 0.34f * size);

    glVertex2f(x + 0.02f * size, y + 0.30f * size);
    glVertex2f(x + 0.04f * size, y + 0.58f * size);
    glVertex2f(x + 0.06f * size, y + 0.34f * size);
    glEnd();

    glColor3ub(90, 50, 20);
    circle(x - 0.02f * size, y + 0.30f * size, 0.018f * size);
    circle(x + 0.04f * size, y + 0.30f * size, 0.018f * size);
}

void drawIsland() {
    drawIsland(0.16f, 0.13f, 0.40f);
    drawTree(-0.16f, 0.21f, 0.80f);
    drawTree(-0.08f, 0.23f, 1.00f);
    drawTree(0.00f, 0.20f, 0.75f);
}

void drawTreasureClosed() {
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
    glVertex3f(-0.61f, 0.35f, 0.0f); glVertex3f(-0.28f, 0.35f, 0.0f);
    glVertex3f(-0.63f, 0.29f, 0.0f); glVertex3f(-0.26f, 0.29f, 0.0f);
    glVertex3f(-0.64f, 0.21f, 0.0f); glVertex3f(-0.25f, 0.21f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.65f, 0.0f);
    glVertex3f(-0.59f, 0.4f, 0.0f);  glVertex3f(-0.64f, 0.18f, 0.0f);
    glVertex3f(-0.74f, 0.18f, 0.0f); glVertex3f(-0.67f, 0.4f, 0.0f);

    glVertex3f(-0.3f, 0.4f, 0.0f);   glVertex3f(-0.25f, 0.18f, 0.0f);
    glVertex3f(-0.15f, 0.18f, 0.0f); glVertex3f(-0.22f, 0.4f, 0.0f);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-0.75f, 0.18f, 0.0f); glVertex3f(-0.14f, 0.18f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.65f, 0.0f);
    glVertex3f(-0.75f, 0.18f, 0.0f); glVertex3f(-0.75f, 0.09f, 0.0f);
    glVertex3f(-0.14f, 0.09f, 0.0f); glVertex3f(-0.14f, 0.18f, 0.0f);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-0.75f, 0.18f, 0.0f); glVertex3f(-0.75f, 0.09f, 0.0f);
    glVertex3f(-0.14f, 0.09f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.65f, 0.0f);
    glVertex3f(-0.75f, 0.09f, 0.0f); glVertex3f(-0.75f, 0.05f, 0.0f);
    glVertex3f(-0.14f, 0.05f, 0.0f); glVertex3f(-0.14f, 0.09f, 0.0f);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-0.75f, 0.09f, 0.0f); glVertex3f(-0.75f, 0.05f, 0.0f);
    glVertex3f(-0.14f, 0.05f, 0.0f); glVertex3f(-0.14f, 0.09f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.65f, 0.0f);
    glVertex3f(-0.71f, 0.05f, 0.0f);  glVertex3f(-0.68f, -0.31f, 0.0f);
    glVertex3f(-0.22f, -0.31f, 0.0f); glVertex3f(-0.18f, 0.05f, 0.0f);

    glColor3f(0.55f, 0.32f, 0.12f);
    glVertex3f(-0.66f, 0.02f, 0.0f);  glVertex3f(-0.63f, -0.29f, 0.0f);
    glVertex3f(-0.27f, -0.29f, 0.0f); glVertex3f(-0.24f, 0.02f, 0.0f);

    glColor3f(1.0f, 0.65f, 0.0f);
    glVertex3f(-0.49f, 0.05f, 0.0f);  glVertex3f(-0.49f, -0.04f, 0.0f);
    glVertex3f(-0.39f, -0.04f, 0.0f); glVertex3f(-0.39f, 0.05f, 0.0f);
    glEnd();

    glLineWidth(3.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    glVertex3f(-0.49f, 0.05f, 0.0f);  glVertex3f(-0.49f, -0.04f, 0.0f);
    glVertex3f(-0.39f, -0.04f, 0.0f); glVertex3f(-0.39f, 0.05f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.55f, 0.32f, 0.12f);
    glVertex3f(-0.445f, 0.01f, 0.0f); glVertex3f(-0.445f, -0.03f, 0.0f);
    glVertex3f(-0.435f, -0.03f, 0.0f);glVertex3f(-0.435f, 0.01f, 0.0f);
    glEnd();

    glPushMatrix();
    glTranslatef(-0.44f, 0.02f, 0.0f);
    glScalef(0.03f, 0.03f, 1.0f);
    glColor3f(0.45f, 0.22f, 0.10f);
    DrawCircle();
    glPopMatrix();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-0.65f, -0.06f, 0.0f); glVertex3f(-0.25f, -0.06f, 0.0f);
    glVertex3f(-0.64f, -0.15f, 0.0f); glVertex3f(-0.26f, -0.15f, 0.0f);
    glVertex3f(-0.63f, -0.23f, 0.0f); glVertex3f(-0.27f, -0.23f, 0.0f);
    glEnd();
    glLineWidth(1.0f);
}

void drawTreasure() {
    glPushMatrix();
    glTranslatef(0.2625f, 0.2263f, 0.0f);
    glScalef(0.23f, 0.23f, 1.0f);
    drawTreasureClosed();
    glPopMatrix();
}

// ============================================================
// SCENE 2 & 3: LUFFY & TREASURE CHEST RENDERING
// ============================================================

void drawBeachBackground(void) {
    glBegin(GL_QUADS);
    glColor3f(0.40f, 0.72f, 0.95f); glVertex2f(-2.5f,  1.2f); glVertex2f( 2.5f,  1.2f);
    glColor3f(0.68f, 0.88f, 0.98f); glVertex2f( 2.5f,  0.15f);glVertex2f(-2.5f,  0.15f);
    glEnd();

    glColor3f(1.0f, 0.88f, 0.35f);
    drawCircle(1.2f, 0.8f, 0.16f, 36);
    glColor4f(1.0f, 0.95f, 0.5f, 0.35f);
    drawCircle(1.2f, 0.8f, 0.22f, 36);

    glColor4f(1.0f, 1.0f, 1.0f, 0.92f);
    float c1X = -1.0f + fmodf(g_walkPhase * 0.04f, 4.0f);
    if (c1X > 2.0f) c1X -= 4.0f;
    drawCircle(c1X - 0.15f, 0.75f, 0.11f, 20);
    drawCircle(c1X,         0.80f, 0.14f, 20);
    drawCircle(c1X + 0.15f, 0.75f, 0.10f, 20);

    float c2X = 0.5f + fmodf(g_walkPhase * 0.025f, 4.0f);
    if (c2X > 2.0f) c2X -= 4.0f;
    drawCircle(c2X - 0.12f, 0.65f, 0.08f, 20);
    drawCircle(c2X,         0.68f, 0.11f, 20);
    drawCircle(c2X + 0.12f, 0.65f, 0.07f, 20);

    glBegin(GL_QUADS);
    glColor3f(0.08f, 0.45f, 0.75f); glVertex2f(-2.5f,  0.15f); glVertex2f( 2.5f,  0.15f);
    glColor3f(0.12f, 0.65f, 0.82f); glVertex2f( 2.5f, -0.25f); glVertex2f(-2.5f, -0.25f);
    glEnd();

    glColor4f(0.15f, 0.72f, 0.88f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(-2.5f, -0.25f); glVertex2f( 2.5f, -0.25f);
    for (float x = 2.5f; x >= -2.5f; x -= 0.1f) {
        float waveY = -0.38f + 0.035f * sinf(x * 5.0f + g_walkPhase * 2.0f);
        glVertex2f(x, waveY);
    }
    glEnd();

    glColor4f(0.96f, 0.98f, 1.0f, 0.95f);
    glBegin(GL_QUAD_STRIP);
    for (float x = -2.5f; x <= 2.5f; x += 0.08f) {
        float waveY = -0.38f + 0.035f * sinf(x * 5.0f + g_walkPhase * 2.0f);
        glVertex2f(x, waveY + 0.015f);
        glVertex2f(x, waveY - 0.015f);
    }
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.85f, 0.70f, 0.48f); glVertex2f(-2.5f, -0.38f); glVertex2f( 2.5f, -0.38f);
    glColor3f(0.96f, 0.84f, 0.58f); glVertex2f( 2.5f, -0.50f); glVertex2f(-2.5f, -0.50f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.96f, 0.84f, 0.58f); glVertex2f(-2.5f, -0.50f); glVertex2f( 2.5f, -0.50f);
    glColor3f(0.90f, 0.74f, 0.46f); glVertex2f( 2.5f, -1.20f); glVertex2f(-2.5f, -1.20f);
    glEnd();

    glColor3f(0.48f, 0.30f, 0.16f);
    glBegin(GL_QUAD_STRIP);
    for (float t = 0.0f; t <= 1.0f; t += 0.1f) {
        float px = 1.6f - 0.12f * sinf(t * PI * 0.5f);
        float py = -0.55f + t * 1.15f;
        float w  = 0.06f - 0.025f * t;
        glVertex2f(px - w, py);
        glVertex2f(px + w, py);
    }
    glEnd();

    float crownX = 1.48f, crownY = 0.60f;
    float frondAngles[6] = { 0.2f, 1.1f, 2.3f, 3.2f, 4.3f, 5.4f };
    for (int i = 0; i < 6; i++) {
        float ang = frondAngles[i] + 0.05f * sinf(g_walkPhase * 1.5f + (float)i);
        float tipX = crownX + cosf(ang) * 0.38f;
        float tipY = crownY + sinf(ang) * 0.24f - 0.06f;

        glColor3f(0.15f, 0.62f, 0.22f);
        glBegin(GL_TRIANGLES);
        glVertex2f(crownX, crownY); glVertex2f(tipX, tipY);
        glVertex2f((crownX + tipX) * 0.5f - 0.04f, (crownY + tipY) * 0.5f + 0.08f);
        glEnd();

        glColor3f(0.09f, 0.45f, 0.15f);
        glBegin(GL_TRIANGLES);
        glVertex2f(crownX, crownY); glVertex2f(tipX, tipY);
        glVertex2f((crownX + tipX) * 0.5f + 0.04f, (crownY + tipY) * 0.5f - 0.08f);
        glEnd();
    }
}

void drawTreasureChestSide(float cx, float cy) {
    glPushMatrix();
    glTranslatef(cx, cy, 0.0f);

    glColor4f(1.0f, 0.84f, 0.2f, 0.25f + 0.10f * sinf(g_walkPhase * 3.0f));
    drawCircle(0.0f, 0.06f, 0.22f, 32);

    glColor3f(0.42f, 0.22f, 0.08f);
    glBegin(GL_QUADS);
    glVertex2f(-0.14f, -0.08f); glVertex2f( 0.14f, -0.08f);
    glVertex2f( 0.14f,  0.08f); glVertex2f(-0.14f,  0.08f);
    glEnd();

    glColor3f(0.28f, 0.14f, 0.04f);
    drawLinePx(-0.14f, -0.03f, 0.14f, -0.03f, 1.5f);
    drawLinePx(-0.14f,  0.03f, 0.14f,  0.03f, 1.5f);

    glColor3f(0.48f, 0.26f, 0.10f);
    glBegin(GL_POLYGON);
    for (int deg = 0; deg <= 180; deg += 10) {
        float rad = (float)deg * PI / 180.0f;
        glVertex2f(0.14f * cosf(rad), 0.08f + 0.07f * sinf(rad));
    }
    glEnd();

    glColor3f(0.85f, 0.65f, 0.12f);
    glBegin(GL_QUADS);
    glVertex2f(-0.10f, -0.08f); glVertex2f(-0.07f, -0.08f);
    glVertex2f(-0.07f,  0.13f); glVertex2f(-0.10f,  0.13f);

    glVertex2f( 0.07f, -0.08f); glVertex2f( 0.10f, -0.08f);
    glVertex2f( 0.10f,  0.13f); glVertex2f( 0.07f,  0.13f);

    glVertex2f(-0.145f, 0.065f); glVertex2f(0.145f, 0.065f);
    glVertex2f( 0.145f, 0.085f); glVertex2f(-0.145f, 0.085f);
    glEnd();

    glColor3f(0.95f, 0.78f, 0.18f);
    drawCircle(0.0f, 0.05f, 0.035f, 16);
    glColor3f(0.10f, 0.05f, 0.0f);
    drawCircle(0.0f, 0.055f, 0.012f, 12);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.01f, 0.05f); glVertex2f( 0.01f, 0.05f); glVertex2f( 0.0f,  0.03f);
    glEnd();

    glPopMatrix();
}

void drawExclamationMark(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    float pulseScale = 1.0f + 0.12f * sinf(g_stateTimer * 12.0f);
    glScalef(pulseScale, pulseScale, 1.0f);

    glColor3f(1.0f, 0.85f, 0.10f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 12; i++) {
        float a = (float)i * (2.0f * PI / 12.0f);
        float r = (i % 2 == 0) ? 0.18f : 0.10f;
        glVertex2f(cosf(a) * r, sinf(a) * r);
    }
    glEnd();

    glColor3f(0.90f, 0.10f, 0.10f);
    glBegin(GL_QUADS);
    glVertex2f(-0.03f,  0.11f); glVertex2f( 0.03f,  0.11f);
    glVertex2f( 0.02f, -0.01f); glVertex2f(-0.02f, -0.01f);
    glEnd();

    drawCircle(0.0f, -0.06f, 0.03f, 16);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(-0.008f, 0.07f, 0.01f, 10);
    drawCircle(-0.008f, -0.055f, 0.008f, 10);

    glPopMatrix();
}

void drawTreasureChestOpen(float cx, float cy) {
    glPushMatrix();
    glTranslatef(cx, cy, 0.0f);

    glColor4f(1.0f, 0.88f, 0.25f, 0.22f);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 12; i++) {
        float a1 = (float)i * (2.0f * PI / 12.0f) + g_sparkleAngle;
        float a2 = a1 + 0.18f;
        glVertex2f(0.0f, 0.08f);
        glVertex2f(cosf(a1) * 0.95f, 0.08f + sinf(a1) * 0.95f);
        glVertex2f(cosf(a2) * 0.95f, 0.08f + sinf(a2) * 0.95f);
    }
    glEnd();

    glColor3f(0.38f, 0.18f, 0.06f);
    glBegin(GL_QUADS);
    glVertex2f(-0.22f, 0.12f); glVertex2f( 0.22f, 0.12f);
    glVertex2f( 0.18f, 0.28f); glVertex2f(-0.18f, 0.28f);
    glEnd();

    glColor3f(0.22f, 0.10f, 0.03f);
    glBegin(GL_QUADS);
    glVertex2f(-0.19f, 0.13f); glVertex2f( 0.19f, 0.13f);
    glVertex2f( 0.16f, 0.26f); glVertex2f(-0.16f, 0.26f);
    glEnd();

    glColor3f(0.45f, 0.23f, 0.08f);
    glBegin(GL_QUADS);
    glVertex2f(-0.22f, -0.15f); glVertex2f( 0.22f, -0.15f);
    glVertex2f( 0.22f,  0.10f); glVertex2f(-0.22f,  0.10f);
    glEnd();

    glColor3f(0.88f, 0.68f, 0.14f);
    glBegin(GL_QUADS);
    glVertex2f(-0.16f, -0.15f); glVertex2f(-0.12f, -0.15f);
    glVertex2f(-0.12f,  0.10f); glVertex2f(-0.16f,  0.10f);

    glVertex2f( 0.12f, -0.15f); glVertex2f( 0.16f, -0.15f);
    glVertex2f( 0.16f,  0.10f); glVertex2f( 0.12f,  0.10f);
    glEnd();

    glColor3f(1.0f, 0.84f, 0.0f);
    drawEllipse(0.0f, 0.10f, 0.18f, 0.06f, 24);

    for (int i = 0; i < 18; i++) {
        float coinX = -0.14f + (float)i * 0.016f + 0.005f * sinf((float)i * 1.7f);
        float coinY = 0.08f + 0.025f * sinf((float)i * 2.3f);
        glColor3f((i % 2 == 0) ? 1.0f : 0.90f, 0.82f, 0.10f);
        drawCircle(coinX, coinY, 0.022f, 12);
    }

    glColor3f(0.95f, 0.15f, 0.20f); drawCircle(-0.06f, 0.11f, 0.025f, 6);
    glColor3f(0.15f, 0.45f, 0.95f); drawCircle( 0.07f, 0.10f, 0.025f, 6);

    for (int k = 0; k < 4; k++) {
        float glintX = -0.10f + (float)k * 0.07f;
        float glintY = 0.10f + 0.03f * sinf(g_sparkleAngle + (float)k);
        float glintSize = 0.025f + 0.012f * sinf(g_sparkleAngle * 2.0f + (float)k);

        glColor4f(1.0f, 1.0f, 1.0f, 0.9f);
        glBegin(GL_TRIANGLES);
        glVertex2f(glintX - glintSize, glintY); glVertex2f(glintX + glintSize, glintY);
        glVertex2f(glintX, glintY + glintSize * 1.5f);

        glVertex2f(glintX - glintSize, glintY); glVertex2f(glintX + glintSize, glintY);
        glVertex2f(glintX, glintY - glintSize * 1.5f);
        glEnd();
    }

    glPopMatrix();
}

void renderLufi(void) {
    const float C_SKIN[3]        = { 0.99f, 0.77f, 0.57f };
    const float C_SKIN_SHADE[3]  = { 0.92f, 0.67f, 0.49f };
    const float C_VEST[3]        = { 0.83f, 0.16f, 0.14f };
    const float C_SHORTS[3]      = { 0.18f, 0.40f, 0.73f };
    const float C_HAT[3]         = { 0.99f, 0.80f, 0.32f };
    const float C_HAT_SHADE[3]   = { 0.90f, 0.66f, 0.20f };
    const float C_RIBBON[3]      = { 0.83f, 0.16f, 0.14f };
    const float C_HAIR[3]        = { 0.10f, 0.10f, 0.10f };
    const float C_CUFF[3]        = { 0.89f, 0.92f, 0.96f };
    const float C_SANDAL[3]      = { 0.44f, 0.23f, 0.10f };
    const float C_STRAP[3]       = { 0.08f, 0.08f, 0.08f };

    glPushMatrix();
    glTranslatef(-88.0f / 125.0f, 152.0f / 125.0f, 0.0f);
    glScalef(1.0f / 125.0f, -1.0f / 125.0f, 1.0f);

    float swing = (g_masterState == MSTATE_LUFFY_SPOT) ? 0.0f : sinf(g_walkPhase);

    float farArmAngRad = (90.0f - 40.0f * swing) * PI / 180.0f;
    float farFistX = 86.0f + cosf(farArmAngRad) * 50.0f;
    float farFistY = 122.0f + sinf(farArmAngRad) * 50.0f;

    glColor3fv(C_SKIN_SHADE);
    drawCapsule(86, 122, farFistX, farFistY, 6.0f);
    drawCircle(farFistX + cosf(farArmAngRad) * 2.0f, farFistY + sinf(farArmAngRad) * 2.0f, 9.0f, 18);

    float bHipX = 78.0f, bHipY = 170.0f;
    float fHipX = 86.0f, fHipY = 170.0f;

    float bLegAngDeg = 90.0f + 40.0f * swing;
    float fLegAngDeg = 90.0f - 40.0f * swing;

    float bLegRad = bLegAngDeg * PI / 180.0f;
    float fLegRad = fLegAngDeg * PI / 180.0f;

    float bKneeX = bHipX + cosf(bLegRad) * 34.0f, bKneeY = bHipY + sinf(bLegRad) * 34.0f;
    float bAnkleX = bKneeX + cosf(bLegRad) * 46.0f, bAnkleY = bKneeY + sinf(bLegRad) * 46.0f;

    float fKneeX = fHipX + cosf(fLegRad) * 34.0f, fKneeY = fHipY + sinf(fLegRad) * 34.0f;
    float fAnkleX = fKneeX + cosf(fLegRad) * 46.0f, fAnkleY = fKneeY + sinf(fLegRad) * 46.0f;

    glColor3fv(C_SKIN_SHADE); drawCapsule(bHipX, bHipY, bAnkleX, bAnkleY, 5.0f);
    glColor3fv(C_SKIN);       drawCapsule(fHipX, fHipY, fAnkleX, fAnkleY, 5.0f);

    float bSoleAngRad = (bLegAngDeg - 80.0f) * PI / 180.0f;
    float bsUx = cosf(bSoleAngRad), bsUy = sinf(bSoleAngRad);
    float bsNx = bsUy, bsNy = -bsUx;
    float bSoleHeelX = bAnkleX - 4.0f * bsUx - 4.0f * bsNx;
    float bSoleHeelY = bAnkleY - 4.0f * bsUy - 4.0f * bsNx;
    float bSoleToeX  = bAnkleX + 24.0f * bsUx - 4.0f * bsNx;
    float bSoleToeY  = bAnkleY + 24.0f * bsUy - 4.0f * bsNx;
    drawFlatFootAndSandal(bSoleHeelX, bSoleHeelY, bSoleToeX, bSoleToeY, 4.5f, bAnkleX, bAnkleY, C_SKIN_SHADE, C_SANDAL, C_STRAP, false);

    float fSoleAngRad = (fLegAngDeg - 80.0f) * PI / 180.0f;
    float fsUx = cosf(fSoleAngRad), fsUy = sinf(fSoleAngRad);
    float fsNx = fsUy, fsNy = -fsUx;
    float fSoleHeelX = fAnkleX - 4.0f * fsUx - 4.0f * fsNx;
    float fSoleHeelY = fAnkleY - 4.0f * fsUy - 4.0f * fsNx;
    float fSoleToeX  = fAnkleX + 24.0f * fsUx - 4.0f * fsNx;
    float fSoleToeY  = fAnkleY + 24.0f * fsUy - 4.0f * fsNx;
    drawFlatFootAndSandal(fSoleHeelX, fSoleHeelY, fSoleToeX, fSoleToeY, 4.5f, fAnkleX, fAnkleY, C_SKIN, C_SANDAL, C_STRAP, true);

    glColor3fv(C_SHORTS);
    drawCapsule(bHipX, bHipY, bKneeX, bKneeY, 11.0f);
    drawCapsule(fHipX, fHipY, fKneeX, fKneeY, 11.0f);
    drawQuadPx(68, 158, 96, 158, 102, 176, 64, 176);

    glColor3fv(C_CUFF);
    float bDirX = bKneeX - bHipX, bDirY = bKneeY - bHipY;
    float bLen = sqrtf(bDirX * bDirX + bDirY * bDirY);
    float bCuffX = bKneeX + (bDirX / bLen) * 5.5f, bCuffY = bKneeY + (bDirY / bLen) * 5.5f;
    drawPerpendicularCuff(bCuffX, bCuffY, bDirX, bDirY, 6.5f, 14.0f);

    float fDirX = fKneeX - fHipX, fDirY = fKneeY - fHipY;
    float fLen = sqrtf(fDirX * fDirX + fDirY * fDirY);
    float fCuffX = fKneeX + (fDirX / fLen) * 5.5f, fCuffY = fKneeY + (fDirY / fLen) * 5.5f;
    drawPerpendicularCuff(fCuffX, fCuffY, fDirX, fDirY, 6.5f, 14.0f);

    glColor3fv(C_SKIN);
    drawCapsule(84, 94, 84, 110, 6.0f);

    glColor3fv(C_VEST);
    drawQuadPx(74, 108, 94, 108, 98, 162, 66, 162);
    drawEllipse(74, 110, 4.0f, 4.0f, 16);
    drawEllipse(92, 110, 4.0f, 4.0f, 16);

    glColor3fv(C_HAIR);
    drawEllipse(84, 80, 22.0f, 20.0f, 24);
    drawTrianglePx(70, 84, 44, 88, 70, 92);
    drawTrianglePx(70, 90, 48, 98, 74, 98);
    drawTrianglePx(72, 96, 58, 104, 78, 102);

    glColor3fv(C_SKIN);
    glBegin(GL_POLYGON);
    glVertex2f(80.0f,  68.0f); glVertex2f(110.0f, 68.0f);
    glVertex2f(118.0f, 74.0f); glVertex2f(124.0f, 78.0f);
    glVertex2f(118.0f, 82.0f); glVertex2f(116.0f, 88.0f);
    glVertex2f(102.0f, 98.0f); glVertex2f(82.0f,  98.0f);
    glVertex2f(78.0f,  80.0f);
    glEnd();

    drawEllipse(97, 81, 17.0f, 17.0f, 24);

    glColor3fv(C_HAIR);
    drawTrianglePx(88, 66, 98, 76, 102, 66);
    drawTrianglePx(100, 66, 110, 74, 112, 66);

    glColor3fv(C_SKIN);
    drawEllipse(88, 79, 6.0f, 7.0f, 16);
    glColor3fv(C_SKIN_SHADE);
    drawEllipse(88, 79, 3.0f, 4.0f, 12);

    glColor3fv(C_HAIR);
    drawEllipse(111, 76, 3.0f, 4.0f, 16);
    drawLinePx(106, 68, 114, 69, 2.0f);

    if (g_masterState == MSTATE_LUFFY_SPOT) {
        glColor3f(0.6f, 0.08f, 0.08f);
        drawEllipse(114, 85, 3.5f, 4.5f, 16);
    } else {
        drawLinePx(110, 84, 114, 86, 2.5f);
        drawLinePx(114, 86, 117, 85, 2.5f);
    }

    float hatBasePxX = 86.0f;
    float hatBasePxY = 66.0f;
    float hatAngleRad = -14.0f * PI / 180.0f;

    float ux = cosf(hatAngleRad);
    float uy = sinf(hatAngleRad);
    float nx = -uy;
    float ny =  ux;

    float basePxX = hatBasePxX;
    float basePxY = hatBasePxY;

    glColor3fv(C_HAT);
    float brimRx = 46.0f;
    float brimRy = 9.0f;
    glBegin(GL_POLYGON);
    for (int deg = 0; deg < 360; deg += 10) {
        float rad = (float)deg * PI / 180.0f;
        float lx = brimRx * cosf(rad);
        float ly = brimRy * sinf(rad);
        glVertex2f(basePxX + lx * ux - ly * nx, basePxY + lx * uy + ly * ny);
    }
    glEnd();

    glColor3fv(C_HAT_SHADE);
    glBegin(GL_POLYGON);
    for (int deg = 0; deg <= 180; deg += 10) {
        float rad = (float)deg * PI / 180.0f;
        float lx = brimRx * cosf(rad);
        float ly = (brimRy * 0.5f) * sinf(rad);
        glVertex2f(basePxX + lx * ux - ly * nx, basePxY + lx * uy + ly * ny);
    }
    glEnd();

    glColor3fv(C_HAT);
    float domeCenterPxX = basePxX - ux * 2.0f;
    float domeCenterPxY = basePxY - uy * 2.0f;

    float rDomeW = 26.0f;
    float rDomeH = 25.0f;
    glBegin(GL_POLYGON);
    for (int deg = 0; deg <= 180; deg += 5) {
        float rad = (float)deg * PI / 180.0f;
        float lx = -rDomeW * cosf(rad);
        float ly =  rDomeH * sinf(rad);
        glVertex2f(domeCenterPxX + lx * ux + ly * nx, domeCenterPxY + lx * uy - ly * ny);
    }
    glEnd();

    glColor3fv(C_RIBBON);
    float ribbonW = 25.5f;
    float ribbonH = 7.0f;
    glBegin(GL_POLYGON);
    for (int deg = 0; deg <= 180; deg += 10) {
        float rad = (float)deg * PI / 180.0f;
        float lx = -ribbonW * cosf(rad);
        float ly =  ribbonH * sinf(rad);
        glVertex2f(domeCenterPxX + lx * ux + ly * nx, domeCenterPxY + lx * uy - ly * ny);
    }
    glEnd();

    float nearArmAngRad = (90.0f + 45.0f * swing) * PI / 180.0f;
    float nearFistX = 80.0f + cosf(nearArmAngRad) * 50.0f;
    float nearFistY = 115.0f + sinf(nearArmAngRad) * 50.0f;

    glColor3fv(C_SKIN);
    drawEllipse(80, 115, 7.0f, 7.0f, 16);
    drawCapsule(80, 115, nearFistX, nearFistY, 6.0f);
    drawCircle(nearFistX + cosf(nearArmAngRad) * 2.0f, nearFistY + sinf(nearArmAngRad) * 2.0f, 9.0f, 18);

    glPopMatrix();
}

void renderLufiRearView(void) {
    const float C_SKIN[3]        = { 0.99f, 0.77f, 0.57f };
    const float C_SKIN_SHADE[3]  = { 0.92f, 0.67f, 0.49f };
    const float C_VEST[3]        = { 0.83f, 0.16f, 0.14f };
    const float C_SHORTS[3]      = { 0.18f, 0.40f, 0.73f };
    const float C_HAT[3]         = { 0.99f, 0.80f, 0.32f };
    const float C_HAT_SHADE[3]   = { 0.90f, 0.66f, 0.20f };
    const float C_RIBBON[3]      = { 0.83f, 0.16f, 0.14f };
    const float C_HAIR[3]        = { 0.10f, 0.10f, 0.10f };
    const float C_CUFF[3]        = { 0.89f, 0.92f, 0.96f };
    const float C_SANDAL[3]      = { 0.44f, 0.23f, 0.10f };
    const float C_STRAP[3]       = { 0.08f, 0.08f, 0.08f };

    glPushMatrix();
    glTranslatef(-88.0f / 125.0f, 152.0f / 125.0f, 0.0f);
    glScalef(1.0f / 125.0f, -1.0f / 125.0f, 1.0f);

    float breatheY = sinf(g_walkPhase * 0.6f) * 1.2f;

    glColor3fv(C_SKIN_SHADE);
    drawCapsule(62, 114 + breatheY, 54, 156 + breatheY, 6.0f);
    drawCapsule(106, 114 + breatheY, 114, 156 + breatheY, 6.0f);
    drawCircle(54, 158 + breatheY, 8.0f, 16);
    drawCircle(114, 158 + breatheY, 8.0f, 16);

    glColor3fv(C_SKIN_SHADE);
    drawCapsule(72, 172, 70, 226, 6.5f);
    drawCapsule(96, 172, 98, 226, 6.5f);

    glColor3fv(C_SANDAL);
    drawQuadPx(62, 226, 78, 226, 78, 234, 62, 234);
    drawQuadPx(90, 226, 106, 226, 106, 234, 90, 234);

    glColor3fv(C_STRAP);
    drawLinePx(62, 222, 78, 222, 4.0f);
    drawLinePx(90, 222, 106, 222, 4.0f);

    glColor3fv(C_SHORTS);
    drawQuadPx(64, 150 + breatheY, 104, 150 + breatheY, 108, 178, 60, 178);

    glColor3fv(C_CUFF);
    drawQuadPx(58, 176, 80, 176, 80, 186, 58, 186);
    drawQuadPx(88, 176, 110, 176, 110, 186, 88, 186);

    glColor3fv(C_SKIN);
    drawCapsule(84, 88 + breatheY, 84, 108 + breatheY, 7.5f);
    drawEllipse(68, 112 + breatheY, 6.0f, 6.0f, 16);
    drawEllipse(100, 112 + breatheY, 6.0f, 6.0f, 16);

    glColor3fv(C_VEST);
    drawQuadPx(68, 108 + breatheY, 100, 108 + breatheY, 104, 152 + breatheY, 64, 152 + breatheY);

    glColor3fv(C_HAIR);
    drawEllipse(84, 76 + breatheY, 26.0f, 18.0f, 24);
    drawTrianglePx(62, 72 + breatheY, 42, 80 + breatheY, 62, 88 + breatheY);
    drawTrianglePx(60, 84 + breatheY, 44, 94 + breatheY, 64, 96 + breatheY);

    drawTrianglePx(106, 72 + breatheY, 126, 80 + breatheY, 106, 88 + breatheY);
    drawTrianglePx(108, 84 + breatheY, 124, 94 + breatheY, 104, 96 + breatheY);

    glColor3fv(C_HAT);
    drawEllipse(84, 66 + breatheY, 48.0f, 14.0f, 36);

    glColor3fv(C_HAT_SHADE);
    drawEllipse(84, 70 + breatheY, 48.0f, 7.0f, 36);

    glColor3fv(C_HAT);
    drawCircle(84, 52 + breatheY, 26.0f, 36);

    glColor3fv(C_RIBBON);
    drawEllipse(84, 62 + breatheY, 26.5f, 6.5f, 36);

    glColor3f(0.92f, 0.76f, 0.28f);
    drawLinePx(78, 74 + breatheY, 74, 116 + breatheY, 3.0f);
    drawLinePx(90, 74 + breatheY, 94, 116 + breatheY, 3.0f);

    glPopMatrix();
}

void drawRearViewScene(void) {
    glBegin(GL_QUADS);
    glColor3f(0.35f, 0.68f, 0.94f); glVertex2f(-2.5f,  1.2f); glVertex2f( 2.5f,  1.2f);
    glColor3f(0.65f, 0.88f, 0.98f); glVertex2f( 2.5f,  0.0f); glVertex2f(-2.5f,  0.0f);
    glEnd();

    glColor3f(1.0f, 0.90f, 0.40f);
    drawCircle(0.0f, 0.10f, 0.20f, 36);
    glColor4f(1.0f, 0.96f, 0.5f, 0.35f);
    drawCircle(0.0f, 0.10f, 0.30f, 36);

    glColor4f(1.0f, 1.0f, 1.0f, 0.92f);
    drawCircle(-0.8f, 0.70f, 0.12f, 20);
    drawCircle(-0.65f, 0.74f, 0.15f, 20);
    drawCircle(-0.50f, 0.70f, 0.11f, 20);

    drawCircle(0.6f, 0.65f, 0.10f, 20);
    drawCircle(0.75f, 0.68f, 0.13f, 20);

    glBegin(GL_QUADS);
    glColor3f(0.08f, 0.45f, 0.75f); glVertex2f(-2.5f,  0.0f); glVertex2f( 2.5f,  0.0f);
    glColor3f(0.12f, 0.65f, 0.82f); glVertex2f( 2.5f, -0.22f); glVertex2f(-2.5f, -0.22f);
    glEnd();

    glColor4f(0.15f, 0.72f, 0.88f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(-2.5f, -0.22f); glVertex2f( 2.5f, -0.22f);
    for (float x = 2.5f; x >= -2.5f; x -= 0.1f) {
        float waveY = -0.32f + 0.025f * sinf(x * 6.0f + g_walkPhase * 2.0f);
        glVertex2f(x, waveY);
    }
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.85f, 0.70f, 0.48f); glVertex2f(-2.5f, -0.32f); glVertex2f( 2.5f, -0.32f);
    glColor3f(0.96f, 0.84f, 0.58f); glVertex2f( 2.5f, -1.20f); glVertex2f(-2.5f, -1.20f);
    glEnd();

    glColor3f(0.48f, 0.30f, 0.16f);
    glBegin(GL_QUADS);
    glVertex2f(-2.1f, -0.5f); glVertex2f(-1.95f, -0.5f);
    glVertex2f(-1.8f,  0.8f); glVertex2f(-1.92f,  0.8f);

    glVertex2f(1.95f, -0.5f); glVertex2f(2.1f, -0.5f);
    glVertex2f(1.92f,  0.8f); glVertex2f(1.8f,  0.8f);
    glEnd();

    // 2. OPEN GLOWING TREASURE CHEST IN CENTER GROUND (Elevated for full visibility)
    drawTreasureChestOpen(0.0f, 0.02f);

    // 3. LUFFY RENDERED FROM BEHIND IN LOWER FOREGROUND (Slightly smaller scale)
    glPushMatrix();
    glTranslatef(0.0f, -0.68f, 0.0f);
    glScalef(0.75f, 0.75f, 1.0f);
    renderLufiRearView();
    glPopMatrix();
}


// ============================================================
// BIRTHDAY SCENE HELPER FUNCTIONS (HAPPY, BIRTHDAY, MAYURESH)
// ============================================================
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

// ============================================================
// BALLOON PRIMITIVE
// ============================================================
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

// ============================================================
// MAYURESH PORTRAIT DRAWING (GL_LINES)
// ============================================================
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

// ============================================================
// BIRTHDAY SCENE DISPLAY & RESET ROUTINES
// ============================================================
void displayBirthday(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

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
}

void resetBirthday(void)
{
	happyX = -2.5f;
	birthdayX = 2.5f;
	MayureshY = -2.0f;
	BalloonY = -2.0f;
	HappyAlpha = 1.0f;
	BirthdayAlpha = 1.0f;
	MayureshAlpha = 1.0f;
	MayureshDrawingAlpha = 0.005f;
	bShowMayureshDrawing = FALSE;
	g_birthdayHoldTimer = 0.0f;
}

// ============================================================
// 2D LETTER & TEXT DRAWING ENGINE (GROUP MEMBERS & CREDITS)
// ============================================================
void graphCoordinate(float xPoint, float yPoint)
{
	float graphXPoint = (((xPoint / X_MAX) * 2.0f) - 1.0f);
	float graphYPoint = (1.0f - ((yPoint / Y_MAX) * 2.0f));
	glVertex3f(graphXPoint, graphYPoint, 0.0f);
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
void setLetterColor(float r, float g, float b)
{
	bodyLightColorArr[0] = r;
	bodyLightColorArr[1] = g;
	bodyLightColorArr[2] = b;

	shadowDarkColorArr[0] = r * 0.45f;
	shadowDarkColorArr[1] = g * 0.45f;
	shadowDarkColorArr[2] = b * 0.45f;
}

// ============================================================
// GROUP MEMBERS DISPLAY FUNCTION
// ============================================================
void displayGroupMembers(void) 
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(-0.3f, 0.3f, 0.0f);
	glScalef(0.7f, 0.7f, 1.0f);

	// ----------------------------- GROUP MEMBERS -----------------------------
	setLetterColor(1.0f, 0.84f, 0.0f);
	float titleY1 = 0.5f;
	drawG(8.9f, titleY1); drawR(10.7f, titleY1); drawO(12.5f, titleY1); drawU(14.3f, titleY1); drawP(16.1f, titleY1);
	drawM(18.9f, titleY1); drawE(21.9f, titleY1); drawM(23.7f, titleY1); drawB(26.7f, titleY1); drawE(28.5f, titleY1); drawR(30.3f, titleY1); drawS(32.1f, titleY1);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5f, 0.5f, 0.0f);
	glScalef(0.5f, 0.5f, 1.0f);

	// ----------------------------- ROW 1 -----------------------------
	// ABHILASH BARI
	setLetterColor(0.2f, 1.0f, 0.2f);
	drawA(1.0f, 4.0f); drawB(2.8f, 4.0f); drawH(4.6f, 4.0f); drawI(6.4f, 4.0f); drawL(7.6f, 4.0f); drawA(9.4f, 4.0f); drawS(11.2f, 4.0f); drawH(13.0f, 4.0f);
	drawB(15.8f, 4.0f); drawA(17.6f, 4.0f); drawR(19.4f, 4.0f); drawI(21.2f, 4.0f);

	// ROHAN LAMBE
	setLetterColor(1.0f, 0.5f, 0.0f);
	drawR(30.0f, 4.0f); drawO(31.8f, 4.0f); drawH(33.6f, 4.0f); drawA(35.4f, 4.0f); drawN(37.2f, 4.0f);
	drawL(40.0f, 4.0f); drawA(41.8f, 4.0f); drawM(43.6f, 4.0f); drawB(46.6f, 4.0f); drawE(48.4f, 4.0f);

	// ----------------------------- ROW 2 -----------------------------
	// SAEED SHAIKH
	setLetterColor(1.0f, 0.2f, 0.8f);
	drawS(1.0f, 7.0f); drawA(2.8f, 7.0f); drawE(4.6f, 7.0f); drawE(6.4f, 7.0f); drawD(8.2f, 7.0f);
	drawS(11.0f, 7.0f); drawH(12.8f, 7.0f); drawA(14.6f, 7.0f); drawI(16.4f, 7.0f); drawK(17.6f, 7.0f); drawH(19.4f, 7.0f);

	// SAURABH MANE
	setLetterColor(1.0f, 0.1f, 0.1f);
	drawS(30.0f, 7.0f); drawA(31.8f, 7.0f); drawU(33.6f, 7.0f); drawR(35.4f, 7.0f); drawA(37.2f, 7.0f); drawB(39.0f, 7.0f); drawH(40.8f, 7.0f);
	drawM(43.6f, 7.0f); drawA(46.6f, 7.0f); drawN(48.4f, 7.0f); drawE(50.6f, 7.0f);

	// ----------------------------- ROW 3 -----------------------------
	// SARVESH BHOSALE
	setLetterColor(0.7f, 0.3f, 1.0f);
	drawS(1.0f, 10.0f); drawA(2.8f, 10.0f); drawR(4.6f, 10.0f); drawV(6.4f, 10.0f); drawE(8.2f, 10.0f); drawS(10.0f, 10.0f); drawH(11.8f, 10.0f);
	drawB(14.6f, 10.0f); drawH(16.4f, 10.0f); drawO(18.2f, 10.0f); drawS(20.0f, 10.0f); drawA(21.8f, 10.0f); drawL(23.6f, 10.0f); drawE(25.4f, 10.0f);

	// SHITAL SHIROLE
	setLetterColor(0.3f, 0.75f, 1.0f);
	drawS(30.0f, 10.0f); drawH(31.8f, 10.0f); drawI(33.6f, 10.0f); drawT(34.8f, 10.0f); drawA(36.6f, 10.0f); drawL(38.4f, 10.0f);
	drawS(41.2f, 10.0f); drawH(43.0f, 10.0f); drawI(44.8f, 10.0f); drawR(46.0f, 10.0f); drawO(47.8f, 10.0f); drawL(49.6f, 10.0f); drawE(51.4f, 10.0f);

	// ----------------------------- ROW 4 -----------------------------
	// ANIKET KEWAT
	setLetterColor(0.95f, 0.95f, 0.1f);
	drawA(1.0f, 13.0f); drawN(2.8f, 13.0f); drawI(5.0f, 13.0f); drawK(6.2f, 13.0f); drawE(8.0f, 13.0f); drawT(9.8f, 13.0f);
	drawK(12.6f, 13.0f); drawE(14.4f, 13.0f); drawW(16.2f, 13.0f); drawA(19.2f, 13.0f); drawT(21.0f, 13.0f);

	// SNEHA BIDVE
	setLetterColor(1.0f, 0.4f, 0.6f);
	drawS(30.0f, 13.0f); drawN(31.8f, 13.0f); drawE(34.0f, 13.0f); drawH(35.8f, 13.0f); drawA(37.6f, 13.0f);
	drawB(40.4f, 13.0f); drawI(42.2f, 13.0f); drawD(43.4f, 13.0f); drawV(45.2f, 13.0f); drawE(47.0f, 13.0f);

	// ----------------------------- ROW 5 -----------------------------
	// PRANAV PATIL
	setLetterColor(0.40f, 0.70f, 0.95f);
	drawP(19.9f, 16.0f); drawR(21.7f, 16.0f); drawA(23.5f, 16.0f); drawN(25.3f, 16.0f); drawA(27.1f, 16.0f); drawV(28.9f, 16.0f);
	drawP(31.7f, 16.0f); drawA(33.5f, 16.0f); drawT(35.3f, 16.0f); drawI(37.1f, 16.0f); drawL(38.3f, 16.0f);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.3f, 0.3f, 0.0f);
	glScalef(0.7f, 0.7f, 1.0f);

	// ----------------------------- GROUP LEADER -----------------------------
	setLetterColor(1.0f, 0.84f, 0.0f);
	float titleY2 = 13.5f;
	drawG(11.0f, titleY2); drawR(12.8f, titleY2); drawO(14.6f, titleY2); drawU(16.4f, titleY2); drawP(18.2f, titleY2);
	drawL(21.0f, titleY2); drawE(22.8f, titleY2); drawA(24.6f, titleY2); drawD(26.4f, titleY2); drawE(28.2f, titleY2); drawR(30.0f, titleY2);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5f, 0.5f, 0.0f);
	glScalef(0.5f, 0.5f, 1.0f);

	// MAYURESH DESHPANDE
	setLetterColor(0.0f, 1.0f, 1.0f);
	drawM(13.6f, 22.5f); drawA(16.6f, 22.5f); drawY(18.4f, 22.5f); drawU(20.2f, 22.5f); drawR(22.0f, 22.5f); drawE(23.8f, 22.5f); drawS(25.6f, 22.5f); drawH(27.4f, 22.5f);
	drawD(30.2f, 22.5f); drawE(32.0f, 22.5f); drawS(33.8f, 22.5f); drawH(35.6f, 22.5f); drawP(37.4f, 22.5f); drawA(39.2f, 22.5f); drawN(41.0f, 22.5f); drawD(42.8f, 22.5f); drawE(44.6f, 22.5f);

	glPopMatrix();

}

// ============================================================
// CREDIT SCREEN DISPLAY FUNCTION
// ============================================================
void displayCreditScreen(void) 
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
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

}

// ============================================================
// MASTER DISPLAY CALLBACK
// ============================================================
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    if (g_masterState == MSTATE_SHEEP_TRANSIT ||
        g_masterState == MSTATE_SHEEP_SAIL ||
        g_masterState == MSTATE_SHEEP_DOCK_PAUSE ||
        g_masterState == MSTATE_FADE_TO_LUFFY_WALK)
    {
        // RENDER SCENE 1: SHEEP ISLAND & GOING MERRY SAILING (2D ORTHO)
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0f, 1.0f, 0.0f, 1.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        drawSky();
        drawSun();
        drawCloud(0.18f, 0.82f);
        drawCloud(0.45f, 0.90f);
        drawSea();

        if (g_masterState != MSTATE_SHEEP_TRANSIT) {
            drawIsland();
            drawTreasure();
        }

        drawShip();
    }
    else if (g_masterState == MSTATE_LUFFY_WALK ||
             g_masterState == MSTATE_LUFFY_SPOT ||
             g_masterState == MSTATE_FADE_TO_REAR)
    {
        // RENDER SCENE 2: LUFFY WALKING ON BEACH & SPOTTING CHEST (3D PERSPECTIVE)
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, (GLfloat)g_winWidth / (GLfloat)g_winHeight, 0.1f, 100.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        float aspect = (float)g_winWidth / (float)g_winHeight;
        float baseZ = -2.42f;
        float cameraZ = (aspect < 1.0f) ? (baseZ / aspect) : baseZ;
        glTranslatef(0.0f, 0.0f, cameraZ);

        drawBeachBackground();
        drawTreasureChestSide(0.4f, -0.42f);

        float bobY = (g_masterState == MSTATE_LUFFY_SPOT) ? 0.0f : -fabsf(sinf(g_walkPhase)) * 0.025f;

        glPushMatrix();
        glTranslatef(g_translateX, bobY, 0.0f);

        renderLufi();

        if (g_masterState == MSTATE_LUFFY_SPOT) {
            drawExclamationMark(0.12f, 0.70f);
        }

        glPopMatrix();
    }
    else if (g_masterState == MSTATE_REAR_VIEW ||
             g_masterState == MSTATE_FADE_TO_BIRTHDAY)
    {
        // RENDER SCENE 3: REAR VIEW LUFFY WATCHING OPEN GLOWING CHEST (3D PERSPECTIVE)
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, (GLfloat)g_winWidth / (GLfloat)g_winHeight, 0.1f, 100.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        float aspect = (float)g_winWidth / (float)g_winHeight;
        float zoomProgress = g_stateTimer / 5.0f;

        if (zoomProgress > 1.0f)
        {
            zoomProgress = 1.0f;
        }

        float baseZ = -2.42f + zoomProgress * 0.97f;
        float cameraZ = (aspect < 1.0f) ? (baseZ / aspect) : baseZ;

        glTranslatef(0.0f, -zoomProgress * 0.08f, cameraZ);
        drawRearViewScene();
    }
    else if (g_masterState == MSTATE_BIRTHDAY ||
             g_masterState == MSTATE_FADE_TO_GROUP_MEMBERS)
    {
        // RENDER SCENE 4: BIRTHDAY CELEBRATION & TRIBUTE
        displayBirthday();
    }
    else if (g_masterState == MSTATE_GROUP_MEMBERS ||
             g_masterState == MSTATE_FADE_TO_CREDITS)
    {
        // RENDER SCENE 5: GROUP MEMBERS & GROUP LEADER
        displayGroupMembers();
    }
    else if (g_masterState == MSTATE_CREDIT_SCREEN ||
             g_masterState == MSTATE_FADE_TO_SHEEP)
    {
        // RENDER SCENE 6: CREDITS SCREEN
        displayCreditScreen();
    }

    // FADE OVERLAY FOR SMOOTH TRANSITIONS ACROSS ALL SCENES
    if (g_fadeAlpha > 0.001f) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0f, 1.0f, 0.0f, 1.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glColor4f(0.0f, 0.0f, 0.0f, g_fadeAlpha);
        glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(1.0f, 0.0f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(0.0f, 1.0f);
        glEnd();
    }

    glutSwapBuffers();
}

// ============================================================
// MASTER ANIMATION TIMER UPDATE
// ============================================================
void update(int value) {
    if (g_isAnimating) {
        // Sea water and flag wave animations for Scene 1
        waterMove += 0.04f;
        if (waterMove > 6.283f) waterMove -= 6.283f;

        flagWave += 0.12f;
        if (flagWave > 6.283f) flagWave -= 6.283f;

        // Master Cutscene Sequence State Machine
        switch (g_masterState) {

        // --- SCENE 1: SHEEP ISLAND & GOING MERRY SAILING ---
        case MSTATE_SHEEP_TRANSIT:
            if (g_fadeAlpha > 0.0f) {
                g_fadeAlpha -= 0.04f;
                if (g_fadeAlpha < 0.0f) g_fadeAlpha = 0.0f;
            }
            shipX -= TRANSIT_SPEED;
            if (shipX <= TRANSIT_EXIT_X) {
                shipX = APPROACH_START_X;
                g_masterState = MSTATE_SHEEP_SAIL;
            }
            break;

        case MSTATE_SHEEP_SAIL:
            shipX -= 0.003f;
            if (shipX <= SHIP_STOP_X) {
                shipX = SHIP_STOP_X;
                dockPauseTimer = 0.0f;
                g_masterState = MSTATE_SHEEP_DOCK_PAUSE;
            }
            break;

        case MSTATE_SHEEP_DOCK_PAUSE:
            dockPauseTimer += 0.03f;
            if (dockPauseTimer >= 1.5f) { // Dock pause duration
                g_masterState = MSTATE_FADE_TO_LUFFY_WALK;
                g_fadeAlpha = 0.0f;
            }
            break;

        case MSTATE_FADE_TO_LUFFY_WALK:
            g_fadeAlpha += 0.04f; // Fade out Scene 1 to black
            if (g_fadeAlpha >= 1.0f) {
                g_fadeAlpha   = 1.0f;
                g_translateX  = -1.8f;
                g_masterState = MSTATE_LUFFY_WALK;
            }
            break;

        // --- SCENE 2: LUFFY WALKING & SPOTTING CHEST ---
        case MSTATE_LUFFY_WALK:
            if (g_fadeAlpha > 0.0f) { // Fade in to Scene 2
                g_fadeAlpha -= 0.04f;
                if (g_fadeAlpha < 0.0f) g_fadeAlpha = 0.0f;
            }
            g_translateX += g_walkSpeed;
            g_walkPhase  += 0.08f;

            if (g_translateX >= 0.0f) { // Reached treasure chest!
                g_masterState = MSTATE_LUFFY_SPOT;
                g_stateTimer  = 0.0f;
            }
            break;

        case MSTATE_LUFFY_SPOT:
            g_stateTimer += 0.016f; // Pause in surprise with '!'
            if (g_stateTimer >= 1.8f) {
                g_masterState = MSTATE_FADE_TO_REAR;
                g_fadeAlpha   = 0.0f;
            }
            break;

        case MSTATE_FADE_TO_REAR:
            g_fadeAlpha += 0.04f; // Fade out Scene 2 to black
            if (g_fadeAlpha >= 1.0f) {
                g_fadeAlpha   = 1.0f;
                g_masterState = MSTATE_REAR_VIEW;
                g_stateTimer  = 0.0f;
            }
            break;

        // --- SCENE 3: REAR VIEW LUFFY & OPEN GLOWING CHEST ---
        case MSTATE_REAR_VIEW:
            if (g_fadeAlpha > 0.0f) { // Fade in to Scene 3
                g_fadeAlpha -= 0.04f;
                if (g_fadeAlpha < 0.0f) g_fadeAlpha = 0.0f;
            }
            g_stateTimer   += 0.016f;
            g_sparkleAngle += 0.05f;
            g_walkPhase    += 0.04f;

            if (g_stateTimer >= 5.0f) { // Hold for 5 seconds
                g_masterState = MSTATE_FADE_TO_BIRTHDAY;
                g_fadeAlpha   = 0.0f;
            }
            break;

        case MSTATE_FADE_TO_BIRTHDAY:
            g_fadeAlpha += 0.04f; // Fade out Scene 3 to black
            if (g_fadeAlpha >= 1.0f) {
                g_fadeAlpha   = 0.0f;
                resetBirthday();
                g_masterState = MSTATE_BIRTHDAY;
            }
            break;

        // --- SCENE 4: BIRTHDAY CELEBRATION & TRIBUTE ---
        case MSTATE_BIRTHDAY:
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
                else
                {
                    // Portrait drawing fully visible - hold for 5 seconds
                    g_birthdayHoldTimer += 0.016f;
                    if (g_birthdayHoldTimer >= 5.0f)
                    {
                        g_masterState = MSTATE_FADE_TO_GROUP_MEMBERS;
                        g_fadeAlpha = 0.0f;
                    }
                }
            }
            break;

        // --- TRANSITION: FADE TO GROUP MEMBERS SCREEN ---
        case MSTATE_FADE_TO_GROUP_MEMBERS:
            g_fadeAlpha += 0.03f;
            if (g_fadeAlpha >= 1.0f) {
                g_fadeAlpha   = 1.0f;
                g_stateTimer  = 0.0f;
                g_masterState = MSTATE_GROUP_MEMBERS;
            }
            break;

        // --- SCENE 5: GROUP MEMBERS & GROUP LEADER SCREEN ---
        case MSTATE_GROUP_MEMBERS:
            if (g_fadeAlpha > 0.0f) {
                g_fadeAlpha -= 0.03f;
                if (g_fadeAlpha < 0.0f) g_fadeAlpha = 0.0f;
            }
            g_stateTimer += 0.033f;
            if (g_stateTimer >= 7.0f) { // Hold Group Members screen for 7 seconds
                g_masterState = MSTATE_FADE_TO_CREDITS;
                g_fadeAlpha   = 0.0f;
            }
            break;

        // --- TRANSITION: FADE TO CREDITS SCREEN ---
        case MSTATE_FADE_TO_CREDITS:
            g_fadeAlpha += 0.03f;
            if (g_fadeAlpha >= 1.0f) {
                g_fadeAlpha   = 1.0f;
                g_stateTimer  = 0.0f;
                g_masterState = MSTATE_CREDIT_SCREEN;
            }
            break;

        // --- SCENE 6: CREDITS SCREEN ---
        case MSTATE_CREDIT_SCREEN:
            if (g_fadeAlpha > 0.0f) {
                g_fadeAlpha -= 0.03f;
                if (g_fadeAlpha < 0.0f) g_fadeAlpha = 0.0f;
            }
            g_stateTimer += 0.033f;
            if (g_stateTimer >= 7.0f) { // Hold Credits screen for 7 seconds
                g_masterState = MSTATE_FADE_TO_SHEEP;
                g_fadeAlpha   = 0.0f;
            }
            break;

        // --- TRANSITION: FADE BACK TO SCENE 1 (LOOP) ---
        case MSTATE_FADE_TO_SHEEP:
            g_fadeAlpha += 0.03f;
            if (g_fadeAlpha >= 1.0f) {
                g_fadeAlpha    = 1.0f;
                shipX          = 1.15f;
                waterMove      = 0.0f;
                flagWave       = 0.0f;
                dockPauseTimer = 0.0f;
                g_translateX   = -1.8f;
                g_stateTimer   = 0.0f;
                resetBirthday();
                g_masterState  = MSTATE_SHEEP_TRANSIT; // Reset back to Scene 1!
            }
            break;
        }

        glutPostRedisplay();
    }

    if (g_masterState == MSTATE_BIRTHDAY) {
        glutTimerFunc(16, update, 0);
    } else {
        glutTimerFunc(33, update, 0);
    }
}

// ============================================================
// INPUT HANDLERS
// ============================================================
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27: // ESC key
        exit(0);
        break;

    case ' ': // Spacebar to pause / resume animation
        g_isAnimating = !g_isAnimating;
        break;

    case 'r':
    case 'R': // Reset back to Scene 1 (Going Merry Sailing)
        shipX          = 1.15f;
        waterMove      = 0.0f;
        flagWave       = 0.0f;
        dockPauseTimer = 0.0f;
        g_translateX   = -1.8f;
        g_fadeAlpha    = 0.0f;
        g_stateTimer   = 0.0f;
        resetBirthday();
        g_masterState  = MSTATE_SHEEP_TRANSIT;
        glutPostRedisplay();
        break;

    case 's':
    case 'S': // Skip to next scene phase
        g_fadeAlpha = 0.0f;
        if (g_masterState < MSTATE_LUFFY_WALK) {
            g_translateX  = -1.8f;
            g_masterState = MSTATE_LUFFY_WALK;
        } else if (g_masterState < MSTATE_REAR_VIEW) {
            g_stateTimer  = 0.0f;
            g_masterState = MSTATE_REAR_VIEW;
        } else if (g_masterState < MSTATE_BIRTHDAY) {
            resetBirthday();
            g_masterState = MSTATE_BIRTHDAY;
        } else if (g_masterState < MSTATE_GROUP_MEMBERS) {
            g_stateTimer  = 0.0f;
            g_masterState = MSTATE_GROUP_MEMBERS;
        } else if (g_masterState < MSTATE_CREDIT_SCREEN) {
            g_stateTimer  = 0.0f;
            g_masterState = MSTATE_CREDIT_SCREEN;
        } else {
            shipX          = 1.15f;
            waterMove      = 0.0f;
            flagWave       = 0.0f;
            dockPauseTimer = 0.0f;
            g_translateX   = -1.8f;
            g_stateTimer   = 0.0f;
            resetBirthday();
            g_masterState  = MSTATE_SHEEP_TRANSIT;
        }
        glutPostRedisplay();
        break;

    case 'f':
    case 'F':
        if (!bIsFullscreen) {
            glutFullScreen();
            bIsFullscreen = true;
        } else {
            glutReshapeWindow(1140, 760);
            glutPositionWindow(100, 50);
            bIsFullscreen = false;
        }
        break;

    default:
        break;
    }
}

void reshape(int w, int h) {
    if (h <= 0) h = 1;
    g_winWidth  = w;
    g_winHeight = h;
    glViewport(0, 0, w, h);
}

// ============================================================
// MAIN ENTRY POINT
// ============================================================
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1140, 760);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Mayuresh Birthday Special - One Piece Animation & Tribute");
    glutFullScreen();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutTimerFunc(0, update, 0);

    glutMainLoop();

    return 0;
}

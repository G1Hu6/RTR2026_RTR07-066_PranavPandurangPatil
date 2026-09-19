#include <GL/freeglut.h>
#include <math.h>
#include <stdlib.h>

bool bIsFullscreen = false;
const float PI = 3.14159265358979323846f;

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
    MSTATE_FADE_TO_RESET         // Fade out to black back to Scene 1
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
// DISPLAY CALLBACK
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
             g_masterState == MSTATE_FADE_TO_RESET)
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
// UNIFIED MASTER ANIMATION TIMER UPDATE (~60 FPS)
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
                g_masterState = MSTATE_FADE_TO_RESET;
                g_fadeAlpha   = 0.0f;
            }
            break;

        case MSTATE_FADE_TO_RESET:
            g_fadeAlpha += 0.04f; // Fade out Scene 3 to black
            if (g_fadeAlpha >= 1.0f) {
                g_fadeAlpha   = 0.0f;
                shipX         = 1.15f; // Reset ship position
                g_masterState = MSTATE_SHEEP_TRANSIT; // Reset back to Scene 1
            }
            break;
        }

        glutPostRedisplay();
    }
    glutTimerFunc(33, update, 0);
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
        shipX         = 1.15f;
        waterMove     = 0.0f;
        flagWave      = 0.0f;
        g_translateX  = -1.8f;
        g_fadeAlpha   = 0.0f;
        g_masterState = MSTATE_SHEEP_TRANSIT;
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
        } else {
            shipX         = 1.15f;
            g_masterState = MSTATE_SHEEP_TRANSIT;
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
    glutCreateWindow("One Piece Master Cutscene - Sheep Island & Luffy");
    glutFullScreen();
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

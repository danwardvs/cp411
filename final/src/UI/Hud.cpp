#include "Hud.hpp"

extern int ballLives;

using namespace std;

float x , y , z;

void Hud::drawHudElement(string text, int corner) {
    int stringLength = text.length();

    //top left corner
    if (corner == 0) x = -5.3, y = 0, z = 5;
    //top right corner
    else if (corner == 0)x = 3, y = 0, z = 5;

    //draw string
    glColor3f(1, 0, 0); 
    for (int i= 0; i < stringLength; i++) {
        glRasterPos3f(x, y, z);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text.at(i));
        x += 0.25;
    }
}
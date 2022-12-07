#include "Hud.hpp"

extern int ballLives;

using namespace std;

float x , y , z;

/* Draws a string on the screen at a specific position
* text = string
* position = position (0 = left corner, 1 = right corner, 2 = middle of the screen)
*/
void Hud::drawHudElement(string text, int position) {
    int stringLength = text.length();

    //top left corner
    if (position == 0) x = -5.3, y = 0, z = 5;
    //top right corner
    else if (position == 1)x = 3, y = 0, z = 5;
    //middle of the screen
    else x = 0, y = 0, z = 0;

    //draw the string
    glColor3f(1, 0, 0); 
    for (int i= 0; i < stringLength; i++) {
        glRasterPos3f(x, y, z);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text.at(i));
        x += 0.25;
    }
}
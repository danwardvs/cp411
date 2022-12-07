#include "Hud.hpp"

extern int ballLives;

using namespace std;

float x , y , z;

/* Draws a string on the screen at a specific position
* text = string
* position = position (0 = left corner, 1 = right corner, 2 = paused, 3 = Game Over, 4 = Win!)
*/
void Hud::drawHudElement(string text, int position) {
    int stringLength = text.length();

    switch (position) {
        case 0: // top left corner (lives)
            x = -5.3, y = 0, z = 5;
            break;
        case 1: // top right corner (level)
            x = 3, y = 0, z = 5;
            break;
        case 2: // middle of the screen (pause)
            x = -4.5, y = 0, z = 0;
            break;
        case 3: // middle of the screen (game over)
            x = -4.9, y = 0, z = 0;
            break;
        case 4: // middle of the screen (win)
            x = -2.5, y = 0, z = 0;
            break;
    }
   
    //draw the string
    glColor3f(1, 0, 0); 
    for (int i= 0; i < stringLength; i++) {
        glRasterPos3f(x, y, z);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text.at(i));
        x += 0.25;
    }
}
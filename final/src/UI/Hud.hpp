#include <GL/glut.h>
#include <string>

#ifndef CHUD_HPP
#define CHUD_HPP

using namespace std;

class Hud {
public:
    /*
    * Draws the string for the hud
    * corner == 0 means top left corner, 1 is top right)
    */
    void drawHudElement(string text, int corner); 
};

#endif

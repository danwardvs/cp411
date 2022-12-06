#include <GL/glut.h>
#include <string>

#ifndef CHUD_HPP
#define CHUD_HPP

using namespace std;

class Hud {
public:
    void drawHud(string text, int corner); //draw the hud (corner == 0 means top left corner, 1 is top right)
protected:
    void drawString(string text, int corner); // draw the string for the hud (corner == 0 means top left corner, 1 is top right)
};

#endif

/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-10-06
 */

#include "Ball.hpp"
#include <GL/gl.h>
#include <stdio.h>

extern RenderMode renderMode;


Ball::Ball(int newItem)
{
    item = newItem;
 direction = 0.5f;
}

Ball::~Ball()
{
}

void Ball::draw()
{
     
    glPushMatrix();
    this->ctmMultiply();
    if(item)
        glColor3f(0.8, 0.2, 0.1);
     else
        glColor3f(0.1, 0.2, 0.8);

    switch (renderMode) {
        case WIRE:
            glutWireSphere(0.2, 8, 8);
            break;
        case CONSTANT:
            glutSolidSphere(0.2, 8, 8);
            break;
        default:
            glutSolidSphere(0.2, 8, 8);
            // float x = this->getMC().mat[0][3];
            // float y = this->getMC().mat[1][3] + 20;
            // float z = this->getMC().mat[2][3];
            // GLfloat position[] = { 0,-3.5, 0, 1 };

            // glLightfv (GL_LIGHT0, GL_POSITION, position);
            // glDisable(GL_LIGHTING);

            // glutSolidSphere(0.2, 8, 8);
            // glEnable(GL_LIGHTING);
            break;
    }

	glPopMatrix();
}


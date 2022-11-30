/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-10-06
 */

#include "Ball.hpp"
#include <GL/gl.h>
#include <stdio.h>

extern RenderMode renderMode;


Ball::Ball()
{
 direction = 0.5f;
}

Ball::~Ball()
{
}

void Ball::draw()
{
    glPushMatrix();
    this->ctmMultiply();
    glColor3f(0.1, 0.2, 0.8);

    if(renderMode==WIRE)
        glutWireSphere(0.2, 8, 8);
    else
        glutSolidSphere(0.2, 8, 8);


	glPopMatrix();
}


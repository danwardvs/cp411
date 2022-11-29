/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-10-06
 */

#include "Ball.hpp"
#include <GL/gl.h>
#include <stdio.h>

Ball::Ball()
{
 direction = 0.78f;
}

Ball::~Ball()
{
}

void Ball::draw()
{
    glPushMatrix();
    this->ctmMultiply();
   glutSolidSphere(0.3, 20, 16);

	glPopMatrix();
}


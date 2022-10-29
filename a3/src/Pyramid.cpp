#include "Pyramid.hpp"
#include "Shape.hpp"
#include <GL/gl.h>

Pyramid::Pyramid()
{
    vertex[0][0] = -0.5; vertex[0][1] = -0.5; vertex[0][2] = 0;
    vertex[1][0] = 0.5; vertex[1][1] = -0.5; vertex[1][2] = 0;
    vertex[2][0] = 0.5; vertex[2][1] = 0.5; vertex[2][2] = 0;
    vertex[3][0] = -0.5; vertex[3][1] = 0.5; vertex[3][2] = 0;
    vertex[4][0] = 0; vertex[4][1] = 0; vertex[4][2] = 0.75f;

    r = 1.0;
    g = 1.0;
    b = 0;

    translate(3.5, 0, 0);

}


void Pyramid::drawPyramid()
{
    glColor3f(r, g, b);


    glBegin(GL_LINE_LOOP);

    glVertex3fv( &(vertex[0][0]) );
    glVertex3fv( &(vertex[1][0]) );
    glVertex3fv( &(vertex[2][0]) );
    glVertex3fv( &(vertex[3][0]) );

    glEnd();

    glBegin(GL_LINE_LOOP);

    glVertex3fv( &(vertex[0][0]) );
    glVertex3fv( &(vertex[1][0]) );
    glVertex3fv( &(vertex[4][0]) );


    glEnd();

    glBegin(GL_LINE_LOOP);

    glVertex3fv( &(vertex[1][0]) );
    glVertex3fv( &(vertex[2][0]) );
    glVertex3fv( &(vertex[4][0]) );


    glEnd();

    glBegin(GL_LINE_LOOP);

    glVertex3fv( &(vertex[2][0]) );
    glVertex3fv( &(vertex[3][0]) );
    glVertex3fv( &(vertex[4][0]) );


    glEnd();


    glBegin(GL_LINE_LOOP);

    glVertex3fv( &(vertex[3][0]) );
    glVertex3fv( &(vertex[0][0]) );
    glVertex3fv( &(vertex[4][0]) );


    glEnd();

}

void Pyramid::draw()
{
    glPushMatrix();
    this->ctmMultiply();
    glScalef(s, s, s);
	drawPyramid();
 
    glPopMatrix();
}


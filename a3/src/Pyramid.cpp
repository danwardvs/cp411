#include "Pyramid.hpp"
#include <GL/gl.h>

Pyramid::Pyramid()
{
    vertex[0][0] = -1; vertex[0][1] = -1; vertex[0][2] = 0;
    vertex[1][0] = 1; vertex[1][1] = -1; vertex[1][2] = 0;
    vertex[2][0] = 1; vertex[2][1] = 1; vertex[2][2] = 0;
    vertex[3][0] = -1; vertex[3][1] = 1; vertex[3][2] = 0;
    vertex[4][0] = 0; vertex[4][1] = 0; vertex[4][2] = 1.5f;

    face[0][0] = 0; face[0][1] = 1; face[0][2] = 2; face[0][3] = 3;
    face[1][0] = 0; face[1][1] = 1; face[1][2] = 2; face[1][3] = 4;
    face[2][0] = 0; face[2][1] = 4; face[2][2] = 5; face[2][3] = 1;
    face[3][0] = 2; face[3][1] = 1; face[3][2] = 5; face[3][3] = 6;
    face[4][0] = 3; face[4][1] = 2; face[4][2] = 6; face[4][3] = 7;

    r = 0;
    g = 1.0;
    b = 1.0;
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


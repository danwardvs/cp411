#include "House.hpp"
#include <GL/gl.h>

House::House()




{
    vertex[0][0] = 0; vertex[0][1] = 0; vertex[0][2] = 0;
    vertex[1][0] = 0; vertex[1][1] = 1; vertex[1][2] = 0;
    vertex[2][0] = 1; vertex[2][1] = 1; vertex[2][2] = 0;
    vertex[3][0] = 1; vertex[3][1] = 0; vertex[3][2] = 0;
    vertex[4][0] = 0; vertex[4][1] = 0; vertex[4][2] = 1;
    vertex[5][0] = 0; vertex[5][1] = 1; vertex[5][2] = 1;
    vertex[6][0] = 1; vertex[6][1] = 1; vertex[6][2] = 1;
    vertex[7][0] = 1; vertex[7][1] = 0; vertex[7][2] = 1;
    vertex[8][0] = 0.5; vertex[8][1] = 0.5; vertex[8][2] = 1.5f;


    r = 1.0;
    g = 1.0;
    b = 1.0;


    face[0][0] = 0; face[0][1] = 1; face[0][2] = 2; face[0][3] = 3;
    face[1][0] = 7; face[1][1] = 6; face[1][2] = 5; face[1][3] = 4;
    face[2][0] = 0; face[2][1] = 4; face[2][2] = 5; face[2][3] = 1;
    face[3][0] = 2; face[3][1] = 1; face[3][2] = 5; face[3][3] = 6;
    face[4][0] = 3; face[4][1] = 2; face[4][2] = 6; face[4][3] = 7;
    face[5][0] = 0; face[5][1] = 3; face[5][2] = 7; face[5][3] = 4;

    r = 0;
    g = 1.0;
    b = 1.0;
}

void House::drawPyramid()
{
    glColor3f(r, g, b);



    glBegin(GL_LINE_LOOP);

    glVertex3fv( &(vertex[4][0]) );
    glVertex3fv( &(vertex[5][0]) );
    glVertex3fv( &(vertex[8][0]) );


    glEnd();

    glBegin(GL_LINE_LOOP);

    glVertex3fv( &(vertex[5][0]) );
    glVertex3fv( &(vertex[6][0]) );
    glVertex3fv( &(vertex[8][0]) );


    glEnd();

    glBegin(GL_LINE_LOOP);

    glVertex3fv( &(vertex[6][0]) );
    glVertex3fv( &(vertex[7][0]) );
    glVertex3fv( &(vertex[8][0]) );


    glEnd();


    glBegin(GL_LINE_LOOP);

    glVertex3fv( &(vertex[7][0]) );
    glVertex3fv( &(vertex[4][0]) );
    glVertex3fv( &(vertex[8][0]) );


    glEnd();

}
void House::drawFace(int i)
{
    glColor3f(r, g, b);

    glBegin(GL_LINE_LOOP);

    glVertex3fv( &(vertex[face[i][0]][0]) );
    glVertex3fv( &(vertex[face[i][1]][0]) );
    glVertex3fv( &(vertex[face[i][2]][0]) );
    glVertex3fv( &(vertex[face[i][3]][0]) );

    glEnd();

}

void House::draw()
{
    glPushMatrix();
    this->ctmMultiply();
    glScalef(s, s, s);
	drawPyramid();
 
    glPopMatrix();
    
    glPushMatrix();
    this->ctmMultiply();
    glScalef(s, s, s);
	    for (int i = 0; i < 6; i++) {
		    drawFace(i);
	    }
 
    glPopMatrix();
}


/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-10-03 (update)
 */
#include "Paddle.hpp"
#include "Camera.hpp"
#include <stdio.h>

extern Camera myCamera;
extern CullMode cullMode;
extern RenderMode renderMode;
extern GLint bigPaddleTime;

Paddle::Paddle() {
  vertex[0][0] = -1;
  vertex[0][1] = -1;
  vertex[0][2] = -0.2;
  vertex[1][0] = -1;
  vertex[1][1] = 1;
  vertex[1][2] = -0.2;
  vertex[2][0] = 1;
  vertex[2][1] = 1;
  vertex[2][2] = -0.2;
  vertex[3][0] = 1;
  vertex[3][1] = -1;
  vertex[3][2] = -0.2;
  vertex[4][0] = -1;
  vertex[4][1] = -1;
  vertex[4][2] = 0.2;
  vertex[5][0] = -1;
  vertex[5][1] = 1;
  vertex[5][2] = 0.2;
  vertex[6][0] = 1;
  vertex[6][1] = 1;
  vertex[6][2] = 0.2;
  vertex[7][0] = 1;
  vertex[7][1] = -1;
  vertex[7][2] = 0.2;

  face[0][0] = 0;
  face[0][1] = 1;
  face[0][2] = 2;
  face[0][3] = 3;
  face[1][0] = 7;
  face[1][1] = 6;
  face[1][2] = 5;
  face[1][3] = 4;
  face[2][0] = 0;
  face[2][1] = 4;
  face[2][2] = 5;
  face[2][3] = 1;
  face[3][0] = 2;
  face[3][1] = 1;
  face[3][2] = 5;
  face[3][3] = 6;
  face[4][0] = 3;
  face[4][1] = 2;
  face[4][2] = 6;
  face[4][3] = 7;
  face[5][0] = 0;
  face[5][1] = 3;
  face[5][2] = 7;
  face[5][3] = 4;

  // faceColor

  faceColor[0][0] = 0.0, faceColor[0][1] = 1.0;
  faceColor[0][2] = 1.0;
  faceColor[1][0] = 0.0, faceColor[1][1] = 0.0;
  faceColor[1][2] = 1.0;
  faceColor[2][0] = 0.0, faceColor[2][1] = 1.0;
  faceColor[2][2] = 0.0;
  faceColor[3][0] = 1.0, faceColor[3][1] = 0.0;
  faceColor[3][2] = 0.0;
  faceColor[4][0] = 1.0, faceColor[4][1] = 1.0;
  faceColor[4][2] = 0.0;
  faceColor[5][0] = 1.0, faceColor[5][1] = 0.0;
  faceColor[5][2] = 1.0;

  for (int i = 0; i < 6; i++) {
    Vector V1 = Vector(vertex[face[i][1]][0] - vertex[face[i][0]][0],
                       vertex[face[i][1]][1] - vertex[face[i][0]][1],
                       vertex[face[i][1]][2] - vertex[face[i][0]][2]);
    Vector V2 = Vector(vertex[face[i][2]][0] - vertex[face[i][1]][0],
                       vertex[face[i][2]][1] - vertex[face[i][1]][1],
                       vertex[face[i][2]][2] - vertex[face[i][1]][2]);
    Vector V3 = V1.cross(V2);
    V3.normalize();
    faceNormal[i][0] = V3.x;
    faceNormal[i][1] = V3.y;
    faceNormal[i][2] = V3.z;
  }

  vertexColor[0][0] = 1.0, vertexColor[0][1] = 0.0;
  vertexColor[0][2] = 0.0;
  vertexColor[1][0] = 0.0, vertexColor[1][1] = 1.0;
  vertexColor[1][2] = 0.0;
  vertexColor[2][0] = 0.0, vertexColor[2][1] = 0.0;
  vertexColor[2][2] = 1.0;
  vertexColor[3][0] = 1.0, vertexColor[3][1] = 1.0;
  vertexColor[3][2] = 0.0;
  vertexColor[4][0] = 1.0, vertexColor[4][1] = 0.0;
  vertexColor[4][2] = 1.0;
  vertexColor[5][0] = 0.0, vertexColor[5][1] = 1.0;
  vertexColor[5][2] = 1.0;
  vertexColor[6][0] = 0.5, vertexColor[6][1] = 0.5;
  vertexColor[6][2] = 0.5;
  vertexColor[7][0] = 0.0, vertexColor[7][1] = 0.0;
  vertexColor[7][2] = 0.0;

  vertexNormal[0][0] = -1;
  vertexNormal[0][1] = -1;
  vertexNormal[0][2] = -1;
  vertexNormal[1][0] = -1;
  vertexNormal[1][1] = 1;
  vertexNormal[1][2] = -1;
  vertexNormal[2][0] = 1;
  vertexNormal[2][1] = 1;
  vertexNormal[2][2] = -1;
  vertexNormal[3][0] = 1;
  vertexNormal[3][1] = -1;
  vertexNormal[3][2] = -1;
  vertexNormal[4][0] = -1;
  vertexNormal[4][1] = -1;
  vertexNormal[4][2] = 1;
  vertexNormal[5][0] = -1;
  vertexNormal[5][1] = 1;
  vertexNormal[5][2] = 1;
  vertexNormal[6][0] = 1;
  vertexNormal[6][1] = 1;
  vertexNormal[6][2] = 1;
  vertexNormal[7][0] = 1;
  vertexNormal[7][1] = -1;
  vertexNormal[7][2] = 1;

  r = 1.0;
  g = 0.0;
  b = 0.0;
}

void Paddle::drawFace(int i) {
  GLfloat shade = 1;

  switch (renderMode) {
  case WIRE: // this case from SimpleView1
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_NORMALIZE);
    glColor3f(r, g, b);
    glBegin(GL_LINE_LOOP);
    glVertex3fv(vertex[face[i][0]]);
    glVertex3fv(vertex[face[i][1]]);
    glVertex3fv(vertex[face[i][2]]);
    glVertex3fv(vertex[face[i][3]]);
    glEnd();
    break;
  case CONSTANT: // this case from SimpleView2
    glColor3f(faceColor[i][0] * shade, faceColor[i][1] * shade,
              faceColor[i][2] * shade);
    glBegin(GL_POLYGON);
    glVertex3fv(vertex[face[i][0]]);
    glVertex3fv(vertex[face[i][1]]);
    glVertex3fv(vertex[face[i][2]]);
    glVertex3fv(vertex[face[i][3]]);
    glEnd();
    break;

  case FLAT:
    glShadeModel(GL_FLAT);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glBegin(GL_POLYGON);
    glColor3f(vertexColor[face[i][0]][0] * shade,
              vertexColor[face[i][0]][1] * shade,
              vertexColor[face[i][0]][2] * shade);
    for (int j = 0; j < 4; j++) {
      glVertex3fv(vertex[face[i][j]]);
    }
    glEnd();
    break;
  case SMOOTH: {
    glShadeModel(GL_SMOOTH);
    glBegin(GL_POLYGON);
    for (int j = 0; j < 4; j++) {
      glColor3f(vertexColor[face[i][j]][0], vertexColor[face[i][j]][1],
                vertexColor[face[i][j]][2]);
      glNormal3f(vertexNormal[face[i][j]][0], vertexNormal[face[i][j]][1],
                 vertexNormal[face[i][j]][2]);
      glVertex3fv(vertex[face[i][j]]);
    }
    glEnd();
  } break;

    break;

  case PHONG:

    break;

  case TEXTURE:

    break;
  }
}

void Paddle::draw() {
  glPushMatrix();
  this->ctmMultiply();
	if(bigPaddleTime>0)
  	glScalef(2*s, s, s);
	else
		glScalef(s, s, s);

	

  for (int i = 0; i < 6; i++) {
    drawFace(i);
  }

  glPopMatrix();
}

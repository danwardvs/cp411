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

Paddle::Paddle() {
    vertex[0][0] = -1; vertex[0][1] = -1; vertex[0][2] = -0.2;
    vertex[1][0] = -1; vertex[1][1] = 1;  vertex[1][2] = -0.2;
    vertex[2][0] = 1;  vertex[2][1] = 1;  vertex[2][2] = -0.2;
    vertex[3][0] = 1;  vertex[3][1] = -1; vertex[3][2] = -0.2;
    vertex[4][0] = -1; vertex[4][1] = -1; vertex[4][2] = 0.2;
    vertex[5][0] = -1; vertex[5][1] = 1;  vertex[5][2] = 0.2;
    vertex[6][0] = 1;  vertex[6][1] = 1;  vertex[6][2] = 0.2;
    vertex[7][0] = 1;  vertex[7][1] = -1; vertex[7][2] = 0.2;

    face[0][0] = 0; face[0][1] = 1; face[0][2] = 2; face[0][3] = 3;
    face[1][0] = 7; face[1][1] = 6; face[1][2] = 5; face[1][3] = 4;
    face[2][0] = 0; face[2][1] = 4; face[2][2] = 5; face[2][3] = 1;
    face[3][0] = 2; face[3][1] = 1; face[3][2] = 5; face[3][3] = 6;
    face[4][0] = 3; face[4][1] = 2; face[4][2] = 6; face[4][3] = 7;
    face[5][0] = 0; face[5][1] = 3; face[5][2] = 7; face[5][3] = 4;

	// faceColor
		
			faceColor[0][0] = 0.0, faceColor[0][1] = 1.0; faceColor[0][2] = 1.0;
			faceColor[1][0] = 0.0, faceColor[1][1] = 0.0; faceColor[1][2] = 1.0;
			faceColor[2][0] = 0.0, faceColor[2][1] = 1.0; faceColor[2][2] = 0.0;
			faceColor[3][0] = 1.0, faceColor[3][1] = 0.0; faceColor[3][2] = 0.0;
			faceColor[4][0] = 1.0, faceColor[4][1] = 1.0; faceColor[4][2] = 0.0;
			faceColor[5][0] = 1.0, faceColor[5][1] = 0.0; faceColor[5][2] = 1.0;


	for (int i = 0 ; i<6; i++) {
		Vector V1 = Vector(vertex[face[i][1]][0]-vertex[face[i][0]][0], vertex[face[i][1]][1]-vertex[face[i][0]][1], vertex[face[i][1]][2]-vertex[face[i][0]][2]);
		Vector V2 = Vector(vertex[face[i][2]][0]-vertex[face[i][1]][0], vertex[face[i][2]][1]-vertex[face[i][1]][1], vertex[face[i][2]][2]-vertex[face[i][1]][2]);
		Vector V3 =  V1.cross(V2);
		V3.normalize();
		faceNormal[i][0] = V3.x;
		faceNormal[i][1] = V3.y;
		faceNormal[i][2] = V3.z;
	}
	
	

	vertexColor[0][0] = 1.0, vertexColor[0][1] = 0.0; vertexColor[0][2] = 0.0;
	vertexColor[1][0] = 0.0, vertexColor[1][1] = 1.0; vertexColor[1][2] = 0.0;
	vertexColor[2][0] = 0.0, vertexColor[2][1] = 0.0; vertexColor[2][2] = 1.0;
	vertexColor[3][0] = 1.0, vertexColor[3][1] = 1.0; vertexColor[3][2] = 0.0;
	vertexColor[4][0] = 1.0, vertexColor[4][1] = 0.0; vertexColor[4][2] = 1.0;
	vertexColor[5][0] = 0.0, vertexColor[5][1] = 1.0; vertexColor[5][2] = 1.0;
	vertexColor[6][0] = 0.5, vertexColor[6][1] = 0.5; vertexColor[6][2] = 0.5;
	vertexColor[7][0] = 0.0, vertexColor[7][1] = 0.0; vertexColor[7][2] = 0.0;

    vertexNormal[0][0] = -1; vertexNormal[0][1] = -1; vertexNormal[0][2] = -1;
    vertexNormal[1][0] = -1; vertexNormal[1][1] = 1;  vertexNormal[1][2] = -1;
    vertexNormal[2][0] = 1;  vertexNormal[2][1] = 1;  vertexNormal[2][2] = -1;
    vertexNormal[3][0] = 1;  vertexNormal[3][1] = -1; vertexNormal[3][2] = -1;
    vertexNormal[4][0] = -1; vertexNormal[4][1] = -1; vertexNormal[4][2] = 1;
    vertexNormal[5][0] = -1; vertexNormal[5][1] = 1;  vertexNormal[5][2] = 1;
    vertexNormal[6][0] = 1;  vertexNormal[6][1] = 1;  vertexNormal[6][2] = 1;
    vertexNormal[7][0] = 1;  vertexNormal[7][1] = -1; vertexNormal[7][2] = 1;
	

	r = 1.0;
	g = 0.0;
	b = 0.0;
}

void Paddle::drawFace(int i)
	{
		GLfloat shade = 1;

	switch (renderMode) {
	case WIRE:   // this case from SimpleView1
	   glColor3f(r, g, b);
	   glBegin(GL_LINE_LOOP);
	     glVertex3fv(vertex[face[i][0]]);
       glVertex3fv(vertex[face[i][1]]);
       glVertex3fv(vertex[face[i][2]]);
       glVertex3fv(vertex[face[i][3]]);
       glEnd();
	   break;
	case CONSTANT:  // this case from SimpleView2
	   glColor3f(faceColor[i][0]*shade, faceColor[i][1]*shade, faceColor[i][2]*shade);
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
	   glColor3f(vertexColor[face[i][0]][0]*shade, vertexColor[face[i][0]][1]*shade, vertexColor[face[i][0]][2]*shade);
	   for (int j=0; j<4; j++) {
		   glVertex3fv(vertex[face[i][j]]);
	   }
	   glEnd();
	   break;
	case SMOOTH:
	{ glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
	   glEnable(GL_NORMALIZE);
	   glShadeModel(GL_SMOOTH);
	   glBegin(GL_POLYGON);
	   for (int j=0; j<4; j++) {
		   glColor3f(vertexColor[face[i][j]][0], vertexColor[face[i][j]][1], vertexColor[face[i][j]][2]);
	       glNormal3f(vertexNormal[face[i][j]][0], vertexNormal[face[i][j]][1], vertexNormal[face[i][j]][2]);
	       glVertex3fv(vertex[face[i][j]]);
	   }
	   glEnd();
	}
	break;

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
	glScalef(s, s, s);

	for (int i = 0; i < 6; i++) {
		if  (cullMode == BACKFACE ) {
			if (isFrontface(i, myCamera)) {
				drawFace(i);
			}
		}
		else {
			drawFace(i);
		}
	}
	
	
	glPopMatrix();
}

bool Paddle::isFrontface(int faceindex, Camera camera) {
	GLfloat v[4];
	v[0] = faceNormal[faceindex][0];  // get faceNormal in MCS
	v[1] = faceNormal[faceindex][1];
	v[2] = faceNormal[faceindex][2];
	v[3] = 0.0;
	mc.multiplyVector(v);   // compute faceNormal in WCS
	   
	if (pmc != NULL) {  // if parent MCS exists, use the parent's origin as reference point. 
		pmc->multiplyVector(v);
		return (pmc->mat[0][3] - camera.eye.x) * v[0] + (pmc->mat[1][3] - camera.eye.y) * v[1] + (pmc->mat[2][3] - camera.eye.z) * v[2] < 0;
	} else {
		return (mc.mat[0][3] - camera.eye.x) * v[0] + (mc.mat[1][3] - camera.eye.y) * v[1] + (mc.mat[2][3] - camera.eye.z) * v[2] < 0;
	}}


GLfloat Paddle::getFaceShade(int faceindex, Light light) {
	GLfloat shade = 1, v[4], s[4], temp;

	// your implementation

	// assign v the first vertex of face[faceindex]
	v[0] = vertex[face[faceindex][0]][0];
	v[1] = vertex[face[faceindex][0]][1];
	v[2] = vertex[face[faceindex][0]][2];
	v[0] = 1;
	mc.multiplyVector(v);  //compute the position of vertex  in WCS
	if (pmc != NULL) pmc->multiplyVector(v); //furtber compute the position of vertex in WCS if the parent MC is not NULL, e.g. in Ball


	// compute the light vector s[] = lightposition - face[faceindex][0]
	s[0] = light.getMC().mat[0][3] - v[0];
	s[1] = light.getMC().mat[1][3] - v[1];
	s[2] = light.getMC().mat[2][3] - v[2];

//	//normalize vector s
	temp = sqrt(s[0]*s[0]+s[1]*s[1]+s[2]*s[2]);
	s[0] = s[0]/temp;
	s[1] = s[1]/temp;
	s[2] = s[2]/temp;

    // compute the normal of  face[faceindex] in WC
 	v[0] = faceNormal[faceindex][0];
	v[1] = faceNormal[faceindex][1];
	v[2] = faceNormal[faceindex][2];
	v[3] = 0;
	mc.multiplyVector(v);

	if (pmc != NULL) pmc->multiplyVector(v);

	//normalize face normal
	temp = sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
	v[0] = v[0]/temp;
	v[1] = v[1]/temp;
	v[2] = v[2]/temp;

	// compute v dot s
	temp = v[0]*s[0]+v[1]*s[1]+v[2]*s[2];

	// compute shade factor
	shade = light.I*light.Rd*temp; // + light.Ia*light.Ra;

	if (shade < 0.01) shade = 0.1;
	if (shade > 0.99 ) shade = 0.9;
	return shade;
}


GLfloat Paddle::getVertexShade(int i, Light light) {
	GLfloat shade = 1, v[4], s[4], temp;

	// assign v the first vertex of face[faceindex]
	v[0] = vertex[i][0];
	v[1] = vertex[i][1];
	v[2] = vertex[i][2];
	v[0] = 1;
	mc.multiplyVector(v);  //compute the position of vertex face[faceindex][0] in WC

	if (pmc != NULL) pmc->multiplyVector(v);

	// compute the light vector s[] = lightposition - face[faceindex][0]
	s[0] = light.getMC().mat[0][3] - v[0];
	s[1] = light.getMC().mat[1][3] - v[1];
	s[2] = light.getMC().mat[2][3] - v[2];

//	//normalize vector s
	temp = sqrt(s[0]*s[0]+s[1]*s[1]+s[2]*s[2]);
	s[0] = s[0]/temp;
	s[1] = s[1]/temp;
	s[2] = s[2]/temp;

    // compute the normal of  face[faceindex] in WC
 	v[0] = vertexNormal[i][0];
	v[1] = vertexNormal[i][1];
	v[2] = vertexNormal[i][2];
	v[3] = 0;
	mc.multiplyVector(v);

	if (pmc != NULL) pmc->multiplyVector(v);

	//normalize face normal
	temp = sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
	v[0] = v[0]/temp;
	v[1] = v[1]/temp;
	v[2] = v[2]/temp;

	// compute v dot s
	temp = v[0]*s[0]+v[1]*s[1]+v[2]*s[2];

	// compute shade factor
	shade = light.I*light.Rd*temp; // + light.Ia*light.Ra;

	if (shade < 0.01) shade = 0.1;
	if (shade > 0.99 ) shade = 0.9;

	return shade;
}

/*
 *  SimpleView2 : reference design
 *  Author: HBF
 *  Version: 2022-10-06 (update)
 */
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Menu.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Paddle.hpp"

GLint winWidth = 800, winHeight = 800;
GLint isInMove = 0,    /* flag for mouse motion */
	  xbegin = 0,      /* hold mouse down xMouse */
	  csType = 1,     /* coordinate system type: 1 for MCS, 2 for WCS, 3 for VCS */
	  transType = 4;  /* depends on csType  */

CullMode cullMode = NONE;          /* culling option */
RenderMode renderMode = CONSTANT;  /* shade option  */

World myWorld;
Camera myCamera;
Light myLight;
Shape *selectObj = NULL;  /* pointer to selected object */

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	selectObj = myWorld.searchById(1);
	myLight.on = false;
}


void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	myCamera.setProjectionMatrix();
	myWorld.draw();
	myLight.draw();
	glFlush();
	glutSwapBuffers();
}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	winWidth = newWidth;
	winHeight = newHeight;
}

void mouseActionFcn( int xMouse, int yMouse) {
		Shape *paddle = myWorld.searchById(0);

			GLfloat x = xMouse;
			paddle->setX( (x/75) - 5);
		glutPostRedisplay();



}

void mouseMotionFcn(GLint xMouse, GLint yMouse) {
		printf("mouse down\n");
	
}
void update(){
			GLfloat speed = 0.07f;
			Shape *ball = myWorld.searchById(1);
			GLfloat direction = ball->getDirection();
			ball->translate2d(sin(direction) * speed, cos(direction) * speed);
			GLfloat x = ball->getMC().mat[0][3];
			GLfloat z = ball->getMC().mat[2][3];
			printf("x: %.10f\n",x);
			printf("z: %.10f\n",z);

			if(x>7){
				ball->setDirection(-direction);
			}
			
			if(x<-7){
				ball->setDirection(-direction);
			}

			if(z>7){
				ball->setDirection(3.1415-direction);
			}

			if(z<-7){
				ball->setDirection(3.1415-direction);
			}
			
		
			
			glutPostRedisplay();


			



}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("SimpleView2 reference design (Danny Van Stemp)");
	init();
	menu();
	glutDisplayFunc(display);
	glutMotionFunc(mouseMotionFcn);
	glutPassiveMotionFunc(mouseActionFcn);
		glutIdleFunc(update);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	glutMainLoop();
	return 0;
}

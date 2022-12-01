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
#include "level/Level.hpp"

GLint winWidth = 800, winHeight = 800;
GLint isInMove = 0,    /* flag for mouse motion */
	  xbegin = 0,      /* hold mouse down xMouse */
	  csType = 1,     /* coordinate system type: 1 for MCS, 2 for WCS, 3 for VCS */
	  transType = 4;  /* depends on csType  */

CullMode cullMode = NONE;          /* culling option */
RenderMode renderMode = WIRE;  /* shade option  */

World myWorld;
Camera myCamera;
Level level;
Shape *selectObj = NULL;  /* pointer to selected object */

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	selectObj = myWorld.searchById(1);
	level.levelLayout(1, 2);
}


void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	myCamera.setProjectionMatrix();
	myWorld.draw();
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
			paddle->setX( (x/75) - 5.5);
		glutPostRedisplay();



}

void mouseMotionFcn(GLint xMouse, GLint yMouse) {
		printf("mouse down\n");
	
}

void handleDeath(){
		printf("you lost\n");

}
GLboolean checkCollision(Shape* block,Shape* ball){
	GLfloat blockX = block->getMC().mat[0][3];
	GLfloat blockZ = block->getMC().mat[2][3];
	GLfloat ballX = ball->getMC().mat[0][3];
	GLfloat ballZ = ball->getMC().mat[2][3];
	
	GLfloat blockWidth = 1;
	GLfloat blockHeight = 0.4;
	GLboolean destroy = false;
	if(ballX > blockX - blockWidth && ballX < blockX + blockWidth && ballZ > blockZ - blockHeight && ballZ < blockZ + blockHeight){

		if(block->getCondition()==0){
			destroy=true;
		}

		block->setCondition(block->getCondition()-1);
		

		if(ballX < blockX - blockWidth*0.95 || ballX > blockX + blockWidth*0.95 )
		
					ball->setDirection(-ball->getDirection());

		
		else 		
			ball->setDirection(3.1415-ball->getDirection());
	
		}
		return destroy;
	

}

void updateBall(Shape* ball){
			std::list<Shape*>::iterator it;

	for (it = myWorld.objlist.begin(); it !=  myWorld.objlist.end(); ++it) {
	  if ((*it)->getId() < 1000 && (*it)->getId() > 0)
			if(checkCollision((*it),ball)){
				it = myWorld.objlist.erase(it); 

			}

    }


		Shape *paddle = myWorld.searchById(0);
			GLfloat paddle_x = paddle->getMC().mat[0][3] + 0.3;

			GLfloat speed = 0.06f;

			GLfloat direction = ball->getDirection();
			ball->translate2d(sin(direction) * speed, cos(direction) * speed);
			GLfloat x = ball->getMC().mat[0][3];
			GLfloat z = ball->getMC().mat[2][3];
			// printf("x: %.10f\n",x);
			// 			printf("y: %.10f\n",ball->getMC().mat[1][3]);

			// printf("z: %.10f\n",z);
			GLfloat worldSize = 5.3;

			if(x>worldSize){
				ball->setDirection(-direction);
			}
			
			if(x<-worldSize){
				ball->setDirection(-direction);
			}

			if(z>worldSize){
				ball->setDirection(3.1415-direction);
			}
			GLfloat paddle_width = 2;
			// if(x>paddle_x-paddle_width && x<paddle_x+paddle_width)
			// 	printf("yes\n");
			// else
			// 	printf("no\n");
			
			if(z<-worldSize+0.7f){
				if(x>paddle_x-paddle_width && x<paddle_x+paddle_width){
				
					GLfloat newDirection = 0;
					if(x>paddle_x){
							
								newDirection = ((abs(paddle_x-x)/paddle_width )*2) + 0.5 ;
					

					}else{
								newDirection =  -((abs(paddle_x-x)/paddle_width)*2) + 0.5 ;

					}
					
					ball->setDirection(newDirection);
				}else{
					ball->setTranslation(0, 0, 0);
					handleDeath();
				}
				
			}
}

void update(){
			
			std::list<Shape*>::iterator it;
	for (it = myWorld.objlist.begin(); it !=  myWorld.objlist.end(); ++it) {
	  if ((*it)->getId() >= 1000)
			updateBall((*it));
    }
		
			
			glutPostRedisplay();


			



}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("3D Brick Breaker");
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

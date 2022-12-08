/*
 *  SimpleView2 : reference design
 *  Author: HBF
 *  Version: 2022-10-06 (update)
 */
#include "Camera.hpp"
#include "Menu.hpp"
#include "Paddle.hpp"
#include "UI/Hud.hpp"
#include "World.hpp"
#include "level/Generation.hpp"
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

GLint winWidth = 800, winHeight = 800;

CullMode cullMode = NONE;     /* culling option */
RenderMode renderMode = WIRE; /* shade option  */
bool ballCanMove = false;
int ballLives = 3;
int paused = 0;
int bigPaddleTime = 0;
bool winGame = false;
GLfloat paddle_width = 2;
GLfloat worldSize = 5.3;

World myWorld;
Camera myCamera;
Generation myGeneration;
Hud myHud;

void init(void) {
  srand(time(NULL)); // initialize random seed
  glClearColor(0.0, 0.0, 0.0, 1.0);
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

void mouseActionFcn(int xMouse, int yMouse) {
  if (!paused) {
    Shape *paddle = myWorld.searchById(0);
    GLfloat x = xMouse;
    paddle->setX((x / 75) - 5.5);
    glutPostRedisplay();
  }
}

GLboolean checkCollision(Shape *block, Shape *ball) {
  GLfloat blockX = block->getMC().mat[0][3];
  GLfloat blockZ = block->getMC().mat[2][3];
  GLfloat ballX = ball->getMC().mat[0][3];
  GLfloat ballZ = ball->getMC().mat[2][3];

  GLfloat blockWidth = 1;
  GLfloat blockHeight = 0.4;
  GLboolean destroy = false;
  if (ballX > blockX - blockWidth && ballX < blockX + blockWidth &&
      ballZ > blockZ - blockHeight && ballZ < blockZ + blockHeight) {

    if (block->getCondition() == 0) {
      destroy = true;
    }

    block->setCondition(block->getCondition() - 1);

    if (ballX < blockX - blockWidth * 0.95 ||
        ballX > blockX + blockWidth * 0.95)

      ball->setDirection(-ball->getDirection());

    else
      ball->setDirection(3.1415 - ball->getDirection());
  }
  return destroy;
}

int updateItem(Shape *item) {
  GLfloat speed = 0.04;
  Shape *paddle = myWorld.searchById(0);
  GLfloat paddle_x = paddle->getMC().mat[0][3] + 0.3;

  GLfloat x = item->getMC().mat[0][3];
  GLfloat z = item->getMC().mat[2][3];

  item->translate2d(0, -speed);

  if (z < -worldSize + 0.7f) {
    if (x > paddle_x - paddle_width && x < paddle_x + paddle_width) {
      return 0;
    }
  }
  if (z < -worldSize) {
    return 2;
  }
  return 1;
}

int updateBall(Shape *ball) {
  std::list<Shape *>::iterator it;

  for (it = myWorld.objlist.begin(); it != myWorld.objlist.end(); ++it) {
    if ((*it)->getId() < 1000 && (*it)->getId() > 0)
      if (checkCollision((*it), ball)) {
        if (rand() % 4 == 0) {
          GLfloat x = (*it)->getMC().mat[0][3];
          GLfloat z = (*it)->getMC().mat[2][3];

          myWorld.createItem(x, z);
        }

        it = myWorld.objlist.erase(it);
        myGeneration.blocksRemaining--; // update remaining block counter
      }
  }

  Shape *paddle = myWorld.searchById(0);
  GLfloat paddle_x = paddle->getMC().mat[0][3] + 0.3;

  GLfloat speed = 0.06f;

  GLfloat direction = ball->getDirection();
  ball->translate2d(sin(direction) * speed, cos(direction) * speed);
  GLfloat x = ball->getMC().mat[0][3];
  GLfloat z = ball->getMC().mat[2][3];

  if (x > worldSize) {
    ball->setDirection(-direction);
  }

  if (x < -worldSize) {
    ball->setDirection(-direction);
  }

  if (z > worldSize) {
    ball->setDirection(3.1415 - direction);
  }

  if (z < -worldSize + 0.7f) {
    if (x > paddle_x - paddle_width && x < paddle_x + paddle_width) {

      GLfloat newDirection = 0;
      if (x > paddle_x) {

        newDirection = ((abs(paddle_x - x) / paddle_width) * 2) + 0.5;

      } else {
        newDirection = -((abs(paddle_x - x) / paddle_width) * 2) + 0.5;
      }

      ball->setDirection(newDirection);
    } else {
      int balls = 0;
      if (myWorld.searchById(1000))
        balls++;
      if (myWorld.searchById(1001))
        balls++;
      if (myWorld.searchById(1002))
        balls++;
      if (balls == 1){
        ballLives--;
				ball->setTranslation(0, 0, 0);

			}else{
				return true;
			}

      if (ballLives <= 0) {
        ballCanMove = false;
      }
    }
  }
	return false;
}

void update() {
  // printf("%d\n", bigPaddleTime);
  // if the game is paused then update nothing
  if (!paused) {
    if (bigPaddleTime > 0) {
      bigPaddleTime--;
    }
    // printf("Object list: \n");

    // // debug
    // for (it = myWorld.objlist.begin(); it != myWorld.objlist.end(); ++it) {
    //   printf("id: %4d - x: %5.2f y: %.2f z: %.2f \n", (*it)->getId(),
    //          (*it)->getMC().mat[0][3], (*it)->getMC().mat[1][3],
    //          (*it)->getMC().mat[2][3]);
    // }

    // printf("End List\n\n\n\n\n\n\n");

    std::list<Shape *>::iterator it;
    for (it = myWorld.objlist.begin(); it != myWorld.objlist.end(); ++it) {
      if ((*it)->getId() >= 2000) {
        int update = updateItem((*it));
        if (update == 0) {
          GLint type = (*it)->getType();
          if (type == 0)
            bigPaddleTime += 500;
          if (type == 1) {
            myWorld.createBall(0, 0);
            myWorld.createBall(0, 1);
          }
          it = myWorld.objlist.erase(it);
        }
        if (update == 2) {
          it = myWorld.objlist.erase(it);
        }
      }
    }

    // update ball if it's allowed to move
    if (ballCanMove == true) {
			for(int i =1000; i<1003; i++)
      if (myWorld.searchById(i)){
        if(updateBall(myWorld.searchById(i)))
					myWorld.deleteById(i);
			}
    }

    // load the next level if all blocks are destroyed (and haven't reached the
    // max level)
    if (myGeneration.blocksRemaining == 0 && myGeneration.currentLevel < 5) {
      myWorld.reset();
      myGeneration.blockGenerator(myGeneration.currentLevel + 1,
                                  myGeneration.currentLevel + 1, true);
    } else if (myGeneration.blocksRemaining == 0 &&
               myGeneration.currentLevel == 5) {
      ballCanMove = false;
      winGame = true;
    }
  }

  glutPostRedisplay();
}
void keyPress(unsigned char key, int x, int y) {
  // pause key (p or escape)
  if (key == 112 || key == 27) {
    if (paused)
      paused = 0;
    else
      paused = 1;
  }
  // restart key (r)
  if (key == 114) {
    myWorld.reset();

    // generate selected level
    myGeneration.blockGenerator(myGeneration.currentLevel,
                                myGeneration.currentDifficulty, false);
  }

  // debug win
  // if (key == )

  // delete before submit
  printf("%d\n", key);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(winWidth, winHeight);
  glutCreateWindow("3D Brick Breaker");
  init();
  menu();
  glutDisplayFunc(display);
  glutPassiveMotionFunc(mouseActionFcn);
  glutIdleFunc(update);
  glutKeyboardFunc(keyPress);

  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutMainLoop();
  return 0;
}

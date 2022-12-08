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
#include <time.h>

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
	// Default setting is for level 1 which isn't wireframe
  renderMode = SMOOTH;
  cullMode = GLCULL;
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
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

	// Move paddle to match mouse x position
  if (!paused) {
    Shape *paddle = myWorld.searchById(0);
    GLfloat x = xMouse;
    paddle->setX((x / 75) - 5.5);
    glutPostRedisplay();
  }
}

// Check collision of block and ball
GLboolean checkCollision(Shape *block, Shape *ball) {
  GLfloat blockX = block->getMC().mat[0][3];
  GLfloat blockZ = block->getMC().mat[2][3];
  GLfloat ballX = ball->getMC().mat[0][3];
  GLfloat ballZ = ball->getMC().mat[2][3];

  GLfloat blockWidth = 1;
  GLfloat blockHeight = 0.4;
  GLboolean destroy = false;
	// If ball is colliding block equation
  if (ballX > blockX - blockWidth && ballX < blockX + blockWidth &&
      ballZ > blockZ - blockHeight && ballZ < blockZ + blockHeight) {
		
		// If damaged past 0, return that it's been destroyed
    if (block->getCondition() == 0) {
      destroy = true;
    }

		// Damage block
    block->setCondition(block->getCondition() - 1);

		// If hit the side, bounce on x axis
    if (ballX < blockX - blockWidth * 0.95 ||
        ballX > blockX + blockWidth * 0.95)

      ball->setDirection(-ball->getDirection());
		// if hit top or bottom, bounce on y axis
    else
      ball->setDirection(3.1415 - ball->getDirection());
  }
	// return the status of the block
  return destroy;
}

int updateItem(Shape *item) {
  GLfloat speed = 0.04;

	// Get paddle location
  Shape *paddle = myWorld.searchById(0);
  GLfloat paddle_x = paddle->getMC().mat[0][3] + 0.3;

  GLfloat x = item->getMC().mat[0][3];
  GLfloat z = item->getMC().mat[2][3];

	// Move item down towards bottom
  item->translate2d(0, -speed);

	// If colliding with paddle, return collision with paddle
  if (z < -worldSize + 0.7f) {
    if (x > paddle_x - paddle_width && x < paddle_x + paddle_width) {
      return 0;
    }
  }
	// If out of world bounds (not paddle), return value to destroy it
  if (z < -worldSize) {
    return 2;
  }
  return 1;
}

int updateBall(Shape *ball) {

	// Check all other blocks for collision
  std::list<Shape *>::iterator it;
  for (it = myWorld.objlist.begin(); it != myWorld.objlist.end(); ++it) {
    if ((*it)->getId() < 1000 && (*it)->getId() > 0)
      if (checkCollision((*it), ball)) {
				// If block is destroyed, there is a 1/4 chance of spawning an item
        if (rand() % 4 == 0) {
          GLfloat x = (*it)->getMC().mat[0][3];
          GLfloat z = (*it)->getMC().mat[2][3];

          myWorld.createItem(x, z);
        }
				// Since block is destroyed, delete block
        it = myWorld.objlist.erase(it);
        myGeneration.blocksRemaining--; // update remaining block counter
      }
  }

	// Get paddle location
  Shape *paddle = myWorld.searchById(0);
  GLfloat paddle_x = paddle->getMC().mat[0][3] + 0.3;

  GLfloat speed = 0.06f;

	// Move ball along direction angle
  GLfloat direction = ball->getDirection();
  ball->translate2d(sin(direction) * speed, cos(direction) * speed);

  GLfloat x = ball->getMC().mat[0][3];
  GLfloat z = ball->getMC().mat[2][3];

	// Bounce off left and right walls
  if (x > worldSize || x < -worldSize) {
    ball->setDirection(-direction);
  }
	// Bounce off of top
  if (z > worldSize) {
    ball->setDirection(3.1415 - direction);
  }

	// Handle bottom of the world
  if (z < -worldSize + 0.7f) {

		// If the paddle is hit
    if (x > paddle_x - paddle_width && x < paddle_x + paddle_width) {

			// Make new direction based on where on the paddle it's hit
      GLfloat newDirection = 0;
      if (x > paddle_x) {

        newDirection = ((abs(paddle_x - x) / paddle_width) * 2) + 0.5;

      } else {
        newDirection = -((abs(paddle_x - x) / paddle_width) * 2) + 0.5;
      }

      ball->setDirection(newDirection);
		
		// Since paddle was not hit, delete the ball
    } else {
      int balls = 0;
      if (myWorld.searchById(1000))
        balls++;
      if (myWorld.searchById(1001))
        balls++;
      if (myWorld.searchById(1002))
        balls++;
			// If the last ball, take a life away and reset ball
      if (balls == 1) {
        ballLives--;
        ball->setTranslation(0, 0, 0);

      } else {
        return true;
      }

			// Handle end of game
      if (ballLives <= 0) {
        ballCanMove = false;
      }
    }
  }
  return false;
}

void update() {
  // if the game is paused then update nothing
  if (!paused) {
		// Countdown for big paddle timer
    if (bigPaddleTime > 0) {
      bigPaddleTime--;
			paddle_width=4;
			
    }else{
			paddle_width=2;
		}

		// Iterate through all objects
    std::list<Shape *>::iterator it;
    for (it = myWorld.objlist.begin(); it != myWorld.objlist.end(); ++it) {
			// If object id is > 2000, it's an item
      if ((*it)->getId() >= 2000) {
				// Handle update of item and get results
        int update = updateItem((*it));

				// This is true if the item is collected by the paddle
        if (update == 0) {
					// Handle the two types of items
          GLint type = (*it)->getType();
          if (type == 0)
            bigPaddleTime += 500;
          if (type == 1) {
            myWorld.createBall(0, 0);
            myWorld.createBall(0, 1);
          }
          it = myWorld.objlist.erase(it);
        }
				// If ball misses paddle, simply delete it
        if (update == 2) {
          it = myWorld.objlist.erase(it);
        }
      }
    }

    // update ball if it's allowed to move
    if (ballCanMove == true) {
      for (int i = 1000; i < 1003; i++)
        if (myWorld.searchById(i)) {
          if (updateBall(myWorld.searchById(i)))
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

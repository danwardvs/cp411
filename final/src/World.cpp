#include "World.hpp"
#include "Ball.hpp"
#include "Cube.hpp"
#include "Item.hpp"
#include "Paddle.hpp"
#include "UI/Hud.hpp"
#include "level/Generation.hpp"
#include <sstream>
#include <string>
#include <stdio.h>

extern GLint winWidth, winHeight;
extern Generation myGeneration;
extern Hud myHud;
extern bool ballCanMove;
extern int ballLives;
extern bool winGame;
extern int paused;
extern int bigPaddleTime;

using namespace std;

World::World() {
  Shape *obj = NULL;

  obj = new Paddle();
  obj->setId(0);
  obj->translate(0, 0, -5);
  objlist.push_back(obj);

  obj = new Ball(false);
  obj->setId(1000);
  obj->translate(0, 0, 0);
  objlist.push_back(obj);

  // obj = new Item();
  // obj->setId(2000);
  // obj->translate(0, 0, 0);
  // objlist.push_back(obj);

  // obj = new Ball();
  // obj->setId(1001);
  // obj->translate(2, 0, 1);
  // objlist.push_back(obj);

  // obj = new Ball();
  // obj->setId(1002);
  // obj->translate(-2, 0, 1);
  // objlist.push_back(obj);

  // start block generation for first level
  myGeneration.blockGenerator(1, 0, true);
}

World::~World() {
  Shape *obj;
  while (!objlist.empty()) {
    obj = objlist.front();
    objlist.pop_front();
    free(obj);
  }
}

void lineSegment(float x1, float y1, float z1, float x2, float y2, float z2) {
  glBegin(GL_LINES);
  glVertex3f(x1, y1, z1);
  glVertex3f(x2, y2, z2);
  glEnd();
}

void World::draw() {
  std::list<Shape *>::iterator it;
  for (it = objlist.begin(); it != objlist.end(); ++it) {
    (*it)->draw();
  }

  // create string for lives
  string livesText = "Lives:";
  ostringstream stream;
  stream << ballLives;
  livesText.append(stream.str());

  // print lives on screen
  myHud.drawHudElement(livesText, 0);

  // create string for level
  string levelText = "Level:";
  ostringstream stream2;
  stream2 << myGeneration.currentLevel;
  levelText.append(stream2.str());

  // print level on screen
  myHud.drawHudElement(levelText, 1);

  // indicate game is paused
  if (paused == 1) {
    string pausedText = "Paused: Press p or Esc to continue";
    myHud.drawHudElement(pausedText, 2);
  }

  // indicate game over
  if (ballLives <= 0) {
    // create string for hud (level)
    string gameOverText = "Game Over: Press R to restart the level";
    myHud.drawHudElement(gameOverText, 3);
  }
  // indicates game won
  else if (winGame == true) {
    // create string for hud (level)
    string WinText = "Congrats, you won!";
    myHud.drawHudElement(WinText, 4);
  }
}

void World::reset() {
  ballCanMove = false; // stop ball

  searchById(0)->setTranslation(0, 0, -5); // reset paddle
  for (int i = 5; i < 3000; i++) {
    deleteById(i);
  }

  createBall(0, 0);

  ballLives = 3;   // reset number of lives
  winGame = false; // reset win status
  paused = false;  // resume game
  bigPaddleTime = 0;
}
void World::createBall(GLfloat x, GLfloat z) {
  int id = 1000;
  Shape *ball1 = searchById(1000);
  Shape *ball2 = searchById(1001);
  Shape *ball3 = searchById(1002);
  if (ball1)
    printf("ball1\n");
  if (ball2)
    printf("ball2\n");
  if (ball3)
    printf("ball3\n");

  if (ball1 && ball2 && ball3) {
    printf("full\n");
    return;
  }
  if (!ball1)
    id = 1000;
  else if (!ball2)
    id = 1001;
  else
    id = 1002;

  printf("new ball: %d\n", id);
  Shape *obj;
  obj = new Ball(false);
  obj->setId(id);
  obj->translate(x, 0, z);
  objlist.push_back(obj);
}

void World::createItem(GLfloat x, GLfloat z) {
  Shape *obj = NULL;
  std::list<Shape *>::iterator it;
  int highest_item = 2000;
  for (it = objlist.begin(); it != objlist.end(); ++it) {
    if ((*it)->getId() > highest_item)
      highest_item = (*it)->getId();
  }

  obj = new Item(rand()%2);
  obj->setId(highest_item);
  obj->translate(x, 0, z);
  objlist.push_back(obj);
}

Shape *World::searchById(GLint i) {
  std::list<Shape *>::iterator it;
  for (it = objlist.begin(); it != objlist.end(); ++it) {
    if ((*it)->getId() == i)
      return *it;
  }
  return NULL;
}

void *World::deleteById(GLint i) {
  std::list<Shape *>::iterator it;
  for (it = objlist.begin(); it != objlist.end(); ++it) {
    if ((*it)->getId() == i) {
      it = objlist.erase(it);
      return NULL;
    }
  }
  return NULL;
}
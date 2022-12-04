#include "World.hpp"
#include "Cube.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "level/Generation.hpp"

#include <stdio.h>
#include <stdlib.h>

using namespace std;

extern GLint winWidth , winHeight;
extern Generation myGeneration;
extern bool ballCanMove;

World::World() {
	Shape *obj = NULL;

	obj = new Paddle();
	obj->setId(0);
	obj->translate(0, 0, -5);
	objlist.push_back(obj);

	obj = new Ball();
	obj->setId(1000);
	obj->translate(0, 0,0);
	objlist.push_back(obj);

	// obj = new Ball();
	// obj->setId(1001);
	// obj->translate(2, 0, 1);
	// objlist.push_back(obj);

	// obj = new Ball();
	// obj->setId(1002);
	// obj->translate(-2, 0, 1);
	// objlist.push_back(obj);

	// initial block generation for first level
	myGeneration.blockGenerator(1, 1);

	// allow ball to move once level is initially generated
	ballCanMove = true;
}

World::~World(){
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
	std::list<Shape*>::iterator it;
	for (it = objlist.begin(); it !=  objlist.end(); ++it) {
	  (*it)->draw();
    }
}

void World::reset(){
	Shape *obj = NULL;

	ballCanMove = false; //stop ball

	searchById(0)->setTranslation(0, 0, -5); //reset paddle
	searchById(1000)->setTranslation(0, 0, 0); //reset ball position (need to adjust)

	//delete all remaining blocks (not working)
	for (int i = 5; i < 1000; i++) {
		deleteById(i);
	}

	printf("objlist items reset= %d\n", objlist.size());

	//re-generate the current level (will generate new pattern with the way I set it up)
	myGeneration.blockGenerator(myGeneration.currentLevel, myGeneration.currentDifficulty);
	
	ballCanMove = true; //allow ball to move
}

Shape* World::searchById(GLint i) {
	std::list<Shape*>::iterator it;
	for (it = objlist.begin(); it !=  objlist.end(); ++it) {
	  if ((*it)->getId() == i) return *it;
    }
	return NULL;
}

void* World::deleteById(GLint i) {
	std::list<Shape*>::iterator it;
	for (it = objlist.begin(); it !=  objlist.end(); ++it) {
	  if ((*it)->getId() == i){
			it = objlist.erase(it);
			return NULL;
		}
  }
	return NULL;
}
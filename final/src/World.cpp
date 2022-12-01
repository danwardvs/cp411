#include "World.hpp"
#include "Cube.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"

using namespace std;

extern GLint winWidth , winHeight ;

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

	obj = new Ball();
	obj->setId(1001);
	obj->translate(2, 0, 1);
	objlist.push_back(obj);

	obj = new Ball();
	obj->setId(1002);
	obj->translate(-2, 0, 1);
	objlist.push_back(obj);

	//initial block generation for first level
	blockGeneration(1, 2);
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
	// glColor3f(1.0, 0.0, 0.0);
	// lineSegment(-2, 0, 0, 4, 0, 0); /* x-axis in red */
 	// glColor3f(0.0, 1.0, 0.0);
	// lineSegment(0, -2, 0, 0, 4, 0); /* y-axis in green */
	// glColor3f(0.0, 0.0, 1.0);
	// lineSegment(0, 0, -2, 0, 0, 4); /* z-axis in blue */

	std::list<Shape*>::iterator it;
	for (it = objlist.begin(); it !=  objlist.end(); ++it) {
	  (*it)->draw();
    }
}

void World::reset(){
	Shape *obj = NULL;

	obj = this->searchById(1);
	obj->reset();
	obj->setScale(0.5);
	obj->translate(2.5, 0, 0);

	obj = this->searchById(2);
	obj->reset();
	obj->setScale(0.5);
	obj->translate(4, 0, 0);

	obj = this->searchById(3);
	obj->reset();
	obj->setScale(0.5);

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

//generates the blocks and moves them based on the number of blocksPerRow + pattern
void World::layoutGeneration() {
	//generate based on certain patterns (need to determine said patterns)
	// ex normal, spaced (space between blocks in row), columns (space between columns of blocks), etc.
	// likely need switch statement to generate based on the pattern
	Shape *obj = NULL;

	//randomly pick pattern

	switch(pattern) {
		case normal:
			for (int i = 0; i < blockPerRow; i++) {
			for (int j = 0; j < 5; j++) {
				obj = new Cube();
				obj->setId(5 + i);
				obj->setCondition(difficulty);
				//i(x) = column, j(z) = row
				//needs to scale to more blocks (scale the blocks smaller)
				obj->translate(-3 + (i * 1.5), 0, j);
				objlist.push_back(obj);
				}
			}
			break;
		case spaced:
			//TODO
			break;
		case column:
			//TODO
			break;

	}

	
}

//determines the number of blocks used based on the level
void World::blockGeneration(int level, int level_difficulty) {
	switch(level) {
	case 1:
		blockPerRow = 5;
		break;
	case 2:
		blockPerRow = 15;
		break;
	case 3:
		blockPerRow = 25;
		break;
	case 4:
		blockPerRow = 30;
		break;
	case 5:
		blockPerRow = 50;
		break;
	}

	//generate the objlist for the blocks
	layoutGeneration();
}
#include "World.hpp"
#include "Cube.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"

using namespace std;

World::World() {
	Shape *obj = NULL;


	obj = new Cube();
	obj->setId(1);
	obj->translate(0, 0, 2);
	objlist.push_back(obj);

		obj = new Cube();
	obj->setId(1);
	obj->translate(0, 0, 3);
	objlist.push_back(obj);
	obj = new Cube();
	obj->setId(1);
	obj->translate(0, 0, 4);
	objlist.push_back(obj);

		obj = new Cube();
	obj->setId(1);
	obj->translate(1.5, 0, 2);
	objlist.push_back(obj);

		obj = new Cube();
	obj->setId(1);
	obj->translate(1.5, 0, 3);
	objlist.push_back(obj);
	obj = new Cube();
	obj->setId(1);
	obj->translate(1.5, 0, 4);
	objlist.push_back(obj);

			obj = new Cube();
	obj->setId(1);
	obj->translate(-1.5, 0, 2);
	objlist.push_back(obj);

		obj = new Cube();
	obj->setId(1);
	obj->translate(-1.5, 0, 3);
	objlist.push_back(obj);
	obj = new Cube();
	obj->setId(1);
	obj->translate(-1.5, 0, 4);
	objlist.push_back(obj);

	obj = new Ball();
	obj->setId(1000);
	obj->translate(0, 0,0);
	objlist.push_back(obj);

	// 	obj = new Ball();
	// obj->setId(1001);
	// obj->translate(2, 0, 1);
	// objlist.push_back(obj);

	// 	obj = new Ball();
	// obj->setId(1002);
	// obj->translate(-2, 0, 1);
	// objlist.push_back(obj);

			obj = new Cube();
	obj->setId(1);
	obj->translate(3, 0, 2);
	objlist.push_back(obj);

		obj = new Cube();
	obj->setId(1);
	obj->translate(3, 0, 3);
	objlist.push_back(obj);
	obj = new Cube();
	obj->setId(1);
	obj->translate(3, 0, 4);
	objlist.push_back(obj);

				obj = new Cube();
	obj->setId(1);
	obj->translate(-3, 0, 2);
	objlist.push_back(obj);

		obj = new Cube();
	obj->setId(1);
	obj->translate(-3, 0, 3);
	objlist.push_back(obj);
	obj = new Cube();
	obj->setId(1);
	obj->translate(-3, 0, 4);
	objlist.push_back(obj);



	obj = new Paddle();
	obj->setId(0);

	obj->translate(0, 0, -5);
	objlist.push_back(obj);
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


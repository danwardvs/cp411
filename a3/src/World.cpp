#include "World.hpp"
#include "Cube.hpp"
#include "Pyramid.hpp"
#include "House.hpp"

using namespace std;

World::World() {
/* add Cube into the world object list */
	Shape *obj = new Cube();
	obj->setId(1);
	objlist.push_back(obj);

	Shape *obj2 = new Pyramid();
	obj2->setId(2);
	objlist.push_back(obj2);

	Shape *obj3 = new House();
	obj3->setId(3);

	objlist.push_back(obj3);


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
	/* draw WCS cordinate axis */
	glColor3f(1.0, 0.0, 0.0);
	lineSegment(-2, 0, 0, 4, 0, 0); /* x-axis in red */
 	glColor3f(0.0, 1.0, 0.0);
	lineSegment(0, -2, 0, 0, 4, 0); /* y-axis in green */
	glColor3f(0.0, 0.0, 1.0);
	lineSegment(0, 0, -2, 0, 0, 4); /* z-axis in blue */

	std::list<Shape*>::iterator it;
	for (it = objlist.begin(); it !=  objlist.end(); ++it) {
	  (*it)->draw();
    }
}

void World::reset(){
	std::list<Shape*>::iterator it;
	int i = 0;
	for (it = objlist.begin(); it !=  objlist.end(); ++it) {

	  (*it)->reset();
		if(i==1)
		    (*it)->translate(2.5, 0, 0);
		if(i==0)
		  (*it)->translate(1.5, 0, 0);
		i++;
		}

}

Shape* World::searchById(GLint i) {
	std::list<Shape*>::iterator it;
	for (it = objlist.begin(); it !=  objlist.end(); ++it) {
	  if ((*it)->getId() == i) return *it;
    }
	return NULL;
}


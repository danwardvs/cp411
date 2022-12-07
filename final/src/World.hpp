/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-10-03
 */
#ifndef CWORLD_HPP
#define CWORLD_HPP

#include <iostream>
#include <list>
#include <vector>
#include "Shape.hpp"

class World {

public:
	std::list<Shape*> objlist;
	World();
	~World();
	void draw();   /* draw all objects in the world */
	void reset();  /* resets all objects */
	Shape *searchById(GLint i);
	void *deleteById(GLint i); 
	void createItem(GLfloat x, GLfloat z);
};

#endif

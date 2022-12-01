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

	// move to seperate class later
	int blockPerRow;
	int difficulty;
	BlockPattern pattern;
	void blockGeneration(int level, int difficulty);
	void layoutGeneration();
};

enum BlockPattern {
	normal,
	spaced,
	column,
};

#endif

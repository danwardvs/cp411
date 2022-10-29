/*
 * Description: SimpleView reference design
 * Author: HBF
 * Version: 2022-10-03
 */
#ifndef CHOUSE_H
#define CHOUSE_H

#include <GL/glut.h>
#include "Shape.hpp"
#include "Cube.hpp"
#include "Pyramid.hpp"
#include "Vector.hpp"

class House: public Shape {
protected:
	GLfloat vertex[9][3];  /* 2D array to store cube vertices */
	GLint face[6][4];      /* 2D array to store faces */
	GLfloat r, g, b;       /* color cube */

public:
	House();
	void draw();
	void drawFace(int);
	void drawPyramid();

};

#endif

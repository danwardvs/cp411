/*
 * Description: SimpleView reference design
 * Author: HBF
 * Version: 2022-10-03
 */
#ifndef CPYRAMID_H
#define CPYRAMID_H

#include <GL/glut.h>
#include "Shape.hpp"
#include "Vector.hpp"

class Pyramid: public Shape {
protected:
	GLfloat vertex[8][3];  /* 2D array to store pyramid vertices */
	GLint face[6][4];      /* 2D array to store faces */
	GLfloat r, g, b;       /* color pyramid */
public:
	Pyramid();
	void draw();
	void drawPyramid();
	void reset();
};

#endif

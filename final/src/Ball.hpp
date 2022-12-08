/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-10-06
 */
#ifndef Ball_HPP_
#define Ball_HPP_

#include <GL/gl.h>
#include <GL/glut.h>

#include "Cube.hpp"


class Ball: public Shape{
protected:

public:
	~Ball();
	Ball(int item);
	int item;

	void draw();
};


#endif /* Ball_HPP_ */

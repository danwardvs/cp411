/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-10-06
 */
#ifndef Item_HPP_
#define Item_HPP_

#include <GL/gl.h>
#include <GL/glut.h>

#include "Shape.hpp"


class Item: public Shape{
protected:

public:
	~Item();
	Item();

	void draw();
};


#endif /* Item_HPP_ */

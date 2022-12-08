#include "Item.hpp"
#include <GL/gl.h>
#include <stdio.h>
#include "Paddle.hpp"
#include "Ball.hpp"

extern RenderMode renderMode;



Item::Item(GLint newType)
{
type=newType;
  if(type==0){
    item = new Paddle();
    item->translate(0, 0, 0);
    item->scaleChange(-0.75);
  }
if(type==1){
    item = new Ball(true);
    item->translate(0, 0, 0);
    item->scaleChange(-0.75);
  }
}

Item::~Item()
{
}

void Item::draw()
{
      glPushMatrix();
    this->ctmMultiply();
    glColor3f(0.8, 0.2, 0.1);
        item->draw();

	glPopMatrix();

}


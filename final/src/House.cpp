/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-10-06
 */

#include "House.hpp"
#include <stdio.h>

House::House()
{

}

House::~House()
{
}

void House::draw()
{
    glPushMatrix();
    this->ctmMultiply();
   glutSolidSphere(1.0, 20, 16);

	glPopMatrix();
}

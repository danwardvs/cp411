/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2022-10-03
 */
#ifndef MENU_HPP_
#define MENU_HPP_

#include <GL/glut.h>

void menu();
void mainMenu(GLint option);

void cullMenu(GLint option);
void shadeMenu(GLint option);
void levelMenu(GLint option);

#endif

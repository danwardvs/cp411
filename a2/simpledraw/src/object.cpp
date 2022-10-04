/*
 * Description: implementation of object.hpp
 * Author: HBF
 * Version: 2021-08-24
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "object.hpp"


void insert(LIST *list, SHAPE *object) {
	if (object == NULL) return;

	NODE *p = (NODE*) malloc(sizeof(NODE));
	p->object = object;
	p->prev = NULL;
	p->next = NULL;

	if (list->start == NULL) {
		list->start = p;
		list->end = p;
	} else {
		list->end->next = p;
		p->prev = list->end;
		list->end = p;
	}
}


void deleteNode(LIST *list, NODE **selectp) {
// ...
}

void clearList(LIST *list) {
// ...
}

void drawShape(SHAPE *object) {
	if (object->type == RECTANGLE) {  // rectangle
		printf(" a rectangle");
	  // draw filled rectangle
		glColor3f(object->fr, object->fg, object->fb);
		glBegin(GL_QUADS);
		glVertex2i(object->x1, object->y1);
		glVertex2i(object->x1, object->y2);
		glVertex2i(object->x2, object->y2);
		glVertex2i(object->x2, object->y1);
		glEnd();
		
		// stroke outline of rectangle
		glColor3f(object->sr, object->sg, object->sb);
		glLineWidth(object->swidth);
		glBegin(GL_LINE_LOOP);
		glVertex2i(object->x1, object->y1);
		glVertex2i(object->x1, object->y2);
		glVertex2i(object->x2, object->y2);
		glVertex2i(object->x2, object->y1);
		glEnd();
		
	

	} else if (object->type == CIRCLE) {  // circle
		// draw filled circle
		// draw outline
	}
}

void drawShapeHighLight(SHAPE *object) {
	// draw outline with high light color
}

void drawList(LIST *list) {
	NODE *p = list->start;
	while (p) {
		drawShape(p->object);
		printf("Printing");
		p = p->next;
	}
}

void setPixel(GLint x, GLint y) {
	glPointSize(2.0);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

// draw points on line of circle
void circlePlotPoints(const GLint& xc, const GLint& yc, const GLint& x,
		const GLint& y) {
// ...
}

// draw circle main function
void circleMidpoint(GLint x1, GLint y1, GLint x2, GLint y2) {
	// ...
}

void circlePlotPointsFill(GLint x1, GLint y1, GLint x, GLint y) {
	// ...
}

void circleMidpointFill(GLint x1, GLint y1, GLint x2, GLint y2) {
	// ...
}

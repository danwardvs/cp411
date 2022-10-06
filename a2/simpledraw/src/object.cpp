/*
 * Description: implementation of object.hpp
 * Author: HBF
 * Version: 2021-08-24
 */

#include "object.hpp"
#include <GL/glut.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

extern TYPE objType;
extern NODE *selectNode;
extern GLint strokeWidth;
extern GLfloat fillred;
extern GLfloat fillgreen;
extern GLfloat fillblue;
extern GLfloat sred;
extern GLfloat sgreen;
extern GLfloat sblue;

void insert(LIST *list, SHAPE *object) {
  if (object == NULL)
    return;

  NODE *p = (NODE *)malloc(sizeof(NODE));
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

  NODE *node = *selectp;

  if (selectp == NULL)
    return;
  if (list == NULL)
    return;

  if (list->start == node) {
    list->start = node->next;
  }

  if (node->next != NULL) {
    node->next->prev = node->prev;
  }
  if (node->prev != NULL) {
    node->prev->next = node->next;
  }
  // free(node);
  return;
}

void clearList(LIST *list) {
  list->end = NULL;
  list->start = NULL;

  objType = RECTANGLE;
  fillred = 1.0;
  fillgreen = 0.0;
  fillblue = 0.0;
  sred = 1.0;
  sgreen = 0.0;
  sblue = 0.0;
  strokeWidth = 1;

  selectNode = NULL;
}

void printObj(SHAPE obj) {
  printf("Type: %d\n", obj.type);
  printf("x1:   %d\n", obj.x1);
  printf("x2:   %d\n", obj.x2);
  printf("y1:   %d\n", obj.y1);
  printf("y2:   %d\n", obj.y2);

  printf("fr:   %.2f\n", obj.fr);
  printf("fg:   %.2f\n", obj.fg);
  printf("fb:   %.2f\n", obj.fb);
}

void drawShape(SHAPE *object) {
  if (object->type == RECTANGLE) { // rectangle
    // printObj(*object);
    //  draw filled rectangle
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

  } else if (object->type == CIRCLE) { // circle
    int x1 = object->x1;
    int y1 = object->y1;
    int x2 = object->x2;
    int y2 = object->y2;
    // printf("%d",x1);

    glColor3f(object->fr, object->fg, object->fb);
    circleMidpointFill(x1, y1, x2, y2);

    glColor3f(object->sr, object->sg, object->sb);

    circleMidpoint(x1, y1, x2, y2);

    // draw outline
  }
}

void drawShapeHighLight(SHAPE *object) {
  glColor3f(1, 1, 0);

  int x1 = object->x1;
  int y1 = object->y1;
  int x2 = object->x2;
  int y2 = object->y2;
  if (object->type == RECTANGLE) {
    // stroke outline of rectangle

    glLineWidth(object->swidth);
    glBegin(GL_LINE_LOOP);
    glVertex2i(x1, y1);
    glVertex2i(x1, y2);
    glVertex2i(x2, y2);
    glVertex2i(x2, y1);
    glEnd();
  }
  if (object->type == CIRCLE) {
    circleMidpoint(x1, y1, x2, y2);
  }
}

void drawList(LIST *list) {
  NODE *p = list->start;
  while (p) {
    drawShape(p->object);
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
void circlePlotPoints(const GLint &xc, const GLint &yc, const GLint &x,
                      const GLint &y) {
  setPixel(xc + x, yc + y);
  setPixel(xc - x, yc + y);
  setPixel(xc + x, yc - y);
  setPixel(xc - x, yc - y);
  setPixel(xc + y, yc + x);
  setPixel(xc - y, yc + x);
  setPixel(xc + y, yc - x);
  setPixel(xc - y, yc - x);
}

// draw circle main function
void circleMidpoint(GLint x1, GLint y1, GLint x2, GLint y2) {
  int r = ceil(sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));

  int yc = y1;
  int xc = x1;
  GLint p = 1 - r;    // Initial value of midpoint parameter.
  GLint x = 0, y = r; // Set coordinates for top point of circle.
  /* Plot the initial point in each circle quadrant. */
  circlePlotPoints(xc, yc, x, y);

  while (x < y) {
    x++;
    if (p < 0)
      p += 2 * x + 1;
    else {
      y--;
      p += 2 * (x - y) + 1;
    }
    circlePlotPoints(xc, yc, x, y);
  }
}

void circlePlotPointsFill(GLint x1, GLint y1, GLint x, GLint y) {
  int xc = x1;
  int yc = y1;
  glLineWidth(2.0);
  glBegin(GL_LINES);
  glVertex2i(xc - x, yc + y);
  glVertex2i(xc + x, yc + y);
  glVertex2i(xc - x, yc - y);
  glVertex2i(xc + x, yc - y);
  glVertex2i(xc - y, yc + x);
  glVertex2i(xc + y, yc + x);
  glVertex2i(xc - y, yc - x);
  glVertex2i(xc + y, yc - x);
  glEnd();
}

void circleMidpointFill(GLint x1, GLint y1, GLint x2, GLint y2) {
  int r = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
  int yc = y1;
  int xc = x1;
  GLint p = 1 - r;    // Initial value of midpoint parameter.
  GLint x = 0, y = r; // Set coordinates for top point of circle.
  /* Plot the initial point in each circle quadrant. */
  circlePlotPointsFill(xc, yc, x, y);
  while (x < y) {
    x++;
    if (p < 0)
      p += 2 * x + 1;
    else {
      y--;
      p += 2 * (x - y) + 1;
    }
    circlePlotPointsFill(xc, yc, x, y);
  }
}

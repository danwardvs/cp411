/*
 * Description: implementation of edit.hpp
 * Author: HBF
 * Version: 2021-08-24
 */

#include "object.hpp"
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

extern LIST objlist;
extern NODE *selectNode;
extern void deleteNode(LIST *list, NODE **selectp);

GLint min(GLint x, GLint y) { return x < y ? x : y; }

GLint max(GLint x, GLint y) {
  if (x < y)
    return y;
  else
    return x;
}

NODE *select(GLint x, GLint y) {

  NODE *ptr = objlist.end;
  while (ptr != NULL) {
    if (ptr->object->type == RECTANGLE) {
      int x1 =
          ptr->object->x1 > ptr->object->x2 ? ptr->object->x2 : ptr->object->x1;
      int x2 =
          ptr->object->x1 > ptr->object->x2 ? ptr->object->x1 : ptr->object->x2;

      int y1 =
          ptr->object->y1 > ptr->object->y2 ? ptr->object->y2 : ptr->object->y1;
      int y2 =
          ptr->object->y1 > ptr->object->y2 ? ptr->object->y1 : ptr->object->y2;

      if (x1 < x && x2 > x && y1 < y && y2 > y)
        return ptr;
    }

    if (ptr->object->type == CIRCLE) {
      int x1 = ptr->object->x1;
      int y1 = ptr->object->y1;
      int y2 = ptr->object->y2;
      int x2 = ptr->object->x2;

      int circle_r = ceil(sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
      int mouse_r = ceil(sqrt(pow(x - x1, 2) + pow(y - y1, 2)));
      if (circle_r >= mouse_r)
        return ptr;
    }

    ptr = ptr->prev;
  }

  return NULL;
}

void Delete(NODE **pp) {
  deleteNode(&objlist, pp);
  selectNode = NULL;
}

void moveBack(NODE *p) {

  if (objlist.end == objlist.start || objlist.end == p)
    return;

  if (objlist.start == p) {
    objlist.start = objlist.start->next;
    objlist.start->prev = NULL;

  } else {
    p->prev->next = p->next;
    p->next->prev = p->prev;
  }
  objlist.end->next = p;
  p->next = NULL;
  p->prev = objlist.end;
  objlist.end = p;
}

void moveFront(NODE *p) {
  if (objlist.start == objlist.end || objlist.start == p)
    return;

  if (objlist.end == p) {
    objlist.end = objlist.end->prev;
    objlist.end->next = NULL;

  } else {
    p->next->prev = p->prev;
    p->prev->next = p->next;
  }
  objlist.start->prev = p;
  p->prev = NULL;
  p->next = objlist.start;
  objlist.start = p;
}

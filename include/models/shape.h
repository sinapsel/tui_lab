#pragma once
#include <math.h>
#include <stdlib.h>
#include "canvas.h"

typedef struct Shape Shape;

typedef struct ShapeVtbl {
    double (*area)(Shape* self);
    void (*draw)(Shape* self, Canvas* canvas, int x, int y);
    void (*destroy)(Shape* self);
} ShapeVtbl;

struct Shape {
    ShapeVtbl* vptr;
};

Shape* shape_create_rectangle(double width, double height);
Shape* shape_create_triangle(double base, double height);


double area(Shape* self);
void draw(Shape* self, Canvas* canvas, int x, int y);
void destroy(Shape* self);
#include "models/circle.h"


typedef struct {
    Shape base;
    double radius;
} Circle;

static double circle_area(Shape* self) {
    Circle* c = (Circle*)self;
    if (c->radius <= 0) return -1.0;
    return acos(-1.0) * c->radius * c->radius;
}

static void circle_draw(Shape* self, Canvas* canvas, int x, int y) {
    Circle* c = (Circle*)self;
    int r = (int)c->radius;
    if (r <= 0) {
        canvas->draw_text(canvas, x, y, "Invalid radius");
        return;
    }
    for (int dy = -r; dy <= r; dy++) {
        int dx = (int)sqrt(r * r - dy * dy);
        if (dx > 0) {
            canvas->draw_point(canvas, x - dx, y + dy, '*');
            canvas->draw_point(canvas, x + dx, y + dy, '*');
        } else {
            canvas->draw_point(canvas, x, y + dy, '*');
        }
    }
}

static void circle_destroy(Shape* self) {
    free(self);
}

static ShapeVtbl circle_vtbl = {
    .area = circle_area,
    .draw = circle_draw,
    .destroy = circle_destroy
};

Shape* shape_create_circle(double radius) {
    Circle* c = malloc(sizeof(Circle));
    c->base.vptr = &circle_vtbl;
    c->radius = radius;
    return (Shape*)c;
}
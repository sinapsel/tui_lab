#include "models/shape.h"


typedef struct {
    Shape base;
    double width;
    double height;
} Rectangle;

static double rectangle_area(Shape* self) {
    Rectangle* r = (Rectangle*)self;
    if (r->width <= 0 || r->height <= 0) abort();
    return r->width * r->height;
}

static void rectangle_draw(Shape* self, Canvas* canvas, int x, int y) {
    Rectangle* r = (Rectangle*)self;
    int w = (int)r->width;
    int h = (int)r->height;
    if (w <= 0 || h <= 0) {
        canvas->draw_text(canvas, x, y, "Invalid size");
        return;
    }
    for (int i = 0; i < w; i++) {
        canvas->draw_point(canvas, x + i, y, '*');
        if (h > 1)
            canvas->draw_point(canvas, x + i, y + h - 1, '*');
    }
    for (int j = 1; j < h - 1; j++) {
        canvas->draw_point(canvas, x, y + j, '*');
        canvas->draw_point(canvas, x + w - 1, y + j, '*');
    }
}

static void rectangle_destroy(Shape* self) {
    free(self);
}

static ShapeVtbl rectangle_vtbl = {
    .area = rectangle_area,
    .draw = rectangle_draw,
    .destroy = rectangle_destroy
};

Shape* shape_create_rectangle(double width, double height) {
    Rectangle* r = malloc(sizeof(Rectangle));
    r->base.vptr = &rectangle_vtbl;
    r->width = width;
    r->height = height;
    return (Shape*)r;
}
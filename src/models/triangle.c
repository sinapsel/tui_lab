#include "models/shape.h"


typedef struct {
    Shape base;
    double base_len;
    double height;
} Triangle;

static double triangle_area(Shape* self) {
    Triangle* t = (Triangle*)self;
    if (t->base_len <= 0 || t->height <= 0) return -1.0;
    return 0.5 * t->base_len * t->height;
}

static void triangle_draw(Shape* self, Canvas* canvas, int x, int y) {
    Triangle* t = (Triangle*)self;
    int w = (int)t->base_len;
    int h = (int)t->height;
    if (w <= 0 || h <= 0) {
        draw_text(canvas, x, y, "Invalid size");
        return;
    }
    for (int row = 0; row < h; row++) {
        int line_width = (row * w) / h; 
        for (int col = 0; col <= line_width; col++) {
            canvas->draw_point(canvas, x + col, y + row, '*');
        }
    }
}

static void triangle_destroy(Shape* self) {
    free(self);
}

static ShapeVtbl triangle_vtbl = {
    .area = triangle_area,
    .draw = triangle_draw,
    .destroy = triangle_destroy
};

Shape* shape_create_triangle(double base, double height) {
    Triangle* t = malloc(sizeof(Triangle));
    t->base.vptr = &triangle_vtbl;
    t->base_len = base;
    t->height = height;
    return (Shape*)t;
}

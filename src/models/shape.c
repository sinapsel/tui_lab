#include "models/shape.h"


double area(Shape* self) {
    return self->vptr->area(self);
}
void draw(Shape* self, Canvas* canvas, int x, int y) {
    return self->vptr->draw(self, canvas, x, y);
}
void destroy(Shape* self) {
    return self->vptr->destroy(self);
}
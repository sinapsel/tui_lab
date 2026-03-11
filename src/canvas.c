#include "canvas.h"

void draw_text(struct Canvas* self, int x, int y, const char* text) {
    return self->draw_text(self, x, y, text);
}
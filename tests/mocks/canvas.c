#include "canvas.h"

typedef struct Canvas {
    void (*draw_point)(struct Canvas* self, int x, int y, char ch);
    void (*draw_line)(struct Canvas* self, int x1, int y1, int x2, int y2, char ch);
    void (*draw_text)(struct Canvas* self, int x, int y, const char* text);
} Canvas;

void __wrap_draw_text(Canvas* self, int x, int y, const char* text) {
   ((MockedCanvas*)self)->drawed_text = text;
}

extern void __real_draw_text(Canvas* self, int x, int y, const char* text);
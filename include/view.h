#pragma once

#include "models/shape.h"
#include <stddef.h>
#include <ncursesw/ncurses.h>

typedef struct UI UI;

UI* ui_init(void);
void ui_cleanup(UI* ui);

void ui_draw_menu(UI* ui, int current_shape);
void ui_draw_input_fields(UI* ui, double val1, double val2, int focused_field);
void ui_draw_buttons(UI* ui, int focused_button);
void ui_draw_drawing_area(UI* ui, Shape* shape);
void ui_draw_status(UI* ui, double area, const wchar_t* message);

void ui_refresh_all(UI* ui);

WINDOW* ui_get_menu_win(UI* ui);
WINDOW* ui_get_input_win(UI* ui);
WINDOW* ui_get_button_win(UI* ui);
WINDOW* ui_get_draw_win(UI* ui);
WINDOW* ui_get_status_win(UI* ui);

#include "controller.h"
#include <stdlib.h>
#include <wchar.h>

typedef enum { SHAPE_CIRCLE, SHAPE_RECT, SHAPE_TRI } ShapeType;
typedef enum { FOCUS_MENU, FOCUS_FIELD1, FOCUS_FIELD2, FOCUS_BUTTON_DRAW, FOCUS_BUTTON_AREA } Focus;

struct Controller {
    UI* ui;
    Shape* current_shape;
    ShapeType shape_type;
    double param1, param2;
    Focus focus;
    double last_area;
    wchar_t message[128];
};

static void update_shape(Controller* ctrl) {
    if (ctrl->current_shape) {
        destroy(ctrl->current_shape);
    }
    switch (ctrl->shape_type) {
        case SHAPE_CIRCLE:
            ctrl->current_shape = shape_create_circle(ctrl->param1);
            break;
        case SHAPE_RECT:
            ctrl->current_shape = shape_create_rectangle(ctrl->param1, ctrl->param2);
            break;
        case SHAPE_TRI:
            ctrl->current_shape = shape_create_triangle(ctrl->param1, ctrl->param2);
            break;
    }
}

static void draw_shape(Controller* ctrl) {
    update_shape(ctrl);
    ui_draw_drawing_area(ctrl->ui, ctrl->current_shape);
}

static void compute_area(Controller* ctrl) {
    if (!ctrl->current_shape) update_shape(ctrl);
    ctrl->last_area = area(ctrl->current_shape);
    if (ctrl->last_area < 0) {
        wcscpy(ctrl->message, L"Ошибка: некорректные параметры");
    } else {
        wcscpy(ctrl->message, L"");
    }
    ui_draw_status(ctrl->ui, ctrl->last_area, ctrl->message);
}

static void edit_field(Controller* ctrl, int field) {
    WINDOW* win = ui_get_input_win(ctrl->ui);
    wmove(win, field+1, 20);
    wclrtoeol(win);
    wrefresh(win);
    echo();
    curs_set(1);
    wchar_t input[32];
    mvwgetn_wstr(win, field+1, 20, input, 31);
    noecho();
    curs_set(0);
    double val = wcstod(input, NULL);
    if (field == 0) ctrl->param1 = val;
    else ctrl->param2 = val;
    update_shape(ctrl);
    ui_draw_input_fields(ctrl->ui, ctrl->param1, ctrl->param2, ctrl->focus == FOCUS_FIELD1 ? 0 : (ctrl->focus == FOCUS_FIELD2 ? 1 : -1));
}

Controller* controller_create(void) {
    Controller* ctrl = malloc(sizeof(Controller));
    ctrl->ui = ui_init();
    ctrl->current_shape = NULL;
    ctrl->shape_type = SHAPE_CIRCLE;
    ctrl->param1 = 5.0;
    ctrl->param2 = 3.0;
    ctrl->focus = FOCUS_MENU;
    ctrl->last_area = -1;
    wcscpy(ctrl->message, L"Добро пожаловать!");
    update_shape(ctrl);
    return ctrl;
}

void controller_destroy(Controller* ctrl) {
    if (ctrl->current_shape) destroy(ctrl->current_shape);
    ui_cleanup(ctrl->ui);
    free(ctrl);
}

void controller_run(Controller* ctrl) {
    int ch;
    while (1) {
        ui_draw_menu(ctrl->ui, ctrl->shape_type);
        int focused_field = -1;
        if (ctrl->focus == FOCUS_FIELD1) focused_field = 0;
        else if (ctrl->focus == FOCUS_FIELD2) focused_field = 1;
        ui_draw_input_fields(ctrl->ui, ctrl->param1, ctrl->param2, focused_field);
        int focused_button = -1;
        if (ctrl->focus == FOCUS_BUTTON_DRAW) focused_button = 0;
        else if (ctrl->focus == FOCUS_BUTTON_AREA) focused_button = 1;
        ui_draw_buttons(ctrl->ui, focused_button);
        ui_draw_drawing_area(ctrl->ui, ctrl->current_shape);
        ui_draw_status(ctrl->ui, ctrl->last_area, ctrl->message);
        ui_refresh_all(ctrl->ui);

        ch = getch();
        switch (ch) {
            case 'q': case 'Q':
                return;
            case '\t': // Tab
                ctrl->focus = (ctrl->focus + 1) % 5;
                break;
            case '\n': case '\r': case KEY_ENTER:
                switch (ctrl->focus) {
                    case FOCUS_MENU:
                        ctrl->shape_type = (ctrl->shape_type + 1) % 3;
                        update_shape(ctrl);
                        break;
                    case FOCUS_FIELD1:
                        edit_field(ctrl, 0);
                        break;
                    case FOCUS_FIELD2:
                        edit_field(ctrl, 1);
                        break;
                    case FOCUS_BUTTON_DRAW:
                        draw_shape(ctrl);
                        break;
                    case FOCUS_BUTTON_AREA:
                        compute_area(ctrl);
                        break;
                }
                break;
            default:
                break;
        }
    }
}
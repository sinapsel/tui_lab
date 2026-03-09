#include "view.h"
#include "models/shape.h"
#include "canvas.h"
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>

struct UI {
    WINDOW *menu_win;
    WINDOW *input_win;
    WINDOW *button_win;
    WINDOW *draw_win;
    WINDOW *status_win;
};

typedef struct {
    Canvas base;
    WINDOW* win;
} NcursesCanvas;

static void ncurses_draw_point(Canvas* self, int x, int y, char ch) {
    NcursesCanvas* nc = (NcursesCanvas*)self;
    int maxy = getmaxy(nc->win);
    int maxx = getmaxx(nc->win);
    if (x >= 0 && x < maxx && y >= 0 && y < maxy) {
        mvwaddch(nc->win, y, x, ch);
    }
}

static void ncurses_draw_line(Canvas* self, int x1, int y1, int x2, int y2, char ch) {
    if (y1 == y2) {
        int xmin = (x1 < x2) ? x1 : x2;
        int xmax = (x1 > x2) ? x1 : x2;
        for (int x = xmin; x <= xmax; x++) {
            ncurses_draw_point(self, x, y1, ch);
        }
    } else if (x1 == x2) {
        int ymin = (y1 < y2) ? y1 : y2;
        int ymax = (y1 > y2) ? y1 : y2;
        for (int y = ymin; y <= ymax; y++) {
            ncurses_draw_point(self, x1, y, ch);
        }
    } else {
        // TODO: в качестве упражнения как рисовать наклонные
    }
}

static void ncurses_draw_text(Canvas* self, int x, int y, const char* text) {
    NcursesCanvas* nc = (NcursesCanvas*)self;
    mvwaddstr(nc->win, y, x, text);
}

static Canvas* create_ncurses_canvas(WINDOW* win) {
    NcursesCanvas* nc = malloc(sizeof(NcursesCanvas));
    nc->base.draw_point = ncurses_draw_point;
    nc->base.draw_line = ncurses_draw_line;
    nc->base.draw_text = ncurses_draw_text;
    nc->win = win;
    return (Canvas*)nc;
}

static void destroy_ncurses_canvas(Canvas* canvas) {
    free(canvas);
}

UI* ui_init(void) {
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    int height, width;
    getmaxyx(stdscr, height, width);

    UI* ui = malloc(sizeof(UI));
    ui->menu_win = newwin(3, width, 0, 0);
    ui->input_win = newwin(5, width, 3, 0);
    ui->button_win = newwin(3, width, 8, 0);
    ui->draw_win = newwin(height - 13, width, 11, 0);
    ui->status_win = newwin(2, width, height - 2, 0);

    return ui;
}

void ui_cleanup(UI* ui) {
    delwin(ui->menu_win);
    delwin(ui->input_win);
    delwin(ui->button_win);
    delwin(ui->draw_win);
    delwin(ui->status_win);
    endwin();
    free(ui);
}

void ui_draw_menu(UI* ui, int current_shape) {
    werase(ui->menu_win);
    box(ui->menu_win, 0, 0);
    const wchar_t* items[] = { L"Круг", L"Прямоугольник", L"Треугольник" };
    int x = 2;
    for (int i = 0; i < 3; i++) {
        if (i == current_shape)
            wattron(ui->menu_win, A_REVERSE);
        mvwaddwstr(ui->menu_win, 1, x, items[i]);
        if (i == current_shape)
            wattroff(ui->menu_win, A_REVERSE);
        x += wcslen(items[i]) + 4;
    }
    wrefresh(ui->menu_win);
}

void ui_draw_input_fields(UI* ui, double val1, double val2, int focused_field) {
    werase(ui->input_win);
    box(ui->input_win, 0, 0);
    mvwaddwstr(ui->input_win, 1, 2, L"Параметр 1:");
    mvwaddwstr(ui->input_win, 2, 2, L"Параметр 2:");

    wchar_t buf1[32], buf2[32];
    swprintf(buf1, 32, L"%.2f", val1);
    swprintf(buf2, 32, L"%.2f", val2);

    if (focused_field == 0) wattron(ui->input_win, A_REVERSE);
    mvwaddwstr(ui->input_win, 1, 20, buf1);
    if (focused_field == 0) wattroff(ui->input_win, A_REVERSE);

    if (focused_field == 1) wattron(ui->input_win, A_REVERSE);
    mvwaddwstr(ui->input_win, 2, 20, buf2);
    if (focused_field == 1) wattroff(ui->input_win, A_REVERSE);

    wrefresh(ui->input_win);
}

void ui_draw_buttons(UI* ui, int focused_button) {
    werase(ui->button_win);
    box(ui->button_win, 0, 0);
    const wchar_t* draw_label = L"[ Нарисовать ]";
    const wchar_t* area_label = L"[ Площадь ]";

    if (focused_button == 0) wattron(ui->button_win, A_REVERSE);
    mvwaddwstr(ui->button_win, 1, 5, draw_label);
    if (focused_button == 0) wattroff(ui->button_win, A_REVERSE);

    if (focused_button == 1) wattron(ui->button_win, A_REVERSE);
    mvwaddwstr(ui->button_win, 1, 25, area_label);
    if (focused_button == 1) wattroff(ui->button_win, A_REVERSE);

    wrefresh(ui->button_win);
}

void ui_draw_drawing_area(UI* ui, Shape* shape) {
    werase(ui->draw_win);
    box(ui->draw_win, 0, 0);
    if (shape) {
        int maxy = getmaxy(ui->draw_win);
        int maxx = getmaxx(ui->draw_win);
        int center_x = maxx / 2;
        int center_y = maxy / 2;
        Canvas* canvas = create_ncurses_canvas(ui->draw_win);
        draw(shape, canvas, center_x, center_y);
        destroy_ncurses_canvas(canvas);
    } else {
        mvwaddwstr(ui->draw_win, 1, 2, L"Нет фигуры");
    }
    wrefresh(ui->draw_win);
}

void ui_draw_status(UI* ui, double area, const wchar_t* message) {
    werase(ui->status_win);
    box(ui->status_win, 0, 0);
    if (area >= 0) {
        wchar_t buf[64];
        swprintf(buf, 64, L"Площадь: %.2f", area);
        mvwaddwstr(ui->status_win, 0, 2, buf);
    }
    if (message) {
        mvwaddwstr(ui->status_win, 1, 2, message);
    }
    wrefresh(ui->status_win);
}

void ui_refresh_all(UI* ui) {
    // wrefresh(ui->status_win);
}

WINDOW* ui_get_menu_win(UI* ui) { return ui->menu_win; }
WINDOW* ui_get_input_win(UI* ui) { return ui->input_win; }
WINDOW* ui_get_button_win(UI* ui) { return ui->button_win; }
WINDOW* ui_get_draw_win(UI* ui) { return ui->draw_win; }
WINDOW* ui_get_status_win(UI* ui) { return ui->status_win; }
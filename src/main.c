#include "controller.h"

int main(void) {
    Controller* ctrl = controller_create();
    controller_run(ctrl);
    controller_destroy(ctrl);
    return 0;
}
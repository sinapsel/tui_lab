#pragma once

#include "models/shape.h"
#include "models/circle.h"
#include "view.h"

typedef struct Controller Controller;

Controller* controller_create(void);
void controller_destroy(Controller* ctrl);
void controller_run(Controller* ctrl);


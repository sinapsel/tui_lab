#include <stdio.h>

void __wrap_abort() {
    fprintf(stderr, "FATAL ERROR OCCURED@ABORTION!");
}

extern void __real_abort();
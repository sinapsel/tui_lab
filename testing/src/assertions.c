
#include "assertions.h"

static size_t success_count = 0;
static size_t fail_count = 0;
static size_t success_count_local = 0;
static size_t fail_count_local = 0;

void inc_success() {
    success_count++; success_count_local++;
}

void inc_fail() {
    fail_count++; fail_count_local++;
}

int pop_fail() {
    int tmp = fail_count_local;
    fail_count_local = 0;
    return tmp;
}

int pop_success() {
    int tmp = success_count_local;
    success_count_local = 0;
    return tmp;
}


int assert_fail(const char* expr, const char* file, size_t lineno) {
	fprintf(stderr, "\033[0;31m%s:%d:\t %s FAILED \033[0m\n", file, lineno, expr);
    inc_fail();
    return 0;
}

int assert_success(const char* expr, const char* file, size_t lineno) {
    fprintf(stderr, "\033[0;32m%s:%d:\t %s PASSED \033[0m\n", file, lineno, expr);    inc_success();
    return 0;
}

int print_stats(){
    fprintf(stderr, "\n\n%d of %d tests passed. %.2f SUCCEEDED\n", 
        success_count,
         fail_count+success_count, 
        (float)success_count/(float)(fail_count+success_count)
    );
    return fail_count == 0;
}
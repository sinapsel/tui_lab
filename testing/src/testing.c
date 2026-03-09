#include "testing.h"

static _test* head = NULL;
static _test* tail = NULL;


void register_test(const char* name, test_func test) {
    _test* tmp = malloc(sizeof(_test));
    tmp->name = name;
    tmp->test = test;
    tmp->next = NULL;
    if (head == NULL && tail == NULL) {
        head = tmp;
        tail = tmp;
        return;
    }
    tail->next = tmp;
    tail = tmp;
}

void run_test() {
    for (_test* t = head; t != NULL; t=t->next) {
        fprintf(stderr, "\n===TESTING CASE: %s===\n\n", t->name);
        t->test();
        int succs = pop_success();
        int all = pop_fail() + succs;
        fprintf(stderr, "\n===%d of %d tests passed"
            "%.2f SUCCEEDED"
            "===\n\n", succs, all,
            (float)succs/(float)all
        );

    }
}
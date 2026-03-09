#pragma once
#include <stdio.h>

int assert_success(const char *expr, const char *file, size_t lineno);
int assert_fail(const char *expr, const char *file, size_t lineno);
int print_stats();

void inc_success();
void inc_fail();
int pop_fail();
int pop_success();

#define assert(expr)                                 \
    ((!!(expr))                                      \
         ? assert_success(#expr, __FILE__, __LINE__) \
         : assert_fail(#expr, __FILE__, __LINE__))

#define assert_eq(expr, expected)                     \
    (((expr == expected))                             \
         ? assert_success(#expr (expr) " = " #expected, __FILE__, __LINE__) \
         : assert_fail(#expr " != " #expected, __FILE__, __LINE__))
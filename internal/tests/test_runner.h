/* vi: set sw=8 ts=8: (internal/tests/test_runner.h) */
#include <stdio.h>

#define GREEN "\x1b[32m"
#define RED "\x1b[31m"
#define RESET "\x1b[0m"

static int tests_failed = 0;

#define RUN(test)                                         \
        do {                                              \
                printf("[ ] %s\n", #test);                \
                test();                                   \
                printf(GREEN "[✓]" RESET " %s\n", #test); \
        } while (0)

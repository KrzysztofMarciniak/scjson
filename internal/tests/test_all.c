/* vi: set sw=8 ts=8: (internal/tests/test_all.c) */
#include <stdio.h>

void test_err(void);
void test_hash(void);
void test_map_set(void);
void test_map_get(void);
void test_set(void);
void test_get(void);
void test_has(void);
void test_len(void);
void test_add(void);
void test_at(void);
void test_str(void);
void test_scalar(void);
void test_dump(void);
void test_pretty(void);
void test_new_free(void);

#define GREEN "\x1b[32m"
#define RED "\x1b[31m"
#define RESET "\x1b[0m"

#define RUN(test)                                         \
        do {                                              \
                test();                                   \
                printf(GREEN "[✓]" RESET " %s\n", #test); \
        } while (0)

int main(void) {
        RUN(test_hash);
        RUN(test_map_set);
        RUN(test_map_get);
        RUN(test_err);
        RUN(test_set);
        RUN(test_get);
        RUN(test_has);
        RUN(test_len);
        RUN(test_add);
        RUN(test_at);
        RUN(test_str);
        RUN(test_scalar);
        RUN(test_dump);
        RUN(test_pretty);
        RUN(test_new_free);

        printf("\n" GREEN "all tests passed" RESET "\n");
        return 0;
}

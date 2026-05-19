/* vi: set sw=8 ts=8: (internal/tests/test_all.c) */
#include <stdio.h>
void test_err(void);
void test_hash(void);
void test_map_set(void);
void test_map_get(void);
void test_set(void);

int main(void) {
        test_hash();
        test_map_set();
        test_map_get();
        test_err();
        test_set();
        printf("all tests passed\n");
        return 0;
}

/* vi: set sw=8 ts=8: (internal/tests/test_all.c) */
#include <stdio.h>
void test_err(void);
void test_hash(void);
void test_map_set(void);
void test_map_get(void);

int main(void) {
        test_hash();
        test_map_set();
        test_map_get();
        test_err();
        printf("all tests passwed\n");
        return 0;
}

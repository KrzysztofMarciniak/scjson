#include <stdio.h>
void test_hash(void);
void test_map_set(void);
void test_map_get(void);

int main(void) {
        test_hash();
        test_map_set();
        test_map_get();
        printf("all tests passwed\n");
        return 0;
}

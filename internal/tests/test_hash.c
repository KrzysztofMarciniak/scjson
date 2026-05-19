#include <assert.h>

#include "../scj_hash.h"

void test_hash(void) {
        unsigned long a, b;
        a = scj_hash("name");
        b = scj_hash("name");

        assert(a == b);
        assert(scj_hash("name") != scj_hash("age"));
}

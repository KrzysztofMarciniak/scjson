/* vi: set sw=8 ts=8: (internal/tests/test_hash.c) */
#include <assert.h>

#include "../scj_hash.h"

void test_hash(void) {
        unsigned long a, b;
        a = _scj_hash("name");
        b = _scj_hash("name");

        assert(a == b);
        assert(_scj_hash("name") != _scj_hash("age"));
}

/* vi: set sw=8 ts=8: (internal/tests/test_err.c) */
#include <assert.h>
#include <string.h>

#include "../scj_error.h"

void test_err(void) {
        for (int i = SCJ_OK; i <= SCJ_ERR_UNKNOWN; i++) {
                const char* msg = scj_error_string((scj_error)i);
                assert(msg != NULL);
        }

        scj_error_info er1 =
            scj_err_set(SCJ_ERR_ALLOC, "failed to allocate memory");

        assert(er1.type == SCJ_ERR_ALLOC);
        assert(er1.message != NULL);
        assert(strcmp(er1.message, "failed to allocate memory") == 0);

        assert(er1.loc.line == 0);
        assert(er1.loc.column == 0);
        assert(er1.loc.position == 0);

        scj_error_info er2 =
            scj_err_set(SCJ_ERR_KEY_NOT_FOUND, "key 'id' not found in object");

        assert(er2.type == SCJ_ERR_KEY_NOT_FOUND);
        assert(er2.message != NULL);
        assert(strcmp(er2.message, "key 'id' not found in object") == 0);
}

/* vi: set sw=8 ts=8: (internal/tests/test_add.c) */
#define _POSIX_C_SOURCE 200809L

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../scj_add.h"
#include "../scj_len.h"
#include "../scj_struct.h"
#include "../scj_type.h"

static scjson make_array(void) {
        scjson j = malloc(sizeof(struct scjson_struct));
        assert(j);

        j->type                 = SCJ_ARRAY;
        j->value.array.items    = NULL;
        j->value.array.count    = 0;
        j->value.array.capacity = 0;

        return j;
}

static scjson make_string(const char* s) {
        scjson j = malloc(sizeof(struct scjson_struct));
        assert(j);

        j->type         = SCJ_STRING;
        j->value.string = strdup(s);

        return j;
}

void test_add(void) {
        scjson arr = make_array();

        scjson a = make_string("a");
        scjson b = make_string("b");

        scj_error_info err;

        err = scj_add(arr, a);
        assert(err.type == SCJ_OK);

        err = scj_add(arr, b);
        assert(err.type == SCJ_OK);

        assert(scj_len(arr) == 2);

        free(arr);
}

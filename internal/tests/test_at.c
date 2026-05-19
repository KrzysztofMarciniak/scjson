/* vi: set sw=8 ts=8: (internal/tests/test_at.c) */
#define _POSIX_C_SOURCE 200809L

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../scj_add.h"
#include "../scj_at.h"
#include "../scj_len.h"
#include "../scj_struct.h"
#include "../scj_type.h"

static scjson make_array(void) {
        scjson j = malloc(sizeof(struct scjson_struct));
        assert(j);

        j->type = SCJ_ARRAY;

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

void test_at(void) {
        scjson arr = make_array();

        scjson a = make_string("a");
        scjson b = make_string("b");

        scj_error_info err;

        err = scj_add(arr, a);
        assert(err.type == SCJ_OK);

        err = scj_add(arr, b);
        assert(err.type == SCJ_OK);

        assert(scj_len(arr) == 2);

        scjson x0 = scj_at(arr, 0);
        scjson x1 = scj_at(arr, 1);

        assert(x0 != NULL);
        assert(x1 != NULL);

        assert(strcmp(x0->value.string, "a") == 0);
        assert(strcmp(x1->value.string, "b") == 0);

        assert(scj_at(arr, 999) == NULL);
        assert(scj_at(NULL, 0) == NULL);

        free(arr);
}

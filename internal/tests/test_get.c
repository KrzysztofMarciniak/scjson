/* vi: set sw=8 ts=8: (internal/tests/test_get.c) */

#define _POSIX_C_SOURCE 200809L
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../scj_get.h"
#include "../scj_set.h"
#include "../scj_struct.h"
#include "../scj_type.h"

static scjson make_object(void) {
        scjson j = malloc(sizeof(struct scjson_struct));
        assert(j != NULL);

        j->type = SCJ_OBJECT;

        j->value.object.map.buckets  = NULL;
        j->value.object.map.count    = 0;
        j->value.object.map.capacity = 0;

        return j;
}

static scjson make_string(const char* s) {
        scjson j = malloc(sizeof(struct scjson_struct));
        assert(j != NULL);

        j->type         = SCJ_STRING;
        j->value.string = strdup(s);

        return j;
}

void test_get(void) {
        scjson obj = make_object();

        scjson val = make_string("hello");

        scj_error_info err = scj_set(obj, "name", val);

        assert(err.type == SCJ_OK);

        scjson out = scj_get(obj, "name");

        assert(out != NULL);
        assert(out->type == SCJ_STRING);
        assert(strcmp(out->value.string, "hello") == 0);

        scjson missing = scj_get(obj, "missing");

        assert(missing == NULL);

        free(obj);
}

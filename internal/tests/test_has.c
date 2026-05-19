/* vi: set sw=8 ts=8: (internal/tests/test_has.c) */
#define _POSIX_C_SOURCE 200809L

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../scj_has.h"
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

void test_has(void) {
        scjson obj = make_object();

        scjson val = make_string("hello");

        scj_error_info err = scj_set(obj, "name", val);

        assert(err.type == SCJ_OK);

        assert(scj_has(obj, "name") == 1);

        assert(scj_has(obj, "missing") == 0);

        assert(scj_has(NULL, "name") == 0);

        free(obj);
}

/* vi: set sw=8 ts=8: (internal/tests/test_len.c) */
#define _POSIX_C_SOURCE 200809L

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../scj_len.h"
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

void test_len(void) {
        scjson obj = make_object();

        assert(scj_len(obj) == 0);

        scjson v1 = make_string("one");
        scjson v2 = make_string("two");

        assert(scj_set(obj, "a", v1).type == SCJ_OK);
        assert(scj_set(obj, "b", v2).type == SCJ_OK);

        assert(scj_len(obj) == 2);

        assert(scj_len(NULL) == 0);

        free(obj);
}

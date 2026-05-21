/* vi: set sw=8 ts=8: (internal/tests/test_set.c) */

#define _POSIX_C_SOURCE 200809L
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../scj_free.h"
#include "../scj_map_get.h"
#include "../scj_set.h"
#include "../../scjson.h"

static scjson make_object(void) {
        scjson j = malloc(sizeof(struct scjson_struct));
        assert(j != NULL);

        j->type                      = SCJ_OBJECT;
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
        assert(j->value.string != NULL);

        return j;
}
void test_set(void) {
        scjson obj = make_object();

        scjson val = make_string("hello");
        scj_set(obj, "name", val);

        scjson out = _scj_map_get(obj, "name");
        assert(out != NULL);
        assert(out->type == SCJ_STRING);
        assert(strcmp(out->value.string, "hello") == 0);

        scjson val2 = make_string("world");
        scj_set(obj, "name", val2);

        scjson out2 = _scj_map_get(obj, "name");
        assert(out2 != NULL);
        assert(out2->type == SCJ_STRING);
        assert(strcmp(out2->value.string, "world") == 0);

        scj_free(obj);
}

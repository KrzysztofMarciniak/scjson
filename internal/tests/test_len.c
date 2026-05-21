/* vi: set sw=8 ts=8: (internal/tests/test_len.c) */
#define _POSIX_C_SOURCE 200809L

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../scj_len.h"
#include "../scj_set.h"
#include "../../scjson.h"

static scjson make_object(void)
{
        scjson j = malloc(sizeof(struct scjson_struct));
        assert(j != NULL);

        j->type = SCJ_OBJECT;

        j->value.object.map.buckets = NULL;
        j->value.object.map.count = 0;
        j->value.object.map.capacity = 0;

        j->error.type = SCJ_OK;
        j->error.message = NULL;

        return j;
}

static scjson make_string(const char* s)
{
        scjson j = malloc(sizeof(struct scjson_struct));
        assert(j != NULL);

        j->type = SCJ_STRING;
        j->value.string = strdup(s);

        j->error.type = SCJ_OK;
        j->error.message = NULL;

        return j;
}

void test_len(void)
{
        scjson obj = make_object();

        assert(_scj_len(obj) == 0);

        scjson v1 = make_string("one");
        scjson v2 = make_string("two");

        _scj_set(obj, "a", v1);
        assert(obj->error.type == SCJ_OK);

        _scj_set(obj, "b", v2);
        assert(obj->error.type == SCJ_OK);

        assert(_scj_len(obj) == 2);
        assert(_scj_len(NULL) == 0);

        scjson v3 = make_string("three");

        _scj_set(obj, "a", v3);
        assert(obj->error.type == SCJ_OK);

        assert(_scj_len(obj) == 2);

        free(v1->value.string);
        free(v2->value.string);
        free(v3->value.string);

        free(v1);
        free(v2);
        free(v3);

        free(obj);
}

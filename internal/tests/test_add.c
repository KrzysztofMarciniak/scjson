/* vi: set sw=8 ts=8: */
#define _POSIX_C_SOURCE 200809L

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "../../scjson.h"
#include "../scj_add.h"
#include "../scj_len.h"

static scjson make_array(void)
{
        scjson j = malloc(sizeof(struct scjson_struct));
        assert(j);

        j->type = SCJ_ARRAY;

        j->value.array.items = NULL;
        j->value.array.count = 0;
        j->value.array.capacity = 0;

        j->error.type = SCJ_OK;
        j->error.message = NULL;

        return j;
}

static scjson make_string(const char* s)
{
        scjson j = malloc(sizeof(struct scjson_struct));
        assert(j);

        j->type = SCJ_STRING;
        j->value.string = strdup(s);

        j->error.type = SCJ_OK;
        j->error.message = NULL;

        return j;
}

void test_add(void)
{
        scjson arr = make_array();

        scjson a = make_string("a");
        scjson b = make_string("b");

        _scj_add(arr, a);
        assert(arr->error.type == SCJ_OK);

        _scj_add(arr, b);
        assert(arr->error.type == SCJ_OK);

        assert(_scj_len(arr) == 2);

        free(a->value.string);
        free(b->value.string);

        free(a);
        free(b);

        free(arr->value.array.items);
        free(arr);
}

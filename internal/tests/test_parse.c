/* vi: set sw=8 ts=8: (internal/tests/test_parse.c) */

#define _POSIX_C_SOURCE 200809L

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../scj_at.h"
#include "../scj_free.h"
#include "../scj_len.h"
#include "../scj_map_get.h"
#include "../scj_parse.h"
#include "../../scjson.h"

static void test_parse_scalar(void)
{
        scjson j;

        j = _scj_parse("\"hello\"");
        assert(j->type == SCJ_STRING);
        assert(strcmp(j->value.string, "hello") == 0);
        _scj_free(j);

        j = _scj_parse("42");
        assert(j->type == SCJ_NUMBER);
        assert(j->value.number == 42);
        _scj_free(j);

        j = _scj_parse("true");
        assert(j->type == SCJ_BOOL && j->value.boolean == 1);
        _scj_free(j);

        j = _scj_parse("false");
        assert(j->type == SCJ_BOOL && j->value.boolean == 0);
        _scj_free(j);

        j = _scj_parse("null");
        assert(j->type == SCJ_NULL);
        _scj_free(j);
}

static void test_parse_array(void)
{
        scjson j = _scj_parse("[1, 2, 3]");
        assert(j != NULL);
        assert(j->type == SCJ_ARRAY);
        assert(_scj_len(j) == 3);

        assert(_scj_at(j, 0)->type == SCJ_NUMBER &&
               _scj_at(j, 0)->value.number == 1);

        assert(_scj_at(j, 1)->type == SCJ_NUMBER &&
               _scj_at(j, 1)->value.number == 2);

        assert(_scj_at(j, 2)->type == SCJ_NUMBER &&
               _scj_at(j, 2)->value.number == 3);

        _scj_free(j);
}

static void test_parse_object(void)
{
        scjson j = _scj_parse("{\"a\":1,\"b\":true,\"c\":\"x\"}");
        assert(j->type == SCJ_OBJECT);
        assert(_scj_len(j) == 3);

        assert(_scj_map_get(j, "a")->type == SCJ_NUMBER &&
               _scj_map_get(j, "a")->value.number == 1);

        assert(_scj_map_get(j, "b")->type == SCJ_BOOL &&
               _scj_map_get(j, "b")->value.boolean == 1);

        assert(_scj_map_get(j, "c")->type == SCJ_STRING &&
               strcmp(_scj_map_get(j, "c")->value.string, "x") == 0);

        _scj_free(j);
}

static void test_parse_nested(void)
{
        scjson j = _scj_parse("{\"arr\":[1,2],\"obj\":{\"x\":10}}");

        scjson arr = _scj_map_get(j, "arr");
        scjson obj = _scj_map_get(j, "obj");

        assert(arr->type == SCJ_ARRAY && _scj_len(arr) == 2);
        assert(_scj_at(arr, 0)->value.number == 1);
        assert(_scj_at(arr, 1)->value.number == 2);

        assert(obj->type == SCJ_OBJECT && _scj_len(obj) == 1);
        assert(_scj_map_get(obj, "x")->value.number == 10);

        _scj_free(j);
}

void test_parse(void)
{
        test_parse_scalar();
        test_parse_array();
        test_parse_object();
        test_parse_nested();
}

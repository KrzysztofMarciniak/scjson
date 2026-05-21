/* vi: set sw=8 ts=8: (internal/tests/test_dump.c) */

#define _POSIX_C_SOURCE 200809L

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../scj_add.h"
#include "../scj_dump.h"
#include "../scj_set.h"
#include "../../scjson.h"

static scjson obj(void)
{
        scjson j = malloc(sizeof(struct scjson_struct));
        assert(j);

        j->type = SCJ_OBJECT;

        j->value.object.map.buckets = NULL;
        j->value.object.map.count = 0;
        j->value.object.map.capacity = 0;

        j->error.type = SCJ_OK;
        j->error.message = NULL;

        return j;
}

static scjson arr(void)
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

static scjson str(const char* s)
{
        scjson j = malloc(sizeof(struct scjson_struct));
        assert(j);

        j->type = SCJ_STRING;
        j->value.string = strdup(s);

        j->error.type = SCJ_OK;
        j->error.message = NULL;

        return j;
}

static scjson num(double v)
{
        scjson j = malloc(sizeof(struct scjson_struct));
        assert(j);

        j->type = SCJ_NUMBER;
        j->value.number = v;

        j->error.type = SCJ_OK;
        j->error.message = NULL;

        return j;
}

static scjson boolean(int v)
{
        scjson j = malloc(sizeof(struct scjson_struct));
        assert(j);

        j->type = SCJ_BOOL;
        j->value.boolean = v;

        j->error.type = SCJ_OK;
        j->error.message = NULL;

        return j;
}

static void test_scalars(void)
{
        scjson n = num(42);
        scjson b = boolean(1);
        scjson s = str("hello");

        char* dn = _scj_dump(n);
        char* db = _scj_dump(b);
        char* ds = _scj_dump(s);

        assert(strcmp(dn, "42") == 0);
        assert(strcmp(db, "true") == 0);
        assert(strcmp(ds, "\"hello\"") == 0);

        free(dn);
        free(db);
        free(ds);

        free(s->value.string);

        free(n);
        free(b);
        free(s);
}

static void test_array_flat(void)
{
        scjson a = arr();

        _scj_add(a, num(1));
        _scj_add(a, num(2));
        _scj_add(a, num(3));

        char* out = _scj_dump(a);

        assert(strstr(out, "[") == out);
        assert(strstr(out, "1") != NULL);
        assert(strstr(out, "2") != NULL);
        assert(strstr(out, "3") != NULL);
        assert(strstr(out, "]") != NULL);

        free(out);
        free(a->value.array.items);
        free(a);
}

static void test_object_flat(void)
{
        scjson o = obj();

        _scj_set(o, "a", num(1));
        _scj_set(o, "b", str("x"));

        char* out = _scj_dump(o);

        assert(strchr(out, '{') != NULL);
        assert(strchr(out, '}') != NULL);
        assert(strstr(out, "\"a\"") != NULL);
        assert(strstr(out, "\"b\"") != NULL);
        assert(strstr(out, "1") != NULL);
        assert(strstr(out, "\"x\"") != NULL);

        free(out);
        free(o);
}

static void test_nested_array(void)
{
        scjson a = arr();

        scjson inner = arr();

        _scj_add(inner, num(1));
        _scj_add(inner, num(2));

        _scj_add(a, inner);
        _scj_add(a, num(3));

        char* out = _scj_dump(a);

        assert(strstr(out, "[") != NULL);
        assert(strstr(out, "1") != NULL);
        assert(strstr(out, "2") != NULL);
        assert(strstr(out, "3") != NULL);

        free(out);

        free(inner->value.array.items);
        free(inner);

        free(a->value.array.items);
        free(a);
}

static void test_nested_object(void)
{
        scjson o = obj();
        scjson inner = obj();

        _scj_set(inner, "x", num(10));
        _scj_set(o, "child", inner);

        char* out = _scj_dump(o);

        assert(strstr(out, "\"child\"") != NULL);
        assert(strstr(out, "\"x\"") != NULL);
        assert(strstr(out, "10") != NULL);

        free(out);

        free(inner);
        free(o);
}

static void test_mixed(void)
{
        scjson o = obj();
        scjson a = arr();

        _scj_add(a, str("hello"));
        _scj_add(a, num(99));

        _scj_set(o, "arr", a);
        _scj_set(o, "ok", boolean(1));

        char* out = _scj_dump(o);

        assert(strstr(out, "\"arr\"") != NULL);
        assert(strstr(out, "\"ok\"") != NULL);
        assert(strstr(out, "hello") != NULL);
        assert(strstr(out, "99") != NULL);
        assert(strstr(out, "true") != NULL);

        free(out);

        free(a->value.array.items);
        free(a);

        free(o);
}

void test_dump(void)
{
        test_scalars();
        test_array_flat();
        test_object_flat();
        test_nested_array();
        test_nested_object();
        test_mixed();
}

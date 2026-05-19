/* vi: set sw=8 ts=8: (internal/tests/test_dump.c) */

#define _POSIX_C_SOURCE 200809L

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../scj_add.h"
#include "../scj_dump.h"
#include "../scj_set.h"
#include "../scj_struct.h"
#include "../scj_type.h"

static scjson obj(void) {
        scjson j = malloc(sizeof(struct scjson_struct));
        assert(j);

        j->type                      = SCJ_OBJECT;
        j->value.object.map.buckets  = NULL;
        j->value.object.map.count    = 0;
        j->value.object.map.capacity = 0;

        return j;
}

static scjson arr(void) {
        scjson j = malloc(sizeof(struct scjson_struct));
        assert(j);

        j->type                 = SCJ_ARRAY;
        j->value.array.items    = NULL;
        j->value.array.count    = 0;
        j->value.array.capacity = 0;

        return j;
}

static scjson str(const char* s) {
        scjson j = malloc(sizeof(struct scjson_struct));
        assert(j);

        j->type         = SCJ_STRING;
        j->value.string = strdup(s);

        return j;
}

static scjson num(double v) {
        scjson j = malloc(sizeof(struct scjson_struct));
        assert(j);

        j->type         = SCJ_NUMBER;
        j->value.number = v;

        return j;
}

static scjson boolean(int v) {
        scjson j = malloc(sizeof(struct scjson_struct));
        assert(j);

        j->type          = SCJ_BOOL;
        j->value.boolean = v;

        return j;
}

static void test_scalars(void) {
        scjson n = num(42);
        scjson b = boolean(1);
        scjson s = str("hello");

        char* dn = scj_dump(n);
        char* db = scj_dump(b);
        char* ds = scj_dump(s);

        assert(strcmp(dn, "42") == 0);
        assert(strcmp(db, "true") == 0);
        assert(strcmp(ds, "\"hello\"") == 0);

        free(dn);
        free(db);
        free(ds);

        free(n);
        free(b);
        free(s);
}

static void test_array_flat(void) {
        scjson a = arr();

        scj_add(a, num(1));
        scj_add(a, num(2));
        scj_add(a, num(3));

        char* out = scj_dump(a);

        assert(strstr(out, "[") == out);
        assert(strstr(out, "1") != NULL);
        assert(strstr(out, "2") != NULL);
        assert(strstr(out, "3") != NULL);
        assert(strstr(out, "]") != NULL);

        free(out);
        free(a);
}

static void test_object_flat(void) {
        scjson o = obj();

        scj_set(o, "a", num(1));
        scj_set(o, "b", str("x"));

        char* out = scj_dump(o);

        assert(strchr(out, '{') != NULL);
        assert(strchr(out, '}') != NULL);
        assert(strstr(out, "\"a\"") != NULL);
        assert(strstr(out, "\"b\"") != NULL);
        assert(strstr(out, "1") != NULL);
        assert(strstr(out, "\"x\"") != NULL);

        free(out);
        free(o);
}

static void test_nested_array(void) {
        scjson a = arr();

        scjson inner = arr();
        scj_add(inner, num(1));
        scj_add(inner, num(2));

        scj_add(a, inner);
        scj_add(a, num(3));

        char* out = scj_dump(a);

        assert(strstr(out, "[") != NULL);
        assert(strstr(out, "1") != NULL);
        assert(strstr(out, "2") != NULL);
        assert(strstr(out, "3") != NULL);

        free(out);
        free(a);
}

static void test_nested_object(void) {
        scjson o     = obj();
        scjson inner = obj();

        scj_set(inner, "x", num(10));
        scj_set(o, "child", inner);

        char* out = scj_dump(o);

        assert(strstr(out, "\"child\"") != NULL);
        assert(strstr(out, "\"x\"") != NULL);
        assert(strstr(out, "10") != NULL);

        free(out);
        free(o);
}

static void test_mixed(void) {
        scjson o = obj();
        scjson a = arr();

        scj_add(a, str("hello"));
        scj_add(a, num(99));

        scj_set(o, "arr", a);
        scj_set(o, "ok", boolean(1));

        char* out = scj_dump(o);

        assert(strstr(out, "\"arr\"") != NULL);
        assert(strstr(out, "\"ok\"") != NULL);
        assert(strstr(out, "hello") != NULL);
        assert(strstr(out, "99") != NULL);
        assert(strstr(out, "true") != NULL);

        free(out);
        free(o);
}

void test_dump(void) {
        test_scalars();
        test_array_flat();
        test_object_flat();
        test_nested_array();
        test_nested_object();
        test_mixed();
}

/* vi: set sw=8 ts=8: (internal/tests/test_pretty.c) */

#define _POSIX_C_SOURCE 200809L

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../scj_add.h"
#include "../scj_pretty.h"
#include "../scj_set.h"
#include "../../scjson.h"

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

static scjson num(double v) {
        scjson j = malloc(sizeof(struct scjson_struct));
        assert(j);

        j->type         = SCJ_NUMBER;
        j->value.number = v;

        return j;
}

static scjson str(const char* s) {
        scjson j = malloc(sizeof(struct scjson_struct));
        assert(j);

        j->type         = SCJ_STRING;
        j->value.string = strdup(s);

        return j;
}

static scjson boolean(int v) {
        scjson j = malloc(sizeof(struct scjson_struct));
        assert(j);

        j->type          = SCJ_BOOL;
        j->value.boolean = v;

        return j;
}

static int contains(const char* haystack, const char* needle) {
        return strstr(haystack, needle) != NULL;
}

static void test_pretty_scalar(void) {
        scjson j = num(42);

        char* out = scj_pretty(j);

        assert(contains(out, "42"));

        free(out);
        free(j);
}

static void test_pretty_array_flat(void) {
        scjson a = arr();

        scj_add(a, num(1));
        scj_add(a, num(2));
        scj_add(a, num(3));

        char* out = scj_pretty(a);

        /* structure checks */
        assert(contains(out, "["));
        assert(contains(out, "]"));
        assert(contains(out, "1"));
        assert(contains(out, "2"));
        assert(contains(out, "3"));

        /* formatting checks */
        assert(contains(out, "\n")); /* must pretty-print */
        assert(contains(out, "  ")); /* indentation */

        free(out);
        free(a);
}

static void test_pretty_object_flat(void) {
        scjson o = obj();

        scj_set(o, "a", num(1));
        scj_set(o, "b", str("x"));

        char* out = scj_pretty(o);

        assert(contains(out, "{"));
        assert(contains(out, "}"));
        assert(contains(out, "\"a\""));
        assert(contains(out, "\"b\""));
        assert(contains(out, "1"));
        assert(contains(out, "\"x\""));

        assert(contains(out, "\n"));
        assert(contains(out, ": "));

        free(out);
        free(o);
}

static void test_pretty_nested_array(void) {
        scjson a     = arr();
        scjson inner = arr();

        scj_add(inner, num(10));
        scj_add(inner, num(20));

        scj_add(a, inner);
        scj_add(a, num(30));

        char* out = scj_pretty(a);

        assert(contains(out, "10"));
        assert(contains(out, "20"));
        assert(contains(out, "30"));

        assert(contains(out, "\n"));
        assert(contains(out, "  "));

        free(out);
        free(a);
}

static void test_pretty_nested_object(void) {
        scjson o     = obj();
        scjson child = obj();

        scj_set(child, "x", num(99));
        scj_set(o, "child", child);

        char* out = scj_pretty(o);

        assert(contains(out, "\"child\""));
        assert(contains(out, "\"x\""));
        assert(contains(out, "99"));

        assert(contains(out, "\n"));
        assert(contains(out, "  "));

        free(out);
        free(o);
}

static void test_pretty_mixed(void) {
        scjson o = obj();
        scjson a = arr();

        scj_add(a, str("hello"));
        scj_add(a, boolean(1));

        scj_set(o, "arr", a);
        scj_set(o, "num", num(123));

        char* out = scj_pretty(o);

        assert(contains(out, "\"arr\""));
        assert(contains(out, "\"num\""));
        assert(contains(out, "hello"));
        assert(contains(out, "true"));
        assert(contains(out, "123"));

        assert(contains(out, "\n"));

        free(out);
        free(o);
}

void test_pretty(void) {
        test_pretty_scalar();
        test_pretty_array_flat();
        test_pretty_object_flat();
        test_pretty_nested_array();
        test_pretty_nested_object();
        test_pretty_mixed();
}

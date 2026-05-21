/* vi: set sw=8 ts=8: (internal/tests/test_scalar.c) */
#define _POSIX_C_SOURCE 200809L

#include <assert.h>
#include <stdlib.h>

#include "../scj_bool.h"
#include "../scj_num.h"
#include "../../scjson.h"

static scjson make_number(double v) {
        scjson j = malloc(sizeof(struct scjson_struct));
        assert(j);

        j->type         = SCJ_NUMBER;
        j->value.number = v;

        return j;
}

static scjson make_bool(int v) {
        scjson j = malloc(sizeof(struct scjson_struct));
        assert(j);

        j->type          = SCJ_BOOL;
        j->value.boolean = v;

        return j;
}

static scjson make_string(void) {
        scjson j = malloc(sizeof(struct scjson_struct));
        assert(j);

        j->type         = SCJ_STRING;
        j->value.string = "x";

        return j;
}

void test_scalar(void) {
        scjson n = make_number(42);
        scjson b = make_bool(1);
        scjson s = make_string();

        assert(scj_num(n) == 42);
        assert(scj_num(b) == 0);
        assert(scj_num(NULL) == 0);

        assert(scj_bool(b) == 1);
        assert(scj_bool(n) == 0);
        assert(scj_bool(NULL) == 0);

        free(n);
        free(b);
        free(s);
}

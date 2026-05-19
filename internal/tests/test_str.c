/* vi: set sw=8 ts=8: (internal/tests/test_str.c) */
#define _POSIX_C_SOURCE 200809L

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../scj_str.h"
#include "../scj_struct.h"
#include "../scj_type.h"

static scjson make_string(const char* s) {
        scjson j = malloc(sizeof(struct scjson_struct));
        assert(j);

        j->type         = SCJ_STRING;
        j->value.string = strdup(s);

        return j;
}

static scjson make_number(void) {
        scjson j = malloc(sizeof(struct scjson_struct));
        assert(j);

        j->type         = SCJ_NUMBER;
        j->value.number = 42;

        return j;
}

void test_str(void) {
        scjson s = make_string("hello");
        scjson n = make_number();

        assert(scj_str(s) != NULL);
        assert(strcmp(scj_str(s), "hello") == 0);

        assert(scj_str(n) == NULL);
        assert(scj_str(NULL) == NULL);

        free(s);
        free(n);
}

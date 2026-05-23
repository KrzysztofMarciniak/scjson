/* vi: set sw=8 ts=8: (internal/tests/test_err.c) */

#include <assert.h>
#include <string.h>

#include "../../scjson.h"

static void test_known_codes(void)
{
        assert(strcmp(scj_error_string(SCJ_OK),                    "SCJSON: no error") == 0);
        assert(strcmp(scj_error_string(SCJ_ERR_ALLOC),             "SCJSON: allocation failed") == 0);
        assert(strcmp(scj_error_string(SCJ_ERR_PARSE),             "SCJSON: parse error") == 0);
        assert(strcmp(scj_error_string(SCJ_ERR_UNEXPECTED_TOKEN),  "SCJSON: unexpected token") == 0);
        assert(strcmp(scj_error_string(SCJ_ERR_UNEXPECTED_END),    "SCJSON: unexpected end") == 0);
        assert(strcmp(scj_error_string(SCJ_ERR_INVALID_STRING),    "SCJSON: invalid string") == 0);
        assert(strcmp(scj_error_string(SCJ_ERR_INVALID_NUMBER),    "SCJSON: invalid number") == 0);
        assert(strcmp(scj_error_string(SCJ_ERR_INVALID_BOOL),      "SCJSON: invalid bool") == 0);
        assert(strcmp(scj_error_string(SCJ_ERR_INVALID_NULL),      "SCJSON: invalid NULL") == 0);
        assert(strcmp(scj_error_string(SCJ_ERR_KEY_NOT_FOUND),     "SCJSON: key not found") == 0);
        assert(strcmp(scj_error_string(SCJ_ERR_INVALID_KEY),       "SCJSON: invalid key") == 0);
        assert(strcmp(scj_error_string(SCJ_ERR_INDEX_OUT_OF_BOUNDS), "SCJSON: index out of bounds") == 0);
        assert(strcmp(scj_error_string(SCJ_ERR_NOT_OBJECT),        "SCJSON: value is not an object") == 0);
        assert(strcmp(scj_error_string(SCJ_ERR_NOT_ARRAY),         "SCJSON: value is not an array") == 0);
        assert(strcmp(scj_error_string(SCJ_ERR_NOT_STRING),        "SCJSON: value is not a string") == 0);
        assert(strcmp(scj_error_string(SCJ_ERR_NOT_NUMBER),        "SCJSON: value is not a number") == 0);
        assert(strcmp(scj_error_string(SCJ_ERR_NOT_BOOL),          "SCJSON: value is not a bool") == 0);
        assert(strcmp(scj_error_string(SCJ_ERR_DUMP),              "SCJSON: serialization failed") == 0);
        assert(strcmp(scj_error_string(SCJ_ERR_INVALID_VALUE),     "SCJSON: invalid value") == 0);
}

static void test_unknown_code(void)
{
        assert(strcmp(scj_error_string((scj_error)9999), "SCJSON: unknown error") == 0);
}

void test_err(void)
{
        test_known_codes();
        test_unknown_code();
}

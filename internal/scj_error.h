/* vi: set sw=8 ts=8: */
#ifndef SCJ_ERROR_H
#define SCJ_ERROR_H
#include <stddef.h>

typedef enum {
        SCJ_OK = 0,
        SCJ_ERR_ALLOC,
        SCJ_ERR_PARSE,
        SCJ_ERR_UNEXPECTED_TOKEN,
        SCJ_ERR_UNEXPECTED_END,
        SCJ_ERR_INVALID_STRING,
        SCJ_ERR_INVALID_NUMBER,
        SCJ_ERR_INVALID_BOOL,
        SCJ_ERR_INVALID_NULL,
        SCJ_ERR_KEY_NOT_FOUND,
        SCJ_ERR_INVALID_KEY,
        SCJ_ERR_INDEX_OUT_OF_BOUNDS,
        SCJ_ERR_NOT_OBJECT,
        SCJ_ERR_NOT_ARRAY,
        SCJ_ERR_NOT_STRING,
        SCJ_ERR_NOT_NUMBER,
        SCJ_ERR_NOT_BOOL,
        SCJ_ERR_DUMP,
        SCJ_ERR_INVALID_VALUE,
        SCJ_ERR_UNKNOWN

} scj_error;

const char* scj_error_string(scj_error error);
void scj_err_set(scj_error type, const char* message);

typedef struct {
        scj_error type;
        const char* message;
        size_t line;
        size_t column;
        size_t position;
} scj_error_info;

#endif

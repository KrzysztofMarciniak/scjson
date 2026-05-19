/* vi: set sw=8 ts=8: (internal/scj_type.h) */
#ifndef SCJ_TYPE_H
#define SCJ_TYPE_H

typedef enum {
        SCJ_NULL = 0,
        SCJ_OBJECT,
        SCJ_ARRAY,
        SCJ_STRING,
        SCJ_NUMBER,
        SCJ_BOOL
} scj_type;
#endif

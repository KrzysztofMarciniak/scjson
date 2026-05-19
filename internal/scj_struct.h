/* vi: set sw=8 ts=8: */
#ifndef SCJ_STRUCT_H
#define SCJ_STRUCT_H
#include <stddef.h>

#include "../scjson.h"
#include "scj_error.h"
#include "scj_map.h"
#include "scj_type.h"

struct scjson_struct {
        scj_error_info (*set)(scjson self, const char* key, scjson value);
        scj_error_info (*add)(scjson self, scjson value);
        scjson (*get)(scjson self, const char* key);
        int (*has)(scjson self, const char* key);
        scjson (*at)(scjson self, size_t index);
        size_t (*len)(scjson self);
        const char* (*str)(scjson self);
        double (*num)(scjson self);
        int (*bool)(scjson self);
        char* (*dump)(scjson self);
        char* (*pretty)(scjson self);
        void (*free)(scjson self);
        scj_type type;

        union {
                char* string;
                double number;
                int boolean;

                struct {
                        scjson* items;
                        size_t count;
                        size_t capacity;
                } array;

                struct {
                        scj_map map;
                } object;
        } value;

        scj_error_info error;
};

#endif

/* vi: set sw=8 ts=8: */
#ifndef SCJ_STRUCT_H
#define SCJ_STRUCT_H
#include <stddef.h>

#include "../scjson.h"

struct scjson_struct {
        scjson (*get)(scjson self, const char* key);
        void (*set)(scjson self, const char* key, void* value);
        void (*free)(scjson self);
        int(*has){scjson self, const char* key};
        void (*add)(scjson self, void* value);
        scjson (*at)(scjson self, size_t index);
        size_t (*len)(scjson self);
        const char* (*str)(scjson self);
        double (*num)(scjson self);
        int (*bool)(scjson self);
        char* (*dump)(scjson self);
        char* (*pretty)(scjson self);
        void* internal;
};

#endif

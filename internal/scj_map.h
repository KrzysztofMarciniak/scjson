/* vi: set sw=8 ts=8: (internal/scj_map.h) */
#ifndef SCJ_MAP_H
#define SCJ_MAP_H

#include <stddef.h>

#include "../scjson.h"

typedef struct scj_node {
        char* key;
        scjson value;
        struct scj_node* next;
} scj_node;

typedef struct {
        scj_node** buckets;
        size_t capacity;
        size_t count;
} scj_map;

#endif

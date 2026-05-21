/* internal/scj_map_init.c */
#include "scj_map_init.h"
#include "../scjson.h"
#include <stdlib.h>

#define SCJ_MAP_INITIAL_CAPACITY 16

void _scj_map_init(scjson self) {
    if (!self) return;

    self->value.object.map.capacity = SCJ_MAP_INITIAL_CAPACITY;
    self->value.object.map.count    = 0;

    self->value.object.map.buckets =
        calloc(SCJ_MAP_INITIAL_CAPACITY, sizeof(scj_node*));

    if (!self->value.object.map.buckets) {
        self->error.type    = SCJ_ERR_ALLOC;
        self->error.message = "scj_map_init.c: mem calloc failed.";
        return;
    }

    self->error.type    = SCJ_OK;
    self->error.message = NULL;
}

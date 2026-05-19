#include "scj_map_init.h"

#include <stdlib.h>

#include "scj_error.h"
#include "scj_struct.h"
#define SCJ_MAP_INITIAL_CAPACITY 16

void scj_map_init(scjson self) {
        self->value.object.map.capacity = SCJ_MAP_INITIAL_CAPACITY;
        self->value.object.map.count    = 0;
        self->value.object.map.buckets =
            calloc(SCJ_MAP_INITIAL_CAPACITY, sizeof(scj_node*));
        if (!self->value.object.map.buckets) {
                scj_err_set(SCJ_ERR_ALLOC, scj_error_string(SCJ_ERR_ALLOC));
        }
}

#define _POSIX_C_SOURCE 200809L
#include "scj_map_set.h"

#include <stdlib.h>
#include <string.h>

#include "scj_error.h"
#include "scj_hash.h"
#include "scj_struct.h"

void scj_map_set(scjson self, const char* key, scjson value) {
        size_t index;
        scj_node* node;
        index = scj_hash(key) % self->value.object.map.capacity;

        node = malloc(sizeof(scj_node));
        if (!node) {
                scj_err_set(SCJ_ERR_ALLOC, scj_error_string(SCJ_ERR_ALLOC));
                return;
        }

        node->key = strdup(key);
        if (!node->key) {
                free(node);
                scj_err_set(SCJ_ERR_ALLOC, scj_error_string(SCJ_ERR_ALLOC));
                return;
        }

        node->value = value;
        node->next  = self->value.object.map.buckets[index];
        self->value.object.map.buckets[index] = node;
        self->value.object.map.count++;
}

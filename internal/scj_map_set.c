/* vi: set sw=8 ts=8: (internal/scj_map_set.c) */
#define _POSIX_C_SOURCE 200809L
#include "scj_map_set.h"

#include <stdlib.h>
#include <string.h>

#include "scj_error.h"
#include "scj_hash.h"
#include "scj_struct.h"

scj_error_info scj_map_set(scjson self, const char* key, scjson value) {
        size_t index;
        scj_node* node;

        if (!self || !key) {
                return scj_err_set(SCJ_ERR_INVALID_VALUE,
                                   "scj_map_set.c: invalid input");
        }

        if (self->value.object.map.capacity == 0) {
                self->value.object.map.capacity = 8;
                self->value.object.map.count    = 0;

                self->value.object.map.buckets =
                    calloc(self->value.object.map.capacity, sizeof(scj_node*));

                if (!self->value.object.map.buckets) {
                        return scj_err_set(
                            SCJ_ERR_ALLOC,
                            "scj_map_set.c: bucket alloc failed");
                }
        }

        index = scj_hash(key) % self->value.object.map.capacity;

        node = self->value.object.map.buckets[index];

        while (node) {
                if (strcmp(node->key, key) == 0) {
                        node->value = value;
                        return scj_err_ok();
                }

                node = node->next;
        }

        node = malloc(sizeof(scj_node));

        if (!node) {
                return scj_err_set(SCJ_ERR_ALLOC,
                                   "scj_map_set.c: node allocation failed");
        }

        node->key = strdup(key);

        if (!node->key) {
                free(node);

                return scj_err_set(SCJ_ERR_ALLOC,
                                   "scj_map_set.c: key strdup failed");
        }

        node->value = value;

        node->next = self->value.object.map.buckets[index];

        self->value.object.map.buckets[index] = node;

        self->value.object.map.count++;
        return scj_err_ok();
}

/* internal/scj_map_set.c */
#define _POSIX_C_SOURCE 200809L
#include "scj_map_set.h"

#include <stdlib.h>
#include <string.h>

#include "../scjson.h"
#include "scj_hash.h"

/**
 * @brief Sets a key-value pair in a JSON object map.
 *
 * This internal function inserts a key and its associated JSON value into the
 * underlying hash map of an `scjson` instance. If the key already exists within
 * the map, its old value is updated with the new one. If the key does not
 * exist, a new bucket node is dynamically allocated, and the key is duplicated
 * via `strdup`.
 *
 * This function also handles the lazy initialization of the hash map buckets
 * upon the first insertion.
 * * @note This is an internal component of the scjson library and should not
 * typically be called directly by the end-user.
 *
 * @param self  The target `scjson` object instance. Must not be NULL.
 * @param key   The string key identifying the value. Must not be NULL.
 * @param value The `scjson` value to be associated with the key.
 *
 * @return void
 *
 * @see _scj_hash()
 *
 * @retval SCJ_OK                On successful insertion or update.
 * @retval SCJ_ERR_INVALID_VALUE If `self` or `key` is NULL.
 * @retval SCJ_ERR_ALLOC         If dynamic memory allocation fails for the
 * bucket array, the bucket node, or the key copy.
 */
void _scj_map_set(scjson self, const char* key, scjson value) {
        if (!self || !key) {
                if (self) {
                        self->error.type    = SCJ_ERR_INVALID_VALUE;
                        self->error.message = "scj_map_set.c: invalid input";
                }
                return;
        }

        if (self->value.object.map.capacity == 0) {
                self->value.object.map.capacity = 8;
                self->value.object.map.count    = 0;
                self->value.object.map.buckets =
                    calloc(self->value.object.map.capacity, sizeof(scj_node*));

                if (!self->value.object.map.buckets) {
                        self->error.type = SCJ_ERR_ALLOC;
                        self->error.message =
                            "scj_map_set.c: bucket alloc failed";
                        return;
                }
        }

        size_t index   = _scj_hash(key) % self->value.object.map.capacity;
        scj_node* node = self->value.object.map.buckets[index];

        while (node) {
                if (strcmp(node->key, key) == 0) {
                        node->value         = value;
                        self->error.type    = SCJ_OK;
                        self->error.message = NULL;
                        return;
                }
                node = node->next;
        }

        node = malloc(sizeof(scj_node));
        if (!node) {
                self->error.type    = SCJ_ERR_ALLOC;
                self->error.message = "scj_map_set.c: node allocation failed";
                return;
        }

        node->key = strdup(key);
        if (!node->key) {
                free(node);
                self->error.type    = SCJ_ERR_ALLOC;
                self->error.message = "scj_map_set.c: key strdup failed";
                return;
        }

        node->value = value;
        node->next  = self->value.object.map.buckets[index];
        self->value.object.map.buckets[index] = node;
        self->value.object.map.count++;

        self->error.type    = SCJ_OK;
        self->error.message = NULL;
}

/* vi: set sw=8 ts=8: (internal/scj_free.c) */
/* internal/scj_free.c */
#include <stdlib.h>
#include <string.h>

#include "scj_struct.h"

/* Forward declaration */
void scj_free(scjson obj);

/* Free a single map node */
static void scj_node_free(scj_node* node) {
        if (!node) return;
        free(node->key);      // free key string
        scj_free(node->value);// recursively free value
        free(node);
}

/* Free all nodes in the map */
static void scj_map_free(scj_map* map) {
        if (!map || !map->buckets) return;

        for (size_t i = 0; i < map->capacity; i++) {
                scj_node* node = map->buckets[i];
                while (node) {
                        scj_node* next = node->next;
                        scj_node_free(node);
                        node = next;
                }
        }

        free(map->buckets);
        map->buckets  = NULL;
        map->count    = 0;
        map->capacity = 0;
}

/* Free an array */
static void scj_array_free(scjson* items, size_t count) {
        if (!items) return;
        for (size_t i = 0; i < count; i++) {
                scj_free(items[i]);
        }
        free(items);
}

/* Main free function */
void scj_free(scjson obj) {
        if (!obj) return;

        switch (obj->type) {
                case SCJ_OBJECT:
                        scj_map_free(&obj->value.object.map);
                        break;

                case SCJ_ARRAY:
                        scj_array_free(obj->value.array.items,
                                       obj->value.array.count);
                        obj->value.array.items    = NULL;
                        obj->value.array.count    = 0;
                        obj->value.array.capacity = 0;
                        break;

                case SCJ_STRING:
                        free(obj->value.string);
                        obj->value.string = NULL;
                        break;

                case SCJ_NUMBER:
                case SCJ_BOOL:
                case SCJ_NULL:
                        // nothing to free
                        break;
        }

        free(obj);
}

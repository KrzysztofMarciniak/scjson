/* vi: set sw=8 ts=8: (internal/scj_map_get.c) */

#include "scj_map_get.h"

#include <string.h>

#include "../scjson.h"
#include "scj_hash.h"
#include "scj_struct.h"

scjson scj_map_get(scjson self, const char* key) {
        scj_node* node;
        size_t index;

        if (!self || !key) return NULL;

        if (self->type != SCJ_OBJECT) return NULL;

        if (self->value.object.map.capacity == 0) return NULL;

        if (!self->value.object.map.buckets) return NULL;

        index = scj_hash(key) % self->value.object.map.capacity;

        node = self->value.object.map.buckets[index];

        while (node) {
                if (node->key && strcmp(node->key, key) == 0)
                        return node->value;

                node = node->next;
        }

        return NULL;
}

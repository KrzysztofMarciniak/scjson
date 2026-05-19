#include "scj_map_get.h"

#include <string.h>

#include "../scjson.h"
#include "scj_hash.h"
#include "scj_struct.h"

scjson scj_map_get(scjson self, const char* key) {
        size_t index;
        scj_node* node;
        index = scj_hash(key) % self->value.object.map.capacity;
        node  = self->value.object.map.buckets[index];
        while (node) {
                if (strcmp(node->key, key) == 0) {
                        return node->value;
                }
                node = node->next;
        }
        return NULL;
}

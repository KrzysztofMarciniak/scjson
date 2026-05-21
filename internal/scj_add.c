/* internal/scj_add.c */
#include "scj_add.h"
#include "../scjson.h"
#include <stdlib.h>
#include <string.h>

#define INIT_CAP 8

void _scj_add(scjson self, scjson value) {
    if (!self) {
        if (self) self->error.type = SCJ_ERR_INVALID_VALUE;
        return;
    }

    if (self->type != SCJ_ARRAY) {
        self->error.type = SCJ_ERR_NOT_ARRAY;
        self->error.message = "scj_add: not an array";
        return;
    }

    if (self->value.array.capacity == 0) {
        self->value.array.items = malloc(sizeof(scjson) * INIT_CAP);
        if (!self->value.array.items) {
            self->error.type = SCJ_ERR_ALLOC;
            self->error.message = "scj_add: malloc failed";
            return;
        }
        self->value.array.capacity = INIT_CAP;
        self->value.array.count = 0;
    }

    if (self->value.array.count == self->value.array.capacity) {
        size_t new_cap = self->value.array.capacity * 2;
        scjson* tmp = realloc(self->value.array.items, sizeof(scjson) * new_cap);
        if (!tmp) {
            self->error.type = SCJ_ERR_ALLOC;
            self->error.message = "scj_add: realloc failed";
            return;
        }
        self->value.array.items = tmp;
        self->value.array.capacity = new_cap;
    }

    self->value.array.items[self->value.array.count++] = value;
    self->error.type = SCJ_OK;
}

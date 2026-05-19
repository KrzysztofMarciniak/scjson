/* vi: set sw=8 ts=8: (internal/scj_add.c) */

#include "scj_add.h"

#include <stdlib.h>

#include "scj_struct.h"
#include "scj_type.h"

#define INIT_CAP 8

scj_error_info scj_add(scjson self, scjson value) {
        if (!self) {
                return scj_err_set(SCJ_ERR_INVALID_VALUE, "scj_add: NULL self");
        }

        if (self->type != SCJ_ARRAY) {
                return scj_err_set(SCJ_ERR_NOT_ARRAY, "scj_add: not an array");
        }

        if (self->value.array.capacity == 0) {
                self->value.array.items = malloc(sizeof(scjson) * INIT_CAP);

                if (!self->value.array.items) {
                        return scj_err_set(SCJ_ERR_ALLOC,
                                           "scj_add: alloc failed");
                }

                self->value.array.capacity = INIT_CAP;
                self->value.array.count    = 0;
        }

        if (self->value.array.count == self->value.array.capacity) {
                size_t new_cap = self->value.array.capacity * 2;

                scjson* tmp =
                    realloc(self->value.array.items, sizeof(scjson) * new_cap);

                if (!tmp) {
                        return scj_err_set(SCJ_ERR_ALLOC,
                                           "scj_add: realloc failed");
                }

                self->value.array.items    = tmp;
                self->value.array.capacity = new_cap;
        }

        self->value.array.items[self->value.array.count++] = value;

        return scj_err_ok();
}

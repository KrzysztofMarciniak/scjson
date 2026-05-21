/* vi: set sw=8 ts=8: (internal/scj_at.c) */

#include "scj_at.h"

#include "../scjson.h"

scjson _scj_at(scjson self, size_t index) {
        if (!self) {
                return NULL;
        }

        if (self->type != SCJ_ARRAY) {
                return NULL;
        }

        if (index >= self->value.array.count) {
                return NULL;
        }

        return self->value.array.items[index];
}

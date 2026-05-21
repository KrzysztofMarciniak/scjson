/* vi: set sw=8 ts=8: (internal/scj_len.c) */

#include "scj_len.h"

size_t _scj_len(scjson self) {
        if (!self) {
                return 0;
        }

        switch (self->type) {
                case SCJ_OBJECT:
                        return self->value.object.map.count;

                case SCJ_ARRAY:
                        return self->value.array.count;

                default:
                        return 0;
        }
}

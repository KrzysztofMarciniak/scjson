/* vi: set sw=8 ts=8: (internal/scj_str.c) */

#include "scj_str.h"

#include "scj_struct.h"
#include "scj_type.h"

const char* scj_str(scjson self) {
        if (!self) {
                return NULL;
        }

        if (self->type != SCJ_STRING) {
                return NULL;
        }

        return self->value.string;
}

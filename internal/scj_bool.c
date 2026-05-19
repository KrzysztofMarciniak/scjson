/* vi: set sw=8 ts=8: (internal/scj_bool.c) */

#include "scj_bool.h"

#include "scj_struct.h"
#include "scj_type.h"

int scj_bool(scjson self) {
        if (!self) {
                return 0;
        }

        if (self->type != SCJ_BOOL) {
                return 0;
        }

        return self->value.boolean;
}

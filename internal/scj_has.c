/* vi: set sw=8 ts=8: (internal/scj_has.c) */

#include "scj_has.h"

#include "scj_get.h"
#include "scj_struct.h"
#include "scj_type.h"

int scj_has(scjson self, const char* key) {
        if (!self || !key) {
                return 0;
        }

        if (self->type != SCJ_OBJECT) {
                return 0;
        }

        return scj_get(self, key) != NULL;
}

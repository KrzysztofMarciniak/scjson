/* vi: set sw=8 ts=8: (internal/scj_get.c) */

#include "scj_get.h"

#include "scj_map_get.h"
#include "scj_struct.h"
#include "scj_type.h"

scjson scj_get(scjson self, const char* key) {
        if (!self || !key) {
                return NULL;
        }

        if (self->type != SCJ_OBJECT) {
                return NULL;
        }

        return scj_map_get(self, key);
}

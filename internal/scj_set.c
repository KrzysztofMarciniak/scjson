/* vi: set sw=8 ts=8: (internal/scj_set.c) */

#include "scj_set.h"

#include "scj_error.h"
#include "scj_map_set.h"
#include "scj_struct.h"
#include "scj_type.h"

scj_error_info scj_set(scjson self, const char* key, scjson value) {
        if (!self || !key) {
                return scj_err_set(SCJ_ERR_INVALID_KEY,
                                   "NULL self or key in scj_set");
        }

        if (self->type != SCJ_OBJECT) {
                return scj_err_set(SCJ_ERR_NOT_OBJECT,
                                   "scj_set called on non-object");
        }

        return scj_map_set(self, key, value);
}

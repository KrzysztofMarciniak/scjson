/* internal/scj_set.c */
#include "scj_set.h"
#include "scj_map_set.h"

void _scj_set(scjson self, const char* key, scjson value) {
    if (!self || !key) {
        if (self) {
            self->error.type    = SCJ_ERR_INVALID_KEY;
            self->error.message = "NULL self or key in scj_set";
        }
        return;
    }

    if (self->type != SCJ_OBJECT) {
        self->error.type    = SCJ_ERR_NOT_OBJECT;
        self->error.message = "scj_set called on non-object";
        return;
    }

    _scj_map_set(self, key, value);
    // _scj_map_set already sets self->error
}

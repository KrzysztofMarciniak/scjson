/* vi: set sw=8 ts=8: (internal/scj_has.c) */
#include "scj_has.h"

#include "../scjson.h"
#include "scj_get.h"

int _scj_has(scjson self, const char* key) {
        if (!self || !key) {
                return 0;
        }

        if (self->type != SCJ_OBJECT) {
                return 0;
        }

        return _scj_get(self, key) != NULL;
}

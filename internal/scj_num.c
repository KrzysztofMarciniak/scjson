/* vi: set sw=8 ts=8: (internal/scj_num.c) */

#include "scj_num.h"
#include "../scjson.h"
double _scj_num(scjson self) {
        if (!self) {
                return 0;
        }

        if (self->type != SCJ_NUMBER) {
                return 0;
        }

        return self->value.number;
}

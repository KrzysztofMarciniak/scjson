/* vi: set sw=8 ts=8: (internal/scj_num.c) */

#include "scj_num.h"

#include "scj_struct.h"
#include "scj_type.h"

double scj_num(scjson self) {
        if (!self) {
                return 0;
        }

        if (self->type != SCJ_NUMBER) {
                return 0;
        }

        return self->value.number;
}

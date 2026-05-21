#define _POSIX_C_SOURCE 200809L
#include <stdarg.h>
#include <string.h>

#include "../scjson.h"
#include "scj_new.h"

scjson _scj_vnew_typed(scj_type type, va_list ap) {
        scjson j = _scj_new();

        if (!j) return NULL;

        j->type = type;

        switch (type) {
                case SCJ_STRING:
                        j->value.string = strdup(va_arg(ap, const char*));
                        break;

                case SCJ_NUMBER:
                        j->value.number = va_arg(ap, double);
                        break;

                case SCJ_BOOL:
                        j->value.boolean = va_arg(ap, int);
                        break;

                default:
                        break;
        }

        return j;
}

/* vi: set sw=8 ts=8: (internal/scj_set.h) */
#ifndef SCJ_SET_H
#define SCJ_SET_H

#include <stddef.h>

#include "../scjson.h"
#include "scj_error.h"

scj_error_info scj_set(scjson self, const char* key, scjson value);

#endif

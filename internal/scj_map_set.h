/* vi: set sw=8 ts=8: (internal/scj_map_set.h) */
#ifndef SCJ_MAP_SET_H
#define SCJ_MAP_SET_H

#include "../scjson.h"
#include "scj_error.h"

scj_error_info scj_map_set(scjson self, const char* key, scjson value);

#endif

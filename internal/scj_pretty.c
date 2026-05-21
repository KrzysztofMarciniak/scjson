/* vi: set sw=8 ts=8: (internal/scj_pretty.c) */

#include "../scjson.h"
#include "scj_writer.h"

char* _scj_pretty(scjson self) { return _scj_write_pretty(self); }

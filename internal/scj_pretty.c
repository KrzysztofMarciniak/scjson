/* vi: set sw=8 ts=8: (internal/scj_pretty.c) */

#include "scj_writer.h"
#include "../scjson.h"
char* _scj_pretty(scjson self) { return _scj_write_pretty(self); }

/* vi: set sw=8 ts=8: (internal/scj_pretty.c) */

#include "scj_struct.h"
#include "scj_writer.h"

char* scj_pretty(scjson self) { return scj_write_pretty(self); }

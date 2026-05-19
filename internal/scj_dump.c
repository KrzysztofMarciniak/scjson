/* vi: set sw=8 ts=8: (internal/scj_dump.c) */

#include "scj_struct.h"
#include "scj_writer.h"

char* scj_dump(scjson self) { return scj_write_dump(self); }

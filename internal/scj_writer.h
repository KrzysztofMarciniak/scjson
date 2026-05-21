/* vi: set sw=8 ts=8: (internal/scj_writer.h) */

#ifndef SCJ_WRITER_H
#define SCJ_WRITER_H

#include <stddef.h>

#include "../scjson.h"

char* _scj_write_dump(scjson self);
char* _scj_write_pretty(scjson self);

#endif

/* internal/scj_free.h */
/* vi: set sw=8 ts=8: */
#ifndef SCJ_FREE_H
#define SCJ_FREE_H

#include "scj_struct.h"

/* Frees a scjson object and all nested contents recursively */
void scj_free(scjson obj);

#endif /* SCJ_FREE_H */

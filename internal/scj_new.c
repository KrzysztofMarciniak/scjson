/* vi: set sw=8 ts=8: (internal/scj_new.c) */
#include "scj_new.h"

#include <stdlib.h>
#include <string.h>
#include "../scjson.h"
#include "scj_free.h"

scjson _scj_new(void) {
        scjson j = malloc(sizeof(struct scjson_struct));
        if (!j) return NULL;

        j->type = SCJ_NULL;

        j->value.string = NULL;
        j->value.number = 0;
        j->value.boolean = 0;

        j->value.array.items = NULL;
        j->value.array.count = 0;
        j->value.array.capacity = 0;

        j->value.object.map.buckets = NULL;
        j->value.object.map.count = 0;
        j->value.object.map.capacity = 0;

        j->error.type = SCJ_OK;
        j->error.message = NULL;
        j->error.loc.line = 0;
        j->error.loc.column = 0;
        j->error.loc.position = 0;

        return j;
}

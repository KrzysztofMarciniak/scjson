/* vi: set sw=8 ts=8: (internal/scj_new.c) */
#include "scj_new.h"

#include <stdlib.h>

#include "scj_error.h"
#include "scj_free.h"
#include "scj_struct.h"

/* API headers */
#include "scj_add.h"
#include "scj_at.h"
#include "scj_bool.h"
#include "scj_dump.h"
#include "scj_get.h"
#include "scj_has.h"
#include "scj_len.h"
#include "scj_num.h"
#include "scj_pretty.h"
#include "scj_set.h"
#include "scj_str.h"

scjson scj_new(void) {
        scjson j = malloc(sizeof(struct scjson_struct));
        if (!j) {
                scj_err_set(SCJ_ERR_ALLOC, scj_error_string(SCJ_ERR_ALLOC));
                return NULL;
        }

        /* ---------------- type ---------------- */
        j->type = SCJ_NULL;

        /* ---------------- safe init of union ---------------- */
        j->value.string  = NULL;
        j->value.number  = 0;
        j->value.boolean = 0;

        j->value.array.items    = NULL;
        j->value.array.count    = 0;
        j->value.array.capacity = 0;

        j->value.object.map.buckets  = NULL;
        j->value.object.map.count    = 0;
        j->value.object.map.capacity = 0;

        /* ---------------- API ---------------- */
        j->get    = scj_get;
        j->set    = scj_set;
        j->has    = scj_has;
        j->add    = scj_add;
        j->at     = scj_at;
        j->len    = scj_len;
        j->str    = scj_str;
        j->num    = scj_num;
        j->bool   = scj_bool;
        j->dump   = scj_dump;
        j->pretty = scj_pretty;
        j->free   = scj_free;

        /* ---------------- error ---------------- */
        j->error.type         = SCJ_OK;
        j->error.message      = NULL;
        j->error.loc.line     = 0;
        j->error.loc.column   = 0;
        j->error.loc.position = 0;

        return j;
}

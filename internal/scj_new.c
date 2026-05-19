/* vi: set sw=8 ts=8: */
#include "scj_new.h"

#include <stdlib.h>

#include "scj_error.h"
#include "scj_free.h"
#include "scj_struct.h"

/*
#include "scj_add.h"
#include "scj_at.h"
#include "scj_bool.h"
#include "scj_dump.h"
#include "scj_free.h"
#include "scj_get.h"
#include "scj_has.h"
#include "scj_len.h"
#include "scj_num.h"
#include "scj_pretty.h"
#include "scj_set.h"
#include "scj_str.h"
#include "scj_struct.h"
*/

/*
scjson scj_new(void) {
        scjson j = malloc(sizeof(struct scjson_struct));
        if (!j) {
                scj_error_set(SCJ_ERR_ALLOC, scj_error_string(SCJ_ERR_ALLOC));
                return NULL;
        }
        j->get            = scj_get;
        j->set            = scj_set; //done
        j->has            = scj_has;
        j->add            = scj_add;
        j->at             = scj_at;
        j->len            = scj_len;
        j->str            = scj_str;
        j->num            = scj_num;
        j->bool           = scj_bool;
        j->dump           = scj_dump;
        j->pretty         = scj_pretty;
        j->free           = scj_free;
        j->internal       = NULL;
        j->error.type     = SCJ_OK;
        j->error.message  = NULL;
        j->error.line     = 0;
        j->error.column   = 0;
        j->error.position = 0;

        return j;

}
*/

scjson scj_new(void) {
        scjson j = malloc(sizeof(struct scjson_struct));
        if (!j) {
                scj_err_set(SCJ_ERR_ALLOC, scj_error_string(SCJ_ERR_ALLOC));
                return NULL;
        }

        j->type                      = SCJ_NULL;
        j->value.object.map.buckets  = NULL;
        j->value.object.map.count    = 0;
        j->value.object.map.capacity = 0;

        j->free = scj_free;
        return j;
}

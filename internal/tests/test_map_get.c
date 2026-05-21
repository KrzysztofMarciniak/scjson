/* vi: set sw=8 ts=8: (internal/tests/test_map_get.c) */
#include <assert.h>

#include "../../scjson.h"
#include "../scj_map_get.h"
#include "../scj_map_init.h"
#include "../scj_map_set.h"
#include "../scj_new.h"
#include "../scj_struct.h"
#include "../scj_free.h"

void test_map_get(void) {
        scjson obj;
        scjson value;
        obj       = scj_new();
        value     = scj_new();
        obj->type = SCJ_OBJECT;
        scj_map_init(obj);
        scj_map_set(obj, "user", value);
        assert(scj_map_get(obj, "user") == value);
        scj_free(obj);
}

#include <assert.h>

#include "../scj_map_init.h"
#include "../scj_map_set.h"
#include "../scj_new.h"
#include "../scj_struct.h"

void test_map_set(void) {
        scjson obj;
        obj       = scj_new();
        obj->type = SCJ_OBJECT;
        scj_map_init(obj);
        scj_map_set(obj, "name", NULL);
        assert(obj->value.object.map.count == 1);
        obj->free(obj);
}

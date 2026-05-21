/* vi: set sw=8 ts=8: (internal/scj_str.c) */

#include "scj_str.h"

#include "../scjson.h"

/**
 * @brief Retrieve the string value from a scjson object.
 *
 * This function returns the underlying string stored in a `scjson` object.
 * If the object is NULL or its type is not `SCJ_STRING`, it returns NULL.
 *
 * @param self A pointer to a `scjson` object.
 * @return The string value if `self` is a string; otherwise, NULL.
 */
const char* _scj_str(scjson self) {
        if (!self) {
                return NULL;
        }

        if (self->type != SCJ_STRING) {
                return NULL;
        }

        return self->value.string;
}

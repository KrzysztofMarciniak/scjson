/* vi: set sw=8 ts=8: */
#include "scj_error.h"

const char* scj_error_string(scj_error error) {
        switch (error) {
                case SCJ_OK:
                        return "SCJSON: no error";
                case SCJ_ERR_ALLOC:
                        return "SCJSON: allocation failed";
                case SCJ_ERR_PARSE:
                        return "SCJSON: parse error";
                case SCJ_ERR_UNEXPECTED_TOKEN:
                        return "SCJSON: unexpected token";
                case SCJ_ERR_UNEXPECTED_END:
                        return "SCJSON: unexpected end";
                case SCJ_ERR_INVALID_STRING:
                        return "SCJSON: invalid string";
                case SCJ_ERR_INVALID_NUMBER:
                        return "SCJSON: invalid number";
                case SCJ_ERR_INVALID_BOOL:
                        return "SCJSON: invalid bool";
                case SCJ_ERR_INVALID_NULL:
                        return "SCJSON: invalid NULL";
                case SCJ_ERR_KEY_NOT_FOUND:
                        return "SCJSON: key not found";
                case SCJ_ERR_INVALID_KEY:
                        return "SCJSON: invalid key";
                case SCJ_ERR_INDEX_OUT_OF_BOUNDS:
                        return "SCJSON: index out of bounds";
                case SCJ_ERR_NOT_OBJECT:
                        return "SCJSON: value is not an object";
                case SCJ_ERR_NOT_ARRAY:
                        return "SCJSON: value is not an array";
                case SCJ_ERR_NOT_STRING:
                        return "SCJSON: value is not a string";
                case SCJ_ERR_NOT_NUMBER:
                        return "SCJSON: value is not a number";
                case SCJ_ERR_NOT_BOOL:
                        return "SCJSON: value is not a bool";
                case SCJ_ERR_DUMP:
                        return "SCJSON: serialization failed";
                case SCJ_ERR_INVALID_VALUE:
                        return "SCJSON: invalid value";
                default:
                        return "SCJSON: unknown error";
        }
}

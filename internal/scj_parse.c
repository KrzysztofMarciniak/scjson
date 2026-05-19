/* vi: set sw=8 ts=8: (internal/scj_parse.c) */
#define _POSIX_C_SOURCE 200809L
#include "scj_parse.h"

#include <stdlib.h>
#include <string.h>

#include "scj_add.h"
#include "scj_at.h"
#include "scj_error.h"
#include "scj_free.h"
#include "scj_len.h"
#include "scj_lexer.h"
#include "scj_map_set.h"
#include "scj_new.h"

/* Forward declarations */
static scjson parse_value(scj_lexer* l);
static scjson parse_array(scj_lexer* l);
static scjson parse_object(scj_lexer* l);

/* parse_value */
static scjson parse_value(scj_lexer* l) {
        scjson j = scj_new();
        if (!j) return NULL;

        scj_token t = scj_lexer_next(l);

        switch (t.type) {
                case SCJ_T_STRING:
                        j->type         = SCJ_STRING;
                        j->value.string = strndup(t.start, t.len);
                        if (!j->value.string) {
                                j->free(j);
                                return NULL;
                        }
                        break;

                case SCJ_T_NUMBER:
                        j->type         = SCJ_NUMBER;
                        j->value.number = t.number;
                        break;

                case SCJ_T_TRUE:
                        j->type          = SCJ_BOOL;
                        j->value.boolean = 1;
                        break;

                case SCJ_T_FALSE:
                        j->type          = SCJ_BOOL;
                        j->value.boolean = 0;
                        break;

                case SCJ_T_NULL:
                        j->type = SCJ_NULL;
                        break;

                case SCJ_T_LBRACK:
                        j->free(j);
                        return parse_array(l);

                case SCJ_T_LBRACE:
                        j->free(j);
                        return parse_object(l);

                default:
                        j->free(j);
                        return NULL;
        }

        return j;
}

/* parse_array */
static scjson parse_array(scj_lexer* l) {
        scjson arr = scj_new();
        if (!arr) return NULL;

        arr->type                 = SCJ_ARRAY;
        arr->value.array.items    = NULL;
        arr->value.array.count    = 0;
        arr->value.array.capacity = 0;

        arr->add  = scj_add;
        arr->len  = scj_len;
        arr->at   = scj_at;
        arr->free = scj_free;

        scj_token t = scj_lexer_next(l);
        if (t.type == SCJ_T_RBRACK) return arr;

        scj_lexer_pushback(l, t);

        while (1) {
                scjson val = parse_value(l);
                if (!val) {
                        arr->free(arr);
                        return NULL;
                }

                scj_error_info err = scj_add(arr, val);
                if (err.type != SCJ_OK) {
                        val->free(val);
                        arr->free(arr);
                        return NULL;
                }

                t = scj_lexer_next(l);
                if (t.type == SCJ_T_COMMA) continue;
                if (t.type == SCJ_T_RBRACK) break;

                arr->free(arr);
                return NULL;
        }

        return arr;
}

/* parse_object */
static scjson parse_object(scj_lexer* l) {
        scjson obj = scj_new();
        if (!obj) return NULL;

        obj->type                      = SCJ_OBJECT;
        obj->value.object.map.buckets  = NULL;
        obj->value.object.map.count    = 0;
        obj->value.object.map.capacity = 0;

        scj_token t = scj_lexer_next(l);
        if (t.type == SCJ_T_RBRACE) return obj;

        scj_lexer_pushback(l, t);

        while (1) {
                t = scj_lexer_next(l);
                if (t.type != SCJ_T_STRING) {
                        obj->free(obj);
                        return NULL;
                }

                char* key = strndup(t.start, t.len);
                if (!key) {
                        obj->free(obj);
                        return NULL;
                }

                t = scj_lexer_next(l);
                if (t.type != SCJ_T_COLON) {
                        free(key);
                        obj->free(obj);
                        return NULL;
                }

                scjson val = parse_value(l);
                if (!val) {
                        free(key);
                        obj->free(obj);
                        return NULL;
                }

                scj_error_info err = scj_map_set(obj, key, val);
                free(key);
                if (err.type != SCJ_OK) {
                        val->free(val);
                        obj->free(obj);
                        return NULL;
                }

                t = scj_lexer_next(l);
                if (t.type == SCJ_T_COMMA) continue;
                if (t.type == SCJ_T_RBRACE) break;

                obj->free(obj);
                return NULL;
        }

        return obj;
}

/* scj_parse API */
scjson scj_parse(const char* text) {
        if (!text) return NULL;

        scj_lexer* l = scj_lexer_new(text);
        if (!l) return NULL;

        scjson result = parse_value(l);

        scj_lexer_free(&l);
        return result;
}

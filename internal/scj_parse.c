#define _POSIX_C_SOURCE 200809L
#include "scj_parse.h"

#include <stdlib.h>
#include <string.h>

#include "scj_add.h"
#include "scj_at.h"
#include "scj_free.h"
#include "scj_len.h"
#include "scj_lexer.h"
#include "scj_map_set.h"
#include "scj_new.h"
#include "../scjson.h"

static scjson parse_value(scj_lexer* l);
static scjson parse_array(scj_lexer* l);
static scjson parse_object(scj_lexer* l);

static void set_error(scjson j, scj_error type, const char* msg, scj_lexer* l) {
    if (!j) return;
    j->error.type = type;
    j->error.message = msg ? msg : "parse error";
    if (l) {
        j->error.loc.line = l->line;
        j->error.loc.column = l->column;
        j->error.loc.position = l->pos;
    }
}

static scjson parse_value(scj_lexer* l) {
    scjson j = scj_new();
    if (!j) return NULL;

    if (!l) {
        set_error(j, SCJ_ERR_PARSE, "Lexer is NULL", NULL);
        return j;
    }

    scj_token t = scj_lexer_next(l);

    switch (t.type) {
    case SCJ_T_STRING:
        j->type = SCJ_STRING;
        j->value.string = strndup(t.start, t.len);
        if (!j->value.string)
            set_error(j, SCJ_ERR_ALLOC, "Failed to allocate string", l);
        return j;

    case SCJ_T_NUMBER:
        j->type = SCJ_NUMBER;
        j->value.number = t.number;
        return j;

    case SCJ_T_TRUE:
        j->type = SCJ_BOOL;
        j->value.boolean = 1;
        return j;

    case SCJ_T_FALSE:
        j->type = SCJ_BOOL;
        j->value.boolean = 0;
        return j;

    case SCJ_T_NULL:
        j->type = SCJ_NULL;
        return j;

    case SCJ_T_LBRACK:
        scj_free(j);
        return parse_array(l);

    case SCJ_T_LBRACE:
        scj_free(j);
        return parse_object(l);

    default:
        set_error(j, SCJ_ERR_UNEXPECTED_TOKEN, "Unexpected token", l);
        return j;
    }
}

static scjson parse_array(scj_lexer* l) {
    scjson arr = scj_new();
    if (!arr) return NULL;

    arr->type = SCJ_ARRAY;
    arr->value.array.items = NULL;
    arr->value.array.count = 0;
    arr->value.array.capacity = 0;

    scj_token t = scj_lexer_next(l);
    if (t.type == SCJ_T_RBRACK) return arr;

    scj_lexer_pushback(l, t);

    while (1) {
        scjson val = parse_value(l);
        if (!val) {
            set_error(arr, SCJ_ERR_PARSE, "Failed to parse array value", l);
            return arr;
        }

        if (val->error.type != SCJ_OK) {
            scj_free(arr);
            return val;
        }

        _scj_add(arr, val);
        if (arr->error.type != SCJ_OK) {
            scj_free(val);
            return arr;
        }

        t = scj_lexer_next(l);
        if (t.type == SCJ_T_COMMA) continue;
        if (t.type == SCJ_T_RBRACK) break;

        set_error(arr, SCJ_ERR_UNEXPECTED_TOKEN, "Expected ',' or ']'", l);
        return arr;
    }

    return arr;
}

static scjson parse_object(scj_lexer* l) {
    scjson obj = scj_new();
    if (!obj) return NULL;

    obj->type = SCJ_OBJECT;
    obj->value.object.map.buckets = NULL;
    obj->value.object.map.count = 0;
    obj->value.object.map.capacity = 0;

    scj_token t = scj_lexer_next(l);
    if (t.type == SCJ_T_RBRACE) return obj;

    scj_lexer_pushback(l, t);

    while (1) {
        t = scj_lexer_next(l);
        if (t.type != SCJ_T_STRING) {
            set_error(obj, SCJ_ERR_INVALID_KEY, "Expected string key", l);
            return obj;
        }

        char* key = strndup(t.start, t.len);
        if (!key) {
            set_error(obj, SCJ_ERR_ALLOC, "Failed to allocate key", l);
            return obj;
        }

        t = scj_lexer_next(l);
        if (t.type != SCJ_T_COLON) {
            free(key);
            set_error(obj, SCJ_ERR_UNEXPECTED_TOKEN, "Expected ':' after key", l);
            return obj;
        }

        scjson val = parse_value(l);
        if (!val) {
            free(key);
            set_error(obj, SCJ_ERR_PARSE, "Failed to parse value for key", l);
            return obj;
        }

        if (val->error.type != SCJ_OK) {
            free(key);
            scj_free(obj);
            return val;
        }

        _scj_map_set(obj, key, val);
        if (obj->error.type != SCJ_OK) {
            free(key);
            scj_free(val);
            return obj;
        }

        free(key);

        t = scj_lexer_next(l);
        if (t.type == SCJ_T_COMMA) continue;
        if (t.type == SCJ_T_RBRACE) break;

        set_error(obj, SCJ_ERR_UNEXPECTED_TOKEN, "Expected ',' or '}'", l);
        return obj;
    }

    return obj;
}

scjson _scj_parse(const char* text) {
    scjson root = scj_new();
    if (!root) return NULL;

    if (!text) {
        set_error(root, SCJ_ERR_INVALID_VALUE, "Input text is NULL", NULL);
        return root;
    }

    scj_lexer* l = scj_lexer_new(text);
    if (!l) {
        set_error(root, SCJ_ERR_ALLOC, "Failed to allocate lexer", NULL);
        return root;
    }

    scjson node = parse_value(l);

    scj_lexer_free(&l);

    if (!node) {
        set_error(root, SCJ_ERR_PARSE, "Failed to parse JSON", NULL);
        return root;
    }

    if (node->error.type != SCJ_OK) {
        scj_free(root);
        return node;
    }

    *root = *node;
    free(node);

    return root;
}

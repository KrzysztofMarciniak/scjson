/* vi: set sw=8 ts=8: (internal/scj_token.h) */
#ifndef SCJ_TOKEN_H
#define SCJ_TOKEN_H

#include <limits.h>
#include <stddef.h>
#include <stdint.h>

/* -------------------- Token types -------------------- */
typedef enum {
        SCJ_T_EOF = 0,

        SCJ_T_LBRACE, /* { */
        SCJ_T_RBRACE, /* } */
        SCJ_T_LBRACK, /* [ */
        SCJ_T_RBRACK, /* ] */
        SCJ_T_COLON,  /* : */
        SCJ_T_COMMA,  /* , */

        SCJ_T_STRING,
        SCJ_T_NUMBER,
        SCJ_T_TRUE,
        SCJ_T_FALSE,
        SCJ_T_NULL,

        SCJ_T_ERROR
} scj_token_type;

/* -------------------- Token structure -------------------- */
typedef struct {
        scj_token_type type;

        const char* start; /* pointer into JSON string, may be NULL */
        size_t len;        /* length of token */

        double number; /* only valid if type == SCJ_T_NUMBER */

        size_t line;     /* line number, 1-based */
        size_t column;   /* column number, 1-based */
        size_t position; /* absolute char offset */
} scj_token;

/* -------------------- Token helpers -------------------- */

/* Initialize token safely */
static inline scj_token scj_token_init(void) {
        scj_token t;
        t.type     = SCJ_T_ERROR;
        t.start    = NULL;
        t.len      = 0;
        t.number   = 0.0;
        t.line     = 0;
        t.column   = 0;
        t.position = 0;
        return t;
}

/* Validate token: returns 1 if valid, 0 if invalid */
static inline int scj_token_valid(const scj_token* t) {
        if (!t) return 0;
        if (t->type < SCJ_T_EOF || t->type > SCJ_T_ERROR) return 0;
        if (t->start == NULL && t->type == SCJ_T_STRING) return 0;
        if (t->len > SIZE_MAX - 1) return 0; /* sanity check */
        if (t->line > SIZE_MAX || t->column > SIZE_MAX ||
            t->position > SIZE_MAX)
                return 0;
        return 1;
}

/* Check if token is a scalar */
static inline int scj_token_is_scalar(const scj_token* t) {
        if (!t) return 0;
        return t->type == SCJ_T_STRING || t->type == SCJ_T_NUMBER ||
               t->type == SCJ_T_TRUE || t->type == SCJ_T_FALSE ||
               t->type == SCJ_T_NULL;
}

#endif

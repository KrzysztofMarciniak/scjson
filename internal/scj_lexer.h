/* vi: set sw=8 ts=8: (internal/scj_lexer.h) */
#ifndef SCJ_LEXER_H
#define SCJ_LEXER_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "scj_token.h"

/* -------------------- Lexer structure -------------------- */
typedef struct scj_lexer {
        const char* src; /* input string */
        size_t pos;      /* current position in src */
        size_t len;      /* length of src */
        size_t line;     /* current line, 1-based */
        size_t column;   /* current column, 1-based */

        /* pushback support */
        int pushback;       /* 1 if a token has been pushed back */
        scj_token pb_token; /* stored pushed-back token */
} scj_lexer;

/* -------------------- Lexer API -------------------- */

/* Allocate a new lexer on heap and initialize */
static inline scj_lexer* scj_lexer_new(const char* input) {
        if (!input) return NULL;
        scj_lexer* l = (scj_lexer*)malloc(sizeof(scj_lexer));
        if (!l) return NULL;
        l->src      = input;
        l->pos      = 0;
        l->len      = strlen(input);
        l->line     = 1;
        l->column   = 1;
        l->pushback = 0;
        return l;
}

/* Free lexer memory */
static inline void scj_lexer_free(scj_lexer** lptr) {
        if (!lptr || !*lptr) return;
        free(*lptr);
        *lptr = NULL;
}

/* Initialize lexer on stack */
void scj_lexer_init(scj_lexer* l, const char* input);

/* Get next token from input */
scj_token scj_lexer_next(scj_lexer* l);

/* Push a token back onto the lexer (for re-parsing) */
void scj_lexer_pushback(scj_lexer* l, scj_token t);

#endif /* SCJ_LEXER_H */

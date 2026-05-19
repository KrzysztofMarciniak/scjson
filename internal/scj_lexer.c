/* vi: set sw=8 ts=8: (internal/scj_lexer.c) */
/* scj_lexer.c */
#include "scj_lexer.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/* -------------------- Helpers -------------------- */
static char peek(scj_lexer* l) {
        if (!l || l->pos >= l->len) return '\0';
        return l->src[l->pos];
}

static char advance(scj_lexer* l) {
        if (!l) return '\0';
        char c = peek(l);
        if (c == '\0') return '\0';

        l->pos++;
        if (c == '\n') {
                l->line++;
                l->column = 1;
        } else {
                l->column++;
        }
        return c;
}

static void skip_ws(scj_lexer* l) {
        while (l && (peek(l) == ' ' || peek(l) == '\t' || peek(l) == '\r' ||
                     peek(l) == '\n')) {
                advance(l);
        }
}

/* -------------------- Lexer initialization -------------------- */
void scj_lexer_init(scj_lexer* l, const char* input) {
        if (!l || !input) return;
        l->src      = input;
        l->pos      = 0;
        l->len      = strlen(input);
        l->line     = 1;
        l->column   = 1;
        l->pushback = 0;
}

/* -------------------- Pushback support -------------------- */
void scj_lexer_pushback(scj_lexer* l, scj_token t) {
        if (!l) return;
        l->pushback = 1;
        l->pb_token = t;
}

/* -------------------- Lexing functions -------------------- */
static scj_token lex_string(scj_lexer* l) {
        scj_token t = scj_token_init();
        if (!l || peek(l) != '"') {
                t.type = SCJ_T_ERROR;
                return t;
        }

        size_t start = ++l->pos;// skip opening quote
        l->column++;

        while (l->pos < l->len) {
                char c = l->src[l->pos];

                if (c == '"') break;
                if (c == '\\') {
                        if (l->pos + 1 < l->len) {
                                l->pos += 2;
                                l->column += 2;
                        } else {
                                l->pos++;
                                l->column++;
                        }
                        continue;
                }

                l->pos++;
                l->column++;
        }

        size_t end = l->pos;
        if (peek(l) == '"') advance(l);

        t.type   = SCJ_T_STRING;
        t.start  = l->src + start;
        t.len    = end - start;
        t.line   = l->line;
        t.column = l->column;

        return t;
}

static int match_kw(scj_lexer* l, const char* kw) {
        size_t i = 0;
        while (kw[i]) {
                if (l->pos + i >= l->len || l->src[l->pos + i] != kw[i])
                        return 0;
                i++;
        }
        return 1;
}

static scj_token lex_keyword(scj_lexer* l) {
        scj_token t = scj_token_init();
        t.start     = l->src + l->pos;
        t.line      = l->line;
        t.column    = l->column;

        if (match_kw(l, "true")) {
                t.type = SCJ_T_TRUE;
                t.len  = 4;
                l->pos += 4;
                l->column += 4;
        } else if (match_kw(l, "false")) {
                t.type = SCJ_T_FALSE;
                t.len  = 5;
                l->pos += 5;
                l->column += 5;
        } else if (match_kw(l, "null")) {
                t.type = SCJ_T_NULL;
                t.len  = 4;
                l->pos += 4;
                l->column += 4;
        } else {
                t.type = SCJ_T_ERROR;
                t.len  = 0;
        }

        return t;
}

static scj_token lex_number(scj_lexer* l) {
        scj_token t  = scj_token_init();
        size_t start = l->pos;

        if (peek(l) == '-' || peek(l) == '+') advance(l);

        int dot_seen = 0;
        while (l->pos < l->len) {
                char c = peek(l);
                if (isdigit(c)) {
                        advance(l);
                } else if (c == '.' && !dot_seen) {
                        dot_seen = 1;
                        advance(l);
                } else {
                        break;
                }
        }

        t.type   = SCJ_T_NUMBER;
        t.start  = l->src + start;
        t.len    = l->pos - start;
        t.number = strtod(t.start, NULL);
        t.line   = l->line;
        t.column = l->column;

        return t;
}

/* -------------------- Public lexer interface -------------------- */
scj_token scj_lexer_next(scj_lexer* l) {
        if (!l) return (scj_token){.type = SCJ_T_ERROR};

        if (l->pushback) {
                l->pushback = 0;
                return l->pb_token;
        }

        skip_ws(l);

        scj_token t = scj_token_init();
        t.line      = l->line;
        t.column    = l->column;

        char c = peek(l);
        if (c == '\0') {
                t.type = SCJ_T_EOF;
                return t;
        }

        switch (c) {
                case '{':
                        advance(l);
                        t.type = SCJ_T_LBRACE;
                        return t;
                case '}':
                        advance(l);
                        t.type = SCJ_T_RBRACE;
                        return t;
                case '[':
                        advance(l);
                        t.type = SCJ_T_LBRACK;
                        return t;
                case ']':
                        advance(l);
                        t.type = SCJ_T_RBRACK;
                        return t;
                case ':':
                        advance(l);
                        t.type = SCJ_T_COLON;
                        return t;
                case ',':
                        advance(l);
                        t.type = SCJ_T_COMMA;
                        return t;
                case '"':
                        return lex_string(l);
        }

        if (isalpha(c)) return lex_keyword(l);
        if (isdigit(c) || c == '-' || c == '+') return lex_number(l);

        advance(l);
        t.type = SCJ_T_ERROR;
        return t;
}

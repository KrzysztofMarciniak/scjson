/* vi: set sw=8 ts=8: (internal/scj_dump.c) */

#include "scj_dump.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scj_struct.h"
#include "scj_type.h"

typedef struct {
        char* buf;
        size_t len;
        size_t cap;
} sbuf;

static int sbuf_reserve(sbuf* b, size_t extra) {
        if (b->len + extra <= b->cap) return 1;

        size_t new_cap = b->cap ? b->cap * 2 : 64;

        while (new_cap < b->len + extra) new_cap *= 2;

        char* tmp = realloc(b->buf, new_cap);
        if (!tmp) return 0;

        b->buf = tmp;
        b->cap = new_cap;
        return 1;
}

static int sbuf_append(sbuf* b, const char* s, size_t n) {
        if (!sbuf_reserve(b, n + 1)) return 0;

        memcpy(b->buf + b->len, s, n);
        b->len += n;
        b->buf[b->len] = '\0';

        return 1;
}

static int sbuf_append_c(sbuf* b, char c) { return sbuf_append(b, &c, 1); }

static int dump_value(sbuf* b, scjson v);

static int dump_string(sbuf* b, const char* s) {
        if (!sbuf_append_c(b, '"')) return 0;

        for (const char* p = s; *p; p++) {
                if (*p == '"' || *p == '\\') {
                        if (!sbuf_append_c(b, '\\')) return 0;
                }
                if (!sbuf_append_c(b, *p)) return 0;
        }

        return sbuf_append_c(b, '"');
}

static int dump_array(sbuf* b, scjson v) {
        if (!sbuf_append_c(b, '[')) return 0;

        for (size_t i = 0; i < v->value.array.count; i++) {
                if (i > 0)
                        if (!sbuf_append_c(b, ',')) return 0;

                if (!dump_value(b, v->value.array.items[i])) return 0;
        }

        return sbuf_append_c(b, ']');
}

static int dump_object(sbuf* b, scjson v) {
        if (!sbuf_append_c(b, '{')) return 0;

        int first = 1;

        for (size_t i = 0; i < v->value.object.map.capacity; i++) {
                scj_node* node = v->value.object.map.buckets[i];

                while (node) {
                        if (!first)
                                if (!sbuf_append_c(b, ',')) return 0;

                        first = 0;

                        if (!dump_string(b, node->key)) return 0;
                        if (!sbuf_append_c(b, ':')) return 0;
                        if (!dump_value(b, node->value)) return 0;

                        node = node->next;
                }
        }

        return sbuf_append_c(b, '}');
}

static int dump_value(sbuf* b, scjson v) {
        if (!v) return sbuf_append(b, "null", 4);

        switch (v->type) {
                case SCJ_NULL:
                        return sbuf_append(b, "null", 4);

                case SCJ_BOOL:
                        return v->value.boolean ? sbuf_append(b, "true", 4)
                                                : sbuf_append(b, "false", 5);
                case SCJ_NUMBER: {
                        char tmp[64];

                        int n =
                            snprintf(tmp, sizeof(tmp), "%g", v->value.number);

                        if (n < 0) {
                                return 0;
                        }

                        /* fast path */
                        if (n < (int)sizeof(tmp)) {
                                return sbuf_append(b, tmp, (size_t)n);
                        }

                        /* fallback path */
                        char* buf = malloc((size_t)n + 1);
                        if (!buf) return 0;

                        snprintf(buf, (size_t)n + 1, "%g", v->value.number);

                        int ok = sbuf_append(b, buf, (size_t)n);

                        free(buf);

                        return ok;
                }
                case SCJ_STRING:
                        return dump_string(b, v->value.string);

                case SCJ_ARRAY:
                        return dump_array(b, v);

                case SCJ_OBJECT:
                        return dump_object(b, v);

                default:
                        return 0;
        }
}

char* scj_dump(scjson self) {
        sbuf b = {0};

        if (!dump_value(&b, self)) {
                free(b.buf);
                return NULL;
        }

        return b.buf;
}

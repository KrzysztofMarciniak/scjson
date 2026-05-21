/* vi: set sw=8 ts=8: (internal/scj_writer.c) */

#include "scj_writer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../scjson.h"

typedef struct {
        char* buf;
        size_t len;
        size_t cap;
        int indent;
        int pretty;
} scj_writer;

static scj_writer writer_new(int pretty) {
        scj_writer w;

        w.buf = malloc(64);
        if (!w.buf) {
                w.len = w.cap = 0;
                return w;
        }

        w.buf[0] = '\0';
        w.len    = 0;
        w.cap    = 64;

        w.indent = 0;
        w.pretty = pretty;

        return w;
}

static int reserve(scj_writer* w, size_t extra) {
        if (w->len + extra + 1 <= w->cap) return 1;

        size_t new_cap = w->cap;

        while (new_cap < w->len + extra + 1) new_cap *= 2;

        char* tmp = realloc(w->buf, new_cap);
        if (!tmp) return 0;

        w->buf = tmp;
        w->cap = new_cap;

        return 1;
}

static int append(scj_writer* w, const char* s, size_t n) {
        if (!reserve(w, n)) return 0;

        memcpy(w->buf + w->len, s, n);
        w->len += n;
        w->buf[w->len] = '\0';

        return 1;
}

static int append_c(scj_writer* w, char c) { return append(w, &c, 1); }

static int append_str(scj_writer* w, const char* s) {
        return append(w, s, strlen(s));
}

static int indent(scj_writer* w) {
        if (!w->pretty) return 1;

        for (int i = 0; i < w->indent; i++) {
                if (!append_str(w, "  ")) return 0;
        }

        return 1;
}

static int write_value(scj_writer* w, scjson v);

static int write_string(scj_writer* w, const char* s) {
        if (!append_c(w, '"')) return 0;

        for (const char* p = s; *p; p++) {
                if (*p == '"' || *p == '\\') {
                        if (!append_c(w, '\\')) return 0;
                }
                if (!append_c(w, *p)) return 0;
        }

        return append_c(w, '"');
}

static int write_array(scj_writer* w, scjson v) {
        if (!append_c(w, '[')) return 0;

        if (w->pretty && v->value.array.count > 0) append_c(w, '\n');

        w->indent++;

        for (size_t i = 0; i < v->value.array.count; i++) {
                if (!indent(w)) return 0;

                if (!write_value(w, v->value.array.items[i])) return 0;

                if (i + 1 < v->value.array.count)
                        append_str(w, w->pretty ? ",\n" : ",");
                else if (w->pretty)
                        append_c(w, '\n');
        }

        w->indent--;

        if (w->pretty && v->value.array.count > 0) indent(w);

        return append_c(w, ']');
}

static int write_object(scj_writer* w, scjson v) {
        if (!append_c(w, '{')) return 0;

        if (w->pretty && v->value.object.map.count > 0) append_c(w, '\n');

        w->indent++;

        int first = 1;

        for (size_t i = 0; i < v->value.object.map.capacity; i++) {
                scj_node* n = v->value.object.map.buckets[i];

                while (n) {
                        if (!first) append_str(w, w->pretty ? ",\n" : ",");

                        first = 0;

                        if (!indent(w)) return 0;
                        if (!write_string(w, n->key)) return 0;
                        if (!append_str(w, w->pretty ? ": " : ":")) return 0;
                        if (!write_value(w, n->value)) return 0;

                        n = n->next;
                }
        }

        w->indent--;

        if (w->pretty && v->value.object.map.count > 0) {
                append_c(w, '\n');
                indent(w);
        }

        return append_c(w, '}');
}

static int write_value(scj_writer* w, scjson v) {
        if (!v) return append_str(w, "null");

        switch (v->type) {
                case SCJ_NULL:
                        return append_str(w, "null");

                case SCJ_BOOL:
                        return v->value.boolean ? append_str(w, "true")
                                                : append_str(w, "false");

                case SCJ_NUMBER: {
                        char tmp[64];
                        int n =
                            snprintf(tmp, sizeof(tmp), "%g", v->value.number);
                        return append(w, tmp, (size_t)n);
                }

                case SCJ_STRING:
                        return write_string(w, v->value.string);

                case SCJ_ARRAY:
                        return write_array(w, v);

                case SCJ_OBJECT:
                        return write_object(w, v);

                default:
                        return 0;
        }
}

char* _scj_write_dump(scjson self) {
        scj_writer w = writer_new(0);

        if (!w.buf) return NULL;

        if (!write_value(&w, self)) {
                free(w.buf);
                return NULL;
        }

        return w.buf;
}

char* _scj_write_pretty(scjson self) {
        scj_writer w = writer_new(1);

        if (!w.buf) return NULL;

        if (!write_value(&w, self)) {
                free(w.buf);
                return NULL;
        }

        return w.buf;
}

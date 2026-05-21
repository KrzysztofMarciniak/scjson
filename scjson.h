#ifndef SCJSON_H
#define SCJSON_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Error codes */
typedef enum {
        SCJ_OK = 0,
        SCJ_ERR_ALLOC,
        SCJ_ERR_PARSE,
        SCJ_ERR_UNEXPECTED_TOKEN,
        SCJ_ERR_UNEXPECTED_END,
        SCJ_ERR_INVALID_STRING,
        SCJ_ERR_INVALID_NUMBER,
        SCJ_ERR_INVALID_BOOL,
        SCJ_ERR_INVALID_NULL,
        SCJ_ERR_KEY_NOT_FOUND,
        SCJ_ERR_INVALID_KEY,
        SCJ_ERR_INDEX_OUT_OF_BOUNDS,
        SCJ_ERR_NOT_OBJECT,
        SCJ_ERR_NOT_ARRAY,
        SCJ_ERR_NOT_STRING,
        SCJ_ERR_NOT_NUMBER,
        SCJ_ERR_NOT_BOOL,
        SCJ_ERR_DUMP,
        SCJ_ERR_INVALID_VALUE,
        SCJ_ERR_UNKNOWN
} scj_error;

/* JSON types */
typedef enum {
        SCJ_NULL = 0,
        SCJ_OBJECT,
        SCJ_ARRAY,
        SCJ_STRING,
        SCJ_NUMBER,
        SCJ_BOOL
} scj_type;

/* Error info struct */
typedef struct {
        scj_error type;
        const char* message;

        struct {
                size_t line;
                size_t column;
                size_t position;
        } loc;
} scj_error_info;

/* Forward declaration of JSON node pointer */
typedef struct scjson_struct* scjson;

/* Map node for objects */
typedef struct scj_node {
        char* key;
        scjson value;
        struct scj_node* next;
} scj_node;

/* Map type */
typedef struct {
        scj_node** buckets;
        size_t capacity;
        size_t count;
} scj_map;

/* JSON struct */
struct scjson_struct {
        scj_type type;

        union {
                char* string;
                double number;
                int boolean;

                struct {
                        scjson* items;
                        size_t count;
                        size_t capacity;
                } array;

                struct {
                        scj_map map;
                } object;
        } value;

        scj_error_info error;
};

/* Parsing */
scjson scj_parse(const char* text);

/* Accessors */
scjson scj_get(scjson self, const char* key);
int scj_has(scjson self, const char* key);
scjson scj_at(scjson self, size_t index);
size_t scj_len(scjson self);

const char* scj_str(scjson self);
double scj_num(scjson self);
int scj_bool(scjson self);
void scj_set(scjson self, const char* key, scjson value);
/* JSON output */
char* scj_dump(scjson self);
char* scj_pretty(scjson self);

/* Modifiers */
void scj_add(scjson self, scjson value);

/* Memory management */
void scj_free(scjson self);
scjson scj_new(void);
scjson scj_new_typed(scj_type type, ...);

/* Error string */
const char* scj_error_string(scj_error error);

#ifdef __cplusplus
}
#endif

#endif /* SCJSON_H */

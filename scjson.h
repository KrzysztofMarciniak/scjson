#ifndef SCJSON_H
#define SCJSON_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct scjson_struct* scjson;

/* -------------------- Creation & Destruction -------------------- */
scjson scj_new(void);
void   scj_free(scjson j);

/* -------------------- Parsing -------------------- */
scjson scj_parse(const char* text);

/* -------------------- Scalars -------------------- */
const char* scj_str(scjson j);     /* returns string value, or NULL if not SCJ_STRING */
double      scj_num(scjson j);     /* returns number value, or 0 if not SCJ_NUMBER */
int         scj_bool(scjson j);    /* returns boolean value, or 0 if not SCJ_BOOL */

/* -------------------- Objects -------------------- */
typedef struct {
    int type;   /* SCJ_OK=0 or error code */
} scj_error_info;

scj_error_info scj_set(scjson obj, const char* key, scjson value);
scjson         scj_get(scjson obj, const char* key);
int            scj_has(scjson obj, const char* key);

/* -------------------- Arrays -------------------- */
scj_error_info scj_add(scjson arr, scjson value);
scjson         scj_at(scjson arr, size_t index);
size_t         scj_len(scjson j);  /* for array or object */

/* -------------------- Serialization -------------------- */
char* scj_dump(scjson j);    /* compact JSON string, must free */
char* scj_pretty(scjson j);  /* indented JSON string, must free */

#ifdef __cplusplus
}
#endif

#endif /* SCJSON_H */

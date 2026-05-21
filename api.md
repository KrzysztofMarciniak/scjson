### Prerequisite Information

Error handling in `scjson` is per-object and stored in `scjson->error`.

```c
scjson root = scj_parse(text);

if (root->error.type != SCJ_OK) {
    printf("Error: %s\n",
        root->error.message
            ? root->error.message
            : scj_error_string(root->error.type));
}
```

Parse errors include location info:

```c
scjson root = scj_parse(text);

if (root->error.type != SCJ_OK) {
    fprintf(stderr,
        "Error: %s (line %zu, col %zu)\n",
        root->error.message,
        root->error.loc.line,
        root->error.loc.column);
}
```

Rule: after any API call that can fail, check:

```c
self->error.type != SCJ_OK
```

No global error state exists, each `scjson` node carries its own error.


### `scj_add`
Adds an element to a JSON array, resizing the internal storage if necessary.
```c
void scj_add(scjson arr, scjson value);
```

```c
scjson arr = scj_new_typed(SCJ_ARRAY);

scj_add(arr, scj_new_typed(SCJ_STRING, "c99"));
scj_add(arr, scj_new_typed(SCJ_STRING, "json"));
scj_add(arr, scj_new_typed(SCJ_STRING, "minimal"));
```

### error list

| condition                | error                   |
| ------------------------ | ----------------------- |
| arr == NULL            | SCJ_ERR_INVALID_VALUE |
| arr->type != SCJ_ARRAY | SCJ_ERR_NOT_ARRAY     |
| allocation failure       | `SCJ_ERR_ALLOC         |


### `scj_at`

Returns the element at a given index from a JSON array. Returns `NULL` if the index is out of bounds or the value is not an array.

```c
scjson scj_at(scjson self, size_t index);
```

```c
scjson arr = scj_new_typed(SCJ_ARRAY);
scj_add(arr, scj_new_typed(SCJ_STRING, "c99"));

scjson v = scj_at(arr, 0);
```

### error list

| condition           | error |
| ------------------- | ----- |
| self == NULL        | NULL  |
| self->type != ARRAY | NULL  |
| index out of bounds | NULL  |

### `scj_bool`

Returns the boolean value stored in a JSON boolean node. Returns `0` if the value is not a boolean or is `NULL`.

```c
int scj_bool(scjson self);
```

```c
if (scj_has(root, "active")) {
    scjson active = scj_get(root, "active");
    printf("active: %s\n", scj_bool(active) ? "true" : "false");
}
```

### error list

| condition          | error |
| ------------------ | ----- |
| self == NULL       | 0     |
| self->type != BOOL | 0     |

I will ignore insults and focus on the task.

### `scj_dump`

Serializes a JSON value into a newly allocated string (compact form). Returns `NULL` on allocation or write failure.
```json
{"enabled":true,"version":2,"tags":["c99","json","minimal"],"title":"scjson"}
```

```c
char* scj_dump(scjson self);
```

```c
scjson obj = scj_new_typed(SCJ_OBJECT);
scj_set(obj, "a", scj_new_typed(SCJ_NUMBER, 1));

char *s = scj_dump(obj);
```

### error list

| condition       | error |
| --------------- | ----- |
| allocation fail | NULL  |
| write failure   | NULL  |
### `scj_error_string`

Converts a `scj_error` code into a human-readable error message string.

```c
const char* scj_error_string(scj_error error);
```

```c
scjson root = scj_parse(text);

if (root->error.type != SCJ_OK) {
    printf("%s\n", scj_error_string(root->error.type));
}
```

### error list

| error type                  | message                        |
| --------------------------- | ------------------------------ |
| SCJ_OK                      | SCJSON: no error               |
| SCJ_ERR_ALLOC               | SCJSON: allocation failed      |
| SCJ_ERR_PARSE               | SCJSON: parse error            |
| SCJ_ERR_UNEXPECTED_TOKEN    | SCJSON: unexpected token       |
| SCJ_ERR_UNEXPECTED_END      | SCJSON: unexpected end         |
| SCJ_ERR_INVALID_STRING      | SCJSON: invalid string         |
| SCJ_ERR_INVALID_NUMBER      | SCJSON: invalid number         |
| SCJ_ERR_INVALID_BOOL        | SCJSON: invalid bool           |
| SCJ_ERR_INVALID_NULL        | SCJSON: invalid NULL           |
| SCJ_ERR_KEY_NOT_FOUND       | SCJSON: key not found          |
| SCJ_ERR_INVALID_KEY         | SCJSON: invalid key            |
| SCJ_ERR_INDEX_OUT_OF_BOUNDS | SCJSON: index out of bounds    |
| SCJ_ERR_NOT_OBJECT          | SCJSON: value is not an object |
| SCJ_ERR_NOT_ARRAY           | SCJSON: value is not an array  |
| SCJ_ERR_NOT_STRING          | SCJSON: value is not a string  |
| SCJ_ERR_NOT_NUMBER          | SCJSON: value is not a number  |
| SCJ_ERR_NOT_BOOL            | SCJSON: value is not a bool    |
| SCJ_ERR_DUMP                | SCJSON: serialization failed   |
| SCJ_ERR_INVALID_VALUE       | SCJSON: invalid value          |
| default                     | SCJSON: unknown error          |

### `scj_free`

Frees a JSON value and all of its nested children recursively.

```c 
void scj_free(scjson obj);
```

```c 
scjson obj = scj_parse(text);

scj_free(obj);
```

### error list

| condition        | error          |
| ---------------- | -------------- |
| obj == NULL      | no-op          |
| allocation state | not applicable |
| type mismatch    | not applicable |

### `scj_get`

Retrieves a value by key from a JSON object. Returns `NULL` if the key does not exist or the value is not an object.

```c
scjson scj_get(scjson self, const char* key);
```

```c
scjson obj = scj_new_typed(SCJ_OBJECT);
scj_set(obj, "name", scj_new_typed(SCJ_STRING, "scjson"));

scjson v = scj_get(obj, "name");
```

### error list

| condition         | error |
| ----------------- | ----- |
| self == NULL      | NULL  |
| key == NULL       | NULL  |
| self->type != OBJ | NULL  |
### `scj_has`

Checks whether a JSON object contains a given key. Returns `1` if present, otherwise `0`.

```c 
int scj_has(scjson self, const char* key);
```

```c 
if (scj_has(obj, "active")) {
    scjson v = scj_get(obj, "active");
}
```

### error list

| condition       | error |
| --------------- | ----- |
| self == NULL    | 0     |
| key == NULL     | 0     |
| self not object | 0     |

### `scj_len`

Returns the number of elements in a JSON array or object. Returns `0` for all other types or `NULL`.

```c
size_t scj_len(scjson self);
```

```c
size_t feature_count = scj_len(features);
```

### error list

| condition    | error |
| ------------ | ----- |
| self == NULL | 0     |
| not array    | 0     |
| not object   | 0     |

### `scj_new`

Allocates and initializes a new empty JSON value (type `NULL`) with zeroed internal state.

```c
scjson scj_new(void);
```

```c
scjson j = scj_new();
```

### error list

| condition       | error |
| --------------- | ----- |
| allocation fail | NULL  |

### `scj_new_typed`

Creates a new JSON value of a given type and initializes its stored value from variadic arguments.

```c
scjson scj_new_typed(scj_type type, ...);
```

```c
scjson s = scj_new_typed(SCJ_STRING, "hello");
scjson n = scj_new_typed(SCJ_NUMBER, 3.14);
scjson b = scj_new_typed(SCJ_BOOL, 1);
```

### error list

| condition        | error                          |
| ---------------- | ------------------------------ |
| allocation fail  | NULL                           |
| strdup fail      | NULL (string case only)        |

### `scj_num`

Returns the numeric value stored in a JSON number node. Returns `0` if the value is `NULL` or not a number.

```c
double scj_num(scjson self);
```

```c 
scjson n = scj_new_typed(SCJ_NUMBER, 42.0);
double v = scj_num(n);
```

### error list

| condition            | error |
| -------------------- | ----- |
| self == NULL         | 0     |
| self->type != NUMBER | 0     |

### `scj_parse`

Parses a JSON string into a `scjson` tree. Returns a root node, on failure returns a node containing error information.

```c
scjson scj_parse(const char* text);
```

```c
scjson root = scj_parse("{\"a\":1,\"b\":[true,false]}");
```

### behavior / errors

| condition          | result                                                          |
| ------------------ | --------------------------------------------------------------- |
| text == NULL       | error node (`SCJ_ERR_INVALID_VALUE`)                            |
| allocation failure | error node (`SCJ_ERR_ALLOC`)                                    |
| lexer failure      | error node (`SCJ_ERR_ALLOC`)                                    |
| parse failure      | error node (`SCJ_ERR_PARSE`)                                    |
| invalid token      | error node (`SCJ_ERR_UNEXPECTED_TOKEN` / `SCJ_ERR_INVALID_KEY`) |

### important design property

* Function **always returns a `scjson` node**
* Errors are stored in `node->error`, not via `NULL` (except internal allocation failures)
* Caller must always check:

```c
scjson root = scj_parse(text);

if (root->error.type != SCJ_OK) {
    // handle error
}
```
### `scj_pretty`

Serializes a JSON value into a newly allocated human-readable (pretty-printed) string.

```c
char* scj_pretty(scjson self);
```

```c 
scjson obj = scj_parse("{\"a\":1,\"b\":[true,false]}");

char *s = scj_pretty(obj);
```

### error list

| condition       | error |
| --------------- | ----- |
| allocation fail | NULL  |
| write failure   | NULL  |

### `scj_set`

Inserts or updates a key-value pair in a JSON object. If the key exists, its value is replaced, otherwise a new entry is created.

```c
void scj_set(scjson self, const char* key, scjson value);
```

```c 
scjson obj = scj_new_typed(SCJ_OBJECT);

scj_set(obj, "a", scj_new_typed(SCJ_NUMBER, 1));
scj_set(obj, "b", scj_new_typed(SCJ_BOOL, 1));
```

### error list

| condition       | error                       |
| --------------- | --------------------------- |
| self == NULL    | sets `SCJ_ERR_INVALID_KEY`  |
| key == NULL     | sets `SCJ_ERR_INVALID_KEY`  |
| self not object | SCJ_ERR_NOT_OBJECT          |
| insert failure  | delegated to `_scj_map_set` |


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

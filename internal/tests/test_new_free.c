/* vi: set sw=8 ts=8: (internal/tests/test_new_free.c) */

#define _POSIX_C_SOURCE 200809L

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../scj_free.h"
#include "../scj_new.h"
#include "../scj_struct.h"
#include "../scj_type.h"

static void test_new_not_null(void) {
        scjson j = scj_new();
        assert(j != NULL);

        scj_free(j);
}

static void test_new_initial_state(void) {
        scjson j = scj_new();
        assert(j != NULL);

        /* type must be valid */
        assert(j->type == SCJ_NULL);

        /* object map must be initialized safely */
        assert(j->value.object.map.buckets == NULL);
        assert(j->value.object.map.count == 0);
        assert(j->value.object.map.capacity == 0);

        /* array must be safe (even if unused) */
        assert(j->value.array.items == NULL);
        assert(j->value.array.count == 0);
        assert(j->value.array.capacity == 0);

        /* scalar fields must be safe */
        assert(j->value.string == NULL);
        assert(j->value.number == 0);
        assert(j->value.boolean == 0);

        scj_free(j);
}

static void test_new_error_state(void) {
        scjson j = scj_new();
        assert(j != NULL);

        assert(j->error.type == SCJ_OK);
        assert(j->error.message == NULL);

        scj_free(j);
}

static void test_free_null_safety(void) {
        /* must not crash */
        scj_free(NULL);
}

static void test_free_object_chain(void) {
        scjson root = scj_new();
        assert(root != NULL);

        /* build a small structure */
        scjson child = scj_new();
        assert(child != NULL);

        scjson leaf = scj_new();
        assert(leaf != NULL);

        root->type                      = SCJ_OBJECT;
        root->value.object.map.capacity = 1;
        root->value.object.map.buckets  = calloc(1, sizeof(scj_node*));

        assert(root->value.object.map.buckets != NULL);

        scj_node* n = malloc(sizeof(scj_node));
        assert(n != NULL);

        n->key   = strdup("a");
        n->value = child;
        n->next  = NULL;

        root->value.object.map.buckets[0] = n;
        root->value.object.map.count      = 1;

        child->type                      = SCJ_OBJECT;
        child->value.object.map.capacity = 1;
        child->value.object.map.buckets  = calloc(1, sizeof(scj_node*));

        scj_node* n2 = malloc(sizeof(scj_node));
        assert(n2 != NULL);

        n2->key   = strdup("b");
        n2->value = leaf;
        n2->next  = NULL;

        child->value.object.map.buckets[0] = n2;
        child->value.object.map.count      = 1;

        scj_free(root);
}

static void test_free_array_chain(void) {
        scjson arr = scj_new();
        assert(arr != NULL);

        arr->type                 = SCJ_ARRAY;
        arr->value.array.capacity = 2;

        arr->value.array.items = calloc(2, sizeof(scjson));
        assert(arr->value.array.items != NULL);

        scjson a = scj_new();
        scjson b = scj_new();

        arr->value.array.items[0] = a;
        arr->value.array.items[1] = b;
        arr->value.array.count    = 2;

        scj_free(arr);
}

void test_new_free(void) {
        test_new_not_null();
        test_new_initial_state();
        test_new_error_state();
        test_free_null_safety();
        test_free_object_chain();
        test_free_array_chain();
}

#include <stdio.h>
#include <stdlib.h>
#include "scjson.h"

static char *read_file(const char *path) {
    FILE *fp = fopen(path, "rb");
    if (!fp) return NULL;

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    char *buffer = malloc(size + 1);
    if (!buffer) {
        fclose(fp);
        return NULL;
    }

    fread(buffer, 1, size, fp);
    buffer[size] = '\0';
    fclose(fp);

    return buffer;
}

int main(void) {
    // -------------------------------------------------------------------------
    // 1. Read and Parse the existing JSON
    // -------------------------------------------------------------------------
    char *text = read_file("data.json");
    if (!text) {
        fprintf(stderr, "failed to read data.json\n");
        return 1;
    }

    scjson root = scj_parse(text);
    if (!root) {
        fprintf(stderr, "failed to parse json\n");
        free(text);
        return 1;
    }

    printf("--- PART 1: Parsing and Validating Existing JSON ---\n");

    // Using scj_has to explicitly check if keys exist before fetching them
    if (scj_has(root, "name")) {
        scjson name = scj_get(root, "name");
        printf("name: %s\n", scj_str(name));
    } else {
        printf("Key 'name' not found.\n");
    }

    if (scj_has(root, "version")) {
        scjson version = scj_get(root, "version");
        printf("version: %.0f\n", scj_num(version));
    }

    if (scj_has(root, "active")) {
        scjson active = scj_get(root, "active");
        printf("active: %s\n", scj_bool(active) ? "true" : "false");
    }

    // -------------------------------------------------------------------------
    // 2. Modifying Arrays via scj_add
    // -------------------------------------------------------------------------
    printf("\n--- PART 2: Modifying an Existing Array ---\n");
    scjson features = scj_get(root, "features");
    if (features) {
        // Print the original features
        size_t feature_count = scj_len(features);
        printf("Original feature count: %zu\n", feature_count);

        // Let's dynamically add a new string item to the array
        // Note: Assuming scj_parse can create transient values or strings
        scjson new_feature = scj_parse("\"auto-updates\"");
        if (new_feature) {
            scj_add(features, new_feature);
            printf("Successfully added 'auto-updates' to features.\n");
        }

        // Verify the array updated using scj_at
        feature_count = scj_len(features);
        printf("Updated feature count: %zu\n", feature_count);
        for (size_t i = 0; i < feature_count; i++) {
            scjson item = scj_at(features, i);
            if (item) printf("  feature[%zu] = %s\n", i, scj_str(item));
        }
    }

    // -------------------------------------------------------------------------
    // 3. Serializing using scj_dump and scj_pretty
    // -------------------------------------------------------------------------
    printf("\n--- PART 3: Serializing Modified JSON ---\n");

    char *raw_dump = scj_dump(root);
    if (raw_dump) {
        printf("Raw JSON string:\n%s\n", raw_dump);
        free(raw_dump);
    }

    char *pretty = scj_pretty(root);
    if (pretty) {
        printf("\nPretty JSON string:\n%s\n", pretty);
        free(pretty);
    }

    // Clean up the parsed structure
    scj_free(root);
    free(text);

    return 0;
}

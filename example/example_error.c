#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    if (fread(buffer, 1, size, fp) != (size_t)size) {
        free(buffer);
        fclose(fp);
        return NULL;
    }

    buffer[size] = '\0';
    fclose(fp);
    return buffer;
}

static void print_error_loc(const char *text, scjson root) {
    size_t err_pos = root->error.loc.position;

    const char *line_start = text;
    const char *p = text;
    while (p < text + err_pos) {
        if (*p == '\n') {
            line_start = p + 1;
        }
        p++;
    }

    const char *line_end = line_start;
    while (*line_end && *line_end != '\n') line_end++;

    fwrite(line_start, 1, line_end - line_start, stdout);
    putchar('\n');

    size_t col = root->error.loc.column > 0 ? root->error.loc.column - 1 : 0;
    for (size_t i = 0; i < col; i++) putchar(' ');
    putchar('^');
    putchar('\n');
}

int main(void) {
    char *text = read_file("invalid.json");
    if (!text) {
        fprintf(stderr, "Error: Failed to read invalid.json\n");
        return 1;
    }

    scjson root = scj_parse(text);

    if (root->error.type != SCJ_OK) {
        fprintf(stderr, "Parse error: %s at line %zu, column %zu (pos %zu)\n",
                root->error.message ? root->error.message : scj_error_string(root->error.type),
                root->error.loc.line,
                root->error.loc.column,
                root->error.loc.position);

        print_error_loc(text, root);

        scj_free(root);
        free(text);
        return 1;
    }

    printf("JSON parsed successfully!\n");

    scj_free(root);
    free(text);
    return 0;
}

#!/usr/bin/env bash

PROJECT_ROOT="$(pwd)"
DOCS_DIR="$PROJECT_ROOT/docs"
HTML_OUTPUT="$DOCS_DIR/html"

mkdir -p "$HTML_OUTPUT"

DOXYFILE="$PROJECT_ROOT/Doxyfile"

if [ ! -f "$DOXYFILE" ]; then
    doxygen -g "$DOXYFILE"
    sed -i "s|OUTPUT_DIRECTORY .*|OUTPUT_DIRECTORY = docs|" "$DOXYFILE"
    sed -i "s|GENERATE_HTML .*|GENERATE_HTML = YES|" "$DOXYFILE"
    sed -i "s|HTML_OUTPUT .*|HTML_OUTPUT = html|" "$DOXYFILE"
    sed -i "s|INPUT .*|INPUT = internal|" "$DOXYFILE"
    sed -i "s|RECURSIVE .*|RECURSIVE = YES|" "$DOXYFILE"
fi

cd "$PROJECT_ROOT" || exit 1
doxygen "$DOXYFILE"

#!/bin/bash

if test $# -ne 1 ; then
    echo "Usage: $0 SCRIPT.c"
    exit 1
fi

SRC=$1

if ! test -f "$SRC"; then
    echo "Error: File '$SRC' not found!"
    exit 1
fi

base_name=$(basename "$SRC" .c)

gcc -Wall -Wextra -std=c99 -o "$base_name" "$SRC"

if test $? -eq 0; then
    echo "Compilation successful: $base_name"
else
    echo "Compilation failed!"
    exit 1
fi

exit 0

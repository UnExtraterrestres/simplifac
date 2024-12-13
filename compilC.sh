#!/bin/bash

get_dir_base_name()
{
    script_path=$(readlink -f "$0")

    script_dir=$(dirname "$script_path")

    dir_name=$(basename "$script_dir")

    dir_base_name=${dir_name%.result}

    echo "$dir_base_name.c"
}

base_pgrm=$(get_dir_base_name)
if test $# -ge 1; then
    base_pgrm="$1"
fi


if ! test -f "$base_pgrm"; then
    echo "Error: File '$base_pgrm' not found!"
    exit 1
fi

base_name=$(basename "$base_pgrm" .c)

gcc -Wall -Wextra -std=c99 -o "$base_name" "$base_pgrm"

if test $? -eq 0; then
    echo "Compilation successful: $base_name"
else
    echo "Compilation failed!"
    exit 1
fi

exit 0

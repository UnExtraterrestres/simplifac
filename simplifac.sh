#!/bin/bash

USAGE="Usage : ./$0 OUTPUT_FILE_NAME FUNCTIONS[...]"
HELPER="For more information, please use : $0 --help"

WEBINFOS="https://github.com/UnExtraterrestres/simplifac"
SIGNATURE="// Fichier généré par simplifac. Plus d'informations : $WEBINFOS"

cmd_help()
{
    echo " "
    echo "$USAGE"
    echo " "
    echo "Generate a .c file, with basic prewritten specified functions, and they needs."
    echo "If OUTPUT_FILE_NAME exists, it will be overwritten."
    echo " "
    echo "OPTIONS"
    echo "   --help                 show help and exit"
    echo " "
    echo "For more code information, please : RTFM."
    echo " "

    exit 0
}

error_message()
{

    # fonction permettant d'afficher et renvoyer un message d'erreur.
    # l'erreur peut-être spécifié en argument

    ERROR_MESSAGE="Error :"

    if test $# -ne 1; then
        ERROR_MESSAGE="$ERROR_MESSAGE unspecified error"
    else
        ERROR_MESSAGE="$ERROR_MESSAGE $1"
    fi

    echo "$ERROR_MESSAGE"
    echo "$HELPER">&2
    exit 1
}

get_needs()
{
    if test $# -ne 1; then
        error_message "get_needs invalid number of arguments."
    fi

    local file="sysfunc/$1.c"

    if ! test -f "$file"; then
        error_message "get_needs file $file does not exist."
    fi

    grep -E '^#(define|include)' "$file"
}

get_functions()
{
    if test $# -ne 1; then
        error_message "get_functions invalid number of arguments."
    fi

    local file="sysfunc/$1.c"

    if ! test -f "$file"; then
        error_message "get_function file $file does not exist."
    fi

    grep -E -v '^#(define|include)|^$' "$file"
}

get_needsNdFunctions()
{
    if test 1 -ge $#; then
        error_message "get_needsNdFunctions invalid number of arguments."
    fi

    ALLNEEDS="$1"
    echo "" > "$ALLNEEDS"
    shift

    ALLFUNCTIONS="$1"
    echo "" > "$ALLFUNCTIONS"
    shift

    for ARG in $@; do
        get_needs "$ARG" >> "$ALLNEEDS"
        get_functions "$ARG" >> "$ALLFUNCTIONS"
    done
}

write_needs()
{
    if test $# -ne 1; then
        error_message "write_needs invalid number of arguments."
    fi

    grep -E '^#define' "$1" >> "$OUTFILE"
    grep -E '^#include' "$1" >> "$OUTFILE"
}

write_functions()
{
    if test $# -ne 1; then
        error_message "write_functions invalid number of arguments."
    fi

    cat "$1" >> "$OUTFILE"
    echo " " >> "$OUTFILE"

    cat << EOF >> "$OUTFILE"
int main(int argc, char **argv)
{

    return 0;
}
EOF
}

write_needsNdFunctions()
{
    if test 1 -ge $#; then
        error_message "write_needsNdFunctions invalid number of arguments."
    fi

    write_needs "$1"
    write_functions "$2"
}

merge_needsNdFunctions()
{
    ALLNEEDS="$RES_PATH/needs"
    ALLFUNCTIONS="$RES_PATH/functions"

    get_needsNdFunctions "$ALLNEEDS" "$ALLFUNCTIONS" $@
    write_needsNdFunctions "$ALLNEEDS" "$ALLFUNCTIONS"
}

if test $1 == '--help'; then
    cmd_help
fi
if test 1 -ge $#; then
    error_message "Invalid number of arguments."
fi

RES_PATH="$1.result"
if ! test -e "$RES_PATH"; then
    mkdir "$RES_PATH"
fi

if ! test "${1##*.}" = "c"; then
    OUTFILE="$RES_PATH/$1.c"
else
    OUTFILE="$RES_PATH/$1"
fi
shift

echo "$SIGNATURE" > "$OUTFILE"

merge_needsNdFunctions $@

exit 0

#!/bin/bash

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
    exit 1
}

check_file_type()
{

    # return 0 if .zip
    # return 1 if .tar.gz
    # TODO : à revoir

    if ! test -e "$1" || ! test -f "$1"; then
        error_message "unarchive '$1' must exist and be a file."
    fi

    file_type=$(file -b --mime-type "$1")

    if test "$file_type" == "application/zip"; then
        exit 0
    fi

    if test "$file_type" == "application/gzip"; then
        
        if tar -tzf "$file" &>/dev/null; then
            exit 1
        else
            error_message "$1 is gzip, but is'nt tarball file."
        fi
    fi

    error_message "$1 is'nt zip or tar.gz."
}

unarchive()
{
    
    if test $# -ne 1; then
        error_message "unarchive invalid number of arguments."
    fi

    type=$( check_file_type "$1" )

    if test $type -eq 0; then
        echo "$1 is a ZIP file."
    else
        echo "$1 is a TAR.GZ file."
    fi
}

unarchive "fichier.zip"

exit 0

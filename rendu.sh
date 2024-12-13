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

unarchive()
{
    
    if test $# -ne 1; then
        error_message "unarchive invalid number of arguments."
    fi

    # test si fichier existe
    # récupération type d'archive
}

exit 0

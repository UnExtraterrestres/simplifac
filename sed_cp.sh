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

if test 3 -ne $#; then
    error_message "Invalid number of arguments."
fi

OLD_STRING="$1"
TEMPLATE_FILENAME="$2"
NEW_FILENAME="$3"

mkdir "res_$NEW_FILENAME"
sed "s/$OLD_STRING/$NEW_FILENAME/g" "$TEMPLATE_FILENAME" > "res_$NEW_FILENAME"/"$NEW_FILENAME"

echo "Nouveau fichier créé : $NEW_FILENAME"

exit 0

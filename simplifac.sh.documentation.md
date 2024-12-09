# simplifac.sh documentation

Ce script Bash génère un fichier .c avec des fonctions prédéfinies spécifiées et leurs dépendances. Si le fichier de sortie existe déjà, il sera écrasé. Le script utilise des fichiers de fonctions système situés dans le répertoire sysfunc/.
Prérequis

    Un interpréteur Bash (/bin/bash).
    Les fichiers de fonctions système doivent être présents dans le répertoire sysfunc/.

## Installation

    Assurez-vous que le script est exécutable :

    chmod +x simplifac.sh

    Placez vos fichiers de fonctions système dans le répertoire sysfunc/.

## Utilisation

./simplifac.sh OUTPUT_FILE_NAME FUNCTIONS[...]

    OUTPUT_FILE_NAME : Le nom du fichier de sortie (sans l'extension .c).
    FUNCTIONS[...] : Une liste de noms de fonctions à inclure dans le fichier de sortie.

### Options

    --help : Affiche l'aide et quitte.

### Exemples

    Générer un fichier .c avec les fonctions foo et bar :

./script_name.sh my_program foo bar

### Afficher l'aide :

    ./script_name.sh --help

## Fonctions Internes
### cmd_help

Affiche l'aide et quitte le script.
### error_message

Affiche un message d'erreur et quitte le script.

    Arguments :
        message (optionnel) : Le message d'erreur à afficher.

### get_needs

Récupère les dépendances (#define et #include) d'un fichier de fonction système.

    Arguments :
        function_name : Le nom de la fonction système.

### get_functions

Récupère le code des fonctions d'un fichier de fonction système.

    Arguments :
        function_name : Le nom de la fonction système.

### get_needsNdFunctions

Récupère les dépendances et les fonctions de plusieurs fichiers de fonctions système.

    Arguments :
        ALLNEEDS : Le fichier où stocker les dépendances.
        ALLFUNCTIONS : Le fichier où stocker les fonctions.
        FUNCTIONS[...] : La liste des fonctions à inclure.

### write_needs

Écrit les dépendances dans le fichier de sortie.

    Arguments :
        needs_file : Le fichier contenant les dépendances.

### write_functions

Écrit les fonctions dans le fichier de sortie et ajoute une fonction main par défaut.

    Arguments :
        functions_file : Le fichier contenant les fonctions.

### write_needsNdFunctions

Écrit les dépendances et les fonctions dans le fichier de sortie.

    Arguments :
        needs_file : Le fichier contenant les dépendances.
        functions_file : Le fichier contenant les fonctions.

### merge_needsNdFunctions

Fusionne les dépendances et les fonctions de plusieurs fichiers de fonctions système et les écrit dans le fichier de sortie.

    Arguments :
        FUNCTIONS[...] : La liste des fonctions à inclure.

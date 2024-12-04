#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

/**
 * \brief Ouvre un répertoire.
 *
 * La fonction open_directory() ouvre un répertoire spécifié par son nom en utilisant la fonction opendir().
 * Si l'ouverture échoue, elle affiche un message d'erreur et termine le programme.
 *
 * \param dirname Le nom du répertoire à ouvrir.
 * \return Un pointeur vers le répertoire ouvert (DIR*), ou NULL en cas d'échec.
 */
DIR* open_directory(const char *dirname)
{
    DIR *dir = opendir(dirname);

    if (dir == NULL)
    {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    return dir;
}

/**
 * \brief Ferme un répertoire.
 *
 * La fonction close_directory() ferme un répertoire ouvert en utilisant la fonction closedir().
 * Si la fermeture échoue, elle affiche un message d'erreur et termine le programme.
 *
 * \param dir Le pointeur vers le répertoire à fermer.
 */
void close_directory(DIR *dir)
{
    if (closedir(dir) == -1)
    {
        perror("closedir");
        exit(EXIT_FAILURE);
    }
}

/**
 * \brief Lit les entrées d'un répertoire.
 *
 * La fonction read_directory() lit toutes les entrées d'un répertoire ouvert et les stocke dans un tableau de chaînes de caractères.
 * Elle utilise readdir() pour lire chaque entrée du répertoire et strdup() pour dupliquer les noms des entrées.
 * Si une allocation de mémoire échoue, elle affiche un message d'erreur et termine le programme.
 *
 * \param dir Le pointeur vers le répertoire ouvert.
 * \param count Un pointeur vers un entier où sera stocké le nombre d'entrées lues.
 * \return Un tableau de chaînes de caractères contenant les noms des entrées du répertoire, ou NULL en cas d'échec.
 */
char** read_directory(DIR *dir, int *count)
{
    struct dirent *entry;
    char **entries = NULL;
    int capacity = 10;
    int size = 0;

    entries = (char**)malloc(capacity * sizeof(char*));

    if (entries == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (size >= capacity)
        {
            capacity *= 2;
            entries = (char**)realloc(entries, capacity * sizeof(char*));

            if (entries == NULL)
            {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }

        entries[size] = strdup(entry->d_name);

        if (entries[size] == NULL)
        {
            perror("strdup");
            exit(EXIT_FAILURE);
        }

        size++;
    }

    *count = size;

    return entries;
}

/**
 * \brief Libère la mémoire allouée pour les entrées d'un répertoire.
 *
 * La fonction free_entries() libère la mémoire allouée pour les entrées d'un répertoire.
 * Elle parcourt le tableau d'entrées et libère chaque chaîne de caractères, puis libère le tableau lui-même.
 *
 * \param entries Le tableau de chaînes de caractères contenant les noms des entrées du répertoire.
 * \param count Le nombre d'entrées dans le tableau.
 */
void free_entries(char **entries, int count)
{
    for (int i = 0; i < count; i++)
    {
        free(entries[i]);
    }

    free(entries);
}

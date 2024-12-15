#include <stdio.h>
#include <stdlib.h>

/**
 * Taille du buffer utilisé pour la lecture et l'écriture des fichiers.
 */
#define BUFSIZE 64

/**
 * \brief Ouvre un fichier en mode spécifié.
 *
 * La fonction open_file() tente d'ouvrir un fichier avec le nom et le mode spécifiés.
 * Si l'ouverture échoue, elle affiche un message d'erreur et termine le programme.
 *
 * \param filename Le nom du fichier à ouvrir.
 * \param mode Le mode d'ouverture du fichier (ex: "r" pour lecture, "w" pour écriture, "a" pour ajout).
 * \return Un pointeur vers le fichier ouvert, ou NULL en cas d'échec.
 */
FILE* open_file(const char *filename, const char *mode)
{
    FILE *file = fopen(filename, mode);

    if (file == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    return file;
}

/**
 * \brief Lit le contenu d'un fichier dans un buffer.
 *
 * La fonction read_file() alloue un buffer de taille BUFSIZE et lit les données du fichier dans ce buffer.
 * Si l'allocation de mémoire ou la lecture échoue, elle affiche un message d'erreur et termine le programme.
 *
 * \param file Le pointeur vers le fichier à lire.
 * \return Un pointeur vers le buffer contenant les données lues, ou NULL en cas d'échec.
 */
char* read_file(FILE *file)
{
    char *buffer = (char *)malloc(BUFSIZE * sizeof(char));

    if (buffer == NULL)
    {
        perror("malloc buffer");
        exit(EXIT_FAILURE);
    }

    size_t sz = fread(buffer, sizeof(char), BUFSIZE, file);

    if (sz == 0 && ferror(file))
    {
        perror("fread");
        free(buffer);
        exit(EXIT_FAILURE);
    }

    return buffer;
}

/**
 * \brief Écrit le contenu d'un buffer dans un fichier.
 *
 * La fonction write_file() écrit les données du buffer dans le fichier spécifié.
 * Si l'écriture échoue, elle affiche un message d'erreur et termine le programme.
 *
 * \param file Le pointeur vers le fichier où écrire.
 * \param buffer Le buffer contenant les données à écrire.
 */
void write_file(FILE *file, const char *buffer)
{
    size_t sz = fwrite(buffer, sizeof(char), BUFSIZE, file);

    if (sz != BUFSIZE)
    {
        perror("fwrite");
        exit(EXIT_FAILURE);
    }
}

/**
 * \brief Ferme un fichier.
 *
 * La fonction close_file() ferme le fichier spécifié.
 * Si la fermeture échoue, elle affiche un message d'erreur et termine le programme.
 *
 * \param file Le pointeur vers le fichier à fermer.
 */
void close_file(FILE *file)
{
    if (fclose(file) == EOF)
    {
        perror("fclose");
        exit(EXIT_FAILURE);
    }
}

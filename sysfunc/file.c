#include <stdio.h>
#include <stdlib.h>

/**
 * Taille du buffer utilisé pour la lecture et l'écriture des fichiers.
 */
#define BUFSIZE 64

/**
 * \struct FileData
 * \brief Structure pour stocker les données lues d'un fichier.
 *
 * Cette structure contient un pointeur vers un buffer de caractères et la taille des données lues.
 * Elle est utilisée pour encapsuler les données lues d'un fichier et leur taille.
 *
 * \var FileData::buffer
 * \brief Pointeur vers le buffer contenant les données lues.
 *
 * Ce pointeur doit être alloué dynamiquement et libéré après utilisation pour éviter les fuites de mémoire.
 *
 * \var FileData::size
 * \brief Taille des données lues dans le buffer.
 *
 * Cette variable indique le nombre d'octets lus dans le fichier et stockés dans le buffer.
 */
typedef struct {
    char *buffer;
    size_t size;
} FileData;

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
 * \return Une structure FileData contenant un pointeur vers le buffer avec les données lues et la taille des données lues.
 *         En cas d'échec, le programme se termine avec un code d'erreur.
 */
FileData read_file(FILE *file)
{
    FileData data;
    data.buffer = (char *)malloc(BUFSIZE * sizeof(char));
    if (data.buffer == NULL)
    {
        perror("malloc buffer");
        exit(EXIT_FAILURE);
    }
    data.size = fread(data.buffer, sizeof(char), BUFSIZE, file);
    if (data.size == 0 && ferror(file))
    {
        perror("fread");
        free(data.buffer);
        exit(EXIT_FAILURE);
    }
    return data;
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

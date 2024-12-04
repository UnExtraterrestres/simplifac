#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * \brief Crée un pipe.
 *
 * La fonction create_pipe() crée un pipe en utilisant la fonction pipe().
 * Si la création du pipe échoue, elle affiche un message d'erreur et termine le programme.
 *
 * \return 0 si la création du pipe réussit, sinon termine le programme.
 */
int create_pipe()
{
    int pipefd[2];

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    return 0;
}

/**
 * \brief Redirige l'entrée standard vers la sortie du pipe.
 *
 * La fonction redirect_stdin_to_pipeout() utilise dup2() pour rediriger l'entrée standard (STDIN_FILENO)
 * vers la sortie du pipe (pipefd). Si la redirection échoue, elle affiche un message d'erreur et termine le programme.
 *
 * \param pipefd Le descripteur de fichier du pipe.
 */
void redirect_stdin_to_pipeout(int pipefd)
{
    if (dup2(pipefd, STDIN_FILENO) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    close(pipefd);
}

/**
 * \brief Redirige la sortie standard vers l'entrée du pipe.
 *
 * La fonction redirect_stdout_to_pipein() utilise dup2() pour rediriger la sortie standard (STDOUT_FILENO)
 * vers l'entrée du pipe (pipefd). Si la redirection échoue, elle affiche un message d'erreur et termine le programme.
 *
 * \param pipefd Le descripteur de fichier du pipe.
 */
void redirect_stdout_to_pipein(int pipefd)
{
    if (dup2(pipefd, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    close(pipefd);
}

/**
 * \brief Redirige la sortie d'erreur standard vers l'entrée du pipe.
 *
 * La fonction redirect_stderr_to_pipein() utilise dup2() pour rediriger la sortie d'erreur standard (STDERR_FILENO)
 * vers l'entrée du pipe (pipefd). Si la redirection échoue, elle affiche un message d'erreur et termine le programme.
 *
 * \param pipefd Le descripteur de fichier du pipe.
 */
void redirect_stderr_to_pipein(int pipefd)
{
    if (dup2(pipefd, STDERR_FILENO) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    close(pipefd);
}

/**
 * \brief Lit des données à partir d'un pipe.
 *
 * La fonction read_from_pipe() lit des données à partir d'un pipe en utilisant la fonction read().
 * Si la lecture échoue, elle affiche un message d'erreur et termine le programme.
 *
 * \param fd Le descripteur de fichier du pipe.
 * \param buf Le buffer où stocker les données lues.
 * \param count Le nombre d'octets à lire.
 * \return Le nombre d'octets lus, ou -1 en cas d'échec.
 */
ssize_t read_from_pipe(int fd, void *buf, size_t count)
{
    ssize_t n = read(fd, buf, count);

    if (n == -1)
    {
        perror("read");
        exit(EXIT_FAILURE);
    }

    return n;
}

/**
 * \brief Écrit des données dans un pipe.
 *
 * La fonction write_to_pipe() écrit des données dans un pipe en utilisant la fonction write().
 * Si l'écriture échoue, elle affiche un message d'erreur et termine le programme.
 *
 * \param fd Le descripteur de fichier du pipe.
 * \param buf Le buffer contenant les données à écrire.
 * \param count Le nombre d'octets à écrire.
 * \return Le nombre d'octets écrits, ou -1 en cas d'échec.
 */
ssize_t write_to_pipe(int fd, const void *buf, size_t count)
{
    ssize_t n = write(fd, buf, count);

    if (n == -1)
    {
        perror("write");
        exit(EXIT_FAILURE);
    }

    return n;
}

/**
 * \brief Ferme un pipe.
 *
 * La fonction close_pipe() ferme les deux extrémités d'un pipe en utilisant la fonction close().
 * Si la fermeture échoue, elle affiche un message d'erreur et termine le programme.
 *
 * \param pipefd Un tableau de deux descripteurs de fichier représentant les deux extrémités du pipe.
 */
void close_pipe(int pipefd[2])
{
    if (close(pipefd[0]) == -1 || close(pipefd[1]) == -1)
    {
        perror("close");
        exit(EXIT_FAILURE);
    }
}

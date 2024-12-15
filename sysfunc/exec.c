#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * \brief Exécute un programme en utilisant execl.
 *
 * La fonction exec_execl() utilise execl pour exécuter un programme spécifié par path avec les arguments donnés.
 * Si l'exécution échoue, elle affiche un message d'erreur et termine le programme.
 *
 * \param path Le chemin vers le programme à exécuter.
 * \param args Le tableau des arguments (doit être terminé par NULL).
 */
void exec_execl(const char *path, char *const args[])
{
    if (execv(path, args) == -1)
    {
        perror("execl");
        exit(EXIT_FAILURE);
    }
}

/**
 * \brief Exécute un programme en utilisant execlp.
 *
 * La fonction exec_execlp() utilise execlp pour exécuter un programme spécifié par file avec les arguments donnés.
 * Si l'exécution échoue, elle affiche un message d'erreur et termine le programme.
 *
 * \param file Le nom du programme à exécuter.
 * \param args Le tableau des arguments (doit être terminé par NULL).
 */
void exec_execlp(const char *file, char *const args[])
{
    if (execvp(file, args) == -1)
    {
        perror("execlp");
        exit(EXIT_FAILURE);
    }
}

/**
 * \brief Exécute un programme en utilisant execle.
 *
 * La fonction exec_execle() utilise execle pour exécuter un programme spécifié par path avec les arguments donnés et un environnement personnalisé.
 * Si l'exécution échoue, elle affiche un message d'erreur et termine le programme.
 *
 * \param path Le chemin vers le programme à exécuter.
 * \param args Le tableau des arguments (doit être terminé par NULL).
 * \param envp L'environnement personnalisé.
 */
void exec_execle(const char *path, char *const args[], char *const envp[])
{
    if (execve(path, args, envp) == -1)
    {
        perror("execle");
        exit(EXIT_FAILURE);
    }
}

/**
 * \brief Exécute un programme en utilisant execv.
 *
 * La fonction exec_execv() utilise execv pour exécuter un programme spécifié par path avec les arguments donnés dans un tableau.
 * Si l'exécution échoue, elle affiche un message d'erreur et termine le programme.
 *
 * \param path Le chemin vers le programme à exécuter.
 * \param argv Le tableau des arguments.
 */
void exec_execv(const char *path, char *const argv[])
{
    if (execv(path, argv) == -1)
    {
        perror("execv");
        exit(EXIT_FAILURE);
    }
}

/**
 * \brief Exécute un programme en utilisant execvp.
 *
 * La fonction exec_execvp() utilise execvp pour exécuter un programme spécifié par file avec les arguments donnés dans un tableau.
 * Si l'exécution échoue, elle affiche un message d'erreur et termine le programme.
 *
 * \param file Le nom du programme à exécuter.
 * \param argv Le tableau des arguments.
 */
void exec_execvp(const char *file, char *const argv[])
{
    if (execvp(file, argv) == -1)
    {
        perror("execvp");
        exit(EXIT_FAILURE);
    }
}

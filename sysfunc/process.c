#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/**
 * \brief Crée un processus enfant en utilisant la fonction fork().
 *
 * La fonction create_child_process() utilise la fonction fork() pour créer un nouveau processus enfant.
 * Si la création du processus échoue, elle affiche un message d'erreur et termine le programme.
 *
 * \return L'identifiant du processus enfant (pid_t) si la création réussit, ou -1 en cas d'échec.
 */
pid_t create_child_process()
{
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    return pid;
}

/**
 * \brief Attend la fin d'un processus enfant.
 *
 * La fonction wait_for_child() utilise la fonction waitpid() pour attendre la fin d'un processus enfant spécifié.
 * Elle affiche un message indiquant si le processus enfant s'est terminé normalement ou a été terminé par un signal.
 * Si l'attente échoue, elle affiche un message d'erreur et termine le programme.
 *
 * \param pid L'identifiant du processus enfant à attendre.
 */
void wait_for_child(pid_t pid)
{
    int status;

    if (waitpid(pid, &status, 0) == -1)
    {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }

    if (WIFEXITED(status))
    {
        printf("Child process %d exited with status %d\n", pid, WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status))
    {
        printf("Child process %d terminated by signal %d\n", pid, WTERMSIG(status));
    }
}

/**
 * \brief Exécute une fonction dans le contexte du processus enfant.
 *
 * La fonction execute_in_child() appelle la fonction spécifiée avec l'argument donné dans le contexte du processus enfant.
 *
 * \param func Un pointeur vers la fonction à exécuter.
 * \param arg L'argument à passer à la fonction.
 */
void execute_in_child(void (*func)(void *), void *arg)
{
    func(arg);
}

/**
 * \brief Fonction exemple à exécuter dans le processus enfant.
 *
 * La fonction child_function() est un exemple de fonction qui peut être exécutée dans le processus enfant.
 * Elle prend un pointeur vers un entier, affiche sa valeur, simule un travail en dormant pendant 2 secondes,
 * puis affiche un message indiquant que le travail est terminé.
 *
 * \param arg Un pointeur vers un entier contenant la valeur à afficher.
 */
void child_function(void *arg) // exemple
{
    int *value = (int *)arg;
    printf("Child process: value = %d\n", *value);
    // Simuler un travail
    sleep(2);
    printf("Child process: work done\n");
}

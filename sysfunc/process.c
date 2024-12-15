#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

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

/**
 * \brief Redirige l'entrée standard vers un descripteur de fichier.
 *
 * La fonction redirect_stdin() utilise dup2() pour rediriger l'entrée standard (STDIN_FILENO)
 * vers le descripteur de fichier spécifié (fd). Si la redirection échoue, elle affiche un message d'erreur et termine le programme.
 *
 * \param fd Le descripteur de fichier vers lequel rediriger l'entrée standard.
 */
void redirect_stdin(int fd)
{
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    close(fd);
}

/**
 * \brief Redirige la sortie standard vers un descripteur de fichier.
 *
 * La fonction redirect_stdout() utilise dup2() pour rediriger la sortie standard (STDOUT_FILENO)
 * vers le descripteur de fichier spécifié (fd). Si la redirection échoue, elle affiche un message d'erreur et termine le programme.
 *
 * \param fd Le descripteur de fichier vers lequel rediriger la sortie standard.
 */
void redirect_stdout(int fd)
{
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    close(fd);
}

/**
 * \brief Redirige la sortie d'erreur standard vers un descripteur de fichier.
 *
 * La fonction redirect_stderr() utilise dup2() pour rediriger la sortie d'erreur standard (STDERR_FILENO)
 * vers le descripteur de fichier spécifié (fd). Si la redirection échoue, elle affiche un message d'erreur et termine le programme.
 *
 * \param fd Le descripteur de fichier vers lequel rediriger la sortie d'erreur standard.
 */
void redirect_stderr(int fd)
{
    if (dup2(fd, STDERR_FILENO) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    close(fd);
}

/**
 * \brief Ouvre un fichier en mode écriture, création et troncature (descripteur, pas un FLUX).
 *
 * La fonction open_file() ouvre un fichier en mode écriture, création et troncature avec les permissions spécifiées.
 * Si l'ouverture du fichier échoue, elle affiche un message d'erreur et termine le programme.
 *
 * \param filename Le nom du fichier à ouvrir.
 * \param mode Les permissions numériques du fichier.
 * \return Le descripteur de fichier si l'ouverture réussit, sinon termine le programme.
 */
int open_file_descriptor(const char *filename, mode_t mode)
{
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, mode);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    return fd;
}

/**
 * \brief Ferme un fichier (descripteur, pas un FLUX).
 *
 * La fonction close_file() ferme un fichier en utilisant la fonction close().
 * Si la fermeture échoue, elle affiche un message d'erreur et termine le programme.
 *
 * \param fd Le descripteur de fichier à fermer.
 */
void close_file_descriptor(int fd)
{
    if (close(fd) == -1)
    {
        perror("close");
        exit(EXIT_FAILURE);
    }
}


/**
 * \brief Fonction exemple complet, d'utilisation des fonctions, pour gérer un processus fils
 *
 * Création d'un processus fils
 * Exection d'une fonction dans un processus fils
 * Synchronisation dans le processus père
 */
int child_process_exemple()
{
    pid_t child_pid = create_child_process();

    if (child_pid == 0)
    {
        // Dans le processus enfant
        int value = 42;
        execute_in_child(child_function, &value);
        exit(EXIT_SUCCESS);
    }
    
    // Dans le processus parent
    wait_for_child(child_pid);

    return 0;
}

int child_process_example_with_redirections()
{

    int pipefd[2];
    create_pipe(pipefd);

    pid_t child_pid = create_child_process();

    if (child_pid == 0)
    {
        
        close_writting_tip(pipefd);

        int fd1 = open_file_descriptor("FILE1", 0644);
        int fd2 = open_file_descriptor("FILE2", 0644);

        redirect_stdin(pipefd[0]);
        redirect_stdout(fd1);
        redirect_stderr(fd2);

        int value = 42;
        execute_in_child(child_function, &value);

        close_file_descriptor(fd1);
        close_file_descriptor(fd2);
        exit(EXIT_SUCCESS);
    }

    close_reading_tip(pipefd);

    // Écrire quelque chose dans le pipe pour que le processus enfant le lise
    const char *message = "Hello from parent\n";
    write_to_pipe(pipefd[1], message, strlen(message));

    close_writting_tip(pipefd);

    wait_for_child(child_pid);

    return 0;
}

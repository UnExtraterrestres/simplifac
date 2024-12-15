/**
 * \brief Fonction exemple complet d'utilisation des fonctions, pour gestion de fichier
 */
int file_exemple()
{
    const char *filename = "example.txt";
    FILE *file = open_file(filename, "w+");

    const char *message = "Hello, World!";
    write_file(file, message);

    rewind(file); // Rembobine le fichier pour lire depuis le début
    char *buffer = read_file(file);
    printf("Read from file: %s\n", buffer);

    free(buffer);
    close_file(file);

    return 0;
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

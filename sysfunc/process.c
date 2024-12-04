#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

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
    } else if (WIFSIGNALED(status))
    {
        printf("Child process %d terminated by signal %d\n", pid, WTERMSIG(status));
    }
}

void execute_in_child(void (*func)(void *), void *arg)
{

    func(arg);
}

void child_function(void *arg) // exemple
{

    int *value = (int *)arg;
    printf("Child process: value = %d\n", *value);
    // Simuler un travail
    sleep(2);
    printf("Child process: work done\n");
}

int main(int argc, char **argv)
{

    return 0;
}

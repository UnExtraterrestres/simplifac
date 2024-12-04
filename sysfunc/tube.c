#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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

void redirect_stdin_to_pipeout(int pipefd)
{

    if (dup2(pipefd, STDIN_FILENO) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    close(pipefd);
}

void redirect_stdout_to_pipein(int pipefd)
{

    if (dup2(pipefd, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    close(pipefd);
}

void redirect_stderr_to_pipein(int pipefd)
{

    if (dup2(pipefd, STDERR_FILENO) == -1)
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    close(pipefd);
}

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

void close_pipe(int pipefd[2])
{

    if (close(pipefd[0]) == -1 || close(pipefd[1]) == -1)
    {
        perror("close");
        exit(EXIT_FAILURE);
    }
}

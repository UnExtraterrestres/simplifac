#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 64

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

void write_file(FILE *file, const char *buffer)
{

    size_t sz = fwrite(buffer, sizeof(char), BUFSIZE, file);

    if (sz != BUFSIZE)
    {
        perror("fwrite");
        exit(EXIT_FAILURE);
    }
}

void close_file(FILE *file)
{

    if (fclose(file) == EOF)
    {
        perror("fclose");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv)
{

    return 0;
}

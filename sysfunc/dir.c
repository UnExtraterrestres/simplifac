#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

DIR* open_directory(const char *dirname)
{

    DIR *dir = opendir(dirname);

    if (dir == NULL)
    {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    return dir;
}

void close_directory(DIR *dir)
{

    if (closedir(dir) == -1)
    {
        perror("closedir");
        exit(EXIT_FAILURE);
    }
}

char** read_directory(DIR *dir, int *count)
{

    struct dirent *entry;
    char **entries = NULL;
    int capacity = 10;
    int size = 0;

    entries = (char**)malloc(capacity * sizeof(char*));

    if (entries == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL)
    {

        if (size >= capacity)
        {

            capacity *= 2;
            entries = (char**)realloc(entries, capacity * sizeof(char*));

            if (entries == NULL)
            {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }

        entries[size] = strdup(entry->d_name);

        if (entries[size] == NULL)
        {
            perror("strdup");
            exit(EXIT_FAILURE);
        }

        size++;
    }

    *count = size;

    return entries;
}

void free_entries(char **entries, int count)
{

    for (int i = 0; i < count; i++)
    {
        free(entries[i]);
    }

    free(entries);
}

int main(int argc, char **argv)
{

    return 0;
}

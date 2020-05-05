#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"
#include <dirent.h>

void print_file(FILE *definition);
FILE *find_file(char *folder, char *name);
char *create_path(char *folder);
int file_exists(char *file, char *folder);

void print_file(FILE *definition)
{
    char c;

    while (1)
    {
        c = getc(definition);
        if (c == EOF)
            break;
        printf("%c", c);
    }
}

//*This function concatenates the SEARCH_DIR with folder and name and returns a file descriptor
FILE *find_file(char *folder, char *name)
{
    FILE *location;
    char path[100];
    char first_letter[2];
    first_letter[0] = name[0];
    first_letter[1] = '\0';
    strcpy(path, SEARCH_DIR);
    strcat(path, folder);
    strcat(path, "/");

    strcat(path, first_letter);
    strcat(path, "/");
    strcat(path, name);

    location = fopen(path, "r");
    return location;
}

char *create_path(char *folder)
{
    char *path = (char *)malloc(sizeof(char) * 100);
    strcpy(path, SEARCH_DIR);
    strcat(path, folder);
    strcat(path, "/");
    printf("%s", path);
    fflush(stdout);
    return path;
}
/**
 * if(1) the file exist inside the folder
 * if(0) the file doesnt exit insed the folder
 * if(-1)error
*/
int file_exists(char *file, char *folder)
{
    return 0;
    char *path = create_path(folder);
    DIR *directory = opendir(path);
    if (directory == NULL)
    {
    }
    return 0;
    free(path);
    return 1;
}

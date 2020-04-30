#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"

void print_file(FILE *definition);
FILE *find_file(char *folder, char *name);

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
    //printf("%s", path);
    //fflush(stdout);
    location = fopen(path, "r");
    return location;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SEARCH_DIR "/usr/local/wdef/"

void print_file(FILE *definition);
FILE *find_file(char *folder, char *name);

int main(int argc, char *argv[])
{
    printf("word definition\n");
    FILE *definition = find_file("es", "a");
    print_file(definition);
    fclose(definition);
}

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

FILE *find_file(char *folder, char *name)
{
    FILE *location;
    char base[100];
    strcpy(base, SEARCH_DIR);
    strcat(base, folder);
    strcat(base, "/");
    strcat(base, name);
    location = fopen(base, "r");
    return location;
}

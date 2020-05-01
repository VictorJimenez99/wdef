#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file_man.h"
#include "mem_man.h"

int main(int argc, char *argv[])
{
    printf("argc: %d", argc);
    fflush(stdout);
    int folder_counter = 0;
    int word_counter = 0;
    int section_counter = 0;

    for (int i = argc - 1; i != 0; i--)
    {
        if (argv[i][0] == '@')
            folder_counter++;
        else if (argv[i][0] == '-')
            section_counter++;
        else
            word_counter++;
    }
    printf("counter %d", word_counter);
    fflush(stdout);
    char **words = (char **)malloc(sizeof(char *) * word_counter);
    if (words == NULL)
    {
        perror("MEMORY ERROR");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i != word_counter; i++)
    {
        words[i] = (char *)malloc(sizeof(char) * 30);
        if (words[i] == NULL)
        {
            perror("MEMORY ERROR");
            exit(EXIT_FAILURE);
        }
    }

    strcpy(words[0], "hola");
    printf("%s", words[0]);

    fflush(stdout);

    printf("%d", folder_counter);
    printf("word definition");
    FILE *definition = find_file("es", "a");
    print_file(definition);
    fclose(definition);
    if (free2d_array(words, word_counter) != 0)
    {
        perror("FREE ERROR");
        exit(EXIT_FAILURE);
    }
}

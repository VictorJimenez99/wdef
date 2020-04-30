#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file_man.h"

int main(int argc, char *argv[])
{
    int folder_counter = 0;
    int word_counter = 0;
    for (int i = argc - 1; i != 0; i--)
    {
        if (argv[i][0] == '@')
            folder_counter++;
    }
    printf("%d", folder_counter);
    printf("word definition");
    FILE *definition = find_file("es", "a");
    print_file(definition);
    fclose(definition);
}

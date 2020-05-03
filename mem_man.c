#include <stdlib.h>
#include <stdio.h>

int free2d_array(char **array, int rows)
{
    if (array == NULL)
    {
        return -1;
    }
    for (int i = rows - 1; i != 0; i--)
    {
        if (array[i] == NULL)
        {
            return -2;
        }
        else
        {
            free(array[i]);
        }
    }
    free(array);
    return 0;
}

void count_arguments(int *folder_counter, int *word_counter, int *section_counter, int argc, char **argv)
{
    for (int i = argc - 1; i != 0; i--)
    {
        if (argv[i][0] == '@')
            *folder_counter = *folder_counter + 1;
        else if (argv[i][0] == '-')
            *section_counter = *section_counter + 1;
        else
            *word_counter = *word_counter + 1;
    }
    if (*folder_counter > 100 || *word_counter > 100 || *section_counter > 100)
    {
        exit(0);
    }
}
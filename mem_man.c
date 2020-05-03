#include <stdlib.h>
#include <stdio.h>

//returns 0 if everything went ok, returns -1 if the array is already free
//returns -2 if a pointer of the second dimension is free
int free2d_array(char **array, int rows)
{
    if (rows == 0)
        return 0;
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

char **create2d_array(int n_pointers, int sizeof_str)
{
    char **array = (char **)malloc(sizeof(char *) * n_pointers);
    if (array == NULL)
    {
        perror("MEMORY ERROR");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i != n_pointers; i++)
    {
        array[i] = (char *)malloc(sizeof(char) * sizeof_str);
        if (array[i] == NULL)
        {
            perror("MEMORY ERROR");
            exit(EXIT_FAILURE);
        }
    }
    return array;
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

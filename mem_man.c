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
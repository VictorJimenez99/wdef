#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file_man.h"
//!CHANGE THIS DEFINE TO WHEREVER YOU HAVE THE WDEF FOLDER
//TODO READ FROM A FILE

int main(int argc, char *argv[])
{
    printf("word definition %03d\n", argc);
    FILE *definition = find_file("es", "a");
    print_file(definition);
    fclose(definition);
}

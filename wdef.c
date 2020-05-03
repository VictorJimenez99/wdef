#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file_man.h"
#include "mem_man.h"

static inline int create_flag(int folder_counter, int word_counter, int section_counter);

int main(int argc, char *argv[])
{
    int folder_counter = 0;
    int word_counter = 0;
    int section_counter = 0;

    count_arguments(&folder_counter, &word_counter, &section_counter, argc, argv);
    char **words = create2d_array(word_counter, 30);
    char **folders = create2d_array(folder_counter, 30);
    char **sections = create2d_array(section_counter, 30);

    char option = create_flag(folder_counter, word_counter, section_counter);

    printf("what needs to be done: %d\n", option);
    /**
     * 0-NoArguments    1-FolderArgument    2-WordArgument  3-Folder&WordArguments
     * 4-SecctionArg    5-Seccion&Folder    6-Section&Word  7-Section&Word&Folder
     * 
     * */

    fflush(stdout);
    //FILE *definition; // = find_file("mineriaDeDatos", "tratamientoDeDatos");
    //print_file(definition);
    //fclose(definition);
    fflush(stdout);
    //word_counter++;
    if (free2d_array(words, word_counter) != 0)
    {
        perror("FREE ERROR");
        exit(EXIT_FAILURE);
    }
    if (free2d_array(folders, folder_counter) != 0)
    {
        perror("FREE ERROR");
        exit(EXIT_FAILURE);
    }
    if (free2d_array(sections, section_counter) != 0)
    {
        perror("FREE ERROR");
        exit(EXIT_FAILURE);
    }
}

static inline int create_flag(int folder_counter, int word_counter, int section_counter)
{
    int fflag = 0, wflag = 0, sflag = 0;
    if (folder_counter > 0)
        fflag = 1;
    if (word_counter > 0)
        wflag = 2;
    if (section_counter > 0)
        sflag = 4;
    return fflag | wflag | sflag;
    /**
     * 0-NoArguments    1-FolderArgument    2-WordArgument  3-Folder&WordArguments
     * 4-SecctionArg    5-Seccion&Folder    6-Section&Word  7-Section&Word&Folder
     * 
     * */
}

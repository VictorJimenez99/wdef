#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file_man.h"
#include "mem_man.h"

int create_flag(int folder_counter, int word_counter, int section_counter);
void gather_args(char **array, int counter, char **argv, int option);
void print2d_array(char **array, int counter);
void security(char *word);

int main(int argc, char *argv[])
{
    int folder_counter = 0;
    int word_counter = 0;
    int section_counter = 0;

    count_arguments(&folder_counter, &word_counter, &section_counter, argc, argv);
    char **words = create2d_array(word_counter, 30);
    char **folders = create2d_array(folder_counter, 30);
    char **sections = create2d_array(section_counter, 30);

    gather_args(folders, folder_counter, argv, 0);
    gather_args(words, word_counter, argv, 1);
    gather_args(sections, section_counter, argv, 2);
    //print2d_array(folders, folder_counter);
    //print2d_array(words, word_counter);
    //print2d_array(sections, section_counter);

    char option = create_flag(folder_counter, word_counter, section_counter);
    //printf("Q:What needs to be done?\nA: %d\n", option);
    /**
     * 0-NoArguments    1-FolderArgument    2-WordArgument  3-Folder&WordArguments
     * 4-SecctionArg    5-Seccion&Folder    6-Section&Word  7-Section&Word&Folder
     * 
     * */
    int found = 0;
    switch (option)
    {
    case 1:
        for (int i = 0; i != folder_counter; i++)
        {
            printf("FOLDER: %s\n", folders[i]);
            security(folders[i]);
            print_folder_content(folders[i]);
        }
        break;
    case 2:
        /**
         * for each word
         *  seach in every folder
         *   print matches
        */

        for (int i = 0; i != word_counter; i++)
        {
            security(words[i]);
            found += search_every_folder(words[i]);
            //printf("%d\n", found);
            if (!found)
            {
                printf("\"%s\" doesn't exist in the wdef folder\n", words[i]);
            }
        }

        break;
    case 3:
        /**
         * for each folder
         *  for each file
         *   printfile
        */
        for (register int i = 0; i != folder_counter; i++)
            for (register int j = 0; j != word_counter; j++)
            {
                security(folders[i]);
                security(words[j]);
                FILE *definition = find_file(folders[i], words[j]);
                if (definition == NULL)
                    printf("the program couldn't find: %s inside: %s\n", words[j], folders[i]);
                else
                {
                    printf("\nFILE: %s\nFOLDER: %s\n\n\n", words[j], folders[i]);
                    print_file(definition);
                    fclose(definition);
                }
            }

        break;
    case 7:
        /**
         * for each folder
         *  for each file
         *   print section
        */
        //printf("case 7");
        for (register int i = 0; i != folder_counter; i++)
            for (register int j = 0; j != word_counter; j++)
            {
                FILE *definition = find_file(folders[i], words[j]);
                if (definition == NULL)
                    printf("The program couldn't find: %s inside: %s\n", words[j], folders[i]);
                else
                {
                    printf("\nFOLDER: %s\nFILE: %s\n\n\n", folders[i], words[j]);
                    for (register int k = 0; k != section_counter; k++)
                    {
                        fseek(definition, 0, SEEK_SET);
                        print_section(definition, sections[k]);
                    }
                    fclose(definition);
                }
            }

        break;
    default:
        printf("NOT ENOUGH ARGUMENTS\ntry:\n $wdef @[folder_name] -[section(optional)] [word]\n");
        break;
    }
    //create_path("test");
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

int create_flag(int folder_counter, int word_counter, int section_counter)
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
void gather_args(char **array, int counter, char **argv, int option)
{
    argv = argv + 1;
    if (option < 0 || option > 2) //its not beeing used properly
    {
        perror("INTERNAL ERROR: GATHER_ARGS FUNCTION");
        exit(EXIT_FAILURE);
    }
    if (counter == 0)
        return;
    int aux = 0;
    char *str;

    if (option == 1)
    {
        //word
        //printf("gathering words\n");
        fflush(stdout);
        while (counter != 0)
        {
            if (argv[aux][0] != '@' && argv[aux][0] != '-')
            {
                str = argv[aux];
                strcpy(array[counter - 1], str);
                counter--;
            }
            aux++;
        }
        return;
    }
    else
    {
        //folder or section
        //printf("gathering data\n");
        fflush(stdout);
        char ch;
        if (option == 0)
            ch = '@'; //folder
        else if (option == 2)
            ch = '-'; //section

        while (counter != 0)
        {
            if (argv[aux][0] == ch)
            {
                str = argv[aux];
                str++;
                strcpy(array[counter - 1], str);
                counter--;
            }

            aux++;
        }
        return;
    }
}

void print2d_array(char **array, int counter)
{
    printf("\nDEBUG, printing 2d array:\n");
    for (int i = 0; i != counter; i++)
    {
        printf("%s\n", array[i]);
    }
}

void security(char *word)
{
    int size = strlen(word);
    for (int i = 0; i != size; i++)
    {
        if (word[i] == '.')
        {
            perror("You're trying to look for something outside the wdef folder\n");
            printf("\"%s\": INVALID ARGUMENT\n", word);
            exit(EXIT_FAILURE);
        }
    }
}

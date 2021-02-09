#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defs.h"
#include <dirent.h>

void create_search_path(char* user_name);

void print_file(FILE *definition);
FILE *find_file(char *folder, char *name);
char *create_path(char *folder);
int file_exists(char *file, char *folder);
void print_section(FILE *file, char *section);
int search_every_folder(char *file);
void print_folder_content(char *folder);

void create_search_path(char* user_name)
{
	strcpy( SEARCH_DIR, user_name );
	strcat(SEARCH_DIR, "/wdef/");
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

    location = fopen(path, "r");
    return location;
}

char *create_path(char *folder)
{
    char *path = (char *)malloc(sizeof(char) * 100);
    strcpy(path, SEARCH_DIR);
    strcat(path, folder);
    strcat(path, "/");
    //printf("%s", path);
    fflush(stdout);
    return path;
}
/**
 * if(1) the file exist inside the folder
 * if(0) the file doesnt exit insed the folder
 * if(-1)error
*/
int file_exists(char *file, char *folder)
{
    return 0;
    char *path = create_path(folder);
    DIR *directory = opendir(path);
    if (directory == NULL)
    {
    }
    return 0;
    free(path);
    return 1;
}

void print_section(FILE *file, char *section)
{
    //printf("section:::::%s\n", section);
    section[strlen(section)] = '\n';
    section[strlen(section)] = '\0';
    int found_match = 0;
    char line[1024];
    while (1)
    {
        if (fgets(line, 1024, file) == NULL)
        {
            section[strlen(section) - 1] = '\0';
            //printf("end of func:%s\n", section);
            if (!found_match)
            {
                printf("PROGRAM:Couldn't find SECTION:\"%s\" inside current FILE\nTry any of the following:\n\n", section);
                fseek(file, 0, SEEK_SET);
                while (1)
                {
                    if (fgets(line, 1024, file) == NULL)
                        break;
                    if (line[0] == '#')
                        printf("%s", line);
                }
                printf("\n\n\n");
            }
            return;
        }
        if (line[0] == '#')
        {
            if (strcmp(section, line + 2) == 0)
            {
                //found a match
                //print this section
                found_match = 1;
                printf("%s", line);
                char c;

                while (1)
                {
                    c = getc(file);
                    if (c == EOF || c == '#')
                    {
                        fseek(file, -1, SEEK_CUR);
                        break;
                    }

                    printf("%c", c);
                }
            }
        }
    }
}

int search_every_folder(char *file)
{
    int retval = 0;
    DIR *root_folder = opendir(SEARCH_DIR);
    struct dirent *subf;

    if (root_folder == 0)
    {
        char ERR[351]; 
        sprintf(ERR, "The program couldn't locate the root folder for wdef make sure you the folder: %s exists\n", SEARCH_DIR);
        perror(ERR);
        exit(EXIT_FAILURE);
    }
    while ((subf = readdir(root_folder)) != NULL)
    {
        if (strcmp(subf->d_name, ".") == 0 || strcmp(subf->d_name, "..") == 0)
            continue;

        char *aux = create_path(subf->d_name);

        char first_letter[2];
        first_letter[0] = file[0];
        first_letter[1] = '\0';
        strcat(aux, first_letter);
        strcat(aux, "/");
        strcat(aux, file);
        //printf("search:%s\n", aux);
        FILE *f = fopen(aux, "r");

        if (f == NULL)
        {
            free(aux);
            retval |= 0;
            continue;
        }

        fclose(f);
        printf("\nfound a match for: \"%s\" at: %s folder\ntry:\nwdef @%s %s\n\n", file, subf->d_name, subf->d_name, file);
        retval |= 1;

        free(aux);

        //printf("%s\n", subf->d_name);
    }

    closedir(root_folder);
    //printf("inside:%d\n", retval);
    return retval;
}

void print_folder_content(char *folder)
{
    char *folder_path = create_path(folder);
    DIR *root_folder = opendir(folder_path);
    struct dirent *sub_f;

    if (root_folder == 0)
    {
        //printf("The specified folder doesn't exist\n");
        return;
    }
    while ((sub_f = readdir(root_folder)) != NULL)
    {
        if (strcmp(sub_f->d_name, ".") == 0 || strcmp(sub_f->d_name, "..") == 0)
            continue;
        printf("%s\n", sub_f->d_name);
        //sub_f->d_name is declared as char[256];
        char sub_folder_name[512];
        sprintf(sub_folder_name, "%s/%s", folder, sub_f->d_name);
        //printf("%s\n", sub_folder_name);

        print_folder_content(sub_folder_name);
    }

    closedir(root_folder);
    free(folder_path);
}

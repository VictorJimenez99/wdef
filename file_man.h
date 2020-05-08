#ifndef FILE_MAN_H
#define FILE_MAN_H

void print_file(FILE *definition);
FILE *find_file(char *folder, char *name);
char *create_path(char *folder);
int file_exists(char *file, char *folder);
void print_section(FILE *file, char *section);
int search_every_folder(char *file);
void print_folder_content(char *folder);
#endif
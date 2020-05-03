#ifndef MEM_MAN_H
#define MEM_MAN_H

int free2d_array(char **array, int rows);
void count_arguments(int *folder_counter, int *word_counter, int *section_counter, int argc, char **argv);
char **create2d_array(int n_pointers, int sizeof_str);
#endif
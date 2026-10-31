#ifndef CREATE_DATABASE_H
#define CREATE_DATABASE_H

#include "types.h"

int create_list(Flist **file_head, char *filename);
Word *create_word_node(char *word);
int add_file_to_word(Word *word_node, char *filename);
Word *search_word(Word *head, char *word);
int search_file(Flist *head, char *filename);
int store_word(Word **head, char *word, char *filename);
void display_word(Word *word);
int write_databasefile(Word *head, FILE *Databasefile);
int read_databasefile(Word **head, FILE *Databasefile);
#endif
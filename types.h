#ifndef TYPES_H
#define TYPES_H
#define FNAME_SIZE 20
#include<ctype.h>
typedef struct node
{   char filename[FNAME_SIZE];
    int count;
    struct node*link;
}Flist;
typedef struct word_node
{    char word[100];
    Flist*file_link;
    struct word_node*link;
}Word;
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "create_database.h"

int create_list(Flist **file_head, char *filename)
{  Flist *new = malloc(sizeof(Flist));
    if (new == NULL)
    {      return 0;
    }
    strcpy(new->filename, filename);
    new->link = NULL;
    if (*file_head == NULL)
    {      *file_head = new;
}
    else
    {      Flist *temp = *file_head;
    while (temp->link != NULL)
        {   temp = temp->link;
        }
        temp->link = new;
    }  return 1;
}
Word *create_word_node(char *word){
    Word*new=malloc(sizeof(Word));
    if(new==NULL){
        return 0;
    }strcpy(new->word,word);
    new->file_link=NULL;
    new->link=NULL;
    return new;
}int add_file_to_word(Word *word_node, char *filename)
{ Flist *temp = word_node->file_link;
      while (temp != NULL)
    {       if (strcmp(temp->filename, filename) == 0)
        {      temp->count++;
            return 1;
        }
        temp = temp->link;
    }
    Flist *new = malloc(sizeof(Flist));
    if (new == NULL)
    { return 0;
    }
    strcpy(new->filename, filename);
    new->count = 1;
    new->link = NULL;
    if (word_node->file_link == NULL)
 {
     word_node->file_link = new;
    }  else
    {
     temp = word_node->file_link;
 while (temp->link != NULL)
        {
            temp = temp->link;
        }
        temp->link = new;
    }
    return 1;
}Word *search_word(Word *head, char *word){
    Word*temp=head;
    while(temp!=NULL){
    if(strcmp(temp->word,word)==0){
       return temp;
    }temp=temp->link;
}return NULL;
}int insert_word(Word **head, char *word)
{
    Word *new = create_word_node(word);
    if (new == NULL)
    {   return 0;
    }
    if (*head == NULL)
    {     *head = new;
return 1;
    }
    if (strcmp(word, (*head)->word) < 0)
    {    new->link = *head;
        *head = new;
        return 1;
    }
    Word *temp = *head;
    while (temp->link != NULL &&
           strcmp(temp->link->word, word) < 0)
    {
  temp = temp->link;
    }
    new->link = temp->link;
    temp->link = new;
    return 1;
}int search_file(Flist *head, char *filename)
{   Flist *temp = head;
    while (temp != NULL)
    {   if (strcmp(temp->filename, filename) == 0)
        {
      return 1;
        }
    temp = temp->link;
    }
    return 0;
}int store_word(Word **head, char *word, char *filename)
{
    Word *temp = search_word(*head, word);
    if (temp == NULL)
    {      if (insert_word(head, word) == 0)
        {
            return 0;
        }
        temp = search_word(*head, word);
    }
    return add_file_to_word(temp, filename);
}
void display_word(Word *word)
{   printf("Word: %s\n", word->word);
    Flist *temp = word->file_link;
while (temp != NULL)
    {
     printf("  File: %s\n", temp->filename);
        temp = temp->link;
    }
}int write_databasefile(Word *head, FILE *Databasefile)
{ Word *wtemp = head;
    while (wtemp != NULL)
    {
        fprintf(Databasefile, "%s", wtemp->word);
        Flist *ftemp = wtemp->file_link;
    while (ftemp != NULL)
        {
         fprintf(Databasefile, " %s:%d",
                    ftemp->filename,
                    ftemp->count);

            ftemp = ftemp->link;
        }
        fprintf(Databasefile, "\n");
        wtemp = wtemp->link;
    }
    return 1;
}int read_databasefile(Word **head, FILE *Databasefile)
{   char line[500];
    while (fgets(line, sizeof(line), Databasefile) != NULL)
    {       char *token = strtok(line, " \n");
 if (token == NULL)
        {
      continue;
        }

 char word[100];
strcpy(word, token);
token = strtok(NULL, " \n");
while (token != NULL)       
{
 char filename[FNAME_SIZE];
int count;
char *colon = strchr(token, ':');
 if (colon != NULL)
     {  *colon = '\0';
        strcpy(filename, token);
        count = atoi(colon + 1);
           Word *temp = search_word(*head, word);
 if (temp == NULL)
                {  insert_word(head, word);
                    temp = search_word(*head, word);
                }
        Flist *new = malloc(sizeof(Flist));
                if (new == NULL)
                {
                    return 0;
                }
        strcpy(new->filename, filename);
        new->count = count;
                new->link = NULL;
   if (temp->file_link == NULL)
           {
                    temp->file_link = new;
                }
                else {     Flist *last = temp->file_link;
                    while (last->link != NULL)
                    {     last = last->link;
              }
                    last->link = new;
                }
            }    token = strtok(NULL, " \n");
        }
    }   return 1;
}
#include <stdio.h>
#include "create_database.h"
#include <ctype.h>
#include <string.h>

int main(int argc, char **argv)
{ Flist *file_head = NULL;
    Word *word_head = NULL;
     for (int i = 1; i <argc; i++)
    {   create_list(&file_head, argv[i]);
    }
    Flist *temp = file_head;
    while (temp != NULL)
    {        FILE *fp = fopen(temp->filename, "r");

 if (fp == NULL)
    {
 printf("File not opened %s\n", temp->filename);
 }
 else
    {
     printf("Successfully opened %s\n", temp->filename);
     printf("\nContents of %s:\n", temp->filename);
  char word[100];
   char ch;
  int i = 0;
  while ((ch = fgetc(fp)) != EOF)
            {
   if (isalpha(ch))
  { word[i++] = ch;
   }
   else
    {
 if (i > 0)
{
   word[i] = '\0';
    printf("Word: %s\n", word);
    store_word(&word_head, word, temp->filename);
    i=0;
    }
      }
  }if (i > 0)
{
    word[i] = '\0';
    printf("Word: %s\n", word);

    store_word(&word_head, word, temp->filename);
}
fclose(fp);
        }
        temp = temp->link;
    }printf("\n========== WORD LIST ==========\n");
Word *wtemp = word_head;

while (wtemp != NULL)
{
    printf("Word: %s\n", wtemp->word);
    Flist *ftemp = wtemp->file_link;
    while (ftemp != NULL)
    {    printf("  File: %s\n", ftemp->filename);
        ftemp = ftemp->link;
    }
    wtemp = wtemp->link;
}FILE *db = fopen("database.txt", "w");

if (db == NULL)
{
    printf("Database file not opened\n");
}
else
{  write_databasefile(word_head, db);
    fclose(db);
    printf("\nDatabase created successfully\n");
}FILE *db_read = fopen("database.txt", "r");

if (db_read == NULL)
{  printf("Database file not opened\n");
}
else
{
    Word *loaded_head = NULL;
    read_databasefile(&loaded_head, db_read);
    fclose(db_read);
    printf("\n========== LOADED DATABASE ==========\n");
    Word *temp_word = loaded_head;

    while (temp_word != NULL)
    {
        printf("Word: %s\n", temp_word->word);

        Flist *temp_file = temp_word->file_link;

        while (temp_file != NULL)
        {         printf("  File: %s\n", temp_file->filename);
            temp_file = temp_file->link;
        }

        temp_word = temp_word->link;
    }int choice;

while (1)
{
    printf("\n========== MENU ==========\n");
    printf("1. Display Database\n");
    printf("2. Search Database\n");
    printf("3. Save Database\n");
    printf("4. Exit\n");
printf("5. Update Database\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("\n========== DATABASE ==========\n");

        Word *temp_word = loaded_head;

        while (temp_word != NULL)
        {
            printf("Word: %s\n", temp_word->word);

            Flist *temp_file = temp_word->file_link;

            while (temp_file != NULL)
            {
               printf("  File: %s  Count: %d\n",
       temp_file->filename,
       temp_file->count);
                temp_file = temp_file->link;
            }

            temp_word = temp_word->link;
        }
    }
    else if (choice == 2)
    {
        char search[500];

        printf("\nEnter words to search: ");
        scanf(" %[^\n]", search);

        char *token = strtok(search, " ");

        char filenames[100][FNAME_SIZE];
        int count[100];
        int file_count = 0;

        while (token != NULL)
        {
            Word *result = search_word(loaded_head, token);
            if (result != NULL)
            {
                Flist *temp_file = result->file_link;
                while (temp_file != NULL)
                {
                    int found = 0;
                    for (int i = 0; i < file_count; i++)
                    {
           if (strcmp(filenames[i], temp_file->filename) == 0)
    {
     count[i]++;
      found = 1;
          break;
           }
         }

         if (found == 0)
             {
             strcpy(filenames[file_count], temp_file->filename);
         count[file_count] = 1;
    file_count++;
                    }

                    temp_file = temp_file->link;
                }
            }

            token = strtok(NULL, " ");
        }

        if (file_count == 0)
        {
            printf("No matching files found\n");
        }
        else
        {
            int max = 0;

            printf("\n========== SEARCH RESULT ==========\n");

            for (int i = 0; i < file_count; i++)
            {
      printf("%s -> %d match(es)\n",
                       filenames[i], count[i]);
                if (count[i] > max)
                {
                    max = count[i];
                }
            }
 printf("\nMaximum matching files:\n");

            for (int i = 0; i < file_count; i++)
            {
                if (count[i] == max)
                {
printf("%s\n", filenames[i]);
                }
            }
        }
    }
    else if (choice == 3)
{
    char backup[FNAME_SIZE];

    printf("Enter backup filename: ");
    scanf("%19s", backup);

    FILE *db_save = fopen(backup, "w");

    if (db_save == NULL)
 {
        printf("Database file not opened\n");
    }
    else
    {
        write_databasefile(loaded_head, db_save);
        fclose(db_save);
  printf("Database saved successfully\n");
    }
}
    else if (choice == 4)
    {
  printf("Exiting...\n");
        break;
    }else if (choice == 5)
{
    char filename[FNAME_SIZE];

    printf("Enter new filename: ");
    scanf("%19s", filename);

    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
 {
        printf("File not opened\n");
    }
 else
{
        char word[100];
        char ch;
        int i = 0;

        printf("\nReading %s...\n", filename);

        while ((ch = fgetc(fp)) != EOF)
        {
            if (isalpha(ch))
            {
                word[i++] = ch;
            }
            else
            {
if (i > 0)
                {
                    word[i] = '\0';

     store_word(&loaded_head, word, filename);

     i = 0;
        }
     }
        }

        /* Handle last word */
        if (i > 0)
        {
      word[i] = '\0';

     store_word(&loaded_head, word, filename);
        }

        fclose(fp);
        printf("Database updated successfully\n");
    }
}
    else
    {
    printf("Invalid choice\n");
    }
}
}
    return 0;

}
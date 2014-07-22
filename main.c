/* Andoni Garcia's Markov Babbler. 2014. */

#include "markov.h"

int main(int argc, char *argv[])
{
  printf("~~~ Welcome to Andoni's Markov Babbler ~~~\n");
  printf("\n\n This program will use Markov Modeling to write sentences and paragraphs using probability analysis of words and their adjacent words from given input files. As such you must input at least one file (preferably a text file of decent size to give the most accurate word predictions) for the Markov Babbler to read before it can begin constructing coherent-ish sentences. The babbler uses a pseudo-random process to grab next words, so every time you run the babbler on the same input file(s), it should produce new and unique outputs. Be warned though, there is a high probability that if your text file contains loops between next words (i.e. it says \"then I\" and later says \"I then\") the babbler might get caught in unwanted loops.\n Have fun!\n");
  printf("===================================================================\n");
  
  // Creates a new hash table
  htable *table;
  table = new_htable(51);

  srand(time(NULL));

  // Parses through a given input file
  char file[127];
  printf("\nWhich file do you want to upload? ");
  scanf("%s", file);
  FILE *upload;
  upload = fopen(file, "r");
  if(upload == NULL){
    printf("Error: Problem uploading file %s", file);
    exit(0);
  }
  table = insert_file(upload, table);
  fclose(upload);

  /* Allows the user to upload multiple files
  char answer[127];
  printf("\nDo you want to insert another file? (yes/no): ");
  scanf("%s", answer);
  while(!strcmp(answer, "yes") || !strcmp(answer, "Yes")){
    printf("\n\nWhich file do you want to upload? ");
    scanf("%s", file);
    upload = fopen(file, "r");
    table = insert_file(upload, table);
    fclose(upload);
    printf("\nDo you want to insert another file? (yes/no): ");
    scanf("%s", answer);
  }
  */

  // Performs the babbling
  int paragraphs, sentences;
  printf("\nHow many paragraphs do you want to write? ");
  scanf("%d", &paragraphs);
  printf("\n\nHow many sentences per paragraph do you want to write? ");
  scanf("%d", &sentences);
  babble(paragraphs, sentences, table);

  /*
   Allows multiple runs
  printf("\n\n\nDo you want to babble more? (yes/no): ");
  scanf("%s", answer);
  while(!strcmp(answer, "yes") || !strcmp(answer, "Yes")){
    printf("\n\nHow many paragraphs do you want to write? ");
    scanf("%d", &paragraphs);
    printf("\n\nHow many sentences per paragraph do you want to write? ");
    scanf("%d", &sentences);
    babble(table, paragraphs, sentences);
    printf("\n\n\nDo you want to babble more? (yes/no): ");
    scanf("%s", answer);
    } */

  // Exit procedure
  printf("\nBye!\n");
  return 0;
}

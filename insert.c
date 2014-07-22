// Andoni Garcia's Markov Babbler. 2014.

#include "markov.h"

// Cleans up non-alpha-numeric characters
char *str_cleanup(char *s)
{
  int len = strlen(s);
  char newstr[++len];

  // Initializing the new string
  int i, j;
  for(i = 0; i < len; i++)
    newstr[i] = '\0';

  // Parsing the input string and only copying alphanumeric or - characters
  int ct = 0;
  for(j = 0; j < len; j++){
    unsigned char c = s[j];
    if(isalpha(c) || isdigit(c) || c == '-'){
      newstr[ct++] = c;
    }
  }
  // Ending the new string and returning the appropriate answer.
  newstr[ct] = '\0';
  if(strlen(newstr) == 0)
    return "ERROR";
  return strdup(newstr);
}

// Inserts words from a file into the hash table
htable *insert_file(FILE *upload, htable *table)
{
  printf("\nIt may take a couple of seconds to set-up the markov model.\n");
  // Creates and intiializes my two buffers
  char current_word[MAX_WORD];
  char next_word[MAX_WORD];

  fscanf(upload, "%s", current_word);
  while(fscanf(upload, "%s", next_word) == 1){
    char *tmp1, *tmp2;
    tmp1 = str_cleanup(current_word);
    tmp2 = str_cleanup(next_word);
    table = htable_insert(table, tmp1, tmp2);
    strcpy(current_word, next_word);
  }
  printf("The file was sucessfully uploaded!\n\n");
  
  return table;
}

// Inserts a given string and its next word into a table
htable *htable_insert(htable *t, char *s, char *next)
{
  unsigned long long int hash, a, b;
  a = t->n_buckets;
  b = hashfn(s);
  hash = (b % a);

  bucket *curr =  t->buckets[hash];
  // If the bucket already contains the current word
  if(bucket_mem(s, curr)){
    // Finds the appropriate entry
    while(strcmp(curr->e->word, s) != 0)
      curr = curr->next;
    entry *ent = curr->e;
    // Increments the entry's count
    (ent->count)++;

    //If the entry already contains the next word
    if(list_mem(next, ent->next_word)){
      list *nextw = ent->next_word;
      // Finds the appropriate list
      while(strcmp(nextw->word, next) != 0)
	nextw = nextw->next;
      // Increments the list's count
      (nextw->count)++;
      return t;
    } else {
      // The entry does not contain the next word
      list *newlist = new_list(next);
      newlist->next = ent->next_word;
      ent->next_word = newlist;
      return t;
    }
  
  // The bucket does not contain the current word
  } else {
    list *lnew = new_list(next);
    entry *enew = new_entry(s);
    enew->next_word = lnew;
    bucket *bnew = new_bucket(enew);
    // This next part seems wrong to me.
    // Looks like you will loose the curr->e.
    bnew->next = curr;
    t->buckets[hash] = bnew;
    return t;
  }
}

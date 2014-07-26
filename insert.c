// Andoni Garcia's Markov Babbler. 2014.

#include "markov.h"

// Checks if the word is the end of the sentence.
int end_of_sent(char *s)
{
  int len = strlen(s);
  char lastchar = s[len - 1];
  if(lastchar == '.' || lastchar == '?' || lastchar == '!')
    return 1;
  return 0;
}

// Checks if the word is "printable" (in our sense as in alphanumeric or '-'
// character).
int printable(char *s)
{
  int len = strlen(s);
  int i;
  for(i = 0; i < len; i++){
    unsigned char c = s[i];
    if(isalpha(c) || isdigit(c) || c == '-')
      return 1;
  }
  return 0;
}

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
  return strdup(newstr);
}



// Inserts words from a file into the hash table
htable *insert_file(FILE *upload, htable *table)
{
  printf("\nIt may take a couple of seconds to set-up the markov model.\n");
  // Creates and intiializes my two buffers
  char current_word[MAX_WORD];
  char next_word[MAX_WORD];
  
  // Grabs the first word of the document
  fscanf(upload, "%s", current_word);
  // Keeps grabbing until it gets a "printable" word
  while(!printable(current_word))
    fscanf(upload, "%s", current_word);
  // Now grabs the next word.
  while(fscanf(upload, "%s", next_word) == 1){
    // Keeps grabbing until it gets a "printable" next word.
    while(!printable(next_word))
      fscanf(upload, "%s", next_word);
    // Checks if the current word is an end of the sentence word.
    if(end_of_sent(current_word)){
      // If so, it inserts the next word as EOS and then uses the next
      // word as a first word for the next iteration.
      char *tmp = str_cleanup(current_word);
      table = htable_insert(table, tmp, "EOS");
      free(tmp);
      strcpy(current_word, next_word);
      continue;
    } else {
      // Else inserts normally
      char *tmp1 = str_cleanup(current_word);
      char *tmp2 = str_cleanup(next_word);
      table = htable_insert(table, tmp1, tmp2);
      free(tmp1);
      free(tmp2);
      strcpy(current_word, next_word);
    }
  }
  char *tmp3 = str_cleanup(current_word);
  table = htable_insert(table, tmp3, "EOS");
  free(tmp3);
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

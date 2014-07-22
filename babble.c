// Andoni Garcia's Markov Babbler. 2014.

#include "markov.h"

char *next_word(entry *e)
{
  int randnum = rand() % e->count;
  list *list = e->next_word;
  while(list != NULL){
    randnum -= list->count;
    if(randnum <= 0)
      return list->word;
    list = list->next;
  }
  printf("Error: Discrepency between entry counts and next_word coutns\n");
  exit(1);
}

char *first_word(htable *t)
{
  int checks = rand() % 5;
  int randnum = rand() % t->n_buckets;
  bucket *buckets = t->buckets[randnum];
  char *firstword;
  while(checks != 0){
    char *tmp = buckets->e->word;
    if('A' <= tmp[0] && tmp[0] <= 'Z'){
      checks--;
      firstword = tmp;
      buckets = buckets->next;
      continue;
    }
    if(buckets->next == NULL){
      int randnum = rand() % t->n_buckets;
      buckets = t->buckets[randnum];
      continue;
    } else {
      buckets = buckets->next;
      continue;
    }
  }
  return firstword;
}

entry *htable_search(htable *t, char *s)
{
  unsigned long long int a = t->n_buckets;
  unsigned long long int b = hashfn(s);
  unsigned long long int c = (b % a);
  bucket *buckets = t->buckets[c];
  while(strcmp(buckets->e->word, s) != 0)
    buckets = buckets->next;
  return buckets->e;
} 

void sentence(htable *t)
{
  // Allocates space for a sentence.
  int buff = MAX_BUFF;
  char *sentence = malloc(buff * sizeof(char));
  if(sentence == NULL){
    printf("Error: Allocation failed for sentence\n");
    exit(1);
  }
  int i;
  for(i = 0; i < buff; i++)
    sentence[i] = '\0';

  int words = (rand() % 20);
  // Creates the sentence
  char *first = first_word(t);
  entry *e = htable_search(t, first);
  int j = 0;
  while(words != 0){
    if(j > MAX_BUFF){
      printf("Error: Sentence too long. Terminating loop.\n");
      exit(1);
    }
    strcat(sentence, e->word);
    j += strlen(e->word);
    if(words != 1)
      sentence[j] = ' ';
    j++;
    char *next = next_word(e);
    e = htable_search(t, next);
    words--;
  }
  printf("%s. ", sentence);
  free(sentence);
  printf("\n");
  return;
}
  

void paragraph(htable *t, int len)
{
  printf("\t");
  while(len != 0){
    sentence(t);
    len--;
  }
  printf("\n");
  return;
}

void babble(int paragraphs, int sentences, htable *t)
{
  while(paragraphs != 0){
    --paragraphs;
    paragraph(t, sentences);
  }
  return;
}

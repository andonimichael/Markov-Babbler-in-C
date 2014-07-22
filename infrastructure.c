/* Andoni Garcia's Markov Babbler. 2014. */

#include "markov.h"

/* The hash function for a given string */
unsigned long long int hashfn(char *word)
{
  

  unsigned long long int res = 17;
  long int len = strlen(word);
  long int i;
  for(i = 0; i < len; i++){
    unsigned long long int tmp = 31 * word[i];
    tmp *= 23;
    res += tmp;
  }
  return res;
}

// =====================================================================
// ====================== Allocating Structs  ==========================
// =====================================================================

// Allocates space for a new list
list *new_list(char *word)
{
  list *newlist = malloc(sizeof(list));
  if(newlist == NULL){
    printf("Error: Allocation failed for new list of %s\n", word);
    exit(1);
  }

  newlist->word = strdup(word);
  newlist->count = 1;
  newlist->next = NULL;
  return newlist;
}

// Allocates space for a new entry
entry *new_entry(char *word)
{
  entry *newentry = malloc(sizeof(entry));
  if(newentry == NULL){
    printf("Error: Allocation failed for new entry of %s\n", word);
    exit(1);
  }
  
  newentry->word = strdup(word);
  newentry->count = 1;
  newentry->next_word = NULL;
  return newentry;
}
  
// Allocates space for a new bucket
bucket *new_bucket(entry *e)
{
  bucket *newbucket = malloc(sizeof(bucket));
  if(newbucket == NULL){
    printf("Error: Allocation failed for new bucket\n");
    exit(1);
  }

  newbucket->e = e;
  newbucket->next = NULL;
  return newbucket;
}

// Allocates space for a new hashtable
htable *new_htable(int nbuckets)
{
  htable *newhtable = malloc(sizeof(htable));
  if(newhtable == NULL){
    printf("Error: Allocation failed for new hash table\n");
    exit(1);
  }

  bucket **bucketarr = malloc(nbuckets * sizeof(void *));
  if(bucketarr == NULL){
    printf("Error: Allocation failed making bucket arrays for htable\n");
    exit(1);
  }
  
  int i;
  for(i = 0; i < nbuckets; i++)
    bucketarr[i] = NULL;
  
  newhtable->n_buckets = nbuckets;
  newhtable->buckets = bucketarr;
  return newhtable;
}

// =====================================================================
// ====================== Membership Testing ===========================
// =====================================================================

// Checks a strings membership in a bucket
int bucket_mem(char *s, bucket *b)
{
  bucket *tmp = b;
  while(tmp != NULL){
    if(strcmp(tmp->e->word, s) == 0)
      return 1;
    tmp = tmp->next;
  }
  return 0;
}

// Checks a strings membership in a list
int list_mem(char *s, list *l)
{
  list *tmp = l;
  while(tmp != NULL){
    if(strcmp(tmp->word, s) == 0)
      return 1;
    tmp = tmp->next;
  }
  return 0;
}

// Checks a strings membership in a htable
int htable_mem(char *s, htable *t)
{
  int nbuckets = t->n_buckets;
  unsigned long long int hash = hashfn(s);
  unsigned long long int bucketnum = (hash % nbuckets);
  return bucket_mem(s, t->buckets[bucketnum]);
}

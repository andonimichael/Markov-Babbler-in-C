// Andoni Garcia's Markov Babbler. 2014

#include "markov.h"

void print_list(list *l)
{
  list *lst = l;
  while(lst != NULL){
    printf("\t%s - %d counts\n", lst->word, lst->count);
    lst = lst->next;
  }
  return;
}

void print_entry(entry *e)
{
  entry *etry = e;
  printf("   %s - %d counts\n", etry->word, etry->count);
  print_list(etry->next_word);
  return;
}

void print_bucket(bucket *b)
{
  bucket *bckt = b;
  while(bckt != NULL){
    print_entry(bckt->e);
    bckt = bckt->next;
  }
  return;
}

void print_htable(htable *t)
{
  htable *tbl = t;
  int bckts = tbl->n_buckets;
  printf("%d buckets\n", bckts);
  int ct;
  for(ct = 0; ct < bckts; ct++){
    printf("%d\n", ct);
    print_bucket(tbl->buckets[ct]);
  }
  printf("END\n");
}

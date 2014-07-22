// Andoni Garcia
// Markov Babbler Header File

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <getopt.h>
#include <unistd.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>

#define MAX_WORD 257
#define MAX_BUFF 2500 //25 chars/word * 100 words/sentence

/*############################################################################
##############################################################################
##########################     DATA STRUCTURES     ###########################
##############################################################################
############################################################################*/

/* A list includes:
   - A word (which comes after a given word)
   - A count (used to compute the frequency)
   - A next to point to the next word in this list
   NULL represents the empty list, and
   "EOS" represents the end of a sentece (the last word with a period afterwards)
*/
typedef struct list list;
struct list{
  char *word;
  int count;
  list *next;
};

/* An entry includes:
   - A word (the current word)
   - A count (used to compute the frequency of next words)
   - A list (to determine the word that comes after)
*/
typedef struct{
  char *word;
  int count;
  list *next_word;
} entry;


typedef struct bucket bucket;
struct bucket{
  entry *e;
  bucket *next;
};

typedef struct{
  int n_buckets;
  bucket **buckets;
} htable;


/*############################################################################
##############################################################################
##########################     INFASTRUCTURE.C     ###########################
##############################################################################
############################################################################*/

// The hash function for a given string
unsigned long long int hashfn(char *word);

// Allocates space for a new list
list *new_list(char *word);

// Allocates space for a new entry
entry *new_entry(char *word);

// Allocates space for a new bucket
bucket *new_bucket(entry *e);

// Allocates space for a new hashtable
htable *new_htable(int nbuckets);

// Checks a strings membership in a bucket
int bucket_mem(char *s, bucket *b);

// Checks a strings membership in a list
int list_mem(char *s, list *l);

// Checks a strings membership in a htable
int htable_mem(char *s, htable *t);


/*############################################################################
##############################################################################
##########################         INSERT.C        ###########################
##############################################################################
############################################################################*/

// Cleans up non-alpha-numeric characters
char *str_cleanup(char *s);

// Inserts words from a file into the hash table
htable *insert_file(FILE *upload, htable *table);

// Inserts a given string and its next word into a table
htable *htable_insert(htable *t, char *s, char *next);


/*############################################################################
##############################################################################
##########################         BABBLE.C        ###########################
##############################################################################
############################################################################*/

// Outputs a next word for a given current entry
char *next_word(entry *e);

// Starts at a capital letter
char *first_word(htable *t);

// Returns quasi-bool for end of a sentence
int end_of_sentence(char *s);

// Searches an htable for a given word and outputs it's entry
entry *htable_search(htable *t, char *s);

// Creates a random sentence given a hash table filled with words
void sentence(htable *t);

// Creates a paragraph of given sentence length
void paragraph(htable *t, int len);

// Writes the babble to the stdout
void babble(int paragraphs, int sentences, htable *t);

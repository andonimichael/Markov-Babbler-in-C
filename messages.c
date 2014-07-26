// Andoni Garcia's Markov Babbler. 2014.

#include "markov.h"

void newline()
{
  printf("\n");
}

// =====================================================================
// ======================== Flag Functions  ============================
// =====================================================================

int isbadanswer(char *answer)
{
  if(!(!strcmp(answer, "yes") || !strcmp(answer, "Yes") ||
       !strcmp(answer, "no") || !strcmp(answer, "No")))
    return 1;
  return 0;
}

char *fixbadanswer(char *answer, void (*func)())
{
  while(isbadanswer(answer)){
    msg_badinput();
    newline();
    func();
    scanf("%s", answer);
  }
  return answer;
}
  

void flag_help()
{
  char answer[127];
  msg_welcome();
  msg_help1();
  msg_help2();

  msg_continue();
  scanf("%s", answer);
  if(isbadanswer(answer))
    strcpy(answer, fixbadanswer(answer, msg_continue));
  if(!strcmp(answer, "no") || !strcmp(answer, "No")){
    msg_exit();
    exit(1);
  }
  return;
}

void flag_print(htable *table)
{
  char answer[127];
  msg_welcome();
  msg_print();
  print_htable(table);
  newline(); newline(); newline();
  msg_continue();
  scanf("%s", answer);
  if(isbadanswer(answer))
    strcpy(answer, fixbadanswer(answer, msg_continue));
  if(!strcmp(answer, "no") || !strcmp(answer, "No")){
    msg_exit();
    exit(1);
  }
  return;
}

// =====================================================================
// ===========================  Messages ===============================
// =====================================================================

void msg_welcome()
{
  system("clear");
  printf("                         ~~~ Welcome to Andoni's Markov Babbler ~~~\n");
  return;
}

void msg_intro()
{
    printf("\n\n\tThis program will use Markov Modeling to write sentences and paragraphs using probability analysis of words and their adjacent words from given input files. As such you must input at least one file (preferably a text file of decent size to give the most\naccurate word predictions) for the Markov Babbler to read before it can begin constructing coherent-ish sentences. The babbler uses a pseudo-random process to grab next words, so every time you run the babbler on the same input file(s), it should produce new and unique outputs. Be warned though, there is a high probability that if your text file contains loops between next words (i.e. it says \"then I\" and later says \"I then\") the babbler might get caught in unwanted loops. Have fun!\n");
  printf("============================================================================================\n");
  return;
}

void msg_file1()
{
  printf("\nWhich file do you want to upload? ");
  return;
}

void msg_file2()
{
  printf("Do you want to insert another file? (yes/no): ");
  return;
}

void msg_babble1()
{
  printf("\nHow many paragraphs do you want to write? ");
  return;
}

void msg_babble2()
{
  printf("\nHow many sentences per paragraph do you want to write? ");
  return;
}

void msg_babble3()
{
  printf("\n\nDo you want to babble more? (yes/no): ");
  return;
}

void msg_babble()
{
  system("clear");
  printf("Babble>\n");
  return;
}

void msg_exit()
{
  printf("\nGood-bye!\n");
  return;
}

void msg_help1()
{
  printf("\n\n\tThis program is a Markov Babbler, which uses a pseudo Markov Model in order to predict which word coherently should come after the current word. This then creates sentences that very from gibberish to coherent and logical phrases. To make the model perform more logical sentences, insert more files. The more statistics the model develops, the better its speaking will be.\n");
  return;
}

void msg_help2()
{
  printf("\nThis program has three (3) option flags that you can include when you run the program:\n -h: This calls this exact help message.\n -p: This prints out a copy of the hash table instead of babbling.\n -s [int]: This specifies the size of the hash table. It requires an integer argument to follow after the flag. For hash tables, it is optimal to use a prime number when choosing the size. If no size flag is specified, it will default to 157 buckets. This may be too large or too small for your input files though.\n");
  printf("\nIf you have more questions, feel free to e-mail me at garcia_andoni@yahoo.com\n");
  return;
}

void msg_continue()
{
  printf("\nWould you like to continue with the Babbler? (yes/no): ");
  return;
}

void msg_badinput()
{
  printf("\nSorry, I did not recognize that answer. Please enter either 'yes' or 'no'.");
  return;
}

void msg_print()
{
  printf("\n\tHere is the hash table. The buckets are numbered in order followed by their entries and counts. Beneath each entry is a list of their next-words with their respective counts.\n\n");
  return;
}

// Andoni Garcia's Markov Babbler. 2014.

#include "markov.h"

int main(int argc, char *argv[])
{
  int paragraphs, sentences, tsize = 157, pflag = 0, hflag = 0;
  htable *table;
  FILE *upload;
  char file[127], answer[127];

  // Handles the flag options.
  system("clear");
  int opt;
  while((opt = getopt(argc, argv, "hpds:")) != -1)
    switch(opt){
    case 'h': hflag = 1; break;
    case 'p': pflag = 1; break;
    case 's': tsize = atoi(optarg); break;
    case '?': 
      if(optopt == 'c')
	printf("The flag -%c needs an integer to follow to set the hash table size. Please re-run the program either ommiting -%c or including the argument.\n", optopt, optopt);
      else if(isprint(optopt))
	printf("The flag -%c is not recognized. Please re-run the program with the flag '-h' to call the help menu.\n", optopt);
      else
	printf("The option '0x%x' is not recognizes. Please re-run the program with the flag '-h' to call the help menu.\n", optopt);
      return 1;
    default: exit(0);
    }
  if(hflag == 1)
    flag_help();

  // Initializations
  msg_welcome();
  msg_intro();
  srand(time(NULL));
  table = new_htable(tsize);

  // Inserts files into the table
  newline();
  strcpy(answer, "yes");
  while(!strcmp(answer, "yes") || !strcmp(answer, "Yes")){
    msg_file1();
    scanf("%s", file);
    upload = fopen(file, "r");
    if(upload == NULL){
      printf("Error: Problem uploading file %s", file);
      exit(0);
    }
    table = insert_file(upload, table);
    fclose(upload);
    msg_file2();
    scanf("%s", answer);
    if(isbadanswer(answer))
      strcpy(answer, fixbadanswer(answer, msg_file2));
  }
  if(pflag == 1)
    flag_print(table);

  // Performs the babbling
  newline();
  strcpy(answer, "yes");
  while(!strcmp(answer, "yes") || !strcmp(answer, "Yes")){
    msg_babble1();
    scanf("%d", &paragraphs);
    msg_babble2();
    scanf("%d", &sentences);
    msg_babble();
    babble(paragraphs, sentences, table);
    msg_babble3();
    scanf("%s", answer);
    if(isbadanswer(answer))
      strcpy(answer, fixbadanswer(answer, msg_babble3));
  }

  // Exit procedure
  msg_exit();
  return 0;
}

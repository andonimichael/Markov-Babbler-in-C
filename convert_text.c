#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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

int main(int argc, char *argv[])
{
  char *file = argv[1];
  FILE *pFile;
  pFile = fopen(file, "r");

  char buffer[250];
  while(fscanf(pFile, "%s", buffer) == 1)
    printf("%s ", str_cleanup(buffer));
  
  fclose(pFile);
  return 0;
}

#include "test.h"
#include "op.h"

int statement_selection(char *line)
{
  char *word;
  int i, j, k = -1;

  i = skip_whitespace(line, 0);
  j = i;
  while (line[i] && line[i] != ' ' && line[i] != '	')
    i++;
  i -= j;
  word = (char*)malloc(sizeof(char) * (i + 1));
  printf("line = %s -> ", line);  
  //  printf("i = %d, ", i);
  while (++k < i)
    word[k] = line[j + k];
  word[k] = '\0';
  i = 0;
  //  printf("word = %s -> ", word);
  strcmp(word, "live") == 0 ? i = 1 : 0;
  strcmp(word, "ld") == 0 ? i = 2 : 0;
  strcmp(word, "st") == 0 ? i = 3 : 0;
  strcmp(word, "add") == 0 ? i = 4 : 0;
  strcmp(word, "sub") == 0 ? i = 5 : 0;
  strcmp(word, "and") == 0 ? i = 6 : 0;
  strcmp(word, "or") == 0 ? i = 7 : 0;
  strcmp(word, "xor") == 0 ? i = 8 : 0;
  strcmp(word, "zjmp") == 0 ? i = 9 : 0;
  strcmp(word, "ldi") == 0 ? i = 10 : 0;
  strcmp(word, "sti") == 0 ? i = 11 : 0;
  strcmp(word, "fork") == 0 ? i = 12 : 0;
  strcmp(word, "lld") == 0 ? i = 13 : 0;
  strcmp(word, "lldi") == 0 ? i = 14 : 0;
  strcmp(word, "lfork") == 0 ? i = 15 : 0;
  strcmp(word, "aff") == 0 ? i = 16 : 0;
  free(word);
  return (i);
}

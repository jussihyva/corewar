#include "test.h"
#include "op.h"

char *get_name(FILE *fp)
{
  char *line = NULL, *str;
  int i;
  size_t linecap = 0;

  i = getline(&line, &linecap, fp);
  str = (char*)malloc(sizeof(char) * (i - 8));
  for (int j = 0; j < i - 9; j++)
    str[j] = line[j + 7];
  str[i - 9] = '\0';
  free(line);
  return(str);
}

char *get_comment(FILE *fp)
{
  char *line = NULL, *str;
  int i;
  size_t linecap = 0;

  i = getline(&line, &linecap, fp);
  str = (char*)malloc(sizeof(char) * (i - 11));
  for (int j = 0; j < i - 12; j++)
    str[j] = line[j + 10];
  str[i - 12] = '\0';
  free(line);
  return(str);
}

void rev_lines(t_cmd **lst)
{
  t_cmd *prev;
  t_cmd *cur;
  t_cmd *next;

  prev = NULL;
  cur = *lst;
  while (cur != NULL)
    {
      next = cur->next;
      cur->next = prev;
      prev = cur;
      cur = next;
    }
  *lst = prev;
}

t_cmd *get_lines(t_champ *champ, FILE *fp)
{
  char *line;
  int i;
  size_t linecap = 0;
  t_cmd *cmd = NULL;
  
  while ((i = getline(&line, &linecap, fp)) > 0)
  {
	  if (line[0] != '\n' && line[0] != COMMENT_CHAR)
      {
		  add_cmd(&cmd, new_cmd(champ, line));
      }
  }
  free(line);
  rev_lines(&cmd);
  return (cmd);
}
